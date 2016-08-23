#include "Includes.h"

int main(void)
{
	gpio_init();
	uart_init();
	i2c_init();
	adc_init();
	timer_init();

	while (1)
	{
		;
	}
}
