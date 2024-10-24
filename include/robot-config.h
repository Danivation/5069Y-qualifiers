using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial Inertial;
extern controller Controller1;
extern digital_out ArmPiston;
extern digital_out MobileGoalPiston;
extern digital_out DoinkerPiston;
extern motor IntakeMotor;
extern motor ConveyorMotor;
extern motor LMotorA;
extern motor LMotorB;
extern motor LMotorC;
extern motor RMotorA;
extern motor RMotorB;
extern motor RMotorC;
extern rotation TrackerWheel;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);