#ifndef __TIME_H
#define __TIME_H

extern void timer_init(void);

extern void delay(u32 delay_hms);
extern u8 get_adc_switch_state(void);
extern void clear_adc_switch_state(void);

#endif

