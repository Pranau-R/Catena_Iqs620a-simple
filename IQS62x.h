;/*****************************************************************************
*                                                                             *
*                                                                             *
*                           	Copyright by                                    *
*                                                                             *
*                         	  Azoteq (Pty) Ltd                                *
*                     	  Republic of South Africa                            *
*                                                                             *
*                     	   Tel: +27(0)21 863 0033                             *
*                    	    E-mail: info@azoteq.com                             *
*                                                                             *
*=============================================================================*
* @file 	    IQS62x.h									 				                              *
* @brief 	    Header for the IQS62x device type for demo purposes			        *
* @author 		AJ van der Merwe; L Theron; PJ Winterbach - Azoteq PTY Ltd      *
* @version 		V1.3.0                                                          *
* @date 	    10/25/2018                                                      *
*******************************************************************************/


#ifndef __IQS62x_H__
#define __IQS62x_H__

#include "Arduino.h"
#include "IQS620_Init.h"
#include "IQS620n_Init.h"


// Define Product Numbers
#define IQS620_PRODUCT_NR			    65
#define IQS620N_SOFTWARE_NR		    8
#define IQS620N_HARDWARE_NR			  130
#define IQS621_PRODUCT_NR			    70
#define IQS622_PRODUCT_NR     		66
#define IQS624_PRODUCT_NR			    67
#define IQS624N_SOFTWARE_NR     	11
#define IQS625_PRODUCT_NR         78
#define IQS625_SOFTWARE_NR        11


// Enum to indicate if we will do a Capacitive or Inductive sensing setup
typedef enum Setup_Type {
	Capacitive = 0,
	Inductive
}Setup_Type_e;

typedef enum ATI_Mode {
	ATI_Disabled = 0,
	Partial_ATI = 1,
	Semi_Partial_ATI = 2,
	Full_ATI = 3,
}ATI_Mode_e;

typedef enum Base_Value {
	Base_75 = 0,
	Base_100 = 1,
	Base_150 = 2,
	Base_200 = 3,
}Base_Value_e;

/*
 *  Create Unions of bitfields to make reading and the IQS62x
 *  easier and more convenient
 */
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// System Flags
typedef union
{
	// Bitfield for System Flags
    struct
    {

    	uint8_t NpSegmentActive     :1;
    	uint8_t Event	              :1;
    	uint8_t InAti	              :1;
    	uint8_t PowerMode           :2;
    	uint8_t None	              :2;
    	uint8_t ShowReset           :1;
    };
    uint8_t SystemFlags;
}SystemFlags_t;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Global Events
typedef union
{
	// Bitfield for Global Events
    struct
    {
    	uint8_t Pxs_Event			      :1;
    	uint8_t Sar_Event			      :1;
    	uint8_t Hall_Event			    :1;
    	uint8_t Metal_Detect_Flag   :1;
    	uint8_t System_Event 	      :1;
    	uint8_t None		            :1;
    	uint8_t Sar_Active          :1;
    	uint8_t Hall_Cover_Closed   :1;
    };
    uint8_t GlobalEvents;
}GlobalEvents_IQS620_t;

// Global Events
typedef union
{
	// Bitfield for Global Events
    struct
    {
    	uint8_t Pxs_Event			      :1;
    	uint8_t Sar_Event			      :1;
    	uint8_t Hall_Event			    :1;
    	uint8_t Metal_Detect_Flag   :1;
    	uint8_t Temp_Event 	    	  :1;
    	uint8_t Sys_Event	          :1;
    	uint8_t Pmu_Event           :1;
    	uint8_t Sar_Active		      :1;
    };
    uint8_t GlobalEvents;
}GlobalEvents_IQS620n_t;

// Global Events - TODO
typedef union
{
	// Bitfield for Global Events
    struct
    {
    	uint8_t Pxs_Event			      :1;
    	uint8_t Hall_Event			    :1;
    	uint8_t ALS_Event			      :1;
    	uint8_t Metal_Detect_Flag   :1;
    	uint8_t Temp_Event 	    	  :1;
    	uint8_t System_Event        :1;
    	uint8_t PMU_Event           :1;
    };
    uint8_t GlobalEvents;
}GlobalEvents_IQS621_t;

// Global Events - TODO
typedef union
{
  // Bitfield for Global Events
    struct
    {
      uint8_t Pxs_Event           :1;
      uint8_t Sar_Event           :1;
      uint8_t Hall_Event          :1;
      uint8_t ALS_Event           :1;
      uint8_t IR_Event            :1;
      uint8_t System_Event        :1;
      uint8_t PMU_Event           :1;
    };
    uint8_t GlobalEvents;
}GlobalEvents_IQS622_t;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// PXS UI Flags
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t CH0_P_Out		        :1;
    	uint8_t CH1_P_Out	          :1;
    	uint8_t CH2_P_Out	          :1;
    	uint8_t None    	          :1;
    	uint8_t CH0_T_Out           :1;
    	uint8_t CH1_T_Out           :1;
    	uint8_t CH2_T_Out           :1;
    };
    uint8_t PXSUIFlags;
}PXSUIFlags_IQS620_t;

// PXS UI Flags
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t CH0_P_Out		        :1;
    	uint8_t CH1_P_Out	          :1;
    	uint8_t None		            :2;
    	uint8_t CH0_T_Out           :1;
    	uint8_t CH1_T_Out           :1;
    };
    uint8_t PXSUIFlags;
}PXSUIFlags_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// SAR and Metal Flags
typedef union
{
	// Bitfield for SAR and Metal Flags
    struct
    {
    	uint8_t FHalt			          :1;
    	uint8_t Movement            :1;
    	uint8_t Quick_Release       :1;
    	uint8_t None		            :1;
    	uint8_t Sar_Active	        :1;
    	uint8_t Metal_Prox	        :1;
    	uint8_t Metal_Touch	        :1;
    	uint8_t Metal_Type	        :1;
    };
    uint8_t SARMetalFlags;
}SARMetalFlags_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Metal Detect Output
typedef union
{
	// Bitfield for Metal Detect Output
    struct
    {
    	uint8_t Metal_Low;
    	uint8_t Metal_High;
    };
    uint16_t MetalValue;
}MetalValue_t;

// SAR and Metal Flags
typedef union
{
	// Bitfield for SAR and Metal Flags
    struct
    {
    	uint8_t Metal_Prox	       :1;
    	uint8_t Metal_Touch	       :1;
    	uint8_t Metal_Type	       :1;
    };
    uint8_t Metal_UI_Flags;
}Metal_UI_Flags_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ALS Flags
typedef union
{
	// Bitfield for ALS UI Flags
    struct
    {
    	uint8_t ALS_Value		      :4;
    	uint8_t None	            :3;
    	uint8_t Light_Dark        :1;
    };
    uint8_t ALSFlags;
}ALSFlags_t;

// ALS Output
typedef union
{
	// Bitfield for ALS UI Flags
    struct
    {
    	uint8_t ALS_Low;
    	uint8_t ALS_High:3;
    };
    uint16_t ALSValue;
}ALSValue_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// IR Flags
typedef union
{
  // Bitfield for IR UI Flags
    struct
    {
      uint8_t IR_Prox         :1;
      uint8_t IR_Touch        :1;
      uint8_t None            :6;
    };
    uint8_t IRFlags;
}IRFlags_t;

// IR UI Flags
typedef union
{
  // Bitfield for IR UI Flags
    struct
    {
      uint8_t IR_Range       :4;
    };
    uint8_t IRUIFlags;
}IRUIFlags_t;

// IR Output
typedef union
{
  // Bitfield for IR UI Flags
    struct
    {
      uint8_t IR_High;
      uint8_t IR_Low;
    };
    uint16_t IRValue;
}IRValue_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Hall UI Flags
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t Hall_N_S			:1;
    	uint8_t Hall_Prox			:1;
    	uint8_t Hall_Touch		:1;
    };
    uint8_t HallFlags;
}HallFlags_t;

// Hall Value
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t Hall_Low;
    	uint8_t Hall_High;
    };
    uint16_t HallValue;
}HallValue_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Hall UI Flags for IQS624
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t Diff				    :1;
    	uint8_t Count				    :1;
    	uint8_t Post_WW				  :1;
    	uint8_t None				    :3;
    	uint8_t Movement_Dir		:1;
    	uint8_t Wheel_Movement	:1;
    };
    uint8_t HallFlags;
}HallFlags_IQS624_t;

// Hall UI Flags for IQS624
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t ATI_Mode			:2;
      uint8_t None          :2;
      uint8_t Charge_Freq   :2;
      uint8_t None1         :1;
      uint8_t ACF_enable    :1;
    };
    uint8_t HallSensorSettings;
}Hall_Sensor_Settings_t;

// Hall UI Flags for IQS624
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t ATI_Target				:6;
    	uint8_t ATI_Base				  :2;
    };
    uint8_t ATISettings;
}Hall_ATI_Settings_t;

// Hall Degrees
typedef union
{
	// Bitfield for Degrees output
    struct
    {
    	uint8_t Hall_Degrees_Low;
    	uint8_t Hall_Degrees_High;
    };
    uint16_t HallDegrees;
}HallDegrees_t;

// Hall Ratio Settings
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t Numerator_Negative		            :1;
    	uint8_t Denominator_Negative	            :1;
    	uint8_t Ratio_Negative			              :1;
    	uint8_t Direction_Invert_Cos_Negative		  :1;
    	uint8_t None					                    :1;
    	uint8_t Quadrature				                :2;
    };
    uint8_t HallRatioSettings;
}Hall_Ratio_Settings_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Temperature Flags Value
typedef union
{
	// Bitfield for Temp Flags
    struct
    {
    	uint8_t None				:7;
    	uint8_t Temp_Trip			:1;
    };
    uint8_t TempFlags;
}TempFlags_t;

// Hall Value
typedef union
{
	// Bitfield for PXS UI Flags
    struct
    {
    	uint8_t Temp_Low;
    	uint8_t Temp_High;
    };
    uint16_t TempValue;
}TempValue_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
}Ch_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// "Object" for IQS620
typedef struct IQS620 {

	// System Flags
	SystemFlags_t SystemFlags;

	// Global Events
	GlobalEvents_IQS620_t GlobalEvents;

	// Proxsense UI Flags
	PXSUIFlags_IQS620_t PXSUIFlags;

	// Sar and Metal Flags
	SARMetalFlags_t SARMetalFlags;

	// Metal Detect Value
	MetalValue_t MetalValue;

	// Hall UI Flags
	HallFlags_t HallFlags;

	// Hall Value (output)
	HallValue_t HallValue;

	// Channel 0 data
	Ch_t Ch[5];

	// LTA data - Ch1
	Ch_t LTA1;

} IQS620_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// "Object" for IQS620 production
typedef struct IQS620n {

	// System Flags
	SystemFlags_t SystemFlags;

	// Global Events
	GlobalEvents_IQS620n_t GlobalEvents;

	// Proxsense UI Flags
	PXSUIFlags_IQS620_t PXSUIFlags;

	// Sar and Metal Flags
	SARMetalFlags_t SARMetalFlags;

	// Metal Detect Value
	MetalValue_t MetalValue;

	// Hall UI Flags
	HallFlags_t HallFlags;

	// Hall Value (output)
	HallValue_t HallValue;

	// Temperature Flags
	TempFlags_t TempFlags;

	// Temperature Value
	TempValue_t TempValue;

	// Channel 0 data
	Ch_t Ch[6];

	// LTA data - Ch1
	Ch_t LTA1;

} IQS620n_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// "Object" for IQS621
typedef struct IQS621 {

	// System Flags
	SystemFlags_t SystemFlags;

	// Global Events
	GlobalEvents_IQS621_t GlobalEvents;

	// Proxsense UI Flags
	PXSUIFlags_t PXSUIFlags;

	// Metal UI flags
	Metal_UI_Flags_t MetalFlags;

	// Metal Detect Value
	MetalValue_t MetalValue;

	// Als Flags
	ALSFlags_t ALSFlags;

	// ALS value
	ALSValue_t ALSValue;

	// Hall UI Flags
	HallFlags_t HallFlags;

	// Hall Value (output)
	HallValue_t HallValue;

	// Temperature flags
	TempFlags_t TempFlags;

	// Temperature value
	TempValue_t TempValue;

	// Channel 0 data
	Ch_t Ch[6];

	// LTA data - Ch1
	Ch_t LTA1;

	// Set flag to indicate Coil is present
	bool coilPresent;
	bool coilFirstExit;

	// Which sensor mode are we running now
	Setup_Type_e sensorMode;

} IQS621_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// "Object" for IQS622
typedef struct IQS622 {

  // System Flags
  SystemFlags_t SystemFlags;

  // Global Events
  GlobalEvents_IQS622_t GlobalEvents;

  // Proxsense UI Flags
  PXSUIFlags_t PXSUIFlags;

  // Sar and Metal Flags
  SARMetalFlags_t SARMetalFlags;

  // Als Flags
  ALSFlags_t ALSFlags;

  // IR Flags
  IRFlags_t IRFlags;

  // IR UI Flags
  IRUIFlags_t IRUIFlags;

  // IR value
  IRValue_t IRValue;

  // Hall UI Flags
  HallFlags_t HallFlags;

  // Hall Value (output)
  HallValue_t HallValue;

  // Channel 0 data
  Ch_t Ch[6];

  // LTA data - Ch1
  Ch_t LTA1;

} IQS622_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// "Object" for IQS624n
typedef struct IQS624n {

	// System Flags
	SystemFlags_t SystemFlags;

  // Global events
  uint8_t GlobalEvents;

	// Proxsense UI Flags
	PXSUIFlags_t PXSUIFlags;

	// Placeholder for SAR UI Flags
	uint8_t SARUIFlags;

	// Hall UI Flags
	HallFlags_IQS624_t HallFlags;
 
  //Hall Ratio Flags (Placeholder)
  HallFlags_IQS624_t HallRatioFlags;

  //Filtered hall degrees 
  HallDegrees_t FillHallDegrees;

  //Interval number 
  uint8_t IntervalNumber;
	
	// Channel 0 data
	Ch_t Ch[6];

	// LTA data - Ch1
	Ch_t LTA1;

	// Keep Setup of hall
	uint8_t HallUISettings;

	// Hall Sensor Settings
	Hall_Sensor_Settings_t HallSensorSettings;

	// Hall ATI Settings
	Hall_ATI_Settings_t HallAtiSettings_CH2_CH3;
	Hall_ATI_Settings_t HallAtiSettings_CH4_CH5;

	// Create space for quadrature
	Hall_Ratio_Settings_t HallRatioSettings;

	// Hall Degrees Output
	HallDegrees_t HallDegrees;

	// Hall angle difference
	uint8_t hallAngleDiff;

  // Hall Calibration bin data
  uint8_t CalibrationBin;

	// Average (filtered value)
	Ch_t AvgCh[6];
} IQS624n_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* Hall Wheel Calibration Table Values */
const static uint16_t LeftTarget[] = {512,608,672,704,768,512,608,672,704,768,512,608,672,704,768};

const static uint16_t RightTarget[] = {480,544,608,640,704,512,576,640,704,736,576,640,704,768,800};

// "Object" for IQS624
typedef struct IQS624 {

  // System Flags
  SystemFlags_t SystemFlags;

  // Proxsense UI Flags
  PXSUIFlags_t PXSUIFlags;

  // Placeholder for SAR UI Flags
  uint8_t SARUIFlags;

  // Hall UI Flags
  HallFlags_IQS624_t HallFlags;

  // Channel 0 data
  Ch_t Ch[6];

  // LTA data - Ch1
  Ch_t LTA1;

  // Keep Setup of hall
  uint8_t HallUISettings;

  // Hall Sensor Settings
  Hall_Sensor_Settings_t HallSensorSettings;

  // Hall ATI Settings
  Hall_ATI_Settings_t HallAtiSettings_CH2_CH3;
  Hall_ATI_Settings_t HallAtiSettings_CH4_CH5;

  // Create space for quadrature
  Hall_Ratio_Settings_t HallRatioSettings;

  // Hall Degrees Output
  HallDegrees_t HallDegrees;

  // Hall angle difference
  uint8_t hallAngleDiff;

  // Average (filtered value)
  Ch_t AvgCh[6];
} IQS624_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// "Object" for IQS625
typedef struct IQS625 {

  // System Flags
  SystemFlags_t SystemFlags;

  // Proxsense UI Flags
  PXSUIFlags_t PXSUIFlags;

  // Interval number
  uint8_t Interval_number;

  // Channel 0 data
  Ch_t Ch[6];

  // LTA data - Ch1
  Ch_t LTA1;

  // Keep Setup of hall
  uint8_t HallUISettings;

  // Hall Sensor Settings
  Hall_Sensor_Settings_t HallSensorSettings;

  // Hall ATI Settings
  Hall_ATI_Settings_t HallAtiSettings_CH2_CH3;
  Hall_ATI_Settings_t HallAtiSettings_CH4_CH5;

  // Create space for quadrature
  Hall_Ratio_Settings_t HallRatioSettings;

  // Hall Degrees Output
  HallDegrees_t HallDegrees;

  // Interval UI divider
  uint8_t Interval_UI_div;

  // Hall angle difference
  uint8_t hallAngleDiff;

  // Hall Calibration bin data
  uint8_t CalibrationBin;

} IQS625_t;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
/****************************************************************/
/*																								              */
/*									IQS621 memory adresses										  */
/*																								              */
/****************************************************************/
#define I2C_ADDRESS               0x44

#define VERSION_INFO              0x00
#define SYSTEM_FLAGS              0x10
#define CHANNEL0_DATA              0x20
#define CHANNEL3_DATA              0x26
#define LTA			                  0x30
#define PXS_SETTINGS_0            0x40
#define PXS_SETTINGS_1            0x50
#define PXS_UI_SETTINGS           0x60
#define SAR_UI_SETTINGS           0x70
#define METAL_UI_SETTINGS         0x80
#define HALL_SENS_SETTINGS        0x90
#define HALL_UI_SETTINGS      	  0xA0
#define TEMP_UI_SETTINGS      	  0xC0
#define DEV_SETTINGS 		          0xD0
#define DIRECT_ADDRESS	          0xF0
#define DIRECT_DATA	              0xF1

/* Bit definitions */
#define ACK_RESET				          0x40
#define REDO_ATI_ALL			        0x02
#define DO_RESEED				          0x01

// RDY Pin for IQS620
#define IQS62x_RDY  			        D12

// Global defines
#define	NO_RDY					(uint8_t)99  		// No RDY pin defined

/* Setup Registers */

// PXS Settings 0 - 0x40
const static uint8_t PXS_Setup_0[] = {
		PXS_SETTINGS0_0	,
		PXS_SETTINGS0_1	,
		PXS_SETTINGS0_2	,
		PXS_SETTINGS0_3	,
		PXS_SETTINGS0_4	,
		PXS_SETTINGS0_5	,
		PXS_SETTINGS0_6	,
		PXS_SETTINGS0_7	,
		PXS_SETTINGS0_8	,
		PXS_SETTINGS0_9	,
		PXS_SETTINGS0_10,
		PXS_SETTINGS0_11,
		PXS_SETTINGS0_12,
		PXS_SETTINGS0_13,
		PXS_SETTINGS0_14,
    PXS_SETTINGS0_15
};

// PXS Settings 1 - 0x50
const static uint8_t PXS_Setup_1[] = {
		PXS_SETTINGS1_0,
		PXS_SETTINGS1_1,
		PXS_SETTINGS1_2,
		PXS_SETTINGS1_3,
		PXS_SETTINGS1_4,
		PXS_SETTINGS1_5,
		PXS_SETTINGS1_6,
		PXS_SETTINGS1_7,
		PXS_SETTINGS1_8,
		PXS_SETTINGS1_9
};


// PXS UI - 0x60
const static uint8_t PXSUi[] = {
		PXS_UI_SETTINGS_0,
		PXS_UI_SETTINGS_1,
		PXS_UI_SETTINGS_2,
		PXS_UI_SETTINGS_3,
		PXS_UI_SETTINGS_4,
    PXS_UI_SETTINGS_5,
    PXS_UI_SETTINGS_6,
    PXS_UI_SETTINGS_7,
    PXS_UI_SETTINGS_8
};


// SAR UI - 0x70
const static uint8_t SARUi[] = {
		SAR_UI_SETTINGS_0,
		SAR_UI_SETTINGS_1,
		SAR_UI_SETTINGS_2,
		SAR_UI_SETTINGS_3,
		SAR_UI_SETTINGS_4,
		SAR_UI_SETTINGS_5
};


// Metal Detect UI - 0x80
const static uint8_t MetalDetect[] = {
		METAL_DETECT_UI_SETTINGS_0,
		METAL_DETECT_UI_SETTINGS_1,
		METAL_DETECT_UI_SETTINGS_2,
		METAL_DETECT_UI_SETTINGS_3
};

// HALL - 0x90
const static uint8_t Hall_Sens[] = {
		HALL_SENSOR_SETTINGS_0,
		HALL_SENSOR_SETTINGS_1,
		HALL_SENSOR_SETTINGS_2,
		HALL_SENSOR_SETTINGS_3
};

// HALL - 0xA0
const static uint8_t Hall_UI[] = {
		HALL_UI_SETTINGS_0,
		HALL_UI_SETTINGS_1,
		HALL_UI_SETTINGS_2
};

// Dev Setup - 0xD0
const static uint8_t DevSetup[] = {
		SYSTEM_SETTINGS|REDO_ATI_ALL|DO_RESEED|ACK_RESET,
		ACTIVE_CHS,
		PMU_SETTINGS,
		REPORT_RATES_TIMINGS_0,
		REPORT_RATES_TIMINGS_1,
		REPORT_RATES_TIMINGS_2,
		REPORT_RATES_TIMINGS_3
};



/****************************************************************/
/*                                                              */
/*                  IQS620 memory adresses                      */
/*                                                              */
/****************************************************************/
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
const static uint8_t nPXS_Setup_1[] = {
		nPXS_SETTINGS1_0,
		nPXS_SETTINGS1_1,
		nPXS_SETTINGS1_2,
		nPXS_SETTINGS1_3,
		nPXS_SETTINGS1_4,
		nPXS_SETTINGS1_5,
		nPXS_SETTINGS1_6,
		nPXS_SETTINGS1_7,
		nPXS_SETTINGS1_8
};


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


//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//----------------- Setting up device to stay in active mode ---------------------------------------
//--------------------------------------------------------------------------------------------------
//                               _________NP segment all
//                               |________Enable ULP mode
//                               ||_______Disable auto modes
//                               |||______Power mode
//                               |||||
//                               |||||____NP segment rate
//                               ||||||||
//                               ||||||||
 #define PMU_SETTINGS_STARTUP  0b00100011
//--------------------------------------------------------------------------------------------------
//---------------__-- Setting up device to use channel 0 as aux touch ------------------------------
//--------------------------------------------------------------------------------------------------
//                               _________Sensor mode Ch0
//                               ||
//                               ||_______Reserved
//                               |||______Proj/Self PXS
//                               ||||_____TX select
//                               ||||||___RX select
//                               ||||||||
//                               ||||||||
 #define PXS_SETTINGS_0_0_VAL  0b00000001
//--------------------------------------------------------------------------------------------------
//----------------- Setting up device to use channel 1 as mode select ------------------------------
//--------------------------------------------------------------------------------------------------
//                               _________Sensor mode Ch1
//                               ||
//                               ||_______Reserved
//                               |||______Proj/Self PXS
//                               ||||_____TX select
//                               ||||||___RX select
//                               ||||||||
//                               ||||||||
 #define PXS_SETTINGS_0_1_VAL  0b00000010

//--------------------------------------------------------------------------------------------------
//                               _________ATI base
//                               ||
//                               ||_______ATI target
//                               ||||||||
//                               ||||||||
//                               ||||||||
//                               ||||||||
//                               ||||||||
 #define PXS_SETTINGS_2_0_VAL  0b00010000
//--------------------------------------------------------------------------------------------------
//----------------- Setting up device to use channel 1 as mode select ------------------------------
//--------------------------------------------------------------------------------------------------
//                               _________ATI base
//                               ||
//                               ||_______ATI target
//                               ||||||||
//                               ||||||||
//                               ||||||||
//                               ||||||||
//                               ||||||||
 #define PXS_SETTINGS_2_1_VAL  0b00010000
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//----------------- Setting up device to stay in active mode ---------------------------------------
//--------------------------------------------------------------------------------------------------
#define PMU_SETTINGS_STARTUP  0b00100011
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//--------- Hall Phase diffrence constants. (Default 25 degrees) -----------------------------------
//--------------------------------------------------------------------------------------------------
#define HALL_SIN_STARTUP      0x63          //    sin(degrees/180*pi)*255
#define HALL_COS_STARTUP      0xEB          //    cos(degrees/180*pi)*255
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//--------- PXS touch threshold -------------------- -----------------------------------------------
//--------------------------------------------------------------------------------------------------
#define PXS_CH1_TCH_THRES      40           //    sin(degrees/180*pi)*255
//--------------------------------------------------------------------------------------------------



//------------------------- Default  definitions ---------------------------------------------------
//--------------------------------------------------------------------------------------------------
#define MAX_ALS_VAL               8000                // Maximum value that the als sensor can sense
#define MIN_ALS_VAL               11		              // Minimum value that the als sensor can sense
#define CHANGE_MODE_RESET         100

#define PROX_MODE_DEMO            0x20
//--------------------------------------------------------------------------------------------------


//-------------------- PXS UI flag bit definitions -------------------------------------------------
//--------------------------------------------------------------------------------------------------
#define PXS_UI_FLAGS_CH0_POUT     0x01
#define PXS_UI_FLAGS_CH1_POUT     0x02
#define PXS_UI_FLAGS_CH0_TOUT     0x10
#define PXS_UI_FLAGS_CH1_TOUT     0x20

#define PXS_SETTINGS_0_0          0x40
#define PXS_SETTINGS_0_1          0x41
#define PXS_SETTINGS_1_0          0x42
#define PXS_SETTINGS_1_1          0x43
#define PXS_SETTINGS_2_0          0x44
#define PXS_SETTINGS_2_1          0x45
#define PXS_SETTINGS_3_0          0x46
#define PXS_SETTINGS_3_1          0x47
#define PXS_SETTINGS_4            0x48
#define PXS_SETTINGS_5            0x49
#define PCC_CH0		                0x4A
#define PCC_CH1		                0x4B
#define NP_MIRROR_CH0             0x4C
#define NP_MIRROR_CH1             0x4D

#define P_THR_CH0                 0x50
#define T_THR_CH0                 0x51
#define P_THR_CH1                 0x52
#define T_THR_CH1                 0x53
#define PXS_UI_HALT_TIME          0x54

//#define METAL_UI_SETTINGS       0x60
#define METAL_UI_FHALT	          0x61
#define METAL_UI_THR_P	          0x62
#define METAL_UI_THR_T            0x63

#define ALS_SETTINGS_0	          0x70
#define ALS_SETTINGS_1	          0x71
#define ALS_FILTER_SPEED          0x72
#define NP_MIRROR_CH3_CH4         0x73

#define ALS_DARK_THR              0x80
#define ALS_LIGHT_THR             0x81
#define ALS_TO_LUX_DIV            0x82

#define HALL_SETTINGS_0           0x90
#define HALL_SETTINGS_1           0x91
#define PCC_CH5_CH6               0x92
#define NP_MIRROR_CH5_CH6         0x93

#define SYSTEM_SETTINGS_0         0xD0
#define ALS_FLAGS                 0x16
#define DIRECT_ADDRESS	          0xF0
#define DIRECT_DATA	              0xF1

//--------------------------------------------------------------------------------------------------
//-------------------- ALS UI flag bit definitions -------------------------------------------------
#define ALS_light_dark            0x80

/****************************************************************/
/*                                                              */
/*                  IQS622 memory adresses                      */
/*                                                              */
/****************************************************************/
//--------------------------------------------------------------------------------------------------
//-------------------- IR UI output register definitions -------------------------------------------
#define IR_OUTPUT_LOW             0x17
#define IR_OUTPUT_HIGH			      0x18

//--------------------------------------------------------------------------------------------------
/****************************************************************/
/*                                                              */
/*                  IQS625 memory adresses                      */
/*                                                              */
/****************************************************************/
//--------------------------------------------------------------------------------------------------
#define HALL_UI_FLAGS             0x14

#define PXS_CH0_THRES             0x51
#define PXS_CH1_THRES             0x53

#define HALL_CH2_3                0x72
#define HALL_CH4_5                0x73
#define INTERVAL_UI_DIV           0x7D
#define WHEEL_OFFSET_L            0x7E
#define WHEEL_OFFSET_H            0x7F

#define HALL_DEG_LSB              0x80
#define HALL_DEG_MSB              0x81
#define HALL_DEG_DIFF             0x8E
#define HALL_SIN                  0x9D
#define HALL_COS                  0xC9

#endif /* __IQS62x_H__ */
