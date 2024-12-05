#include <Arduino.h>
#include <FlexyStepper.h>
#include "motor.h"
#include "main.h"
#include "utility.h"
#include "task.h"

FlexyStepper stepperX;
FlexyStepper stepperZ;
extern int speed;
int text1 = 0;
int counter = 0;


void vDoStepperXInit(void)
{
    stepperX.connectToPins(X_step, X_dir);
    //   stepperX.setSpeedInStepsPerSecond(800);
    //   stepperX.setAccelerationInStepsPerSecondPerSecond(800);
    //   stepperX.moveRelativeInSteps(200 * 10);
    stepperX.setCurrentPositionInSteps(0);
    stepperX.setSpeedInStepsPerSecond(2000);
    // stepperX.setTargetPositionInSteps(2000000000);
    stepperX.setTargetPositionInSteps(20000);
    // stepperX.setSpeedInStepsPerSecond(2000);
    stepperX.setAccelerationInStepsPerSecondPerSecond(8000);
}

void vDoStepperZInit(void)
{
    stepperZ.connectToPins(Z_step, Z_dir);
    //   stepperX.setSpeedInStepsPerSecond(800);
    //   stepperX.setAccelerationInStepsPerSecondPerSecond(800);
    //   stepperX.moveRelativeInSteps(200 * 10);
    stepperZ.setCurrentPositionInSteps(0);
    stepperZ.setSpeedInStepsPerSecond(2000);
    // stepperX.setTargetPositionInSteps(2000000000);
    stepperZ.setTargetPositionInSteps(20000);
    // stepperZ.setSpeedInStepsPerSecond(1000);
    stepperZ.setAccelerationInStepsPerSecondPerSecond(6000);
}

void vDoStepperX(void)
{
    if (motor_state == 0)
    {
        text1 = 1;
        stepperX.setSpeedInStepsPerSecond(motorXspeed);
        //stepperX.setCurrentPositionInSteps(2000);
        stepperX.setTargetPositionInSteps(20000000);
        if (!stepperX.motionComplete())
        {
            stepperX.processMovement();
        }
    }
    if (motor_state1 == 1)
    {
        text1 = 2;
        // Serial.println("Light OFF");
        stepperX.setSpeedInStepsPerSecond(motorXspeed);
        //stepperX.setCurrentPositionInSteps(0);
        stepperX.setTargetPositionInSteps(-20000000);
        if (!stepperX.motionComplete())
        {
            stepperX.processMovement();
        }
    }
}

void vDoStepperZ(void)
{

    // stepperX.setCurrentPositionInSteps(0);
    // stepperX.setTargetPositionInSteps(200000);
    stepperZ.setSpeedInStepsPerSecond(motorZspeed);
    //stepperZ.setCurrentPositionInSteps(0);
    stepperZ.setTargetPositionInSteps(20000000);
    if (!stepperZ.motionComplete())
    {
        stepperZ.processMovement();
    }
}
