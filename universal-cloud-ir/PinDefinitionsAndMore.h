/*
 *  PinDefinitionsAndMore.h
 *
 *  Contains pin definitions for IRremote examples for various platforms
 *  as well as definitions for feedback LED and tone() and includes
 *
 *  Copyright (C) 2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 *  Arduino-IRremote is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

/*
 * Pin mapping table for different platforms
 *
 * Platform     IR input    IR output   Tone
 * -----------------------------------------
 * DEFAULT/AVR  2           3           4
 * ATtinyX5     0           4           3
 * ATtiny167    9           8           5 // Digispark pro number schema
 * ATtiny167    3           2           7
 * ATtiny3217   10          11          3 // TinyCore schema
 * ATtiny1604   2           PA5/3       %
 * SAMD21       3           4           5
 * ESP8266      14 // D5    12 // D6    %
 * ESP32        15          4           27
 * BluePill     PA6         PA7         PA3
 * APOLLO3      11          12          5
 */

#if defined(ESP8266)
#define FEEDBACK_LED_IS_ACTIVE_LOW // The LED on my board (D4) is active LOW
#define IR_RECEIVE_PIN          14 // D5
#define IR_RECEIVE_PIN_STRING   "D5"
#define IR_SEND_PIN             12 // D6 - D4/pin 2 is internal LED
#define IR_SEND_PIN_STRING      "D6"
#define TONE_PIN                42 // Dummy for examples using it
#define _IR_TIMING_TEST_PIN     13 // D7
#define APPLICATION_PIN          0 // D3
#endif

#if !defined (FLASHEND)
#define FLASHEND 0xFFFF // Dummy value for platforms where FLASHEND is not defined
#endif
/*
 * Helper macro for getting a macro definition as string
 */
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
