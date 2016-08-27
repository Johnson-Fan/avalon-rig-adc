#include "Includes.h"

static u16 adc_buf[ADC_COUNT][SAMPLE_COUNT];
static f32 vol_buf[ADC_COUNT];
static u16 adc_avg[ADC_COUNT];
static u8  adc_finish = 0;

u16 get_adc_avg(u16 *data, u8 len)
{
	u16 sum = 0;
	u16 max = 0;
	u16 min = 0;
	u16 i = 0;

	if (len < 3)
		return 0;

	max = *data;
	min = *data;
	for (i = 0; i < len; i++) {
		max = max > *data ? max : *data;
		min = min < *data ? min : *data;
		sum += *data;
		data++;
	}

	return ((sum - max - min) / (len -2));
}

int main(void)
{
	u8 i = 0;

	gpio_init();
	uart_init();
	i2c_init();
	adc_init();
	timer_init();

	while (1)
	{
		if (get_adc_switch_state()) {
			clear_adc_switch_state();
			led_green_off();
			led_yellow_on();

			adc_finish = 0;

			for (i = 0; i < SAMPLE_COUNT; i++) {
				read_max34409_adc_data();
				adc_buf[0][i] = max34409_data.adc1;
				adc_buf[1][i] = max34409_data.adc2;
				adc_buf[2][i] = max34409_data.adc3;
				adc_buf[3][i] = max34409_data.adc4;
				adc_buf[4][i] = SamplingData.adc1;
				adc_buf[5][i] = SamplingData.adc2;
				delay(4);
			}

			for (i = 0; i < 4; i++) {
				adc_avg[i] = get_adc_avg(adc_buf[i], SAMPLE_COUNT);
				vol_buf[i] = CURRENT_STD_VALUE /256.0 * (f32)adc_avg[i];
			}

			adc_avg[4] = get_adc_avg(adc_buf[4], SAMPLE_COUNT);
			adc_avg[5] = get_adc_avg(adc_buf[5], SAMPLE_COUNT);

			if (adc_avg[4] > adc_avg[5])
				vol_buf[4] = (adc_avg[4] - adc_avg[5]) * 3.3 / (4096.0 * 0.066);
			else
				vol_buf[4] = (adc_avg[5] - adc_avg[4]) * 3.3 / (4096.0 * 0.066);

			printf("VDDIOA: %.00f\r\n", vol_buf[0]);
			printf("VDDIOB: %.00f\r\n", vol_buf[1]);
			printf("VDDPLL: %.00f\r\n", vol_buf[2]);
			printf("VDDTOP: %.00f\r\n", vol_buf[3]);
			printf("VIOUT:  %.00f\r\n", vol_buf[4]);

			adc_finish = 1;
			led_yellow_off();
		}

		if (adc_finish) {
			if (vol_buf[0] >= IO_HL)
				led_green_blink();
			else if (vol_buf[0] > 0)
				led_green_on();

			if (vol_buf[1] >= IO_HL)
				led_green_blink();
			else if (vol_buf[1] > 0)
				led_green_on();

			if (vol_buf[2] >= PLL_HL)
				led_green_blink();
			else if (vol_buf[2] > 0)
				led_green_on();

			if (vol_buf[3] >= IO_HL)
				led_green_blink();
			else if (vol_buf[3] > 0)
				led_green_on();

			if (vol_buf[4] >= CORE_HL)
				led_green_blink();
			else if (vol_buf[4] > 0)
				led_green_on();
		}
	}
}

