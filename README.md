# Lab 6: Flow and Error Control in Communication


## 1. Introduction
This lab focuses on implementing **Flow Control** and **Error Control**, which are the primary responsibilities of the data link layer. 
* **Flow Control**: Coordinates the amount of data sent before receiving an acknowledgment to prevent buffer overflow.
* **Error Control**: Involves error detection and re-transmission, often referred to as **Automatic Repeat Request (ARQ)**.

The objective is to establish UART communication between an **STM32F103C6** and a simulated terminal.

---

## 2. System Configuration
### 2.1 Hardware Simulation (Proteus)
* **Microcontroller**: STM32F103C6.
* **Virtual Terminal**: Set to 9600 baud, 8 data bits, no parity, and 1 stop bit.
* **Sensor Simulation**: A variable resistor (RV2 - POT-HG) connected to an OPAMP (U3) configured as a voltage follower.
* **ADC Input**: The output of the OPAMP is connected to pin **PA0**.
* **LED**: Connected to pin **PA5** for blinky status.

### 2.2 Peripheral Settings
* **UART (USART2)**: Configured in Asynchronous mode with 9600 bits/s.
* **ADC1**: Configured to read voltage signals from the simulated sensor at PA0.
* **Interrupts**: UART global interrupt is enabled to handle incoming data.

---

## 3. Lab Exercises

### Exercise 4: UART Loop-back Communication
* **Task**: Verify the UART channel by sending back (echoing) any character received from the terminal.
* **Implementation**: Uses the `HAL_UART_RxCpltCallback` interrupt service routine to trigger the transmission whenever a byte is received
### Exercise 5: Sensor Reading
* **Task**: Periodically read the ADC value from PA0 and transmit it to the console.
* **Details**: 
    * The ADC value is read every 500ms.
    * Values are converted to ASCII characters using the `sprintf` function for transmission.
    * A 12-bit ADC (referred to as 13 bits in the text) converts 5V to a decimal value of 4095.

### Exercise 6: Communication Protocol Project
* **Task**: Implement a simple communication protocol with a command parser and re-transmission logic.
* **Protocol Steps**:
    1. User sends `!RST#` from the console to request sensor data.
    2. STM32 responds with the packet `!ADC=VALUE#`.
    3. User ends the session by sending `!OK#`.
* **Error Control**: A **3-second timeout** is implemented[cite: 311]. [cite_start]If `!OK#` is not received within this period, the STM32 re-transmits the previous ADC packet.

---

## 4. Software Architecture
The project is structured using two Finite State Machines (FSMs) implemented in separate modules:
* **Command Parser FSM**: Extracts commands (`RST` or `OK`) from the received character buffer.
* **UART Communication FSM**: Manages data transmission, timeout counting, and re-transmission logic
```c
// Core Program Structure
while (1) {
    if (buffer_flag == 1) {
        command_parser_fsm(); // Parse command from buffer
        buffer_flag = 0;
    }
    uart_communication_fsm(); // Handle transmission and timeouts
}
