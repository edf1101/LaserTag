/*
 * Code from Techcamp (techcamp.org.uk) for LaserTag20
 *
 * This handles the low level IR communication.
 * Don't edit this file unless you know what you're doing,
 * often you'll want to edit Firing.cpp/.h and even then its likely
 * you want to change a gun or gamemode file.
*/

#ifndef LASERTAG_INFRARED_H
#define LASERTAG_INFRARED_H


#include "driver/rmt.h"
#include "driver/periph_ctrl.h"
#include "soc/rmt_reg.h"

struct irPacketStruct { // order of fields gets reversed when sent, so bit sequence will be control,unitnum,weapon,checksum with msb of each sent first
    uint16_t checksum: 4;
    // uint16_t extra:1;
    uint16_t weapon: 4;
    uint16_t unitnum: 7;
    uint16_t control: 1;
} __attribute__ ((packed));

class Infrared {
public:
    Infrared();

    void init(gpio_num_t irPinIn, gpio_num_t irPinOut);

    void sendIR(uint8_t control, uint8_t unitnum, uint8_t weapon);//,uint8_t extra);
    int receiveIR();

    uint8_t infraredReceived = 0;
    uint8_t crcValid = 0;
    struct irPacketStruct irPacketIn;

    void setPower(char power);

private:
    int32_t processIR(rmt_item32_t *item, size_t size);

    rmt_config_t rmtConfigOut, rmtConfigIn;
    rmt_item32_t rmtDataOut[17]; // data to send
    RingbufHandle_t buffer = NULL;
};

#endif //LASERTAG_INFRARED_H
