/*
* This file contains all the necessary settings for the IQS620 and this file can
* be changed from the GUI or edited here
* File:   IQS620_init.h
* Author: Azoteq
*/

#ifndef IQS620_INIT_H
#define IQS620_INIT_H

/* Change the Prox Sensor Settings 0 */
/* Memory Map Position 0x40 - 0x4F */
#define PXS_SETTINGS0_0						0x01
#define PXS_SETTINGS0_1						0x01
#define PXS_SETTINGS0_2						0x02
#define PXS_SETTINGS0_3						0xD0
#define PXS_SETTINGS0_4						0x77
#define PXS_SETTINGS0_5						0x77
#define PXS_SETTINGS0_6						0x57
#define PXS_SETTINGS0_7						0x14
#define PXS_SETTINGS0_8						0x66
#define PXS_SETTINGS0_9						0x66
#define PXS_SETTINGS0_10						0xD0
#define PXS_SETTINGS0_11						0xD0
#define PXS_SETTINGS0_12						0xC6
#define PXS_SETTINGS0_13						0xC6
#define PXS_SETTINGS0_14						0x06
#define PXS_SETTINGS0_15						0x06

/* Change the Prox Sensor Settings 1 */
/* Memory Map Position 0x50 - 0x59 */
#define PXS_SETTINGS1_0						0x80
#define PXS_SETTINGS1_1						0x01
#define PXS_SETTINGS1_2						0x69
#define PXS_SETTINGS1_3						0x69
#define PXS_SETTINGS1_4						0x82
#define PXS_SETTINGS1_5						0x00
#define PXS_SETTINGS1_6						0x57
#define PXS_SETTINGS1_7						0x57
#define PXS_SETTINGS1_8						0x1C
#define PXS_SETTINGS1_9						0x14

/* Change the Prox UI Settings */
/* Memory Map Position 0x60 - 0x68 */
#define PXS_UI_SETTINGS_0					0x16
#define PXS_UI_SETTINGS_1					0x20
#define PXS_UI_SETTINGS_2					0x14
#define PXS_UI_SETTINGS_3					0x25
#define PXS_UI_SETTINGS_4					0x12
#define PXS_UI_SETTINGS_5					0x20
#define PXS_UI_SETTINGS_6					0x16
#define PXS_UI_SETTINGS_7					0x20
#define PXS_UI_SETTINGS_8					0x28

/* Change the SAR UI Settings */
/* Memory Map Position 0x70 - 0x75 */
#define SAR_UI_SETTINGS_0					0x14
#define SAR_UI_SETTINGS_1					0x25
#define SAR_UI_SETTINGS_2					0x05
#define SAR_UI_SETTINGS_3					0x16
#define SAR_UI_SETTINGS_4					0x20
#define SAR_UI_SETTINGS_5					0x28

/* Change the Metal Detect UI Settings */
/* Memory Map Position 0x80 - 0x83 */
#define METAL_DETECT_UI_SETTINGS_0				0x12
#define METAL_DETECT_UI_SETTINGS_1				0x20
#define METAL_DETECT_UI_SETTINGS_2				0x16
#define METAL_DETECT_UI_SETTINGS_3				0x20

/* Change the HALL Sensor Settings */
/* Memory Map Position 0x90 - 0x93 */
#define HALL_SENSOR_SETTINGS_0				0x03
#define HALL_SENSOR_SETTINGS_1				0x50
#define HALL_SENSOR_SETTINGS_2				0xC8
#define HALL_SENSOR_SETTINGS_3				0x0A

/* Change the HALL Switch UI Settings */
/* Memory Map Position 0xA0 - 0xA2 */
#define HALL_UI_SETTINGS_0					0x00
#define HALL_UI_SETTINGS_1					0x19
#define HALL_UI_SETTINGS_2					0x19

/* Change the Device & PMU Settings */
/* Memory Map Position 0xD0 - 0xD7 */
#define SYSTEM_SETTINGS						0x08
#define ACTIVE_CHS							0x3F
#define PMU_SETTINGS						0x03
#define REPORT_RATES_TIMINGS_0				0x10
#define REPORT_RATES_TIMINGS_1				0x0B
#define REPORT_RATES_TIMINGS_2				0x08
#define REPORT_RATES_TIMINGS_3				0x14

#endif	/* IQS620_INIT_H */
