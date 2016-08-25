#ifndef __GPIO_H
#define __GPIO_H

#define LED_RED     1
#define LED_GREEN   2
#define LED_YELLOW  3

#define LED_ON      1
#define LED_OFF     0

extern void gpio_init(void);
extern void set_led(u8 led_type, u8 led_state);
extern u8 get_input_single(void);
extern void led_green_blink(void);
extern void led_green_on(void);
extern void led_green_off(void);

#endif

