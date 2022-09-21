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
#define AXIS1_ENCODER                 OFF //    OFF, AB, CW_CCW, PULSE_DIR, AS37_H39B_B. RA/Azm Axis (A/MA) & (B/SLO.)        Option
#define AXIS1_ENCODER_OFFSET            0 //      0, +/- offset in counts (for absolute encoders.)                            Option
#define AXIS1_ENCODER_SCALE             1 //      1, scales up encoder counts to achieve a higher artificial resolution       Option
                                          //         to enable control/correction between the encoder counts.

#define AXIS2_ENCODER                 OFF //    OFF, AB, CW_CCW, PULSE_DIR, AS37_H39B_B. Dec/Alt Axis (A/MA) & (B/SLO.)       Option
#define AXIS2_ENCODER_OFFSET            0 //      0, +/- offset in counts (for absolute encoders.)                            Option
#define AXIS2_ENCODER_SCALE             1 //      1, scales up encoder counts to achieve a higher artificial resolution       Option
                                          //         to enable control/correction between the encoder counts.

// THAT'S IT FOR USER CONFIGURATION!
// -------------------------------------------------------------------------------

#include "Extended.config.h"
