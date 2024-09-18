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
#define SERIAL_ONSTEP              Serial // Serial, specify serial interface for encoder output.                             Option
#define SERIAL_BAUD                460800 // 460800, Or use 921600,460800,230400,115200,etc.                                  Option
#define SERIAL_SWAP                   OFF //    OFF, ON for swapped port or OFF for default port (ESP32/ESP8266 only.)        Option

// ENCODER SUPPORT -----------------------------------------------------------------------------------------------------------------
#define AXIS1_ENCODER                 OFF //    OFF, AB, CW_CCW, PULSE_DIR, etc.         RA/Azm Axis (A/MA) & (B/SLO.)        Option
#define AXIS1_ENCODER_REVERSE         OFF //    OFF, ON to reverse the count direction.                                       Option
#define AXIS1_ENCODER_ORIGIN            0 //      0, +/- offset so encoder count is 0 at home (for absolute encoders)         Option

#define AXIS2_ENCODER                 OFF //    OFF, AB, CW_CCW, PULSE_DIR, etc.         Dec/Alt Axis (A/MA) & (B/SLO.)       Option
#define AXIS2_ENCODER_REVERSE         OFF //    OFF, ON to reverse the count direction.                                       Option
#define AXIS2_ENCODER_ORIGIN            0 //      0, +/- offset so encoder count is 0 at home (for absolute encoders)         Option

// THAT'S IT FOR USER CONFIGURATION!
// -------------------------------------------------------------------------------

#include "Extended.config.h"
