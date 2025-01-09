// -----------------------------------------------------------------------------------
// Configuration defaults
#pragma once

// host name for this microcontroller
#ifndef HOST_NAME
#define HOST_NAME                      "OnStep-EB"
#endif

// settings identification
#ifndef CONFIG_NAME
#define CONFIG_NAME                    HOST_NAME
#endif

// use the HAL specified default NV driver
#ifndef NV_DRIVER
#define NV_DRIVER                      NV_DEFAULT
#endif
