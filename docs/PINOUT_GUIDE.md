# Hardware Pinout & Wiring Guide

This document specifies the exact pin connections between the **Arduino Uno R3**, the sensors (**MQ-3** and **DHT11**), the output devices (**16x2 Character LCD** and **Piezo Buzzer**), and the power rails.

---

## 1. Quick Pin Reference Table

| Device / Module | Pin on Module | Connected to Pin on Arduino Uno | Wire Type / Role |
| :--- | :--- | :--- | :--- |
| **MQ-3 Gas Sensor** | `VCC` | `5V` (Power Bus) | 5V DC Power |
| | `GND` | `GND` (Ground Bus) | Ground |
| | `A0` (Analog Out) | `A0` (Analog In) | Gas Concentration Signal |
| | `D0` (Digital Out)| *Unused* | Comparator Output |
| **DHT11 Sensor** | `VCC` | `5V` (Power Bus) | 5V DC Power |
| | `GND` | `GND` (Ground Bus) | Ground |
| | `DATA` (Signal) | `Digital Pin 2 (D2)` | Single-Bus Temp/Humidity Signal |
| **Piezo Buzzer** | `(+)` (Long leg) | `Digital Pin 8 (D8)` | PWM / Digital Active High Trigger |
| | `(-)` (Short leg)| `GND` (Ground Bus) | Ground Return |
| **16x2 LCD (HD44780)**| `Pin 1 (VSS)` | `GND` (Ground Bus) | Power Ground |
| | `Pin 2 (VDD)` | `5V` (Power Bus) | Logic Power (+5V) |
| | `Pin 3 (VO)` | Voltage divider (`1kΩ` & `300Ω` to GND)| Contrast Adjustment Bias |
| | `Pin 4 (RS)` | `Digital Pin 12 (D12)` | Register Select |
| | `Pin 5 (RW)` | `GND` (Ground Bus) | Read/Write (Hardwired to Write) |
| | `Pin 6 (E)` | `Digital Pin 11 (D11)` | Operation Enable Pulse |
| | `Pin 7-10 (D0-D3)`| *Unused* (4-bit mode) | Lower Data Nibble (Floating) |
| | `Pin 11 (D4)` | `Digital Pin 7 (D7)` | Data Bit 4 |
| | `Pin 12 (D5)` | `Digital Pin 6 (D6)` | Data Bit 5 |
| | `Pin 13 (D6)` | `Digital Pin 5 (D5)` | Data Bit 6 |
| | `Pin 14 (D7)` | `Digital Pin 4 (D4)` | Data Bit 7 |
| | `Pin 15 (A)` | `5V` (Power Bus) | Backlight LED Anode (+) |
| | `Pin 16 (K)` | `GND` (Ground Bus) | Backlight LED Cathode (-) |

---

## 2. Power Distribution (Breadboard Rail Setup)

Since the Arduino Uno R3 has a single 5V pin and two GND pins on the power header:
1. Connect the Arduino `5V` pin to the breadboard positive (`+`) red power bus.
2. Connect the Arduino `GND` pin to the breadboard negative (`-`) blue ground bus.
3. Distribute `5V` and `GND` across all three modules (MQ-3, DHT11, and 16x2 LCD).

---

## 3. LCD Contrast Circuit Detail

Standard LCD modules use a 10k potentiometer on pin 3 (VO). In this fixed hardware build, a fixed resistor combination is used to ensure contrast stability:
- Connect a `1kΩ` and `~300Ω` resistor combination between **VO (Pin 3)** and **GND**.
- This creates an optimal bias voltage (~0.8V - 1.0V) for clean, crisp character rendering without needing a bulky trimmer potentiometer.
