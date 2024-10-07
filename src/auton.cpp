#include <cstdio>
#include "vex.h"
#include "drive.h"
#include "auton.h"

using namespace vex;

void (*autonCallback)();

const vex::controller::button AutonSelector = Controller1.ButtonA;

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
  // autonomous actions (blue left)
  Inertial.setHeading(180, degrees);
  drivePID(-340);
  turnPID(215);
  drivePID(-330);
  MobileGoalPiston.set(true);
  turnPID(270);
  IntakeMotor.spin(forward);
  drivePID(300);
  wait(500, msec);
  turnPID(45);
  drivePID(600);
}

void autonBlueRight() {
  // autonomous actions (blue right)
  Inertial.setHeading(180, degrees);
  drivePID(-165);
  turnPID(145);
  drivePID(-470);
  MobileGoalPiston.set(true);
  turnPID(85);
  IntakeMotor.spin(forward);
  drivePID(210);
  wait(500, msec);
  turnPID(20);
  drivePID(220);
  wait(500, msec);
  turnPID(255);
  drivePID(600);
}

int AutonSelect() {
  while (true) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: None");
    printf("Screen set\n");
    autonCallback = autonNone;
    printf("Variable set\n");
    waitUntil(!AutonSelector.pressing());
    printf("Button not pressing\n");
    waitUntil(AutonSelector.pressing());
    printf("Button pressing\n");

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Auton: Red Left");
    printf("Screen set\n");
    autonCallback = autonRedLeft;
    printf("Variable set\n");
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

