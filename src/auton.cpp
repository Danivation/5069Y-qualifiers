#include <iostream>
#include <cstdio>
#include "vex.h"
#include "auton.h"
#include "drive.h"

using namespace vex;

void (*autonCallback)();

// controller bindings
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

