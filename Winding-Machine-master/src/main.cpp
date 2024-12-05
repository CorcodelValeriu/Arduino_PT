#include <Arduino.h>
#include "FreeRTOS_ARM.h"
#include "task.h"
#include <LiquidCrystal_I2C.h>
#include "main.h"
#include <Wire.h>
#include "motor.h"


/* Define the strings that will be passed in as the task parameters.  These are
defined const and off the stack to ensure they remain valid when the tasks are
executing. */
const char *pcTextForTask10ms = "vDoTaskfstm Started\r\n";
const char *pcTextForTask100ms = "vDoTaskButon Started\r\n";
const char *pcTextForTaskLcd = "vDoTaskLcd Started\r\n";
//const char *pcTextForTaskSensors = "vDoTaskSensors Started\r\n";
const char *pcTextForTaskMotor = "vDoTaskMotor Started\r\n";

uint32_t u32WhileCnt = 0;
TaskHandle_t TaskHandle_1;
void setup(void)
{
  Serial.begin(9600);

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(X_step, OUTPUT);
  digitalWrite(X_step, LOW);
  pinMode(X_dir, OUTPUT);
  digitalWrite(X_dir, LOW);
  pinMode(Z_step, OUTPUT);
  digitalWrite(Z_step, LOW);
  pinMode(Z_dir, OUTPUT);
  digitalWrite(Z_dir, LOW);
  // pinMode(MOTOR_EN,OUTPUT);
  // digitalWrite(MOTOR_EN, LOW);

  /* Create two instances of the continuous processing task, both at priority 1. */
  xTaskCreate(vDoTaskMotor, "Task Stepper Control", 4000, (void *)pcTextForTaskMotor, 1, &TaskHandle_1);
  xTaskCreate(vDoTaskfstm, "Task fstm", 1000, (void *)pcTextForTask10ms, 1, NULL);
  xTaskCreate(vDoTaskButon, "Task 100 ms", 1000, (void *)pcTextForTask100ms, 1, NULL);
  xTaskCreate(vDoTaskLcd, "Task For LCD Control", 2000, (void *)pcTextForTaskLcd, 1, NULL);
  xTaskCreate(TaskBlink, "Toggle LED", 1000, NULL, 1, NULL);
  //xTaskCreate(vDoTaskSensors, "Task For Sensors Control", 2000, (void *)pcTextForTaskLcd, 1, NULL);

  /* Start the scheduler so our tasks start executing. */

  vTaskStartScheduler();

  for (;;)
    ;
}

void loop()
{

  /* Do Nothing */
}
