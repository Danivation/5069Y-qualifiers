#include <string>
#include <sstream>
#include <math.h>
#include "vex.h"
#include "controller.h"

using namespace vex;
timer Timer;

// controller bindings
const vex::controller::axis ForwardAxis = Controller1.Axis3;
const vex::controller::axis TurnAxis = Controller1.Axis1;
const vex::controller::button IntakeInButton = Controller1.ButtonR1;
const vex::controller::button IntakeOutButton = Controller1.ButtonR2;
const vex::controller::button IntakePistonToggle = Controller1.ButtonL1;
const vex::controller::button MobileGoalPistonToggle = Controller1.ButtonDown;
const vex::controller::button MotorControlToggle = Controller1.ButtonB;

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