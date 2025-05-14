![Build Status](https://img.shields.io/github/actions/workflow/status/Badredenyx/BotBuddy2/ci.yml?branch=main)
![License](https://img.shields.io/github/license/Badredenyx/BotBuddy2)

# BotBuddy2 (SErobot V7)

**Autonomous exploration robot integrating Raspberry Pi control, microcontroller-based C drivers, and MBSE-guided design.**

## Summary

BotBuddy2 is designed for hazardous-site reconnaissance, navigating to given GPS coordinates, and streaming video to a remote operator via WiFi. It unifies a Raspberry Pi application in Java (using PI4J for GPIO, I²C, and serial) with a PIC18F46K22 microcontroller in C, managing sensors (GPS, compass, IR, ultrasonic, battery) and actuators (motors, gripper, camera pan). Communications occur over I²C (Pi → MCU) and TCP sockets (operator ↔ Pi). This README outlines installation, configuration, usage, and development guidelines.

## Table of Contents

* [Mission & Context](#mission--context)
* [Key Features](#key-features)
* [Repository Structure](#repository-structure)
* [Installation & Setup](#installation--setup)
* [Configuration](#configuration)
* [Usage](#usage)
* [Communication Protocols](#communication-protocols)
* [Architecture](#architecture)
* [Contributing](#contributing)
* [License](#license)

## Mission & Context

This project deploys an autonomous robot to a nuclear site (coords: 44°08′10.7″N, 4°05′53.6″E) for remote visual assessment. After arrival, a single Android/tablet client connects via WiFi to:

* **Control actuators:** drive motors, gripper, camera pan
* **Read sensors:** proximity (IR), ultrasonic, compass, GPS, battery
* **Stream images:** an updated JPEG every 0.5 s via Apache on Raspberry Pi

The Pi hosts a single-client TCP server; upon readiness, the camera pans right then centers to signal availability.

## Key Features

* **Autonomous Navigation:** GPS‐based waypoint travel on MCU/GPS module
* **Real‐time Video:** Serves `vueRobot.jpg` to Apache every 500 ms via `raspistill`
* **Sensor Suite:** IR, ultrasonic (3 sensors), compass (HMC6352), GPS (SUP500R), battery monitor
* **Actuation:** PWM motor control, servo-driven gripper and camera pan
* **Robust Communication:** Java TCP sockets (commands/acks), I²C bus to PIC slave (0x70)
* **MBSE Architecture:** Modular C drivers with SWIG wrappers for Java
* **Network Config:** Dedicated Ethernet for dev (192.168.0.1/2) and managed WiFi for operation

## Repository Structure

```
/ (root)
├── firmware/                   # PIC microcontroller C code
│   ├── const.h                  Constants & LED macros
│   ├── bat.h/.c                 Battery ADC monitor
│   ├── boussole.h/.c            Compass I²C driver
│   ├── irDetect.h/.c            IR obstacle detection
│   ├── usensor.h/.c             Ultrasonic sensor driver
│   ├── moteur.h/.c              PWM motor control
│   ├── comI2C.h/.c              I²C command interface
│   ├── main.c                   Production entry point
│   ├── main-tmp.c               Test harness
│   ├── funclist                 Function memory map
│   └── Makefile                 Build & flash scripts
├── controller/                 # Raspberry Pi Java application
│   ├── src/com/botbuddy/        Java sources (ServerSocket, I2C, serial, video)
│   ├── demos/                   Example demos (ObstacleAvoidance, GPSLogger)
│   ├── config.properties        I²C bus, compass offsets, PWM freq
│   └── pom.xml or build scripts
├── docs/
│   ├── architecture.md         Functional and UML diagrams
│   ├── demo_obstacle.gif       Obstacle avoidance demo
│   └── MiseEnOeuvre_VSCode.pdf VS Code setup guide
├── A_LIRE_V7.txt               Update notes
├── BotBuddy-main.zip/.7z/.rar  Full source archives
├── BotBuddy.mp4                Video demo
└── nbproject/configurations.xml NetBeans IDE settings
```

## Installation & Setup

### Prerequisites

* **Raspberry Pi OS** (Buster or newer) with SSH enabled
* **Java 11+**, **PI4J 1.4**
* **GCC** (`arm-none-eabi`) and **Make**
* **SWIG** (for Java-C bindings)
* **raspistill**, **libcamera-tools**, **Apache2**
* Enable I²C, SPI, UART: `sudo raspi-config`

### Build Firmware (MCU)

```bash
cd firmware
make all       # compiles .hex and .elf
make flash     # flashes to PIC via programmer
```

### Build Controller (Pi)

```bash
cd controller
swig -java -package com.botbuddy -outdir src comI2C.i
mvn package     # or javac with provided scripts
```

## Configuration

Edit `controller/config.properties` to match your hardware and network:

```properties
# Communication
i2c.bus=/dev/i2c-1
tcp.port=5000
# Compass calibration
compass.offset.x=0
compass.offset.y=0
# PWM settings
moteur.pwm.frequency=20000
# Video output
video.dir=/var/www/html
video.file=vueRobot.jpg
video.intervalMs=500
```

## Usage

1. **Start Apache**: `sudo systemctl start apache2`
2. **Run Pi application** (background):

   ```bash
   cd controller/target
   java -jar BotBuddy2.jar &
   ```

   * Upon ready state, camera will pan right then center.
3. **Connect from Android client** via TCP to `<robot-ip>:<tcp.port>`
4. **Flash MCU** (if not auto-run): `/firmware/make flash`

## Communication Protocols

### Java TCP Socket API

* **Single client**: uses `ServerSocket` to accept one connection; handles disconnects to await new.
* **Frame format**: `<COMMAND>[ <param>]\n`
* **Ack**: `COMMAND TRAME_OK\n` or `COMMAND TRAME_NOK\n`
* **Sensor responses** include data fields (e.g., `DETECT AVG AVD\n`).

### I²C Commands (0x70)

* **Format**: `<cmdByte><paramByte>`; responses via I²C reads.
* **Action commands**: motors, gripper, camera pan/center
* **Sensor commands**: IR (0x50), US (0x40), compass (0x60), battery (0x70)

## Architecture

![Architecture](docs/architecture.md)
*See `docs/architecture.md` for detailed UML diagrams.*

## Contributing

1. Fork & clone repository
2. Create branch: `git checkout -b feature/YourFeature`
3. Commit & push
4. Submit a PR referencing relevant issues

Please follow the [Code of Conduct](CODE_OF_CONDUCT.md).

## License

MIT License © 2025 Badredenyx. See [LICENSE](LICENSE).
