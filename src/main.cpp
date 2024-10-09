/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Daniel Velasco                                            */
/*    Created:      Wed Aug 28 2024                                           */
/*    Description:  5069Y Competition Code (qualifier rounds)                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Inertial             inertial      14              
// Controller1          controller                    
// IntakePiston         digital_out   A               
// MobileGoalPiston     digital_out   B               
// IntakeMotor          motor         4               
// LMotorA              motor         11              
// LMotorB              motor         12              
// LMotorC              motor         13              
// RMotorA              motor         1               
// RMotorB              motor         2               
// RMotorC              motor         3               
// TrackerWheel         rotation      15              
// ArmPiston            digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include <iostream>
#include "vex.h"
//#include "auton.h"
#include "controller.h"
#include "drive.h"

using namespace vex;
competition Competition;

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

void driver() {
  // set coast for driver control
  LMotorA.setStopping(coast);
  LMotorB.setStopping(coast);
  LMotorC.setStopping(coast);
  RMotorA.setStopping(coast);
  RMotorB.setStopping(coast);
  RMotorC.setStopping(coast);
  
  task autons(AutonSelect);
  task a(MotorControl);
  task b(DrivetrainControl);
  task c(IntakeControl);
  task d(IntakePistonControl);
  task e(MobileGoalPistonControl);
  task f(ArmPistonControl);
}

int main() {
  // initialize things i guess
  vexcodeInit();

  // set brake for accurate auton
  LMotorA.setStopping(brake);
  LMotorB.setStopping(brake);
  LMotorC.setStopping(brake);
  RMotorA.setStopping(brake);
  RMotorB.setStopping(brake);
  RMotorC.setStopping(brake);

  // motor things
  IntakeMotor.setStopping(hold);
  IntakeMotor.setVelocity(600, rpm);

  // set starting piston positions
  MobileGoalPiston.set(false);
  IntakePiston.set(true);
  ArmPiston.set(false);

  // calibrate inertial
  Inertial.calibrate();
  wait(5, sec);
  Controller1.rumble(rumbleShort);

  // set up auton selector
  //task autons(AutonSelect);

  // when competition switch or field control is plugged in, stop auton selector, initialize competition variables, and start screen control
  waitUntil(Competition.isFieldControl() || Competition.isCompetitionSwitch());
  //autons.stop();
  Competition.drivercontrol(driver);
  Competition.autonomous(autonCallback);
  Controller1.Screen.clearScreen();
  //task screen(ScreenControl);

  while (true) {
    wait(20, msec);
  }
  return 0;
}
