/*

Module: Catena_Iqs620a.h

Function:
    Top-level include file for MCCI Catena IQS620A library (simple).

Copyright and License:
    See accompanying LICENSE file for copyright and license information.

Author:
    Pranau R, MCCI Corporation   March 2023

*/

#ifndef CATENA_IQS620A_H
#define CATENA_IQS620A_H

#include <Arduino.h>

/*  Global defines      ----------------------------------------------------------*/

#define MS_500                                  500
#define ONE_SEC                                 1000
#define TWO_SEC                                 2000
#define THREE_SEC                               3000
#define TWELVE_SEC                              12000
#define MS_5                                    5

// Define Product Numbers
#define IQS620_PRODUCT_NR                       65
#define IQS620N_SOFTWARE_NR                     8
#define IQS620N_HARDWARE_NR                     130

/* Device data registers*/

#define I2C_ADDRESS                             0x44

#define VERSION_INFO                            0x00
#define SYSTEM_FLAGS                            0x10
#define CHANNEL0_DATA                           0x20
#define CHANNEL1_DATA                           0x22
#define CHANNEL2_DATA                           0x24
#define CHANNEL3_DATA                           0x26
#define CHANNEL4_DATA                           0x28
#define CHANNEL5_DATA                           0x2A
#define LTA                                     0x30
#define HALL_CH4                                0x17
#define HALL_CH5                                0x18
#define PXS_SETTINGS_0                          0x40
#define PXS_SETTINGS_1                          0x50
#define PXS_UI_SETTINGS                         0x60
#define SAR_UI_SETTINGS                         0x70
#define METAL_UI_SETTINGS                       0x80
#define HALL_SENS_SETTINGS                      0x90
#define HALL_UI_SETTINGS                        0xA0
#define TEMP_UI_SETTINGS                        0xC0
#define DEV_SETTINGS                            0xD0
#define DIRECT_ADDRESS                          0xF0
#define DIRECT_DATA                             0xF1

/* Bit definitions */
#define ACK_RESET                               0x40
#define REDO_ATI_ALL                            0x02
#define DO_RESEED                               0x01

// Sensor Settings
/* Change the Prox Sensor Settings 0 */
/* Memory Map Position 0x40 - 0x4F */
#define nPXS_SETTINGS0_0                        0x01
#define nPXS_SETTINGS0_1                        0x01
#define nPXS_SETTINGS0_2                        0x02
#define nPXS_SETTINGS0_3                        0x67
#define nPXS_SETTINGS0_4                        0x67
#define nPXS_SETTINGS0_5                        0x67
#define nPXS_SETTINGS0_6                        0xE0
#define nPXS_SETTINGS0_7                        0xE0
#define nPXS_SETTINGS0_8                        0xD0
#define nPXS_SETTINGS0_9                        0x06
#define nPXS_SETTINGS0_10                       0x06
#define nPXS_SETTINGS0_11                       0x06

/* Change the Prox Sensor Settings 1 */
/* Memory Map Position 0x50 - 0x59 */
#define nPXS_SETTINGS1_0                        0x80
#define nPXS_SETTINGS1_1                        0x01
#define nPXS_SETTINGS1_2                        0xAA
#define nPXS_SETTINGS1_3                        0xB0
#define nPXS_SETTINGS1_4                        0x8C
#define nPXS_SETTINGS1_5                        0x18
#define nPXS_SETTINGS1_6                        0x18
#define nPXS_SETTINGS1_7                        0x19
#define nPXS_SETTINGS1_8                        0x40

/* Change the Prox UI Settings */
/* Memory Map Position 0x60 - 0x68 */
#define nPXS_UI_SETTINGS_0                      0x16
#define nPXS_UI_SETTINGS_1                      0x25
#define nPXS_UI_SETTINGS_2                      0x13
#define nPXS_UI_SETTINGS_3                      0x24
#define nPXS_UI_SETTINGS_4                      0x16
#define nPXS_UI_SETTINGS_5                      0x25
#define nPXS_UI_SETTINGS_6                      0x0A

/* Change the SAR UI Settings */
/* Memory Map Position 0x70 - 0x75 */
#define nSAR_UI_SETTINGS_0                      0x13
#define nSAR_UI_SETTINGS_1                      0x24
#define nSAR_UI_SETTINGS_2                      0x01
#define nSAR_UI_SETTINGS_3                      0x16
#define nSAR_UI_SETTINGS_4                      0x25
#define nSAR_UI_SETTINGS_5                      0x0A

/* Change the Metal Detect UI Settings */
/* Memory Map Position 0x80 - 0x83 */
#define nMETAL_DETECT_UI_SETTINGS_0             0xA2
#define nMETAL_DETECT_UI_SETTINGS_1             0x0A
#define nMETAL_DETECT_UI_SETTINGS_2             0x16
#define nMETAL_DETECT_UI_SETTINGS_3             0x25

/* Change the HALL Sensor Settings */
/* Memory Map Position 0x90 - 0x93 */
#define nHALL_SENSOR_SETTINGS_0                 0x03
#define nHALL_SENSOR_SETTINGS_1                 0x50
#define nHALL_SENSOR_SETTINGS_2                 0x0D
#define nHALL_SENSOR_SETTINGS_3                 0x47

/* Change the HALL Switch UI Settings */
/* Memory Map Position 0xA0 - 0xA2 */
#define nHALL_UI_SETTINGS_0                     0x00
#define nHALL_UI_SETTINGS_1                     0x19
#define nHALL_UI_SETTINGS_2                     0x19

/* Change the Temperature UI Settings */
/* Memory Map Position 0xC0 - 0xC3 */
#define nTEMP_UI_SETTINGS_0                     0x00
#define nTEMP_UI_SETTINGS_1                     0x03
#define nTEMP_UI_SETTINGS_2                     0x03
#define nTEMP_UI_SETTINGS_3                     0xD5

/* Change the Device & PMU Settings */
/* Memory Map Position 0xD0 - 0xD7 */
#define nSYSTEM_SETTINGS                        0x08
#define nACTIVE_CHS                             0x3F
#define nPMU_SETTINGS                           0x03
#define nREPORT_RATES_TIMINGS_0                 0x10
#define nREPORT_RATES_TIMINGS_1                 0x30
#define nREPORT_RATES_TIMINGS_2                 0x08
#define nREPORT_RATES_TIMINGS_3                 0x14
#define nGLOBAL_EVENT_MASK                      0x00
#define nPWM_DUTY_CYCLE                         0x00

/* Setup Registers */

// PXS Settings 0 - 0x40
const static uint8_t nPXS_Setup_0[] = {
    nPXS_SETTINGS0_0,
    nPXS_SETTINGS0_1,
    nPXS_SETTINGS0_2,
    nPXS_SETTINGS0_3,
    nPXS_SETTINGS0_4,
    nPXS_SETTINGS0_5,
    nPXS_SETTINGS0_6,
    nPXS_SETTINGS0_7,
    nPXS_SETTINGS0_8,
    nPXS_SETTINGS0_9,
    nPXS_SETTINGS0_10,
    nPXS_SETTINGS0_11
};

// PXS Settings 1 - 0x50
const static uint8_t nPXS[] = {nPXS_SETTINGS1_8};

// PXS UI - 0x60
const static uint8_t nPXSUi[] = {
    nPXS_UI_SETTINGS_0,
    nPXS_UI_SETTINGS_1,
    nPXS_UI_SETTINGS_2,
    nPXS_UI_SETTINGS_3,
    nPXS_UI_SETTINGS_4,
    nPXS_UI_SETTINGS_5,
    nPXS_UI_SETTINGS_6
};

// SAR UI - 0x70
const static uint8_t nSARUi[] = {
    nSAR_UI_SETTINGS_0,
    nSAR_UI_SETTINGS_1,
    nSAR_UI_SETTINGS_2,
    nSAR_UI_SETTINGS_3,
    nSAR_UI_SETTINGS_4,
    nSAR_UI_SETTINGS_5
};


// Metal Detect UI - 0x80
const static uint8_t nMetalDetect[] = {
    nMETAL_DETECT_UI_SETTINGS_0,
    nMETAL_DETECT_UI_SETTINGS_1,
    nMETAL_DETECT_UI_SETTINGS_2,
    nMETAL_DETECT_UI_SETTINGS_3
};

// HALL - 0x90
const static uint8_t nHall_Sens[] = {
    nHALL_SENSOR_SETTINGS_0,
    nHALL_SENSOR_SETTINGS_1,
    nHALL_SENSOR_SETTINGS_2,
    nHALL_SENSOR_SETTINGS_3
};

// HALL - 0xA0
const static uint8_t nHall_UI[] = {
    nHALL_UI_SETTINGS_0,
    nHALL_UI_SETTINGS_1,
    nHALL_UI_SETTINGS_2
};

// HALL - 0xA0
const static uint8_t nTemp_UI[] = {
    nTEMP_UI_SETTINGS_0,
    nTEMP_UI_SETTINGS_1,
    nTEMP_UI_SETTINGS_2,
    nTEMP_UI_SETTINGS_3
};

// Dev Setup - 0xD0
const static uint8_t nDevSetup[] = {
    nSYSTEM_SETTINGS|REDO_ATI_ALL|DO_RESEED|ACK_RESET,
    nACTIVE_CHS,
    nPMU_SETTINGS,
    nREPORT_RATES_TIMINGS_0,
    nREPORT_RATES_TIMINGS_1,
    nREPORT_RATES_TIMINGS_2,
    nREPORT_RATES_TIMINGS_3,
    nGLOBAL_EVENT_MASK,
    nPWM_DUTY_CYCLE
};

/*  Typedefs        --------------------------------------------------------------*/

// Enum to determine what to show on screen
typedef enum IC_Type
    {
    IQS620n = 1
    } IC_Type_e;

// 'Timer' object
typedef struct Timer
    {
    uint32_t Timer_counter;     // This timer's counter
    uint32_t Timer_start;       // This timer's start ms
    bool TimerExpired;          // Flag indicating whether timer expired
    } Timer_t;

// PXS CH  Value
typedef union
    {
    // Bitfield for PXS UI Flags
    struct
        {
        uint8_t Ch_Low;
        uint8_t Ch_High;
        };
    uint16_t Ch;
    } Ch_t;

typedef union
    {
    // Bitfield for System Flags
    struct
        {

        uint8_t NpSegmentActive     :1;
        uint8_t Event               :1;
        uint8_t InAti               :1;
        uint8_t PowerMode           :2;
        uint8_t None                :2;
        uint8_t ShowReset           :1;
        };
    uint8_t SystemFlags;
    } SystemFlags_t;

// "Object" for IQS620 production
typedef struct IQS620n
    {
    // System Flags
    SystemFlags_t SystemFlags;

    // Channel 0 data
    Ch_t Ch[6];

    } IQS620n_t;

/// \brief instance object for IPS-7100 Sensor
class cIQS620A
    {
public:
    cIQS620A();
    virtual ~cIQS620A();

    enum class Address : std::int8_t
        {
        Error = -1,
        IQS620n = 0x44,
        };

    bool begin();

    uint8_t configureIqs620n();

    uint8_t iqsRead();

    void setTimer(Timer_t* timer);

    void setTimer(Timer_t* timer, uint32_t time);

    bool timerExpired(Timer_t* timer);

    bool writeRegister(uint16_t command, uint8_t* pData);

    bool readRegisters(uint16_t command, std::uint8_t *pBuffer, size_t nBuffer);

    int16_t getSarCountCh0();
    int16_t getSarCountCh1();
    int16_t getSarCountCh2();

    int16_t getAmplitude();

private:
    //ProxFusion IC's
    IQS620n_t m_iqs620n;              // Create variable for iqs620A

    // Indicate chip is ready for polling
    bool m_chipReady = false;

    // Buffer to read data into
    uint8_t m_buffer[20];
    // What type of IC is this?
    IC_Type_e m_icType;

    // Timer
    Timer_t m_errorTimer          = {0};          // Error Timer
    Timer_t m_mainTimer           = {0};          // Error Timer
    };

#endif /* _CATENA_IQS620A_H_ */