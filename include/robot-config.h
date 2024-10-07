using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial Inertial;
extern controller Controller1;
extern digital_out IntakePiston;
extern digital_out MobileGoalPiston;
extern motor IntakeMotor;
extern motor LMotorA;
extern motor LMotorB;
extern motor LMotorC;
extern motor RMotorA;
extern motor RMotorB;
extern motor RMotorC;
extern rotation TrackerWheel;
extern digital_out ArmPiston;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );