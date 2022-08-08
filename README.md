# Blindr

## Background

![Blindr blinds](https://github.com/PeterChu3/Blindr/blob/main/Photos/blindr.gif?raw=true)

Georgia Tech CS 3651 Prototyping Intelligent Appliances

Throughout the semester, we learn how to use microcontrollers and sensors to sense and react to the world around us. Near the end of the semester, we apply what we learned throughout the semester to make an intelligent device that senses and reacts to the real world.

## Explanation

#### Hardware

![Blindr blinds](https://github.com/PeterChu3/Blindr/blob/main/Photos/protoboardTop.jpeg?raw=true)
For this project, my team Sam Roquitte and Peter Chu came up with the idea of motorizing blinds overlooking Midtown Atlanta in the CS3651 classroom. To achieve this we use a D1 mini microcontroller with ESP8266.

The motor driver is an H-bridge breakout to allow the motor to be controlled from the D1 mini.

To display the state of the blinds, we used LEDs to show the intended position of the blinds.

To sense the world we use a BMP280 to obtain temperature and pressure. However, we used I2C so any future I2C sensor would be able to easily integrate into the system in hardware.

![encoder side](https://github.com/PeterChu3/Blindr/blob/main/Photos/encoderside.png?raw=true)

The motor is a brushed motor that was plentiful in the classroom. We based our design on the shape of the motor.

To prevent a stall condition of the motor, we designed a rotary encoder from an optical encoder that detects the rotation distance the motor has rotated from the start of the request.

#### Software

The software was coded using the Arduino environment. We used libraries to host a REST server on the D1 Mini.

![Blindr blinds](https://github.com/PeterChu3/Blindr/blob/main/Photos/REST%20diagram.jpg?raw=true)

Above is a system paradigm to illustrate how requests are handled and replied to.

We also used a state machine to make sure that all of the different states and transitions are handled and have actions.

[More details of Blindr are available in Final Documentation](https://github.com/PeterChu3/Blindr/blob/main/Docs/Final%20Documentation.pdf)

#### Software

Folders in this repo:

CAD - Contains all of the solidworks files used to create the project

Code - Contains all of the development code for the D1 Mini

Docs - Contains all of the documentation generated for CS 3651.

Photos - Contains photos to illustrate Blindr.
