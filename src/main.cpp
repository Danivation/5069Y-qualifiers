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

#include "vex.h"
#include "auton.h"
#include "controller.h"
#include "drive.h"

using namespace vex;
competition Competition;

extern static void (*autonCallback)();

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
  task autons(AutonSelect);

  // when competition switch or field control is plugged in, stop auton selector, initialize competition variables, and start screen control
  waitUntil(Competition.isFieldControl() || Competition.isCompetitionSwitch());
  autons.stop();
  Competition.autonomous(autonCallback);
  Competition.drivercontrol(driver);
  Controller1.Screen.clearScreen();
  //task screen(ScreenControl);

  while (true) {
    wait(20, msec);
  }
  return 0;
}
