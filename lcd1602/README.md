# Welcome to LCD 16x02 Components

I created a repository containing the components needed for the ESP32 to work with the LCD 16x02.

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/19d10dde-bb40-4f7f-af51-232489787d73" />


## How the LCD 16x02 Works

The LCD 16x02 uses a built-in HD44780 controller to manipulate liquid crystals and polarized light. By controlling whether light can pass through or is blocked, it creates characters and symbols on the screen.

Since the LCD 16x02 has multiple pins, it’s helpful to organize them:

- **Command and control pins:** Used to send instructions to the LCD.

- **Data pins:** Used to send data to display characters.

- **Power pins:** Connect to +5V or GND as required.

This structure ensures proper operation and simplifies wiring with the ESP32.

Pin Ground:

| Commanding Ground | Data Pin Ground |
|-------------------|-----------------|
|        RS         |       D0        |
|        RW         |       D1        |
|      ENABLE       |       D2        |
|                   |       D3        |
|                   |       D4        |
|                   |       D5        |
|                   |       D6        |
|                   |       D7        |


**RS** (Register Select): This pin determines the LCD mode. Setting RS to 0 selects command mode, which allows you to control the LCD, such as choosing a row or configuring settings. Setting RS to 1 selects data mode, enabling you to write characters directly to the LCD.

**RW** (Read/Write): This pin controls the data direction. Setting RW to 0 allows writing to the LCD, while 1 enables reading the current content displayed on the LCD. 

**Enable** (E): The Enable pin is required to commit any input to the LCD. Without triggering this pin, the LCD will not respond to commands or data.

**Data Pins** (D0 – D7): These pins are used to send data or commands to the LCD.

Special Note on LCD Modes: LCDs support two modes for data transfer:

- 8-bit mode: Uses all eight data pins (D0–D7) to send data.

- 4-bit mode: Uses only the upper four data pins (D4–D7), simplifying wiring while still allowing full functionality.

Other pins like VDD and Anode connect to +5, while VSS, V0, Cathode connect to GND.

** Recommend Wiring:

| LCD Pin | Function        | ESP32 GPIO    |
| ------- | --------------- | ------------- |
| RS      | Register Select | `GPIO_NUM_4`  |
| ENABLE  | Enable (E)      | `GPIO_NUM_5`  |
| D4      | Data bit 4      | `GPIO_NUM_18` |
| D5      | Data bit 5      | `GPIO_NUM_19` |
| D6      | Data bit 6      | `GPIO_NUM_21` |
| D7      | Data bit 7      | `GPIO_NUM_22` |

## Warning: this component doesn't support reading LCD function. Therefore, RW should be connect to GND to make the LCD in the writing mode continuously.
