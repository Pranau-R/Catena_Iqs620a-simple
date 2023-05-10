/*

Module:  Catena_Iqs620a_simple.ino

Function:
        IQS620A Sensor program for Catena 4610.

Copyright notice:
        This file copyright (C) 2023 by

                MCCI Corporation
                3520 Krums Corners Road
                Ithaca, NY  14850

        See project LICENSE file for license information.

Author:
        Pranau R, MCCI Corporation	April 2023

*/

#include <Catena.h>

#include <Catena_Led.h>
#include <Catena_TxBuffer.h>
#include <Catena_CommandStream.h>
#include <Catena_Mx25v8035f.h>

#include <Wire.h>
#include <hal/hal.h>
#include <mcciadk_baselib.h>

#include <cmath>
#include <type_traits>
#include <MCCI_Catena_Iqs620a.h>
#include <stm32_eeprom.h>

using namespace McciCatena;
using namespace McciCatenaIqs620a;

/****************************************************************************\
|
|   Manifest Constants & Typedefs
|
\****************************************************************************/

/* adjustable timing parameters */
enum    {
        // set this to interval between transmissions, in seconds
        // Actual time will be a little longer because have to
        // add measurement and broadcast time, but we attempt
        // to compensate for the gross effects below.
        CATCFG_T_CYCLE = 6 * 60,        // every 6 minutes
        CATCFG_T_CYCLE_TEST = 30,       // every 30 seconds
        CATCFG_T_CYCLE_INITIAL = 30,    // every 30 seconds initially
        CATCFG_INTERVAL_COUNT_INITIAL = 10,     // repeat for 5 minutes
        CATCFG_T_REBOOT = 30 * 24 * 60 * 60,    // reboot every 30 days
        };

/* additional timing parameters; ususually you don't change these. */
enum    {
        CATCFG_T_WARMUP = 1,
        CATCFG_T_SETTLE = 5,
        CATCFG_T_OVERHEAD = (CATCFG_T_WARMUP + CATCFG_T_SETTLE + 4),
        CATCFG_T_MIN = CATCFG_T_OVERHEAD,
        CATCFG_T_MAX = CATCFG_T_CYCLE < 60 * 60 ? 60 * 60 : CATCFG_T_CYCLE,     // normally one hour max.
        CATCFG_INTERVAL_COUNT = 30,
        };

constexpr uint32_t CATCFG_GetInterval(uint32_t tCycle)
        {
        return (tCycle < CATCFG_T_OVERHEAD + 1)
                ? 1
                : tCycle - CATCFG_T_OVERHEAD
                ;
        }

enum    {
        CATCFG_T_INTERVAL = CATCFG_GetInterval(CATCFG_T_CYCLE),
        };

/****************************************************************************\
|
|   handy constexpr to extract the base name of a file
|
\****************************************************************************/

// two-argument version: first arg is what to return if we don't find
// a directory separator in the second part.
static constexpr const char *filebasename(const char *s, const char *p)
    {
    return p[0] == '\0'                     ? s                            :
           (p[0] == '/' || p[0] == '\\')    ? filebasename(p + 1, p + 1)   :
                                              filebasename(s, p + 1)       ;
    }

static constexpr const char *filebasename(const char *s)
    {
    return filebasename(s, s);
    }

/****************************************************************************\
|
|   Read-only data
|
\****************************************************************************/

static const char sVersion[] = "1.0.0";

/****************************************************************************\
|
|   VARIABLES
|
\****************************************************************************/

// the primary object
Catena gCatena;

cIQS620A gIQS620A;
bool fProximity;

//
// the LED
//
StatusLed gLed (Catena::PIN_STATUS_LED);

SPIClass gSPI2(
        Catena::PIN_SPI2_MOSI,
        Catena::PIN_SPI2_MISO,
        Catena::PIN_SPI2_SCK
        );

//  The flash
Catena_Mx25v8035f gFlash;
bool fFlash;

/*

Name:   setup()

Function:
        Arduino setup function.

Definition:
        void setup(
            void
            );

Description:
        This function is called by the Arduino framework after
        basic framework has been initialized. We initialize the sensors
        that are present on the platform, set up the LoRaWAN connection,
        and (ultimately) return to the framework, which then calls loop()
        forever.

Returns:
        No explicit result.

*/

void setup(void)
    {
    gCatena.begin();

    setup_platform();
    setup_flash();

    setup_iqs();
    }

void setup_platform(void)
    {
#ifdef USBCON
    // if running unattended, don't wait for USB connect.
    if (! (gCatena.GetOperatingFlags() &
        static_cast<uint32_t>(gCatena.OPERATING_FLAGS::fUnattended)))
        {
        while (!Serial)
            /* wait for USB attach */
            yield();
        }
#endif

    gCatena.SafePrintf("\n");
    gCatena.SafePrintf("-------------------------------------------------------------------------------\n");
    gCatena.SafePrintf("This is %s V%s.\n", filebasename(__FILE__), sVersion);
            {
            }
    gCatena.SafePrintf("Enter 'help' for a list of commands.\n");
    gCatena.SafePrintf("(remember to select 'Line Ending: Newline' at the bottom of the monitor window.)\n");

    gCatena.SafePrintf("SYSCLK: %u MHz\n", unsigned(gCatena.GetSystemClockRate() / (1000 * 1000)));

#ifdef USBCON
    gCatena.SafePrintf("USB enabled\n");
#else
    gCatena.SafePrintf("USB disabled\n");
#endif

    Catena::UniqueID_string_t CpuIDstring;

    gCatena.SafePrintf(
        "CPU Unique ID: %s\n",
        gCatena.GetUniqueIDstring(&CpuIDstring)
        );

    gCatena.SafePrintf("--------------------------------------------------------------------------------\n");
    gCatena.SafePrintf("\n");

    // set up the LED
    gLed.begin();
    gCatena.registerObject(&gLed);
    gLed.Set(LedPattern::FastFlash);

    /* find the platform */
    const Catena::EUI64_buffer_t *pSysEUI = gCatena.GetSysEUI();

    uint32_t flags;
    const CATENA_PLATFORM * const pPlatform = gCatena.GetPlatform();

    if (pPlatform)
        {
        gCatena.SafePrintf("EUI64: ");
        for (unsigned i = 0; i < sizeof(pSysEUI->b); ++i)
            {
            gCatena.SafePrintf("%s%02x", i == 0 ? "" : "-", pSysEUI->b[i]);
            }
        gCatena.SafePrintf("\n");
        flags = gCatena.GetPlatformFlags();
        gCatena.SafePrintf(
            "Platform Flags:  %#010x\n",
            flags
            );
        gCatena.SafePrintf(
            "Operating Flags:  %#010x\n",
            gCatena.GetOperatingFlags()
            );
        }
    else
        {
        gCatena.SafePrintf("**** no platform, check provisioning ****\n");
        flags = 0;
        }
    }

void setup_flash(void)
    {
    if (gFlash.begin(&gSPI2, Catena::PIN_SPI2_FLASH_SS))
        {
        fFlash = true;
        gFlash.powerDown();
        gCatena.SafePrintf("FLASH found, put power down\n");
        }
    else
        {
        fFlash = false;
        gFlash.end();
        gSPI2.end();
        gCatena.SafePrintf("No FLASH found: check hardware\n");
        }
    }

void setup_iqs()
    {
    Wire.begin();
    delay(100);

    if(!gIQS620A.begin())
        {
        gCatena.SafePrintf("No IQS620A Sensor found: check wiring\n");
        fProximity = false;
        }
    else
        {
        gCatena.SafePrintf("IQS620A Sensor found!\n");
        fProximity = true;
        }

    // gIQS620A.begin();
    }

uint32_t gRebootMs;

void loop()
    {
    gCatena.poll();

    if (fProximity)
        {
        // IQS620A data
        gIQS620A.iqsRead();

        // SAR Count
        int16_t Ch0Data = gIQS620A.getCh0Data();  // Display Channel Data
        gCatena.SafePrintf("Channel 0 data: %d", Ch0Data);
        int16_t Ch1Data = gIQS620A.getCh1Data();  // Display Channel Data
        gCatena.SafePrintf("\t\tChannel 1 data: %d", Ch1Data);
        int16_t Ch2Data = gIQS620A.getCh2Data();  // Display Channel Data
        gCatena.SafePrintf("\t\tChannel 2 data: %d", Ch2Data);

        // Hall Effect Amplitude
        int16_t Amplitude = gIQS620A.getAmplitude();
        gCatena.SafePrintf("\t\tHall Effect Amplitude: %d", Amplitude);

        gCatena.SafePrintf("\n");
        }
    delay(5000);
    }
