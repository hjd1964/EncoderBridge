// ---------------------------------------------------------------------------------------------------------------------------------
// Configuration for Encoder Serial Bridge

/*
 *               For more information on setting this addon up see https://onstep.groups.io/g/main/wiki/7119 
 *                           and join the OnStep Groups.io at https://groups.io/g/onstep
 * 
 *           *** Read the compiler warnings and errors, they are there to help guard against invalid configurations ***
*/

// ---------------------------------------------------------------------------------------------------------------------------------
// ADJUST THE FOLLOWING TO CONFIGURE YOUR ADD-ON'S FEATURES ------------------------------------------------------------------------
// <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed

// SERIAL PORTS --------------------------------------------------------------------------------------------------------------------
#define SERIAL                     Serial // Serial, specify serial interface for encoder output.                             Option
#define SERIAL_BAUD                460800 // 460800, Or use 460800,230400,115200,etc.                                         Option
#define SERIAL_SWAP                   OFF //    OFF, ON for swapped port or OFF for default port (ESP32/ESP8266 only.)        Infreq

// ENCODER SUPPORT -----------------------------------------------------------------------------------------------------------------
#define AXIS1_ENCODER                BISS //    OFF, AB, CW_CCW, PULSE_DIR, BISS. RA/Azm Axis (A/MA) & (B/SLO.)               Option
#define AXIS1_BISS_ENCODER_VARIANT  AS37_H39B_B //    AS37_H39B_B or TRI24 for trident 24 bit custom encoder                  Option
#define AXIS1_ENCODER_TICKS_DEG 23301.689 // 22.222, n, (ticks/degree.) Encoder ticks per degree.                             Adjust
#define AXIS1_ENCODER_REVERSE          ON //    OFF, ON to reverse the count direction.                                       Option
#define AXIS1_ENCODER_ORIGIN            0 //      0, +/- offset so encoder count is 0 at home (for absolute encoders)         Option

#define AXIS2_ENCODER                BISS //    OFF, AB, CW_CCW, PULSE_DIR, BISS. Dec/Alt Axis (A/MA) & (B/SLO.)              Option
#define AXIS2_BISS_ENCODER_VARIANT  AS37_H39B_B //    AS37_H39B_B or TRI24 for trident 24 bit custom encoder                  Option
#define AXIS2_ENCODER_TICKS_DEG 23301.689 // 22.222, n, (ticks/degree.) Encoder ticks per degree.                             Adjust
#define AXIS2_ENCODER_REVERSE          ON //    OFF, ON to reverse the count direction.                                       Option
#define AXIS2_ENCODER_ORIGIN            0 //      0, +/- offset so encoder count is 0 at home (for absolute encoders)         Option

#define AS37_SINGLE_TURN
#define AS37_CLOCK_RATE_KHZ          4000 // error rate is: ~2.0% at 500 KHz, ~0.5% @ 2000 KHz, ~0.01% at 4000KHz
// THAT'S IT FOR USER CONFIGURATION!
// -------------------------------------------------------------------------------

#include "Extended.config.h"
