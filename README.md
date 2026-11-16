# adaptive-vechile-dashboard-simulator
# LPC2129-Based CAN Vehicle Monitoring and Control System

## 1. Project Overview

This project implements a vehicle monitoring and control system using two LPC2129 microcontrollers communicating through the CAN (Controller Area Network) protocol.

The system uses Node A to collect sensor information and send control commands through CAN. Node B receives the CAN messages, controls the indicators and headlight, and displays the received sensor values through UART communication.

## 2. Project Objectives

- Establish CAN communication between two LPC2129 microcontrollers.
- Monitor sensor data using ADC and an ultrasonic sensor.
- Control left and right indicators.
- Control the vehicle headlight.
- Receive and display sensor information on the Node B UART terminal.

## 3. Hardware Requirements

- LPC2129 Microcontroller – Node A
- LPC2129 Microcontroller – Node B
- CAN transceiver modules
- Potentiometer
- LM35 Temperature Sensor
- Ultrasonic Sensor
- LEDs for indicators and headlight
- UART-to-USB converter
- Power supply and connecting wires

## 4. System Architecture

### Node A – Transmitter

Node A performs the following operations:

- Reads potentiometer values using ADC.
- Reads temperature using the LM35 sensor.
- Measures distance using the ultrasonic sensor.
- Detects external interrupt inputs for indicator and headlight control.
- Transmits sensor values and control commands through CAN.

### Node B – Receiver

Node B performs the following operations:

- Initializes CAN1 communication.
- Receives CAN messages from Node A.
- Checks the received message ID and frame type.
- Decodes control commands.
- Controls the left indicator, right indicator, and headlight LEDs.
- Extracts potentiometer, temperature, and ultrasonic sensor values.
- Displays the received information through UART0 at 9600 baud.

## 5. CAN Communication Configuration

| Parameter | Configuration |
|---|---|
| Microcontroller | LPC2129 |
| CAN Channel | CAN1 |
| CAN Identifier | 0x123 |
| Data Length | 8 Bytes |
| Frame Type | Data Frame |
| CAN Bitrate | 125 Kbps (as configured in the driver) |
| UART Baud Rate | 9600 |

## 6. CAN Data Format

The CAN message contains two 32-bit data fields: `byteA` and `byteB`.

| CAN Data Byte | Information |
|---|---|
| Byte 0 | Control command |
| Byte 1 | Potentiometer value |
| Byte 2 | Temperature value |
| Byte 3 | Reserved |
| Byte 4 | Ultrasonic sensor value |
| Byte 5–7 | Reserved |

Node B extracts the values using bitwise operations:

- Control command: `r.byteA & 0xFF`
- Potentiometer: `(r.byteA >> 8) & 0xFF`
- Temperature: `(r.byteA >> 16) & 0xFF`
- Ultrasonic value: `r.byteB & 0xFF`

## 7. Control Commands

| Command | Operation |
|---|---|
| 0x01 | Left Indicator ON |
| 0x11 | Left Indicator OFF |
| 0x02 | Headlight ON |
| 0x22 | Headlight OFF |
| 0x03 | Right Indicator ON |
| 0x33 | Right Indicator OFF |

## 8. Node B LED Pin Configuration

| LED Function | LPC2129 Pin |
|---|---|
| Left Indicator | P0.4 |
| Headlight | P0.5 |
| Right Indicator | P0.6 |

The LEDs are controlled using `IOSET0` and `IOCLR0`.

## 9. UART Output

Node B displays the received information through UART0.

Example output:

```text
Waiting for Node A
===============================================

Left indicator ON
Speed = 120 KM/h
Temperature = 30 C
Fuel = 20 L

===============================================
```

*Example values are illustrative, not measured results.*

**Note:** In the current Node B code, the value printed as `Fuel` is extracted from `r.byteB`, which contains the ultrasonic sensor data. Change the output label to `Distance` if that value represents ultrasonic distance.

## 10. Software Requirements

- Embedded C
- Keil uVision IDE
- LPC2129 Microcontroller
- CAN Protocol
- UART Communication
- ADC
- External Interrupts
- Timer Programming

## 11. Applications

- Vehicle monitoring systems
- CAN-based embedded communication
- Vehicle lighting control
- Sensor data monitoring
- Automotive embedded system development

## 12. Conclusion

This project demonstrates communication between two LPC2129 microcontrollers using the CAN protocol. Node A collects sensor information and sends control commands, while Node B receives the data, controls vehicle lighting, and displays sensor information through UART.

The project provides practical experience with CAN communication, ADC interfacing, external interrupts, timers, UART communication, and embedded C programming.
