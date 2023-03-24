/*
* This file contains all the necessary settings for the IQS620 and this file can
* be changed from the GUI or edited here
* File:   IQS620_init.h
* Author: Azoteq
*/

#ifndef IQS620n_INIT_H
#define IQS620n_INIT_H

/* Change the Prox Sensor Settings 0 */
/* Memory Map Position 0x40 - 0x4F */
#define nPXS_SETTINGS0_0						0x01
#define nPXS_SETTINGS0_1						0x01
#define nPXS_SETTINGS0_2						0x02
#define nPXS_SETTINGS0_3						0x67
#define nPXS_SETTINGS0_4						0x67
#define nPXS_SETTINGS0_5						0x67
#define nPXS_SETTINGS0_6						0xE0
#define nPXS_SETTINGS0_7						0xE0
#define nPXS_SETTINGS0_8						0xD0
#define nPXS_SETTINGS0_9						0x06
#define nPXS_SETTINGS0_10						0x06
#define nPXS_SETTINGS0_11						0x06

/* Change the Prox Sensor Settings 1 */
/* Memory Map Position 0x50 - 0x59 */
#define nPXS_SETTINGS1_0						0x80
#define nPXS_SETTINGS1_1						0x01
#define nPXS_SETTINGS1_2						0xAA
#define nPXS_SETTINGS1_3						0xB0
#define nPXS_SETTINGS1_4						0x8C
#define nPXS_SETTINGS1_5						0x18
#define nPXS_SETTINGS1_6						0x18
#define nPXS_SETTINGS1_7						0x19
#define nPXS_SETTINGS1_8						0x40

/* Change the Prox UI Settings */
/* Memory Map Position 0x60 - 0x68 */
#define nPXS_UI_SETTINGS_0					0x16
#define nPXS_UI_SETTINGS_1					0x25
#define nPXS_UI_SETTINGS_2					0x13
#define nPXS_UI_SETTINGS_3					0x24
#define nPXS_UI_SETTINGS_4					0x16
#define nPXS_UI_SETTINGS_5					0x25
#define nPXS_UI_SETTINGS_6					0x0A

/* Change the SAR UI Settings */
/* Memory Map Position 0x70 - 0x75 */
#define nSAR_UI_SETTINGS_0					0x13
#define nSAR_UI_SETTINGS_1					0x24
#define nSAR_UI_SETTINGS_2					0x01
#define nSAR_UI_SETTINGS_3					0x16
#define nSAR_UI_SETTINGS_4					0x25
#define nSAR_UI_SETTINGS_5					0x0A

/* Change the Metal Detect UI Settings */
/* Memory Map Position 0x80 - 0x83 */
#define nMETAL_DETECT_UI_SETTINGS_0				0xA2
#define nMETAL_DETECT_UI_SETTINGS_1				0x0A
#define nMETAL_DETECT_UI_SETTINGS_2				0x16
#define nMETAL_DETECT_UI_SETTINGS_3				0x25

/* Change the HALL Sensor Settings */
/* Memory Map Position 0x90 - 0x93 */
#define nHALL_SENSOR_SETTINGS_0				0x03
#define nHALL_SENSOR_SETTINGS_1				0x50
#define nHALL_SENSOR_SETTINGS_2				0x0D
#define nHALL_SENSOR_SETTINGS_3				0x47

/* Change the HALL Switch UI Settings */
/* Memory Map Position 0xA0 - 0xA2 */
#define nHALL_UI_SETTINGS_0					0x00
#define nHALL_UI_SETTINGS_1					0x19
#define nHALL_UI_SETTINGS_2					0x19

/* Change the Temperature UI Settings */
/* Memory Map Position 0xC0 - 0xC3 */
#define nTEMP_UI_SETTINGS_0					0x00
#define nTEMP_UI_SETTINGS_1					0x03
#define nTEMP_UI_SETTINGS_2					0x03
#define nTEMP_UI_SETTINGS_3					0xD5

/* Change the Device & PMU Settings */
/* Memory Map Position 0xD0 - 0xD7 */
#define nSYSTEM_SETTINGS						0x08
#define nACTIVE_CHS							0x3F
#define nPMU_SETTINGS						0x03
#define nREPORT_RATES_TIMINGS_0				0x10
#define nREPORT_RATES_TIMINGS_1				0x30
#define nREPORT_RATES_TIMINGS_2				0x08
#define nREPORT_RATES_TIMINGS_3				0x14
#define nGLOBAL_EVENT_MASK					0x00
#define nPWM_DUTY_CYCLE					0x00

#endif	/* IQS620n_INIT_H */
