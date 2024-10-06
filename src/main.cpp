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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "controller.h"
#include "drive.h"
#include "main.h"

using namespace vex;
competition Competition;

void autonNone() {
  // successfully do nothing
  drivePID(600);
}

void autonRedLeft() {
  // autonomous actions (red left)
  Inertial.setHeading(180, degrees);
  drivePID(-165);
  turnPID(215);
  drivePID(-470);
  MobileGoalPiston.set(true);
  turnPID(275);
  IntakeMotor.spin(forward);
  drivePID(210);
  wait(500, msec);
  turnPID(340);
  drivePID(220);
  wait(500, msec);
  turnPID(105);
  drivePID(600);
}

void autonRedRight() {
  // autonomous actions (red right)
  Inertial.setHeading(180, degrees);
  drivePID(-900);
  MobileGoalPiston.set(true);
  IntakeMotor.spin(forward);
  turnPID(90);
  drivePID(600);
  wait(500, msec);
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

void driver() {
  // set coast for driver control
  LMotorA.setStopping(coast);
  LMotorB.setStopping(coast);
  LMotorC.setStopping(coast);
  RMotorA.setStopping(coast);
  RMotorB.setStopping(coast);
  RMotorC.setStopping(coast);

  task a(MotorControl);
  task b(DrivetrainControl);
  task c(IntakeControl);
  task e(IntakePistonControl);
  task d(MobileGoalPistonControl);
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

  // calibrate inertial
  Inertial.calibrate();
  wait(5, sec);
  Controller1.rumble(rumbleShort);

  // set up driver control and auton selector
  Competition.drivercontrol(driver);
  //task autons(AutonSelect);

  // stop auton selector and start screen control when competition switch is plugged in
  waitUntil(Competition.isFieldControl() || Competition.isCompetitionSwitch());
  //Competition.autonomous(autonCallback);
  Competition.autonomous(autonNone);
  //autons.stop();
  Controller1.Screen.clearScreen();
  //task screen(ScreenControl);

  while (true) {
    wait(20, msec);
  }
  return 0;
}
