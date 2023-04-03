/*

Module: Catena_Iqs620a.cpp

Function:
    Implementation code for MCCI Catena IQS620A sensor library (simple).

Copyright and License:
    See accompanying LICENSE file for copyright and license information.

Author:
    Pranau R, MCCI Corporation   March 2023

*/

#include "Catena_Iqs620a.h"
#include <Wire.h>

cIQS620A::cIQS620A()
    {
    //default constructor
    }

cIQS620A::~cIQS620A()
    {
    }

bool cIQS620A::begin()
    {
    // Get the Version info
    uint8_t res = 0;
    res = configureIqs620n();
    readRegisters(VERSION_INFO, m_buffer, sizeof(m_buffer));

    // Set the appropriate IC
    if(m_buffer[0] == IQS620_PRODUCT_NR && m_buffer[1] == IQS620N_SOFTWARE_NR && m_buffer[2] == IQS620N_HARDWARE_NR)
        {
        m_icType = IQS620n;
        }
    // No valid IC type found
    else
        {
        Serial.println("Err invalid IC! Check wiring...");
        while(1);
        }

    setTimer(&m_mainTimer);

    if (m_icType == IQS620n)
        {
        Serial.println ("620n Found!");
        delay(1000); //Wait here for device splash on serial
        // setup device
        res = configureIqs620n();
        }

    // An error occured
    if(res)
        {
        // Serial.print("res: ");
        // Serial.println(res);
        }

    delay(1000);

    // Initialise Mode timer
    m_errorTimer.Timer_counter = THREE_SEC;       // 3s timer
    m_mainTimer.Timer_counter = ONE_SEC;          // 1s timer
    }

uint8_t cIQS620A::configureIqs620n()
    {
    uint8_t res = 0;

    res |= writeRegister(DEV_SETTINGS, (uint8_t *)nDevSetup);

    res |= writeRegister(PXS_SETTINGS_0, (uint8_t *)nPXS_Setup_0);

    res |= writeRegister(PXS_SETTINGS_1, (uint8_t *)nPXS);

    res |= writeRegister(PXS_UI_SETTINGS, (uint8_t *)nPXSUi);

    res |= writeRegister(SAR_UI_SETTINGS, (uint8_t *)nSARUi);

    res |= writeRegister(METAL_UI_SETTINGS, (uint8_t *)nMetalDetect);

    res |= writeRegister(HALL_SENS_SETTINGS, (uint8_t *)nHall_Sens);

    res |= writeRegister(HALL_UI_SETTINGS, (uint8_t *)nHall_UI);

    res |= writeRegister(TEMP_UI_SETTINGS, (uint8_t *)nTemp_UI);

    // Wait for Redo Ati to complete
    do
        {
        res |= readRegisters(SYSTEM_FLAGS, &m_iqs620n.SystemFlags.SystemFlags, sizeof(&m_iqs620n.SystemFlags.SystemFlags));
        }
    while (!res && m_iqs620n.SystemFlags.InAti);

    return res;
    }

uint8_t cIQS620A::iqsRead()
    {
    uint8_t res = 0;

    if(m_icType == IQS620n)
        {
        // Read version number to insure we still have the correct device attached - otherwise, do setup
        res = readRegisters(VERSION_INFO, m_buffer, sizeof(m_buffer));

        // System flags, Global Events and PXS UI Flags - 9 bytes
        res |= readRegisters(SYSTEM_FLAGS, &m_iqs620n.SystemFlags.SystemFlags, sizeof(&m_iqs620n.SystemFlags.SystemFlags));

        // Read PXS Channel 0 Data - 12 bytes
        res |= readRegisters(CHANNEL0_DATA, &m_iqs620n.Ch[0].Ch_Low, sizeof(&m_iqs620n.Ch[0].Ch_Low));

        // Read channel 1 for SAR
        res |= readRegisters(CHANNEL1_DATA, &m_iqs620n.Ch[1].Ch_Low, sizeof(&m_iqs620n.Ch[1].Ch_Low));

        // Read channel 2 for SAR
        res |= readRegisters(CHANNEL2_DATA, &m_iqs620n.Ch[2].Ch_Low, sizeof(&m_iqs620n.Ch[2].Ch_Low));

        // Read channel 4 for SAR
        res |= readRegisters(CHANNEL4_DATA, &m_iqs620n.Ch[4].Ch_Low, sizeof(&m_iqs620n.Ch[4].Ch_Low));

        // Read channel 5 for SAR
        res |= readRegisters(CHANNEL5_DATA, &m_iqs620n.Ch[5].Ch_Low, sizeof(&m_iqs620n.Ch[5].Ch_Low));
        }

    // A read error occurred
    if(res)
        {
        // Serial.print("res : ");
        // Serial.println(res);
        }

    // reset timer
    setTimer(&m_errorTimer);

    m_chipReady = true;

    if(timerExpired(&m_errorTimer))
        {
        //Serial.print("Timer Expired : ");
        //Serial.println(ERR_TIMEOUT);
        }
    }

bool cIQS620A::writeRegister(uint16_t command, uint8_t* pData)
    {
    Wire.beginTransmission((uint8_t) Address::IQS620n);
    Wire.write(command);

    // No send the number of bytes required to write
    for(uint8_t i = 0; (i < sizeof(pData)); i++)
        {
        // Send each required byte
        Wire.write(pData[i]);
        }

    if (Wire.endTransmission() != 0)
        {
        return false;
        }

    return true;
    }

bool cIQS620A::readRegisters(uint16_t command, std::uint8_t *pBuffer, size_t nBuffer)
    {
    if (pBuffer == nullptr || nBuffer > 32)
        {
        return false;
        }

    Wire.beginTransmission((uint8_t) Address::IQS620n);
    if (Wire.write((uint8_t)command) != 1)
        {
        return false;
        }
    if (Wire.endTransmission() != 0)
        {
        return false;
        }

    auto nReadFrom = Wire.requestFrom((uint8_t) Address::IQS620n, std::uint8_t(nBuffer));

    if (nReadFrom != nBuffer)
        {
        return false;
        }

    auto const nResult = unsigned(Wire.available());

    if (nResult > nBuffer)
        {
        return false;
        }

    for (unsigned i = 0; i < nResult; ++i)
        {
        pBuffer[i] = Wire.read();
        }

    if (nResult != nBuffer)
        {
        return false;
        }

    return true;
    }

int16_t cIQS620A::getSarCountCh0()
    {
    return m_iqs620n.Ch[0].Ch;    // return Channel Data
    }

int16_t cIQS620A::getSarCountCh1()
    {
    return m_iqs620n.Ch[1].Ch;    // return Channel Data
    }

int16_t cIQS620A::getSarCountCh2()
    {
    return m_iqs620n.Ch[2].Ch;    // return Channel Data
    }

int16_t cIQS620A::getAmplitude()
    {
    int16_t hallEffectch4 = m_iqs620n.Ch[4].Ch;  // get Channel Data
    int16_t hallEffectch5 = m_iqs620n.Ch[5].Ch;  // get Channel Data
    return hallEffectch4 - hallEffectch5;
    }

void cIQS620A::setTimer(Timer_t* timer)
    {
    timer->TimerExpired = false;
    timer->Timer_start = millis();  // get this instant millis
    }

void cIQS620A::setTimer(Timer_t* timer, uint32_t time)
    {
    timer->TimerExpired = false;
    timer->Timer_start = millis();  // get this instant millis
    timer->Timer_counter = time;  // the timeout time for the timer
    }

bool cIQS620A::timerExpired(Timer_t* timer)
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