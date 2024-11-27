#include "mbed.h"
#include <string>

// Configure UART pins for HC-05
Serial bt(D1, D0); // D1 is TX, D0 is RX for HC-05
DigitalOut led(LED1); // Onboard LED for feedback

// Buffer for incoming messages
char buffer[100];

int main() {
    bt.baud(9600); // Set baud rate for communication with HC-05

    while (true) {
        if (bt.readable()) { // Check if there’s data to read
            bt.gets(buffer, sizeof(buffer)); // Read the incoming message
            printf("Received: %s\n", buffer); // Output the received message
            led = !led; // Toggle LED to indicate a message was received
        }
    }
}