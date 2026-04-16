/******************************************************************************
* Copyright (C) 2026 by Mauricio Vela Chavira - CETYS Universidad
*****************************************************************************/
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdint.h>

typedef enum {
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED = 1
} button_state_t;

void button_init(void);
button_state_t button_get_state(void);

#endif /* __BUTTON_H__ */