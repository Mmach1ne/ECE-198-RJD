#include "mbed.h"

// Define the rows and columns for the keypad
#define ROWS 4
#define COLS 4

DigitalOut rowPins[ROWS] = {
    DigitalOut(PA_0),  // Replace with your row pins
    DigitalOut(PA_1),
    DigitalOut(PA_2),
    DigitalOut(PA_3)
};

DigitalIn columnPins[COLS] = {
    DigitalIn(PB_0),   // Replace with your column pins
    DigitalIn(PB_1),
    DigitalIn(PB_2),
    DigitalIn(PB_3)
};

// Keypad layout
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Function to scan the keypad
char scanKeypad() {
    for (int row = 0; row < ROWS; row++) {
        // Set all rows low except the current one
        for (int r = 0; r < ROWS; r++) {
            rowPins[r] = (r == row) ? 0 : 1;
        }

        // Read the columns
        for (int col = 0; col < COLS; col++) {
            if (columnPins[col].read() == 0) { // Active low detection
                wait_us(20); // Debounce delay
                if (columnPins[col].read() == 0) { // Confirm the press
                    return keys[row][col];
                }
            }
        }
    }

    return '\0'; // No key pressed
}

int main() {
    printf("Keypad Test\n");

    while (true) {
        char key = scanKeypad();
        if (key != '\0') {
            printf("Key Pressed: %c\n", key);
            wait_us(300000); // Prevent multiple detections
        }
    }
}
