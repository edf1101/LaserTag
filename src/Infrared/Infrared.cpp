/*
 * Code from Techcamp (techcamp.org.uk) for LaserTag20
 *
 * This handles the low level IR communication.
 * Don't edit this file unless you know what you're doing,
 * often you'll want to edit Firing.cpp/.h and even then its likely
 * you want to change a gun or gamemode file.
*/

#include "Infrared.h"

Infrared::Infrared() {
}

void Infrared::setPower(char power) {
  unsigned int freq;
  switch (power) {
    case 0:
      freq = 8800;
      break;
    case 1:
      freq = 10000;
      break;
    case 2:
      freq = 20000;
      break;
    case 3:
      freq = 38000;
      break;
  }
  rmtConfigOut.tx_config.carrier_freq_hz = freq;
  rmt_config(&rmtConfigOut);
}

void Infrared::init(gpio_num_t irPinIn, gpio_num_t irPinOut) {
  rmtConfigOut.rmt_mode = RMT_MODE_TX;  // transmit mode
  rmtConfigOut.channel = RMT_CHANNEL_0;  // channel to use 0 - 7
  rmtConfigOut.clk_div = 80;  // clock divider 1 - 255. source clock is 80MHz -> 80MHz/80 = 1MHz -> 1 tick = 1 us
  rmtConfigOut.gpio_num = irPinOut; // pin to use
  rmtConfigOut.mem_block_num = 1; // memory block size
  rmtConfigOut.tx_config.loop_en = 0; // no loop
  rmtConfigOut.tx_config.carrier_freq_hz = 38000;  // IR remote controller uses 38kHz carrier frequency
  rmtConfigOut.tx_config.carrier_duty_percent = 33; // duty
  rmtConfigOut.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH; // carrier level
  rmtConfigOut.tx_config.carrier_en = 1;  // carrier enable
  rmtConfigOut.tx_config.idle_level = RMT_IDLE_LEVEL_LOW; // signal level at idle
  rmtConfigOut.tx_config.idle_output_en = 1;  // output if idle
  rmt_config(&rmtConfigOut);
  rmt_driver_install(rmtConfigOut.channel, 0, 0);

  rmtConfigIn.rmt_mode = RMT_MODE_RX;
  rmtConfigIn.channel = RMT_CHANNEL_1;
  rmtConfigIn.clk_div = 80;
  rmtConfigIn.gpio_num = irPinIn;
  rmtConfigIn.mem_block_num = 1;
  rmtConfigIn.rx_config.filter_en = 1;
  rmtConfigIn.rx_config.filter_ticks_thresh = 150; // Less than this number of uS, the pulse will be ignored
  rmtConfigIn.rx_config.idle_threshold = 1500; // More than this number of uS, will assume reception is over
  rmt_config(&rmtConfigIn);
  rmt_driver_install(rmtConfigIn.channel, 2048, 0);
  rmt_get_ringbuf_handle(rmtConfigIn.channel, &buffer);
  rmt_rx_start(rmtConfigIn.channel, 1);
}

void Infrared::sendIR(uint8_t control, uint8_t unitnum, uint8_t weapon) {
  struct irPacketStruct irPacketOut;
  uint16_t Data, i;

  irPacketOut.control = control;
  irPacketOut.unitnum = unitnum;
  irPacketOut.weapon = weapon;
  // irPacketOut.extra=extra;
  i = *(uint16_t * ) & irPacketOut;
  i = i >> 4; // This is the packet without the checksum ...
  while (i > 15) i = (i >> 4) + (i & 15); // ... now make a simple checksum out of this ...
  irPacketOut.checksum = i;
  Data = *(uint16_t * ) & irPacketOut;

  /* leader code 800us on, 800us off ... */
  rmtDataOut[0].duration0 = 800;
  rmtDataOut[0].level0 = 1;
  rmtDataOut[0].duration1 = 800;
  rmtDataOut[0].level1 = 0;

  for (int i = 1; i <= 16; i++) {
    if (Data & (1 << (16 - i))) // high bit - 800us on, 400us off ...
      rmtDataOut[i].duration0 = 800;
    else
      rmtDataOut[i].duration0 = 400;
    rmtDataOut[i].level0 = 1;
    if (Data & (1 << (16 - i))) // low bit - 400us on, 800us off ...
      rmtDataOut[i].duration1 = 400;
    else
      rmtDataOut[i].duration1 = 800;
    rmtDataOut[i].level1 = 0;
  }
  rmt_write_items(RMT_CHANNEL_0, rmtDataOut, 17, true);
}

int32_t Infrared::processIR(rmt_item32_t *item, size_t size) {
  int n;
  char error = 0;
  uint16_t data = 0;

  // Check for 17 bits (size=68), pulse of 800us, break of 800us ...
  if ((size == 68) && (item[0].duration0 >= 600) && (item[0].duration0 <= 1000) && (item[0].duration1 >= 600) &&
      (item[0].duration1 <= 1000)) {
    for (n = 1; n <= 16; n++) {
      // If pulse of 800us and break of 400us (or last bit which will have no break), then is a high bit ...
      // N.B. Nominally when looking for 800us pulse, the window should be 600-100us but we go for 30us more for pulse (and 30us less for break) because this seems more accurate from experiments
      if ((item[n].duration0 >= 630) && (item[n].duration0 <= 1030) &&
          (((item[n].duration1 >= 170) && (item[n].duration1 <= 570)) || (n == 16)))
        data |= (1 << (16 - n));
        // If pulse of 400us and break of 800us (or last bit which will have no break), then is a low bit ...
      else if ((item[n].duration0 >= 230) && (item[n].duration0 <= 630) &&
               (((item[n].duration1 >= 570) && (item[n].duration1 <= 970)) || (n == 16)));
        // .. otherwise data reception error:
      else
        error = 1;
    }
  } else
    error = 1;

  n = -1;
  do {
    n++;

  } while (item[n].duration1);


  if (!error)
    return data;
  else
    return -1;
}

int Infrared::receiveIR() {
  int32_t receivedIR;
  uint16_t i;
  size_t rxSize = 0;
  int retval = 0;

  rmt_item32_t *item = (rmt_item32_t *) xRingbufferReceive(buffer, &rxSize, 0);
  if (item) {
    retval = 1;
    crcValid = 0;
    receivedIR = processIR(item, rxSize);
    if (!infraredReceived && (receivedIR == -1)) {
      crcValid = 0;
      infraredReceived = 1; // Something received via infrared, but not a correctly formatted packet
    } else if (!infraredReceived && (receivedIR >=
                                     0)) // Correctly formatted packet received - whether crc is valid is yet to be determined ...
    {
      i = receivedIR;
      irPacketIn = *(irPacketStruct *) &i;
      i = i >> 4; // This is the packet without the checksum ...
      while (i > 15) i = (i >> 4) + (i & 15); // ... now make a simple checksum out of this ...

      if (i == irPacketIn.checksum) // ... and compare it with the received checksum
      {
        crcValid = 1;
      }

      infraredReceived = 1;
    }
    vRingbufferReturnItem(buffer, (void *) item);
  }
  return (retval);
}