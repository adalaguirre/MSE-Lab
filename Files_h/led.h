/******************************************************************************
* Copyright (C) 2026 by Mauricio Vela Chavira - CETYS Universidad
*****************************************************************************/
#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif /* __LED_H__ */