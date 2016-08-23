#include "Includes.h"

static u32 timer_tick_cnt = 0;
static vu8 timer_input_single_state = 0;
static vu8 timer_input_single_valid = 0;

/* Time interval 0.5ms */
static void InitTime2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	TIM_DeInit(TIM2);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitStructure.TIM_Prescaler = 999;

	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInitStructure.TIM_Period = 25;

	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	TIM_ARRPreloadConfig(TIM2, DISABLE);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		if ((!get_input_single()) && (timer_input_single_state)) {
			timer_input_single_state = 0;
			timer_input_single_valid = 1;
		} else if ((get_input_single()) && (!timer_input_single_state)) {
			timer_input_single_state = 1;
			timer_input_single_valid = 1;
		}

		if (timer_tick_cnt != 0)
		{
			timer_tick_cnt--;
		}
	}

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void delay(u32 delay_hms)
{
	timer_tick_cnt = delay_hms;

	while (timer_tick_cnt != 0);
}

void timer_init(void)
{
	InitTime2();
	timer_input_single_state = get_input_single();
}

u8 get_adc_switch_state(void)
{
	return timer_input_single_valid;
}

void clear_adc_switch_state(void)
{
	timer_input_single_valid = 0;
}

