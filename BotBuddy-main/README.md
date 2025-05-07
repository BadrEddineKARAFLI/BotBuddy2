# BotBuddy
{BotBuddy :} Robot intelligent (Raspberry Pi, capteurs, GPS, caméra), programmé en Java et C, avec conception guidée par l'Ingénierie des Systèmes basée sur les Modèles (MBSE). Exigences précises, drivers en C (UART, SPI, I2C) pour communication optimale. Objectif : robot polyvalent harmonisant matériel et logiciel dans une approche d'ingénierie systémique avancée.

# Project Description for SErobot V7

This document provides an in-depth overview of the files in the SErobot V7 project, detailing their purpose, content, and implementation. The SErobot V7 is an intelligent robot designed to integrate various sensors and actuators, programmed in C, with a focus on efficient communication protocols like I2C.

## 1. `const.h`
- **Purpose**: This header file defines constants used throughout the project, ensuring consistency and clarity in the code.
- **Content**:
  - `_XTAL_FREQ`: Defines the oscillator frequency (40 MHz), which is crucial for timing operations in the microcontroller.
  - Macros for LED control:
    - `LED_INFO_INIT`: Initializes the LED state.
    - `LED_INFO`: Represents the LED control pin.
    - `LED_INFO_ON` and `LED_INFO_OFF`: Macros to turn the LED on and off.
- **Implementation**: This file is included in various source files to ensure that constants are consistently defined and used, reducing the risk of errors due to hard-coded values.

## 2. `bat.h`
- **Purpose**: Header file for battery management functions, providing an interface for battery-related operations.
- **Content**:
  - Function declarations for `bat_init()` (initializes the battery monitoring system) and `bat_get_v()` (returns the current battery voltage).
  - Constants for voltage thresholds (`V_BAT_MIN`, `V_BAT_MAX`) and reference values (`V_REF`, `PONT_DIV_BAT`).
- **Implementation**: This header is included in `bat.c` to manage battery voltage readings and is essential for monitoring the robot's power supply.

## 3. `bat.c`
- **Purpose**: Implements battery management functions, allowing the robot to monitor its battery status.
- **Content**:
  - `bat_init()`: Configures the ADC (Analog-to-Digital Converter) for battery voltage measurement, setting up the necessary registers.
  - `bat_get_v()`: Reads the ADC value and returns the current battery voltage, using a formula to convert the ADC reading into a voltage value.
- **Implementation**: This file utilizes ADC functions to read the battery voltage and controls an LED indicator based on voltage levels, alerting the user when the battery is low.

## 4. `boussole.h`
- **Purpose**: Header file for compass functions, providing an interface for compass-related operations.
- **Content**:
  - Function declarations for compass initialization (`bouss_init()`), calibration (`bouss_calibration()`), and heading reading (`bouss_read_heading()`).
  - I2C address definitions and command constants for communication with the compass sensor.
- **Implementation**: This header is included in `boussole.c` to facilitate the implementation of compass functionalities.

## 5. `boussole.c`
- **Purpose**: Implements compass functions, allowing the robot to determine its orientation.
- **Content**:
  - `bouss_i2c_init()`: Initializes I2C communication for the compass, setting up the necessary pins and configurations.
  - `bouss_read_heading_f()`: Reads the heading from the compass and returns it as a float, combining two bytes received from the sensor.
  - `bouss_calibration()`: Sends commands to the compass to calibrate it, ensuring accurate readings.
- **Implementation**: This file uses I2C functions to communicate with the compass sensor, allowing the robot to navigate based on its heading.

## 6. `comI2C.h`
- **Purpose**: Header file for I2C communication functions, defining the commands used for robot control.
- **Content**:
  - Command definitions for various robot actions (e.g., `CMD_ROBOT_AVANCER`, `CMD_ROBOT_STOP`).
  - Function declarations for I2C initialization (`comI2C_init()`) and command handling (`comI2C_cmd()`).
- **Implementation**: This header provides a structured way to manage I2C commands and responses, ensuring that the robot can communicate effectively with other devices.

## 7. `comI2C.c`
- **Purpose**: Implements I2C communication functions, enabling the robot to receive and respond to commands.
- **Content**:
  - `comI2C_init()`: Initializes the I2C interface, configuring the necessary registers and enabling interrupts.
  - `comI2C_cmd()`: Handles incoming I2C commands, determining the action to take based on the command received.
  - `comI2c_acqu()`: Manages data acquisition requests, sending sensor data back to the master device.
- **Implementation**: This file uses the I2C protocol to communicate with other devices, allowing the robot to respond to commands and share sensor data.

## 8. `irDetect.h`
- **Purpose**: Header file for infrared sensor functions, providing an interface for managing IR sensors.
- **Content**:
  - Function declarations for initializing (`irDetect_init()`) and reading from infrared sensors (`irDetect_getState()`).
- **Implementation**: This header is included in `irDetect.c` to facilitate the implementation of infrared sensor functionalities.

## 9. `irDetect.c`
- **Purpose**: Implements infrared sensor functions, allowing the robot to detect obstacles and navigate accordingly.
- **Content**:
  - `irDetect_init()`: Initializes the infrared sensors, configuring the necessary pins as inputs.
  - `irDetect_getState()`: Returns the state of the infrared sensors as a byte, indicating whether obstacles are detected.
- **Implementation**: This file uses digital input to read sensor states and control LED indicators, providing feedback on the robot's environment.

## 10. `moteur.h`
- **Purpose**: Header file for motor control functions, providing an interface for managing motors.
- **Content**:
  - Function declarations for motor initialization (`moteur_init_pwm()`) and control functions.
- **Implementation**: This header is included in `moteur.c` to facilitate motor management.

## 11. `moteur.c`
- **Purpose**: Implements motor control functions, allowing the robot to move.
- **Content**:
  - `moteur_init_pwm()`: Initializes PWM (Pulse Width Modulation) for motor control, configuring timers and setting up the PWM frequency.
- **Implementation**: This file configures timers and PWM settings to control motor speed and direction, enabling movement.

## 12. `main.c`
- **Purpose**: Main entry point for the robot's firmware, orchestrating the operation of all subsystems.
- **Content**:
  - Initializes all subsystems (I2C, battery, compass, motors, etc.) in the `main()` function.
  - Contains the main loop for handling commands and controlling the robot's behavior based on sensor inputs.
- **Implementation**: This file manages the overall operation of the robot, responding to commands and controlling hardware components based on sensor data.

## 13. `main-tmp.c`
- **Purpose**: Temporary main file for testing purposes, allowing for experimentation without affecting the main firmware.
- **Content**:
  - Contains alternative implementations of the main loop for testing different functionalities, such as sensor readings and motor control.
- **Implementation**: This file is used for debugging and testing, providing a safe environment to try out new features or changes.

## 14. `funclist`
- **Purpose**: A list of functions and their memory addresses, useful for debugging and optimization.
- **Content**:
  - Function names with their corresponding memory addresses and sizes, providing insight into the firmware's structure.
- **Implementation**: This file helps developers understand the memory layout of the firmware and identify potential issues.

## 15. `nbproject/configurations.xml`
- **Purpose**: Configuration file for the project, defining the structure and settings used by the IDE.
- **Content**:
  - Defines project structure, including source files, header files, and build configurations.
- **Implementation**: This file is used by the IDE to manage project settings, ensuring that all files are correctly included in the build process.

## 16. `Makefile`
- **Purpose**: Build script for the project, automating the compilation and linking of source files.
- **Content**:
  - Rules for compiling the project, specifying how to build object files and link them into the final executable.
- **Implementation**: This file streamlines the build process, allowing developers to compile the project with a single command.

## 17. `A_LIRE_V7.txt`
- **Purpose**: Notes on modifications and project updates, providing context for changes made to the code.
- **Content**:
  - Describes changes made to the main file and other important notes, serving as a reference for developers.
- **Implementation**: This file helps maintain a history of changes and decisions made during the development process.

## Conclusion
The SErobot V7 project implements a sophisticated robot control system that integrates various sensors and actuators, managed through efficient I2C communication. Each file plays a specific role in ensuring the robot operates effectively, from reading sensor data to controlling motors and managing power. This modular design allows for easy updates and maintenance, facilitating ongoing development and enhancements.