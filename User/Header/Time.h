#ifndef __TIME_H
#define __TIME_H

#define TIMER_BLINK_CNT_MAX 1000

extern void timer_init(void);

extern void delay(u32 delay_hms);
extern u8 get_adc_switch_state(void);
extern void clear_adc_switch_state(void);
extern u8 get_led_blink_state(void);

#endif

