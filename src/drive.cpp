#include <iostream>
#include "vex.h"
#include "drive.h"

using namespace vex;
timer TimerDrive;
timer TimerTurn;

void drivePID(float targetDistance) {
  // reset the position of each motor to 0
  LMotorA.resetPosition();
  LMotorB.resetPosition();
  LMotorC.resetPosition();
  RMotorA.resetPosition();
  RMotorB.resetPosition();
  RMotorC.resetPosition();
  //wait(100, msec);
  //TrackerWheel.resetPosition();
  TimerDrive.clear();

  const float kP = 0.5;
  const float kI = 0.02;
  const float kD = 2.5;

  float targetRange = 5;
  float integralLimit = 100;
  float maxSpeed = 200;

  float leftDistance;
  float rightDistance;
  float traveledDistance = 0;

  float error = 0;
  float integral = 0;
  float derivative = 0;
  float previousError = targetDistance;
  
  float speed = 0;

  bool driveFinished = false;

  while (driveFinished == false) {
    // update variables
    leftDistance = ((LMotorA.position(rev) + LMotorB.position(rev) + LMotorC.position(rev)) / 3) * 220;
    rightDistance = ((RMotorA.position(rev) + RMotorB.position(rev) + RMotorC.position(rev)) / 3) * 220;
    traveledDistance = ((leftDistance + rightDistance) / 2);
    // update variables
    //traveledDistance =  TrackerWheel.position(rev) * 171;

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

/**
    // stop derivative from increasing before needed
    if (error > dLimit || error < -dLimit) {
      derivative = 0;
    }
/**/

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
    std::cout << speed << "\n";

/**/
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
/**/

    wait(10, msec);
  }
  // Drive __ mm (error __ mm) completed in __ seconds (__ ms)
  std::cout << "Drive " << targetDistance << " mm (error " << error << " mm) completed in " << TimerDrive.time(sec) << " seconds (" << TimerDrive.time(msec) << " ms)" << "\n";
}

void turnPID(float targetHeading) {
  TimerTurn.clear();

  const float kP = 2;
  const float kI = 0.05;
  const float kD = 10;

  float targetRange = 1;
  float integralLimit = 10;
  float maxSpeed = 600;

  float currentHeading = 0;

  float error = 0;
  float integral = 0;
  float derivative = 0;
  float previousError = 0;

  float speed = 0;

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
  // Turn to __ degrees (error __ degrees) completed in __ seconds (__ ms)
  std::cout << "Turn to " << targetHeading << " degrees (error " << error << " degrees) completed in " << TimerTurn.time(sec) << " seconds (" << TimerTurn.time(msec) << " ms)" << "\n";
}