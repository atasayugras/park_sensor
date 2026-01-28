# Park Sensor

An Arduino-based ultrasonic distance sensing system with visual and auditory feedback, designed as a parking assistance prototype.

![Demo](park_sensor.gif)

## Overview

This project implements a real-time distance measurement system using an HC-SR04 ultrasonic sensor. The system provides multi-modal feedback through an RGB LED, active buzzer, and 16x2 LCD display, making it suitable for parking assistance or general proximity detection applications.

## Features

- **Real-time distance measurement** with HC-SR04 ultrasonic sensor (0-400cm range)
- **RGB LED feedback** with color transitions based on proximity:
  - Red: Safe distance (>30cm)
  - Red→Green gradient: Approaching (5-30cm)
  - Green: Critical proximity (<5cm)
- **Variable buzzer alerts** with frequency and interval changes based on distance
- **LCD display** showing current distance in centimeters
- **Toggle switch** for system on/off control with debouncing
- **Low power standby mode** when system is disabled

## Hardware Requirements

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- 16x2 LCD Display (HD44780 compatible)
- RGB LED (common cathode)
- Active/Passive Buzzer
- Push Button
- 10kΩ Potentiometer (for LCD contrast)
- 3× 220Ω Resistors (for RGB LED)
- Jumper wires
- Breadboard

## Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| Button | A0 (INPUT_PULLUP) |
| Buzzer | D2 |
| Sensor TRIG | D3 |
| Sensor ECHO | D4 |
| RGB LED - Red | D5 (PWM) |
| RGB LED - Green | D6 (PWM) |
| RGB LED - Blue | D7 (PWM) |
| LCD D7 | D8 |
| LCD D6 | D9 (PWM) |
| LCD D5 | D10 (PWM) |
| LCD D4 | D11 (PWM) |
| LCD E | D12 |
| LCD RS | D13 |

### LCD Wiring
- VSS → GND
- VDD → 5V
- V0 → Potentiometer (contrast)
- RS → D13
- RW → GND
- E → D12
- D4-D7 → D11, D10, D9, D8
- A (backlight) → 5V
- K (backlight) → GND

### RGB LED Wiring
- Common cathode (longest pin) → GND
- Red → 220Ω → D5
- Green → 220Ω → D6
- Blue → 220Ω → D7

## Distance-Based Behavior

| Range | LED Color | Buzzer Frequency | Blink/Beep Interval |
|-------|-----------|------------------|---------------------|
| 0-5cm | Green | 1500 Hz | 100ms (Fast) |
| 5-30cm | Red→Green gradient | 1000 Hz | 300ms (Medium) |
| >30cm | Red | 600 Hz | 600ms (Slow) |

## Installation

1. Clone this repository:
```bash
git clone https://github.com/yourusername/park_sensor.git
cd park_sensor
```

2. Open `park_sensor.ino` in Arduino IDE

3. Install required library:
   - LiquidCrystal (usually pre-installed with Arduino IDE)

4. Connect hardware according to pin configuration

5. Upload to Arduino Uno

## Usage

1. Power on the Arduino
2. Press the button to toggle the system on/off
3. When active, the system will:
   - Display distance on LCD
   - Change LED color based on proximity
   - Emit variable frequency beeps
4. Press button again to enter standby mode (white LED)

## Code Structure

- `setup()`: Initializes pins, LCD, and displays startup message
- `loop()`: Main control flow with button debouncing, sensor reading, and feedback logic
- Debounce delay: 50ms for stable button operation
- Distance calculation: `duration / 58` for centimeters

## Technical Notes

- Uses `INPUT_PULLUP` for button, eliminating need for external pull-up resistor
- PWM on LED pins enables smooth color transitions via `analogWrite()`
- Ultrasonic sensor timeout set to 30ms (~5m maximum range)
- LCD operates in 4-bit mode to conserve pins

## Future Improvements

- Add EEPROM storage for distance thresholds
- Implement multiple sensor array for wider coverage
- Add serial output for data logging
- Customizable alert patterns

## License

MIT License - feel free to modify and use for your projects.

## Author

Built as a learning project for Arduino-based sensor systems.