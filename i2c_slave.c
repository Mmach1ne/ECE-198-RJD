/*
 * i2c_slave.c
 *
 *  Created on: Nov 26, 2024
 *      Author: joannemoon
 */

#include "main.h"
#include "i2c_slave.h"
#include "i2c-lcd.h"

extern I2C_HandleTypeDef hi2c1;

#define RxSIZE 50
char RxData[RxSIZE];     // Buffer to store received data

/**
  * @brief I2C Address Match Callback
  * This function is triggered when the I2C Slave receives data from the Master.
  */
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode) {
    if (hi2c->Instance == I2C1) { // Ensure it's the correct I2C instance
        if (TransferDirection == I2C_DIRECTION_RECEIVE) {
            // Set up to receive data
            HAL_I2C_Slave_Sequential_Receive_IT(hi2c, (uint8_t *)RxData, RxSIZE, I2C_FIRST_AND_LAST_FRAME);
        }
    }
}

/**
  * @brief I2C Slave Receive Complete Callback
  * This function is called when the data has been successfully received.
  */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C3) { // Ensure it's the correct I2C instance
        // Clear the LCD and display the received string
        lcd_clear();
        lcd_send_string(RxData); // Display the received string on the LCD
        lcd_send_string("Test LCD22");

        // Re-enable listening mode for future transmissions
        HAL_I2C_EnableListen_IT(hi2c);
    }
}

/**
  * @brief I2C Error Callback
  * Handle any I2C errors.
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) { // Ensure it's the correct I2C instance
        // Handle error (optional: display an error message on the LCD)
        lcd_clear();
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

        lcd_send_string("I2C Error!");

        // Re-enable listening mode after error handling
        HAL_I2C_EnableListen_IT(hi2c);
    }
}

/**
  * @brief I2C Listen Complete Callback
  * Handle the completion of the I2C listening operation.
  */
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) { // Ensure it's the correct I2C instance
        // Restart listening for future transmissions
        HAL_I2C_EnableListen_IT(hi2c);
    }
}
