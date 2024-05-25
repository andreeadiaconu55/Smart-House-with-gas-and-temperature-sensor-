# Smart-House-with-gas-and-temperature-sensor

## Description

This project aims to create a smart home safety and climate control system using an Arduino Uno R3 microcontroller. The system is designed to monitor and respond to changes in temperature and gas levels, enhancing home safety and comfort.



![ss1](https://github.com/andreeadiaconu55/Smart-House-with-gas-and-temperature-sensor-/assets/132846833/0c1cb164-5660-446a-b1cc-b3e6ad8920b5)


![ss2](https://github.com/andreeadiaconu55/Smart-House-with-gas-and-temperature-sensor-/assets/132846833/454a585e-255a-4c23-8da0-dbef6be88852)

## Components

| Component           | Description              |
| ------------------- | ------------------------ |
| Microcontroller     | Arduino Uno R3           |
| Motor               | Micro Servo              |
| Fan                 | I.9110 with DC motor     |
| Gas Sensor          | MQ2                      |
| Temperature Sensor  | DHT11                    |
| Alarm               | Active Buzzer            |
| Buttons             | Push Down Buttons        |
| LCD                 | I2C                      |
| Batteries           | x2 AAA                   |
| Breadboard          | 850 pins                 |
| Resistors           | 330 Ohms                 |


## Schematic 
![Tinkercad](https://github.com/andreeadiaconu55/Smart-House-with-gas-and-temperature-sensor-/assets/132846833/2f2a4290-a409-41ca-b23a-087ee612a283)

## How it works
The system has a temperature threshold set at 27°C and a gas level danger threshold at 450 ppm.

The DHT11 sensor measures the temperature and, if it exceeds 27°C, the fan motor receives a PWM command to start. The fan continues running until the temperature drops below the threshold, at which point the motor gradually stops, and a blue LED lights up.

The MQ2 gas sensor measures gas levels. Under normal conditions, it should read 100-150 ppm. If the level exceeds 450 ppm, the servo motor rotates 180 degrees to slide open a door, and the buzzer sounds an alarm. The system stays in this state (door open and alarm on) until the gas level drops below the threshold, at which point the door closes, and the alarm stops. A red LED indicates the presence of danger.

The system includes three buttons:

- Two buttons adjust the temperature threshold by ±0.5°C, with changes displayed on the LCD.
- An emergency button slides the door open for a short period before closing it. If the door is already open, pressing the button has no effect.
The LCD displays "hot" or "cold" based on the temperature, along with the measured and reference temperatures on the first line. The second line shows "high!" or "safe" based on the gas level.

During testing, the fan module was powered separately using two AAA batteries in series, as the 5V supply from the board was insufficient. Resistors were used to protect LEDs and buttons.

The project model includes a cardboard house with a sliding door attached to the servo motor, ensuring stable movement with wooden guides. The fan module simulates an air conditioning unit.

The code was implemented in Arduino IDE and it is attached in the repository.

Here is a demo for the project: 

* Temperature sensor reaction


https://github.com/andreeadiaconu55/Smart-House-with-gas-and-temperature-sensor-/assets/132846833/28f034bb-3985-467b-b457-26a17b2afc75

* Gas sensor reaction

https://github.com/andreeadiaconu55/Smart-House-with-gas-and-temperature-sensor-/assets/132846833/7a2621c1-79d6-4f7c-9567-861374c2b651

