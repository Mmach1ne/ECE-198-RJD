#include "mbed.h"


#define ROWS 4
#define COLS 4

DigitalOut rowPins[ROWS] = {
    DigitalOut(PA_0),  
    DigitalOut(PA_1),
    DigitalOut(PA_2),
    DigitalOut(PA_3)
};

DigitalIn columnPins[COLS] = {
    DigitalIn(PB_0),   
    DigitalIn(PB_1),
    DigitalIn(PB_2),
    DigitalIn(PB_3)
};


char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


char scanKeypad() {
    for (int row = 0; row < ROWS; row++) {
        for (int r = 0; r < ROWS; r++) {
            rowPins[r] = (r == row) ? 0 : 1;
        }


        for (int col = 0; col < COLS; col++) {
            if (columnPins[col].read() == 0) { 
                wait_us(20); 
                if (columnPins[col].read() == 0) { 
                    return keys[row][col];
                }
            }
        }
    }

    return '\0'; 
}

int main() {
    printf("Keypad Test\n");

    while (true) {
        char key = scanKeypad();
        if (key != '\0') {
            printf("Key Pressed: %c\n", key);
            wait_us(300000); 
        }
    }
}