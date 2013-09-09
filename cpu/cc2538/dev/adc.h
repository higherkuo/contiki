#ifndef ADC_H_
#define ADC_H_


/* Defines for the different resolutions */
#define ADC_7_BIT           0x00000000 //  64 decimation rate ( 7 bits ENOB)
#define ADC_9_BIT           0x00000010 // 128 decimation rate ( 9 bits ENOB)
#define ADC_10_BIT          0x00000020 // 256 decimation rate (10 bits ENOB)
#define ADC_12_BIT          0x00000030 // 512 decimation rate (12 bits ENOB)

/* Bitshifts for the resulting value */
#define ADC_7_BIT_RSHIFT        9 // Mask for getting data( 7 bits ENOB)
#define ADC_9_BIT_RSHIFT        7 // Mask for getting data( 9 bits ENOB)
#define ADC_10_BIT_RSHIFT       6 // Mask for getting data(10 bits ENOB)
#define ADC_12_BIT_RSHIFT       4 // Mask for getting data(12 bits ENOB)

/* Defines for the different reference voltage levels */
#define ADC_REF_INTERNAL    0x00000000 // Internal reference
#define ADC_REF_EXT_AIN7    0x00000040 // External reference on AIN7 pin
#define ADC_REF_AVDD5       0x00000080 // AVDD5 pin
#define ADC_REF_EXT_AIN67   0x000000c0 // External reference on AIN6-AIN7
                                          // differential input pins

/* Defines for the various channels */
#define ADC_CHANNEL_AIN0       0x00000000  // Single ended Pad PA0
#define ADC_CHANNEL_AIN1       0x00000001  // Single ended Pad PA1
#define ADC_CHANNEL_AIN2       0x00000002  // Single ended Pad PA2
#define ADC_CHANNEL_AIN3       0x00000003  // Single ended Pad PA3
#define ADC_CHANNEL_AIN4       0x00000004  // Single ended Pad PA4
#define ADC_CHANNEL_AIN5       0x00000005  // Single ended Pad PA5
#define ADC_CHANNEL_AIN6       0x00000006  // Single ended Pad PA6
#define ADC_CHANNEL_AIN7       0x00000007  // Single ended Pad PA7
#define ADC_CHANNEL_AIN01      0x00000008  // Differential Pads PA0-PA1
#define ADC_CHANNEL_AIN23      0x00000008  // Differential Pads PA2-PA3
#define ADC_CHANNEL_AIN45      0x00000008  // Differential Pads PA4-PA5
#define ADC_CHANNEL_AIN67      0x00000008  // Differential Pads PA6-PA7
#define ADC_CHANNEL_GND        0x0000000c  // Ground
#define ADC_CHANNEL_TEMP_SENS  0x0000000e  // On-chip temperature sensor
#define ADC_CHANNEL_VDD        0x0000000f  // Vdd/3

/* Register locations */
#define ADC_ADCCON1         0x400D7000
#define ADC_ADCCON2         0x400D7004
#define ADC_ADCCON3         0x400D7008
#define ADC_ADCL            0x400D700C
#define ADC_ADCH            0x400D7010
#define ADC_RNDL            0x400D7014
#define ADC_RNDH            0x400D7018
#define ADC_CMPCTL          0x400D7024

/* Bitfields and masks */
#define ADC_ADCCON1_EOC     0x00000080
#define ADC_ADCCON1_EOC_M   0x00000080
#define ADC_ADCCON1_EOC_S   7
#define ADC_ADCCON1_ST      0x00000040
#define ADC_ADCCON1_ST_M    0x00000040
#define ADC_ADCCON1_ST_S    6
#define ADC_ADCCON1_STSEL_M 0x00000030
#define ADC_ADCCON1_STSEL_S 4
#define ADC_ADCCON1_RCTRL_M 0x0000000C
#define ADC_ADCCON1_RCTRL_S 2

#define ADC_ADCCON2_SREF_M  0x000000C0
#define ADC_ADCCON2_SREF_S  6
#define ADC_ADCCON2_SDIV_M  0x00000030
#define ADC_ADCCON2_SDIV_S  4
#define ADC_ADCCON2_SCH_M   0x0000000F
#define ADC_ADCCON2_SCH_S   0

#define ADC_ADCCON3_EREF_M  0x000000C0
#define ADC_ADCCON3_EREF_S  6
#define ADC_ADCCON3_EDIV_M  0x00000030
#define ADC_ADCCON3_EDIV_S  4
#define ADC_ADCCON3_ECH_M   0x0000000F
#define ADC_ADCCON3_ECH_S   0

#define ADC_ADCL_ADC_M      0x000000FC
#define ADC_ADCL_ADC_S      2

#define ADC_ADCH_ADC_M      0x000000FF
#define ADC_ADCH_ADC_S      0

#define ADC_RNDL_RNDL_M     0x000000FF
#define ADC_RNDL_RNDL_S     0

#define ADC_RNDH_RNDH_M     0x000000FF
#define ADC_RNDH_RNDH_S     0

#define ADC_CMPCTL_EN       0x00000002
#define ADC_CMPCTL_EN_M     0x00000002
#define ADC_CMPCTL_EN_S     1
#define ADC_CMPCTL_OUTPUT   0x00000001
#define ADC_CMPCTL_OUTPUT_M 0x00000001
#define ADC_CMPCTL_OUTPUT_S 0


int adc_configure_single(uint32_t resolution, uint32_t reference_voltage);
uint16_t adc_sample_single(uint32_t channel);

#endif
