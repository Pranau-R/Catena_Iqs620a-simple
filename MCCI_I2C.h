/*

Module: MCCI_I2C.h

Function:
    Top-level include file for MCCI I2C APIs.

Copyright and License:
    See accompanying LICENSE file for copyright and license information.

Author:
    Pranau R, MCCI Corporation   March 2023

*/

#ifndef _MCCI_I2C_H_
#define _MCCI_I2C_H_ /* prevent multiple includes */

#include <Wire.h>

class cI2C
    {
public:
    cI2C();
    virtual ~cI2C();
    enum class Address : std::int8_t
        {
        Error = -1,
        IQS620n = 0x44,
        };

    bool writeRegister(uint16_t command, uint8_t* pData);
    bool readRegisters(uint16_t command, std::uint8_t *pBuffer, size_t nBuffer);
    };

#endif /* _MCCI_I2C_H_ */
