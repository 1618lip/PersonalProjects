# DIY Reactive Night Lamp

This code controls a DIY reactive night lamp that responds to sound and motion. The lamp consists of three LEDs (red, green, and blue) and a servo motor. The intensity of the LEDs and the rotation of the servo motor are controlled based on input from a sound sensor and a motion sensor.

## Hardware Components

- Red LED connected to PWM pin 11 (red)
- Green LED connected to PWM pin 10 (green)
- Blue LED connected to PWM pin 9 (blue)
- Sound sensor connected to analog pin 0 (sound)
- Motion sensor connected to PWM pin 12 (motion)

## Variables

- `state`: Signals if the servo motor has reached its maximum rotation (LOW or HIGH).
- `d`: Determines how fast the servo motor spins by delaying the rotation.
- `k`: Stores the value from the sound sensor.
- `t`: Acts as a time variable to cycle through the LEDs.
- `r`: Initial incremental value for the position of the servo motor.
- `a1`, `a2`, `a3`: Variables for the luminosity of each LED.
- `v`: Maximum luminosity of the LEDs.

## Libraries

This code utilizes the `Servo` library to control the servo motor.

## Setup

In the `setup()` function:
- IO pins are set for the LEDs, sound sensor, and motion sensor.
- The servo motor is attached to PWM pin 3.
- The servo motor is initialized at the 0th position.
- Serial communication is initiated at a baud rate of 115200.

## Main Loop

The `loop()` function continuously runs the main logic of the code.

1. Sound Sensor Input:
   - If the analog reading from the sound sensor is above 490, the value is multiplied by 0.8 and assigned to `k`.
   - Otherwise, `k` is set to 0.

2. LED Luminosity:
   - `a1`, `a2`, and `a3` are calculated based on the current value of `t` and `k`, using the `sin` function and absolute values.
   - The LED luminosity is controlled by multiplying the calculated values with the maximum luminosity `v`.
   - The `analogWrite()` function is used to set the PWM output for each LED.

3. Time Increment:
   - The value of `t` is incremented by 0.0006 to cycle through the LEDs.

4. Motion Sensor Input:
   - If the motion sensor detects motion (HIGH), the servo motor's rotating motion is triggered.
   - The `d` variable determines the speed of rotation. If `d` is equal to 150, the servo motor's position (`pos`) is incremented by 1.
   - `d` is then decreased by 0.02. If `d` is still greater than 0, the servo motor remains at its current position.
   - If `d` becomes 0, the servo motor's position is updated to `r`, and `r` is incremented or decremented based on the current `state`.
   - If `r` reaches 180, `state` is set to HIGH. If `state` is HIGH, `r` is decremented until it reaches 0, and then `state` is set to LOW.
   - The servo motor's position is updated using `myservo.write()`.

The code continues to run in an infinite loop, repeating the above steps.
