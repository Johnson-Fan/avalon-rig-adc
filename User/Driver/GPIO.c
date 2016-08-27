#include "Includes.h"

void gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void set_led(u8 led_type, u8 led_state)
{
	switch (led_type) {
	case LED_YELLOW:
		if (led_state == LED_ON)
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		else
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		break;
	case LED_RED:
		if (led_state == LED_ON)
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
		else
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		break;
	case LED_GREEN:
		if (led_state == LED_ON)
			GPIO_SetBits(GPIOB, GPIO_Pin_2);
		else
			GPIO_ResetBits(GPIOB, GPIO_Pin_2);
		break;
	default:
		break;
	}
}

u8 get_input_single(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10);
}

void led_green_blink(void)
{
	if (get_led_blink_state())
		set_led(LED_GREEN, LED_ON);
	else
		set_led(LED_GREEN, LED_OFF);
}

void led_green_on(void)
{
	set_led(LED_GREEN, LED_ON);
}

void led_green_off(void)
{
	set_led(LED_GREEN, LED_OFF);
}

void led_yellow_on(void)
{
	set_led(LED_YELLOW, LED_ON);
}

void led_yellow_off(void)
{
	set_led(LED_YELLOW, LED_OFF);
}

void led_red_on(void)
{
	set_led(LED_RED, LED_ON);
}

void led_red_off(void)
{
	set_led(LED_RED, LED_OFF);
}

