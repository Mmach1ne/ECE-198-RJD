#include "main.h"
#include "i2c.h"  // Include the HAL I2C header

// I2C address for the LCD (adjust if different for your device)
#define LCD_I2C_ADDRESS 0x4E // Check your LCD datasheet for the correct address

// LCD Commands
#define LCD_CMD_CLEAR_DISPLAY 0x01
#define LCD_CMD_RETURN_HOME 0x02
#define LCD_CMD_ENTRY_MODE 0x06
#define LCD_CMD_DISPLAY_ON 0x0C
#define LCD_CMD_DISPLAY_OFF 0x08
#define LCD_CMD_SET_CURSOR 0x80

// Function prototypes
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Init();
void LCD_Print(const char* str);

int main(void) {
    // Initialize the HAL Library
    HAL_Init();

    // System clock configuration (adjust as needed for your board)
    SystemClock_Config();

    // Initialize the I2C peripheral
    MX_I2C1_Init();

    // Initialize the LCD
    LCD_Init();

    // Display a message
    LCD_Print("Hello, World!");
    HAL_Delay(2000);

    // Clear display and print another message
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
    HAL_Delay(2);
    LCD_Print("STM32 + LCD2004");

    while (1) {
        // Main loop
    }
}

void LCD_Init() {
    HAL_Delay(50); // Power-on initialization delay

    // Send initialization commands to the LCD
    LCD_SendCommand(0x30); // Wake up
    HAL_Delay(5);
    LCD_SendCommand(0x30); // Wake up
    HAL_Delay(1);
    LCD_SendCommand(0x30); // Wake up
    HAL_Delay(10);
    LCD_SendCommand(0x20); // 4-bit mode
    HAL_Delay(1);

    // Configure LCD
    LCD_SendCommand(0x28); // Function set: 2-line, 5x8 dots
    LCD_SendCommand(LCD_CMD_DISPLAY_ON); // Display ON
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY); // Clear display
    LCD_SendCommand(LCD_CMD_ENTRY_MODE); // Entry mode set
}

void LCD_SendCommand(uint8_t cmd) {
    uint8_t data[4];

    // Split the command into two 4-bit nibbles
    data[0] = (cmd & 0xF0) | 0x08;  // Upper nibble + backlight
    data[1] = data[0] & ~0x04;     // Clear enable
    data[2] = (cmd << 4) | 0x08;   // Lower nibble + backlight
    data[3] = data[2] & ~0x04;     // Clear enable

    // Send data to LCD over I2C
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDRESS, data, 4, HAL_MAX_DELAY);
}

void LCD_SendData(uint8_t data) {
    uint8_t data_arr[4];

    // Split the data into two 4-bit nibbles
    data_arr[0] = (data & 0xF0) | 0x0D;  // Upper nibble + RS + backlight
    data_arr[1] = data_arr[0] & ~0x04;  // Clear enable
    data_arr[2] = (data << 4) | 0x0D;   // Lower nibble + RS + backlight
    data_arr[3] = data_arr[2] & ~0x04;  // Clear enable

    // Send data to LCD over I2C
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDRESS, data_arr, 4, HAL_MAX_DELAY);
}

void LCD_Print(const char* str) {
    while (*str) {
        LCD_SendData((uint8_t)*str++);
    }
}
