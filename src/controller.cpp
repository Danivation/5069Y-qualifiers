#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "vex.h"
#include "controller.h"
#include "drive.h"

using namespace vex;
timer Timer;
extern competition Competition;

void (*autonCallback)();

// controller bindings
const vex::controller::axis ForwardAxis =               Controller1.Axis3;
const vex::controller::axis TurnAxis =                  Controller1.Axis1;

const vex::controller::button MobileGoalPistonToggle =  Controller1.ButtonDown;
const vex::controller::button DoinkerPistonToggle =     Controller1.ButtonB;
const vex::controller::button ArmPistonToggle =         Controller1.ButtonR1;
const vex::controller::button IntakeInButton =          Controller1.ButtonL1;
const vex::controller::button IntakeOutButton =         Controller1.ButtonL2;

const vex::controller::button AutonSelector =           Controller1.ButtonA;

float motorSetting;               // motor rpm multiplier (x100)
int totalSec, timeSec, timeMin;   // timer variables
std::ostringstream Line1, Line3;  // controller screen lines

int DrivetrainControl() {
  while (true) {
    LMotorA.spin(forward, (ForwardAxis.position(percent) + (TurnAxis.position(percent) * 0.5)) * motorSetting, rpm);
    LMotorB.spin(forward, (ForwardAxis.position(percent) + (TurnAxis.position(percent) * 0.5)) * motorSetting, rpm);
    LMotorC.spin(forward, (ForwardAxis.position(percent) + (TurnAxis.position(percent) * 0.5)) * motorSetting, rpm);
    RMotorA.spin(forward, (ForwardAxis.position(percent) - (TurnAxis.position(percent) * 0.5)) * motorSetting, rpm);
    RMotorB.spin(forward, (ForwardAxis.position(percent) - (TurnAxis.position(percent) * 0.5)) * motorSetting, rpm);
    RMotorC.spin(forward, (ForwardAxis.position(percent) - (TurnAxis.position(percent) * 0.5)) * motorSetting, rpm);
    wait(5, msec);
  }
}

int IntakeControl() {
  while (true) {
    if (IntakeInButton.pressing()) {
      IntakeMotor.spin(forward);
      ConveyorMotor.spin(forward);
      waitUntil(!IntakeInButton.pressing());
      IntakeMotor.stop();
      ConveyorMotor.stop();
    }
    if (IntakeOutButton.pressing()) {
      IntakeMotor.spin(reverse);
      ConveyorMotor.spin(reverse);
      waitUntil(!IntakeOutButton.pressing());
      IntakeMotor.stop();
      ConveyorMotor.stop();
    }
  }
}

int MobileGoalPistonControl() {
  while (true) {
    MobileGoalPiston.set(false);
    waitUntil(!MobileGoalPistonToggle.pressing());
    waitUntil(MobileGoalPistonToggle.pressing());

    MobileGoalPiston.set(true);
    waitUntil(!MobileGoalPistonToggle.pressing());
    waitUntil(MobileGoalPistonToggle.pressing());
  }
}

int ArmPistonControl() {
  while (true) {
    ArmPiston.set(false);
    waitUntil(!ArmPistonToggle.pressing());
    waitUntil(ArmPistonToggle.pressing());

    ArmPiston.set(true);
    waitUntil(!ArmPistonToggle.pressing());
    waitUntil(ArmPistonToggle.pressing());
  }
}

int DoinkerPistonControl() {
  while (true) {
    DoinkerPiston.set(false);
    waitUntil(!DoinkerPistonToggle.pressing());
    waitUntil(DoinkerPistonToggle.pressing());

    DoinkerPiston.set(true);
    waitUntil(!DoinkerPistonToggle.pressing());
    waitUntil(DoinkerPistonToggle.pressing());
  }
}

/**
int MotorControl() {
  while (true) {
    motorSetting = 6;   // 600 rpm
    waitUntil(!MotorControlToggle.pressing());
    waitUntil(MotorControlToggle.pressing());

    motorSetting = 0.1; // 10 rpm
    waitUntil(!MotorControlToggle.pressing());
    waitUntil(MotorControlToggle.pressing());
  }
}
/**/

void autonNone() {
  // successfully do nothing
  drivePID(600);
}

void autonRedLeft() {
  // autonomous actions (new red left)
  Inertial.setHeading(180, degrees);
  drivePID(-900);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(270);
  drivePID(600);
  wait(500, msec);
  turnPID(10);
  drivePID(600);
  wait(500, msec);
  drivePID(-300);
  turnPID(350);
  drivePID(300);
  wait(500, msec);
  turnPID(135);
  drivePID(1697);
  MobileGoalPiston.set(false);
  wait(500, msec);
  IntakeMotor.spin(reverse);
  wait(500, msec);
  ArmPiston.set(true);
  IntakeMotor.stop();
  turnPID(180);
  drivePID(600);
  ArmPiston.set(false);
  drivePID(-600);
  turnPID(340);
  drivePID(1800);
}

void autonRedRight() {
  // autonomous actions (new red right)
  Inertial.setHeading(180, degrees);
  drivePID(-900);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(90);
  drivePID(600);
  wait(1500, msec);
  IntakeMotor.stop();
  MobileGoalPiston.set(false);
  turnPID(180);
  drivePID(-600);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(225);
  drivePID(1697);
  wait(500, msec);
  IntakeMotor.spin(reverse);
  wait(500, msec);
  ArmPiston.set(true);
  IntakeMotor.stop();
  turnPID(180);
  drivePID(600);
  ArmPiston.set(false);
  drivePID(-600);
  turnPID(20);
  drivePID(1800);
}

void autonBlueLeft() {
  // autonomous actions (new blue left)
  Inertial.setHeading(0, degrees);
  drivePID(-500);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(90);
  drivePID(500);
  wait(1500, msec);
  IntakeMotor.stop();
  MobileGoalPiston.set(false);
  turnPID(0);
  drivePID(-600);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(315);
  drivePID(1697);
  wait(500, msec);
  IntakeMotor.spin(reverse);
  wait(500, msec);
  ArmPiston.set(true);
  IntakeMotor.stop();
  turnPID(0);
  drivePID(600);
  ArmPiston.set(false);
  drivePID(-600);
  turnPID(160);
  drivePID(1800);
}

void autonBlueRight() {
  // autonomous actions (new blue right)
  Inertial.setHeading(0, degrees);
  drivePID(-900);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(270);
  drivePID(600);
  wait(500, msec);
  turnPID(170);
  drivePID(600);
  wait(500, msec);
  drivePID(-300);
  turnPID(190);
  drivePID(300);
  wait(500, msec);
  turnPID(45);
  drivePID(1697);
  MobileGoalPiston.set(false);
  wait(500, msec);
  IntakeMotor.spin(reverse);
  wait(500, msec);
  ArmPiston.set(true);
  IntakeMotor.stop();
  turnPID(0);
  drivePID(600);
  ArmPiston.set(false);
  drivePID(-600);
  turnPID(200);
  drivePID(1800);
}

void autonSkills() {
  // autonomous skills actions
  Inertial.setHeading(180, degrees);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(270);
  drivePID(600);
  wait(500, msec); // ring
  turnPID(0);
  drivePID(300);
  wait(500, msec); // ring
  turnPID(270);
  drivePID(300);
  wait(500, msec); // ring
  turnPID(30);
  drivePID(600);
  wait(500, msec); // ring
  turnPID(90);
  drivePID(600);
  wait(500, msec); // ring
  IntakeMotor.stop();
  MobileGoalPiston.set(false); // drop mogo
  turnPID(300);
  drivePID(-1200);
  MobileGoalPiston.set(true); // pick up mogo
  IntakeMotor.spin(forward);
  turnPID(120);
  drivePID(600);
  wait(500, msec); // ring
  turnPID(0);
  drivePID(300);
  wait(500, msec); // ring
  turnPID(90);
  drivePID(300);
  wait(500, msec); // ring
  turnPID(330);
  drivePID(600);
  wait(500, msec); // ring
  turnPID(270);
  drivePID(600);
  wait(500, msec); // ring
  turnPID(315);
  drivePID(800);
  wait(500, msec); // ring
  IntakeMotor.stop();
  MobileGoalPiston.set(false); // drop mogo
  turnPID(330);
  drivePID(1200);
  turnPID(270);
  drivePID(-600);
  MobileGoalPiston.set(true); // pick up mogo
  IntakeMotor.spin(forward);
  turnPID(225);
  drivePID(800);
  wait(500, msec); // ring
  turnPID(270);
  drivePID(600);
  wait(500, msec); // ring
  turnPID(0);
  drivePID(600);
  wait(500, msec); // ring
  drivePID(-300);
  turnPID(315);
  drivePID(400);
  wait(500, msec); // ring
  turnPID(180);
  drivePID(1200);
  wait(500, msec); // ring
  turnPID(40);
  drivePID(800);
  turnPID(315);
  drivePID(400);
  wait(500, msec); // ring
  IntakeMotor.stop();
  MobileGoalPiston.set(false); // drop mogo
  IntakeMotor.spin(forward);
  turnPID(120);
  drivePID(2000);
  wait(500, msec); // ring
  IntakeMotor.spin(reverse);
  wait(500, msec); // ring on claw
  IntakeMotor.spin(forward);
  turnPID(120);
  drivePID(1000);
  wait(500, msec); // ring
  IntakeMotor.spin(reverse);
  wait(500, msec); // ring on claw
  IntakeMotor.stop();
  ArmPiston.set(true); // raise arm
  turnPID(90);
  drivePID(300);
  ArmPiston.set(false); // lower arm
}

int AutonSelect() {
  while (true) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: None");
    autonCallback = autonNone;
    waitUntil(!AutonSelector.pressing());
    waitUntil(AutonSelector.pressing());

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Red Left");
    autonCallback = autonRedLeft;
    waitUntil(!AutonSelector.pressing());
    waitUntil(AutonSelector.pressing());

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Red Right");
    autonCallback = autonRedRight;
    waitUntil(!AutonSelector.pressing());
    waitUntil(AutonSelector.pressing());

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Blue Left");
    autonCallback = autonBlueLeft;
    waitUntil(!AutonSelector.pressing());
    waitUntil(AutonSelector.pressing());

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Blue Right");
    autonCallback = autonBlueRight;
    waitUntil(!AutonSelector.pressing());
    waitUntil(AutonSelector.pressing());

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Skills");
    autonCallback = autonSkills;
    waitUntil(!AutonSelector.pressing());
    waitUntil(AutonSelector.pressing());
  }
}

/**
int ScreenControl() {
  while (true) {
    // x:xx Auton/Driver
    //
    // xx%
    Controller1.Screen.clearScreen();
    waitUntil(Competition.isAutonomous());
    Timer.clear();

    while (Competition.isAutonomous()) {
      totalSec = 15 - Timer.time(sec);
      timeMin = totalSec / 60;
      timeSec = totalSec % 60;

      Line1 << timeMin << ":" << timeSec << " Autonomous";
      Line3 << Brain.Battery.capacity() << "%";
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(Line1.str());
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print(Line3.str());
    }

    Controller1.Screen.clearScreen();
    waitUntil(Competition.isDriverControl());
    Timer.clear();
    
    while (Competition.isDriverControl()) {
      totalSec = 105 - Timer.time(sec);
      timeMin = totalSec / 60;
      timeSec = totalSec % 60;
      
      Line1 << timeMin << ":" << timeSec << " Driver";
      Line3 << Brain.Battery.capacity() << "%";
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(Line1.str());
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print(Line3.str());
    }
  }
}
/**/
