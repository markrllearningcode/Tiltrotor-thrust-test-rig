# Tiltrotor-thrust-test-rig
Arduino-based 3D-printed tiltrotor nacelle test rig for measuring vertical thrust as a function of rotor tilt angle.

This repository will contain all the code, data, images and analysis that I will do for my 3D printed tiltrotor nacelle thrust test rig, this will all then be used to create a research paper that I will attempt to publish.

The rig uses a 3D-printed structure, an A2212 brushless motor, a 30A ESC, an SG90 servo for angle control, and a load cell with an HX711 amplifier for force measurement. Data is logged through the Arduino Serial Monitor in CSV format and analysed to compare vertical thrust across different tilt angles.

## Research Question

How does rotor tilt angle affect the vertical thrust produced by a 3D-printed tiltrotor nacelle test rig?

## Main Components

- Arduino UNO R4 WiFi
- A2212 1000KV brushless motor
- 30A ESC
- 10x4.5 propeller
- SG90 servo motor
- 5 kg load cell
- HX711 amplifier
- 12 V power supply
- 3D-printed PLA+ test rig

## Data Collection

Thrust measurements were taken at rotor tilt angles of 0°, 15°, 30°, 45°, 60°, 75°, and 90°. Five repeated load-cell readings were recorded for each angle at a fixed throttle signal.

## Calibration

The load cell was calibrated using a 1 kg mass. The calibration factor used was:

```text
44493.17023 raw counts per Newton
