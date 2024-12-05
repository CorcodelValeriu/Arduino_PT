#ifndef MOTOR_h
#define MOTOR_h
#include <arduino.h>
#include <FlexyStepper.h>
#include <stdlib.h>
extern FlexyStepper stepperX;
extern FlexyStepper stepperZ;
extern int text1;
void vDoStepperXInit(void);
void vDoStepperZInit(void);
void vDoStepperX(void);
void vDoStepperZ(void);
#endif
