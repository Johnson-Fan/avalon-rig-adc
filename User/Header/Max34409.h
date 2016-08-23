#ifndef __MAX34409_H
#define __MAX34409_H

#define MAX34409_ADDR   0x3C

#define STATUS_CMD      0x00
#define CONTROL_CMD     0x01
#define OCDELAY_CMD     0x02
#define SDDELAY_CMD     0x03

#define ADC1_CMD        0x04
#define ADC2_CMD        0x05
#define ADC3_CMD        0x06
#define ADC4_CMD        0x07

#define OCT1_CMD        0x08
#define OCT2_CMD        0x09
#define OCT3_CMD        0x0A
#define OCT4_CMD        0x0B

#define DID_CMD         0x0C
#define DCYY_CMD        0x0D
#define DCWW_CMD        0x0E

typedef struct
{
	vu8 status;
	vu8 control;
	vu8 ocdelay;
	vu8 sddelay;

	vu8 adc1;
	vu8 adc2;
	vu8 adc3;
	vu8 adc4;

	vu8 oct1;
	vu8 oct2;
	vu8 oct3;
	vu8 oct4;

	vu8 did;
	vu8 dcyy;
	vu8 dcww;
} MAX34409_ADC_TypeDef;

extern MAX34409_ADC_TypeDef max34409_data;

extern void read_max34409_adc_data(void);

#endif

