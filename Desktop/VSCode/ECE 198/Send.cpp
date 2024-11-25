#include "mbed.h"
#include <string>

// Configure UART pins for HC-05
Serial bt(D1, D0); // D1 is TX, D0 is RX for HC-05
DigitalOut led(LED1); // Onboard LED for feedback

// Function to generate a dynamic message
std::string generateMessage() {
    static int counter = 0; // Example: Dynamic counter-based message
    counter++;
    return "Dynamic Message: Counter = " + std::to_string(counter);
}

int main() {
    bt.baud(9600); // Set baud rate for communication with HC-05

    while (true) {
        std::string message = generateMessage(); // Generate a message dynamically
        bt.printf("%s\n", message.c_str()); // Send the message over Bluetooth
        led = !led; // Toggle LED to indicate message sent
        wait(1); // Wait for 1 second before sending the next message
    }
}
