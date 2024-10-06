#ifndef CONTROLLER_FUNCS
#define CONTROLLER_FUNCS

int DrivetrainControl();
int IntakeControl();
int IntakePistonControl();
int MobileGoalPistonControl();
int MotorControl();
int ScreenControl();
int AutonSelect();

extern void (*autonCallback)();

#endif