/*

Module: MCCI_I2C.cpp

Function:
    Implementation code for MCCI I2C APIs.

Copyright and License:
    See accompanying LICENSE file for copyright and license information.

Author:
    Pranau R, MCCI Corporation   March 2023

*/

#include "MCCI_I2C.h"
#include <Wire.h>

cI2C::cI2C()
    {
    //default constructor
    }

cI2C::~cI2C()
    {
    }

bool cI2C::writeRegister(uint16_t command, uint8_t* pData)
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

bool cI2C::readRegisters(uint16_t command, std::uint8_t *pBuffer, size_t nBuffer)
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

/**** end of MCCI_I2C.cpp ****/
