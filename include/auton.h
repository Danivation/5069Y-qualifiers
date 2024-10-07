#ifndef AUTON_FUNCS
#define AUTON_FUNCS

extern void (*autonCallback)();

void autonNone();
void autonRedLeft();
void autonRedRight();
void autonBlueLeft();
void autonBlueRight();
int autonSelect();

#endif