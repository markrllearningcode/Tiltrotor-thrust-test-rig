#include <Servo.h>
#include "HX711.h"

#define ESC_PIN 9
#define SERVO_PIN 10

#define HX711_DT 3
#define HX711_SCK 2

Servo esc;
Servo tiltServo;
HX711 scale;

int currentAngle = 90;
int currentThrottle = 1000;

void setup() {
  Serial.begin(9600);
  delay(1000);

  tiltServo.attach(SERVO_PIN);
  tiltServo.write(currentAngle);

  esc.attach(ESC_PIN);
  esc.writeMicroseconds(1000);

  delay(5000); 

  scale.begin(HX711_DT, HX711_SCK);

  delay(1000);
  scale.tare();

  Serial.println("# Tiltrotor nacelle test rig CSV logger");
  Serial.println("# Commands:");
  Serial.println("# a90 = set angle to 90 degrees");
  Serial.println("# t1150 = set throttle to 1150 us");
  Serial.println("# r = record one averaged reading");
  Serial.println("# tare = zero load cell");
  Serial.println("# stop = motor minimum throttle");
  Serial.println();
  Serial.println("time_ms,angle_deg,throttle_us,raw_reading");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "tare") {
      scale.tare();
      Serial.println("# Tare complete");
    }

    else if (command == "stop") {
      currentThrottle = 1000;
      esc.writeMicroseconds(1000);
      Serial.println("# Motor stopped/minimum throttle");
    }

    else if (command == "r") {
      long raw = scale.get_value(20);

      Serial.print(millis());
      Serial.print(",");
      Serial.print(currentAngle);
      Serial.print(",");
      Serial.print(currentThrottle);
      Serial.print(",");
      Serial.println(raw);
    }

    else if (command.startsWith("a")) {
      int newAngle = command.substring(1).toInt();

      if (newAngle >= 0 && newAngle <= 90) {
        currentAngle = newAngle;
        tiltServo.write(currentAngle);
        delay(800);

        Serial.print("# Angle set to ");
        Serial.println(currentAngle);
      } else {
        Serial.println("# ERROR: angle must be 0 to 90");
      }
    }

    else if (command.startsWith("t")) {
      int newThrottle = command.substring(1).toInt();

      if (newThrottle >= 1000 && newThrottle <= 1250) {
        currentThrottle = newThrottle;
        esc.writeMicroseconds(currentThrottle);
        delay(1000);

        Serial.print("# Throttle set to ");
        Serial.println(currentThrottle);
      } else {
        Serial.println("# ERROR: throttle must be 1000 to 1250");
      }
    }

    else {
      Serial.println("# Unknown command");
    }
  }
}