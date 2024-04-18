/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This file contains definitions for various configuration variables
 * along with pins on the ESP32 board and where they are used.
*/

#ifndef LASERTAG_CONFIG_H
#define LASERTAG_CONFIG_H

// General config settings
#define DEBUG 1  // Whether we print to the serial monitor or not
#define SOUND_ON 1 // Whether we play sounds or not
#define ADMIN_PASS 0000 // Must be 4 digit num

// Config settings for the OLED display
#define SCREEN_ADDRESS 0x3C // 0x3D or 0x3C

// Pin definitions for the side display
#define TFT_CS 14
#define TFT_RST 15
#define TFT_DC 32

// Pin definitions for the rotary encoder
#define ROT_OUT_A 17
#define ROT_OUT_B 5
#define ROT_SWITCH 19

// Pin definitions for IR Transmitter & Receiver
#define IR_RECEIVER GPIO_NUM_35
#define IR_TRANSMITTER GPIO_NUM_26
#define MUZZLE_LED 13
#define VIBRATE_PIN 33

// Config & Pin definitions for the buttons
#define TRIGGER_BUTTON 12
#define MAGAZINE_BUTTON 16

// Speaker pins
#define DAC_PIN 25

// Cosmetic LED Pins
#define NEOPIXEL_ON 1 // 1 for true 0 for false
#define NEOPIXEL_LEDS_PIN 4
#define NEOPIXEL_LEDS_COUNT 5 // If there are more than 5 LEDs put here and will scale

#endif //LASERTAG_CONFIG_H
