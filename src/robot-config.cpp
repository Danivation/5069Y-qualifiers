#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
inertial Inertial = inertial(PORT14);
controller Controller1 = controller(primary);
digital_out IntakePiston = digital_out(Brain.ThreeWirePort.A);
digital_out MobileGoalPiston = digital_out(Brain.ThreeWirePort.B);
motor IntakeMotor = motor(PORT4, ratio6_1, true);
motor LMotorA = motor(PORT11, ratio6_1, false);
motor LMotorB = motor(PORT12, ratio6_1, false);
motor LMotorC = motor(PORT13, ratio6_1, false);
motor RMotorA = motor(PORT1, ratio6_1, true);
motor RMotorB = motor(PORT2, ratio6_1, true);
motor RMotorC = motor(PORT3, ratio6_1, true);
rotation TrackerWheel = rotation(PORT16, false);
digital_out ArmPiston = digital_out(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}