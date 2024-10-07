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
#include "auton.h"

using namespace vex;
competition Competition;

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
