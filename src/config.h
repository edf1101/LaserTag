/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This file contains definitions for various configuration variables
 * along with pins on the ESP32 board and where they are used.
*/

#ifndef LASERTAG_CONFIG_H
#define LASERTAG_CONFIG_H

// General config settings
#define DEBUG_SERIAL 1  // Whether we print to the serial monitor or not
#define SOUND_ON 1 // Whether we play sounds or not
#define ADMIN_PASS "0000" // Must be number between 1-8 chars written as a string
#define MINS_TO_SLEEP 20 // Time in seconds before the gun goes to sleep (atm 240s is 4 minutes)

// Mesh network settings (To make sure other guns don't connect to you change the SSID and PASSWORD)
#define MESH_SSID "LaserTag"
#define MESH_PASSWORD "LaserTag"
#define MESH_PORT 5555

// Pin definition for the Latch mechanism
#define POWER_HOLD_PIN 17

// Pin definitions for the side display
#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 32

// Colour definitions for the side display. These are RGB565 colours.
#define TFT_PRIMARY_COLOUR 0xFFFF // Primary is for highlighted text, icons etc.
#define TFT_SECONDARY_COLOUR 0x07E0 // Secondary is for non-highlighted text, borders etc.

// Pin definitions for the rotary encoder
#define ROT_OUT_A 33
#define ROT_OUT_B 34
#define ROT_SWITCH 2

// Pin definitions for IR Transmitter & Receiver
#define IR_RECEIVER GPIO_NUM_35
#define IR_TRANSMITTER GPIO_NUM_26
#define MUZZLE_LED 14
#define VIBRATE_PIN 16

// Config & Pin definitions for the buttons
#define TRIGGER_BUTTON 2
#define MAGAZINE_BUTTON 2

// Amplifier pins
#define AMP_LRCLK 25
#define AMP_BCLK 0
#define AMP_DATA 19

// Cosmetic LED Pins
#define NEOPIXEL_ON 0 // 1 for true 0 for false
#define NEOPIXEL_LEDS_PIN 27
#define NEOPIXEL_LEDS_COUNT 5 // If there are more than 5 LEDs put here and will scale

#endif //LASERTAG_CONFIG_H
