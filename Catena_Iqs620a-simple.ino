/*

Module:  Catena_Iqs620a-simple.ino

Function:
        IQS620A Sensor program for Catena 4610.

Copyright notice:
        This file copyright (C) 2019 by

                MCCI Corporation
                3520 Krums Corners Road
                Ithaca, NY  14850

        See project LICENSE file for license information.

Author:
        Pranau R, MCCI Corporation	March 2023

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
#include "Arduino.h"
#include "IQS62x.h"
#include "Types.h"
#include "limits.h"
#include "MCCI_I2C.h"
#include <stm32_eeprom.h>

/*  Global defines      ----------------------------------------------------------*/

#define MS_500      500
#define ONE_SEC     1000
#define TWO_SEC     2000
#define THREE_SEC   3000
#define TWELVE_SEC  12000
#define MS_5        5

using namespace McciCatena;

/****************************************************************************\
|
|	Manifest Constants & Typedefs
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

/*  Typedefs        --------------------------------------------------------------*/

// Enum to determine what to show on screen
typedef enum IC_Type
    {
    IQS620n = 1
    } IC_Type_e;

/** Enum for RDY active low and active high or Polling */
typedef enum RDY_Type
    {
    Active_Low = 0,
    Active_High = 1,
    Polling = 2
    }RDY_Type_e;

/*  Global Variables    ----------------------------------------------------------*/

// What type of IC is this?
IC_Type_e ICType;

cI2C gI2C;

// Timer 1
Timer_t Mode_Switch_Timer   = {0};          // Mode switch timer
Timer_t ErrorTimer          = {0};          // Error Timer
Timer_t MainTimer           = {0};          // Error Timer
Timer_t ButtonTimer         = {0};          // Button double tap Timer

RDY_Type_e _RDY_Type;
volatile bool _RDY_Window;

//ProxFusion IC's
IQS620n_t iqs620n;              // Create variable for iqs620A

// Indicate chip is ready for polling
bool chipReady = false;

// Buffer to read data into
uint8_t buffer[20];

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
|	Read-only data
|
\****************************************************************************/

static const char sVersion[] = "1.1.0";

/****************************************************************************\
|
|	VARIABLES
|
\****************************************************************************/

// the primary object
Catena gCatena;

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

Name:	setup()

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

    _RDY_Type = Polling;
    _RDY_Window = false;

    // Get the Version info
    uint8_t res = 0;
    res = configure_iqs620n();
    gI2C.readRegisters(VERSION_INFO, buffer, sizeof(buffer));

    // Set the appropriate IC
    if(buffer[0] == IQS620_PRODUCT_NR && buffer[1] == IQS620N_SOFTWARE_NR && buffer[2] == IQS620N_HARDWARE_NR)
        {
        ICType = IQS620n;
        }
    // No valid IC type found
    else
        {
        Serial.println("Err invalid IC! Check wiring...");
        while(1);
        }

    setTimer(&MainTimer);

    if (ICType == IQS620n)
        {
        Serial.println ("620n Found!");
        delay(1000); //Wait here for device splash on serial
        // setup device
        res = configure_iqs620n();
        }

    // An error occured
    if(res)
        {
        // Serial.print("res: ");
        // Serial.println(res);
        }

    delay(1000);

    // Initialise Mode timer
    Mode_Switch_Timer.Timer_counter = ONE_SEC;  // 1s timer

    ErrorTimer.Timer_counter = THREE_SEC;       // 3s timer

    MainTimer.Timer_counter = ONE_SEC;          // 1s timer

    ButtonTimer.Timer_counter = 300;            // 300ms timer
    }

uint32_t gRebootMs;

uint8_t configure_iqs620n()
    {
    uint8_t res = 0;

    res |= gI2C.writeRegister(DEV_SETTINGS, (uint8_t *)nDevSetup);

    res |= gI2C.writeRegister(PXS_SETTINGS_0, (uint8_t *)nPXS_Setup_0);

    res |= gI2C.writeRegister(PXS_SETTINGS_1, (uint8_t *)nPXS);

    res |= gI2C.writeRegister(PXS_UI_SETTINGS, (uint8_t *)nPXSUi);

    res |= gI2C.writeRegister(SAR_UI_SETTINGS, (uint8_t *)nSARUi);

    res |= gI2C.writeRegister(METAL_UI_SETTINGS, (uint8_t *)nMetalDetect);

    res |= gI2C.writeRegister(HALL_SENS_SETTINGS, (uint8_t *)nHall_Sens);

    res |= gI2C.writeRegister(HALL_UI_SETTINGS, (uint8_t *)nHall_UI);

    res |= gI2C.writeRegister(TEMP_UI_SETTINGS, (uint8_t *)nTemp_UI);

    // Wait for Redo Ati to complete
    do
        {
        res |= gI2C.readRegisters(SYSTEM_FLAGS, &iqs620n.SystemFlags.SystemFlags, sizeof(&iqs620n.SystemFlags.SystemFlags));
        }
    while (!res && iqs620n.SystemFlags.InAti);

    return res;
    }

void iqsRead()
    {
    uint8_t res = 0;

    if(ICType == IQS620n)
        {
        // Read version number to insure we still have the correct device attached - otherwise, do setup
        res = gI2C.readRegisters(VERSION_INFO, buffer, sizeof(buffer));

        // System flags, Global Events and PXS UI Flags - 9 bytes
        res |= gI2C.readRegisters(SYSTEM_FLAGS, &iqs620n.SystemFlags.SystemFlags, sizeof(&iqs620n.SystemFlags.SystemFlags));

        // Read PXS Channel 0 Data - 12 bytes
        res |= gI2C.readRegisters(CHANNEL0_DATA, &iqs620n.Ch[0].Ch_Low, sizeof(&iqs620n.Ch[0].Ch_Low));

        // Read channel 1 for SAR
        res |= gI2C.readRegisters(CHANNEL1_DATA, &iqs620n.Ch[1].Ch_Low, sizeof(&iqs620n.Ch[1].Ch_Low));

        // Read channel 2 for SAR
        res |= gI2C.readRegisters(CHANNEL2_DATA, &iqs620n.Ch[2].Ch_Low, sizeof(&iqs620n.Ch[2].Ch_Low));

        // Read channel 4 for SAR
        res |= gI2C.readRegisters(CHANNEL4_DATA, &iqs620n.Ch[4].Ch_Low, sizeof(&iqs620n.Ch[4].Ch_Low));

        // Read channel 5 for SAR
        res |= gI2C.readRegisters(CHANNEL5_DATA, &iqs620n.Ch[5].Ch_Low, sizeof(&iqs620n.Ch[5].Ch_Low));
        }

    // A read error occurred
    if(res)
        {
        // Serial.print("res : ");
        // Serial.println(res);
        }

    // reset timer
    setTimer(&ErrorTimer);

    chipReady = true;

    if(timerExpired(&ErrorTimer))
        {
        //Serial.print("Timer Expired : ");
        //Serial.println(ERR_TIMEOUT);
        }
    }

uint32_t getDecimal(float data)
        {
        uint32_t dataInt = data;
        float dataDecimal = data - dataInt;
        uint32_t dataFrac = dataDecimal * 100 + 0.5;

        return dataFrac;
        }

void loop()
        {
        gCatena.poll();

        // IQS620A data
        iqsRead();

        // SAR Count
        int16_t sarCountCh0 = iqs620n.Ch[0].Ch;  // Display Channel Data
        gCatena.SafePrintf("SAR counts ch0: %d", sarCountCh0);
        int16_t sarCountCh1 = iqs620n.Ch[1].Ch;  // Display Channel Data
        gCatena.SafePrintf("\t\tSAR counts ch1: %d", sarCountCh1);
        int16_t sarCountCh2 = iqs620n.Ch[2].Ch;  // Display Channel Data
        gCatena.SafePrintf("\t\tSAR counts ch2: %d", sarCountCh2);

        // Hall Effect Amplitude
        int16_t hallEffectch4 = iqs620n.Ch[4].Ch;  // get Channel Data
        int16_t hallEffectch5 = iqs620n.Ch[5].Ch;  // get Channel Data

        int16_t Amplitude = hallEffectch4 - hallEffectch5;
        gCatena.SafePrintf("\t\tHall Effect Amplitude: %d", Amplitude);

        gCatena.SafePrintf("\n");
        delay(5000);
        }

/**************************************************************************************************/
/*                                                                                                */
/*                                     Timer Functions                                            */
/*                                                                                                */
/**************************************************************************************************/

/**
 * @brief
 */
void setTimer(Timer_t* timer)
    {
    timer->TimerExpired = false;
    timer->Timer_start = millis();  // get this instant millis
    }

/**
 * @brief
 */
void setTimer(Timer_t* timer, uint32_t time)
    {
    timer->TimerExpired = false;
    timer->Timer_start = millis();  // get this instant millis
    timer->Timer_counter = time;  // the timeout time for the timer
    }

bool timerExpired(Timer_t* timer)
    {
    // This is a timeout
    if(((millis() - timer->Timer_start) >= timer->Timer_counter))
        timer->TimerExpired = true;
    // We haven't timed out yet
    else
        timer->TimerExpired  = false;

    // Return the state of this timer
    return timer->TimerExpired;
    }
