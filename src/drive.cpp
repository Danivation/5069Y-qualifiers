#include "vex.h"
#include "drive.h"

using namespace vex;

void drivePID(double targetDistance) {
  TrackerWheel.resetPosition();

  const double kP = 0.5;
  const double kI = 0.04;
  const double kD = 0;

  double targetRange = 5;
  double integralLimit = 100;
  double maxSpeed = 600;

  double traveledDistance = 0;

  double error = 0;
  double integral = 0;
  double derivative = 0;
  double previousError = 0;
  
  double speed = 0;

  bool driveFinished = false;

  while (driveFinished == false) {
    // update variables
    traveledDistance =  TrackerWheel.position(rev) * 165;

    // calculate error, integral, and derivative
    error = targetDistance - traveledDistance;
    integral += error;
    derivative = error - previousError;
    previousError = error;

    // stop moving when target is reached
    if (error < targetRange && error > -targetRange) {
      error = 0;
      integral = 0;
    }

    // stop integral from increasing before needed
    if (error > integralLimit || error < -integralLimit) {
      integral = 0;
    }

    // calculate motor speed
    speed = (error * kP) + (integral * kI) + (derivative * kD);
    if (speed > maxSpeed) {
      speed = maxSpeed;
    }
    if (speed < -maxSpeed) {
      speed = -maxSpeed;
    }

    // spin the motors
    LMotorA.spin(forward, speed, rpm);
    LMotorB.spin(forward, speed, rpm);
    LMotorC.spin(forward, speed, rpm);
    RMotorA.spin(forward, speed, rpm);
    RMotorB.spin(forward, speed, rpm);
    RMotorC.spin(forward, speed, rpm);

    // exit loop when target is reached
    if (error < targetRange && error > -targetRange) {
      LMotorA.stop();
      LMotorB.stop();
      LMotorC.stop();
      RMotorA.stop();
      RMotorB.stop();
      RMotorC.stop();
      driveFinished = true;
    }

    wait(10, msec);
  }
  printf("Drive PID finished");
}

void turnPID(double targetHeading) {
  const double kP = 2;
  const double kI = 0.05;
  const double kD = 0;

  double targetRange = 1;
  double integralLimit = 10;
  double maxSpeed = 600;

  double currentHeading = 0;

  double error = 0;
  double integral = 0;
  double derivative = 0;
  double previousError = 0;
  
  double speed = 0;

  bool turnFinished = false;

  while (turnFinished == false) {
    // update variables
    currentHeading = Inertial.heading();

    // calculate error and integral
    error = targetHeading - currentHeading;
    if (error > 180) { error -= 360; }
    if (error < -180) { error += 360; }
    integral += error;
    derivative = error - previousError;
    previousError = error;

    // stop moving when target is reached
    if (error < targetRange && error > -targetRange) {
      error = 0;
      integral = 0;
    }

    // stop integral from increasing before needed
    if (error > integralLimit || error < -integralLimit) {
      integral = 0;
    }

    // calculate motor speed
    speed = (error * kP) + (integral * kI) + (derivative * kD);
    if (speed > maxSpeed) {
      speed = maxSpeed;
    }
    if (speed < -maxSpeed) {
      speed = -maxSpeed;
    }

    // spin the motors
    LMotorA.spin(forward, speed, rpm);
    LMotorB.spin(forward, speed, rpm);
    LMotorC.spin(forward, speed, rpm);
    RMotorA.spin(forward, -speed, rpm);
    RMotorB.spin(forward, -speed, rpm);
    RMotorC.spin(forward, -speed, rpm);

    // exit loop when target is reached
    if (error < targetRange && error > -targetRange) {
      LMotorA.stop();
      LMotorB.stop();
      LMotorC.stop();
      RMotorA.stop();
      RMotorB.stop();
      RMotorC.stop();
      turnFinished = true;
    }

    wait(10, msec);
  }
}