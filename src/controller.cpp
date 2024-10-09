#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "vex.h"
#include "controller.h"
#include "drive.h"

using namespace vex;
timer Timer;

void (*autonCallback)();

// controller bindings
const vex::controller::axis ForwardAxis = Controller1.Axis3;
const vex::controller::axis TurnAxis = Controller1.Axis1;
const vex::controller::button IntakeInButton = Controller1.ButtonR1;
const vex::controller::button IntakeOutButton = Controller1.ButtonR2;
const vex::controller::button IntakePistonToggle = Controller1.ButtonL1;
const vex::controller::button MobileGoalPistonToggle = Controller1.ButtonDown;
const vex::controller::button ArmPistonToggle = Controller1.ButtonL2;
const vex::controller::button MotorControlToggle = Controller1.ButtonB;
const vex::controller::button AutonSelector = Controller1.ButtonA;

double motorSetting;              // motor rpm multiplier (x100)
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
      waitUntil(!IntakeInButton.pressing());
      IntakeMotor.stop();
    }
    if (IntakeOutButton.pressing()) {
      IntakeMotor.spin(reverse);
      waitUntil(!IntakeOutButton.pressing());
      IntakeMotor.stop();
    }
  }
}

int IntakePistonControl() {
  while (true) {
    IntakePiston.set(true);
    waitUntil(!IntakePistonToggle.pressing());
    waitUntil(IntakePistonToggle.pressing());

    IntakePiston.set(false);
    waitUntil(!IntakePistonToggle.pressing());
    waitUntil(IntakePistonToggle.pressing());
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
  drivePID(-900);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(90);
  drivePID(600);
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

int AutonSelect() {
  while (true) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: None");
    printf("Screen set\n");

    std::cout << autonCallback << "\n";
    autonCallback = autonNone;
    printf("Variable set\n");
    std::cout << autonCallback << "\n";
    
    waitUntil(!AutonSelector.pressing());
    printf("Button not pressing\n");
    waitUntil(AutonSelector.pressing());
    printf("Button pressing\n");


    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Red Left");
    printf("Screen set\n");
    
    std::cout << autonCallback << "\n";
    autonCallback = autonRedLeft;
    printf("Variable set\n");
    std::cout << autonCallback << "\n";

    waitUntil(!AutonSelector.pressing());
    printf("Button not pressing\n");
    waitUntil(AutonSelector.pressing());
    printf("Button pressing\n");


    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Red Right");
    printf("Screen set\n");
    autonCallback = autonRedRight;
    printf("Variable set\n");
    waitUntil(!AutonSelector.pressing());
    printf("Button not pressing\n");
    waitUntil(AutonSelector.pressing());
    printf("Button pressing\n");

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Blue Left");
    printf("Screen set\n");
    autonCallback = autonBlueLeft;
    printf("Variable set\n");
    waitUntil(!AutonSelector.pressing());
    printf("Button not pressing\n");
    waitUntil(AutonSelector.pressing());
    printf("Button pressing\n");

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Blue Right");
    printf("Screen set\n");
    autonCallback = autonBlueRight;
    printf("Variable set\n");
    waitUntil(!AutonSelector.pressing());
    printf("Button not pressing\n");
    waitUntil(AutonSelector.pressing());
    printf("Button pressing\n");
  }
}

/*
int ScreenControl() {
  while (true) {
    // X:XX Auton/Driver
    //
    // XX%
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
    Controller1.Screen.clearScreen();
  }
}
*/
