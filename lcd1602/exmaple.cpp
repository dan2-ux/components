#include "lcd1602.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

extern "C" void app_main(void)
{
    // Create LCD object
    LCD1602_Handle *lcd = LCD1602_create(
        GPIO_NUM_21, // RS
        GPIO_NUM_22, // EN
        GPIO_NUM_18, // D4
        GPIO_NUM_19, // D5
        GPIO_NUM_23, // D6
        GPIO_NUM_5   // D7
    );

    // Initialize LCD
    LCD1602_init(lcd);

    // Print first line
    LCD1602_set_cursor(lcd, 0, 0);
    LCD1602_print(lcd, "Hello World");

    // Print second line
    LCD1602_set_cursor(lcd, 1, 0);
    LCD1602_print(lcd, "ESP32 LCD");

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}