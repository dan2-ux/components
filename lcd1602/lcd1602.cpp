#include "lcd1602.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"
#include "esp_rom_sys.h"

// ================== C++ CLASS ==================
namespace LCD1602
{
    class Setup
    {
    public:
        Setup(gpio_num_t rs,
              gpio_num_t en,
              gpio_num_t d4,
              gpio_num_t d5,
              gpio_num_t d6,
              gpio_num_t d7)
            : rs(rs), en(en), d4(d4), d5(d5), d6(d6), d7(d7) {}

        void Init()
        {
            vTaskDelay(pdMS_TO_TICKS(50));

            gpio_reset_pin(rs);
            gpio_reset_pin(en);
            gpio_reset_pin(d4);
            gpio_reset_pin(d5);
            gpio_reset_pin(d6);
            gpio_reset_pin(d7);

            gpio_set_direction(rs, GPIO_MODE_OUTPUT);
            gpio_set_direction(en, GPIO_MODE_OUTPUT);
            gpio_set_direction(d4, GPIO_MODE_OUTPUT);
            gpio_set_direction(d5, GPIO_MODE_OUTPUT);
            gpio_set_direction(d6, GPIO_MODE_OUTPUT);
            gpio_set_direction(d7, GPIO_MODE_OUTPUT);

            sendNibble(0, 0x3);
            vTaskDelay(pdMS_TO_TICKS(5));
            sendNibble(0, 0x3);
            vTaskDelay(pdMS_TO_TICKS(5));
            sendNibble(0, 0x3);
            vTaskDelay(pdMS_TO_TICKS(5));
            sendNibble(0, 0x2);
            vTaskDelay(pdMS_TO_TICKS(5));

            sendByte(0, 0x28);
            vTaskDelay(pdMS_TO_TICKS(2));

            sendByte(0, 0x0C);
            vTaskDelay(pdMS_TO_TICKS(2));

            sendByte(0, 0x06);
            vTaskDelay(pdMS_TO_TICKS(2));

            Clear();
        }

        void Clear()
        {
            sendByte(0, 0x01);
            vTaskDelay(pdMS_TO_TICKS(2));
        }

        void Print(const char *data)
        {
            while (*data)
            {
                sendByte(1, *data++);
            }
        }

        void SetCursor(uint8_t row, uint8_t col)
        {
            if (row > 1)
                row = 1;
            if (col > 15)
                col = 15;

            uint8_t offsets[] = {0x00, 0x40};
            sendByte(0, 0x80 | (offsets[row] + col));
        }

    private:
        gpio_num_t rs, en, d4, d5, d6, d7;

        void pulseEnable()
        {
            gpio_set_level(en, 0);
            esp_rom_delay_us(1);

            gpio_set_level(en, 1);
            esp_rom_delay_us(1);

            gpio_set_level(en, 0);
            esp_rom_delay_us(100);
        }

        void sendNibble(uint8_t rs_state, uint8_t data)
        {
            gpio_set_level(rs, rs_state);

            gpio_set_level(d4, (data >> 0) & 0x01);
            gpio_set_level(d5, (data >> 1) & 0x01);
            gpio_set_level(d6, (data >> 2) & 0x01);
            gpio_set_level(d7, (data >> 3) & 0x01);

            pulseEnable();
        }

        void sendByte(uint8_t rs_state, uint8_t data)
        {
            sendNibble(rs_state, data >> 4);
            sendNibble(rs_state, data & 0x0F);
        }
    };
}

// ================== C WRAPPER ==================

// Define the hidden struct
struct LCD1602_Handle
{
    LCD1602::Setup *obj;
};

// Create instance
LCD1602_Handle *LCD1602_create(gpio_num_t rs,
                               gpio_num_t en,
                               gpio_num_t d4,
                               gpio_num_t d5,
                               gpio_num_t d6,
                               gpio_num_t d7)
{
    LCD1602_Handle *handle = new LCD1602_Handle;
    handle->obj = new LCD1602::Setup(rs, en, d4, d5, d6, d7);
    return handle;
}

// Wrapper functions
void LCD1602_init(LCD1602_Handle *lcd)
{
    lcd->obj->Init();
}

void LCD1602_clear(LCD1602_Handle *lcd)
{
    lcd->obj->Clear();
}

void LCD1602_print(LCD1602_Handle *lcd, const char *text)
{
    lcd->obj->Print(text);
}

void LCD1602_set_cursor(LCD1602_Handle *lcd, uint8_t row, uint8_t col)
{
    lcd->obj->SetCursor(row, col);
}