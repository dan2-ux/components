#pragma once

#include "driver/gpio.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // Opaque handle (user cannot see inside)
    typedef struct LCD1602_Handle LCD1602_Handle;

    // Constructor
    LCD1602_Handle *LCD1602_create(gpio_num_t rs,
                                   gpio_num_t en,
                                   gpio_num_t d4,
                                   gpio_num_t d5,
                                   gpio_num_t d6,
                                   gpio_num_t d7);

    // Functions
    void LCD1602_init(LCD1602_Handle *lcd);
    void LCD1602_clear(LCD1602_Handle *lcd);
    void LCD1602_print(LCD1602_Handle *lcd, const char *text);
    void LCD1602_set_cursor(LCD1602_Handle *lcd, uint8_t row, uint8_t col);

#ifdef __cplusplus
}
#endif