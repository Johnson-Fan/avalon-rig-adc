#include "Includes.h"

MAX34409_ADC_TypeDef max34409_data;

void read_max34409_adc_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, ADC1_CMD, &max34409_data.adc1);
	i2c_read_single_byte(MAX34409_ADDR, ADC2_CMD, &max34409_data.adc2);
	i2c_read_single_byte(MAX34409_ADDR, ADC3_CMD, &max34409_data.adc3);
	i2c_read_single_byte(MAX34409_ADDR, ADC4_CMD, &max34409_data.adc4);
}

static void read_max34409_oct_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, OCT1_CMD, &max34409_data.oct1);
	i2c_read_single_byte(MAX34409_ADDR, OCT2_CMD, &max34409_data.oct2);
	i2c_read_single_byte(MAX34409_ADDR, OCT3_CMD, &max34409_data.oct3);
	i2c_read_single_byte(MAX34409_ADDR, OCT4_CMD, &max34409_data.oct4);
}

static void write_max34409_oct_data(void)
{
	i2c_write_single_byte(MAX34409_ADDR, OCT1_CMD, &max34409_data.oct1);
	i2c_write_single_byte(MAX34409_ADDR, OCT2_CMD, &max34409_data.oct2);
	i2c_write_single_byte(MAX34409_ADDR, OCT3_CMD, &max34409_data.oct3);
	i2c_write_single_byte(MAX34409_ADDR, OCT4_CMD, &max34409_data.oct4);
}

static void read_max34409_status_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, STATUS_CMD, &max34409_data.status);
}

static void write_max34409_status_data(void)
{
	i2c_write_single_byte(MAX34409_ADDR, STATUS_CMD, &max34409_data.status);
}

static void read_max34409_control_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, CONTROL_CMD, &max34409_data.control);
}

static void write_max34409_control_data(void)
{
	i2c_write_single_byte(MAX34409_ADDR, CONTROL_CMD, &max34409_data.control);
}

static void read_max34409_ocdelay_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, OCDELAY_CMD, &max34409_data.ocdelay);
}

static void write_max34409_ocdelay_data(void)
{
	i2c_write_single_byte(MAX34409_ADDR, OCDELAY_CMD, &max34409_data.ocdelay);
}

static void read_max34409_sddelay_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, SDDELAY_CMD, &max34409_data.sddelay);
}

static void write_max34409_sddelay_data(void)
{
	i2c_write_single_byte(MAX34409_ADDR, SDDELAY_CMD, &max34409_data.sddelay);
}

static void read_max34409_did_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, DID_CMD, &max34409_data.did);
}

static void read_max34409_dcyy_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, DCYY_CMD, &max34409_data.dcyy);
}

static void read_max34409_dcww_data(void)
{
	i2c_read_single_byte(MAX34409_ADDR, DCWW_CMD, &max34409_data.dcww);
}

