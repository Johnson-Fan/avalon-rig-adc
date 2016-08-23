#ifndef __ADC_H
#define __ADC_H

#define ADC1_COUNT           4
#define ADC1_DR_Address      ((u32)0x4001244C)

typedef struct
{
	vu16 adc1;
	vu16 adc2;
	vu16 adc3;
	vu16 adc4;
} SamplingDataTypeDef;

extern SamplingDataTypeDef SamplingData;

extern void adc_init(void);

#endif

