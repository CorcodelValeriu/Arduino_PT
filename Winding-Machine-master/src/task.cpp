#include <Arduino.h>
#include "FreeRTOS_ARM.h"
#include <FlexyStepper.h>
#include "task.h"
#include "motor.h"
#include "main.h"
#include "utility.h"
int val[10];
int val1[10];
int lightON = 0;  // light status
int lightON1 = 0; // light status
int pushed = 0;   // push status
int pushed1 = 0;  // push status
int motor_state = 0;
int motor_state1 = 0;
int cmd = 1;
int sensors = 0;
int motorXspeed = 0;
int motorZspeed = 0;
int potspeed = 0;

enum fstm
{
  Init,
  Home,
  Idle,
  Run,
  Stop,
  Error
} state = Init;

void vDoTaskfstm(void *pvParameters)
{
  char *pcTaskName;
  pcTaskName = (char *)pvParameters;
  Serial.println(pcTaskName);
  for (;;)
  {
    switch (state)
    {
    case Init: // initializare pini, initializare pini
               // Serial.print("Init");
      vDoStepperXInit();
      vDoStepperZInit();
      vTaskSuspend(TaskHandle_1);
      state = Home;
      // Serial.print("Init");
      break;
    case Home: // Porneste al doilea state machine cu starea motoarelor
      // vDoGoHome();
      stepperX.moveToHomeInSteps(1, 3000, 2000000, SW2);
      motor_state = 0;
      state = Idle;
      break;
    case Idle: // astept comanda (Run/Stop)
      // Serial.print("Idle");
      cmd = digitalRead(SW3);
      if (cmd == HIGH)
      {
        // Serial.print("Idle");
        state = Run;
      }
      else
      {
        state = Idle;
      }

      break;

    case Run: // Porneste al doilea state machine cu starea motoarelor
      vTaskResume(TaskHandle_1);
      cmd = digitalRead(SW3);
      if (cmd == LOW || potspeed < 200)
      {
        state = Stop;
      }

      if (val[5] == HIGH && val1[5] == HIGH)
      {
        state = Stop;
      }

      break;

    case Stop: // Astept comanda de la switch
      vTaskSuspend(TaskHandle_1);
      cmd = digitalRead(SW3);
      if (cmd == HIGH && digitalRead(S1) == LOW && potspeed > 200)
      {
        state = Run;

        if (val[5] == LOW && val1[5] == LOW)
        {
          state = Run;
        }
        else
        {
          state = Stop;
        }
      }

      break;

    case Error:
      // vTaskSuspend(TaskHandle_1);
      // Serial.print("Error");
      break;
    }
    // vTaskDelay(10 / portTICK_PERIOD_MS); // wait for 10 ms
  }
}

void vDoTaskButon(void *pvParameters) // Tasku-ul
{
  char *pcTaskName;

  /* The string to print out is passed in via the parameter.  Cast this to a
  character pointer. */
  pcTaskName = (char *)pvParameters;
  Serial.println(pcTaskName);

  /* As per most tasks, this task is implemented in an infinite loop. */
  for (;;)
  {
    val[0] = digitalRead(SW2);
    val1[0] = digitalRead(SW1);
    vTaskDelay(15 / portTICK_PERIOD_MS);
    val[1] = digitalRead(SW2);
    val1[1] = digitalRead(SW1);
    vTaskDelay(15 / portTICK_PERIOD_MS);
    val[2] = digitalRead(SW2);
    val1[2] = digitalRead(SW1);
    vTaskDelay(15 / portTICK_PERIOD_MS);
    val[3] = digitalRead(SW2);
    val1[3] = digitalRead(SW1);
    vTaskDelay(15 / portTICK_PERIOD_MS);
    val[4] = digitalRead(SW2);
    val1[4] = digitalRead(SW1);
    if (val[0] == val[1] && val[1] == val[2] && val[2] == val[3] && val[3] == val[4])
    {
      val[5] = val[4];

      if (val[4] == HIGH && lightON == LOW)
      {
        pushed = 1 - pushed;
      }
      lightON = val[4];
      if (pushed == LOW)
      {
        motor_state = 1;
        pushed1 = HIGH;
      }
      if (pushed == HIGH)
      {
        motor_state1 = 0;
        pushed1 = LOW;
      }
    }
    if (val1[0] == val1[1] && val1[1] == val1[2] && val1[2] == val1[3] && val1[3] == val1[4])
    {
      val1[5] = val1[4];
      if (val1[4] == HIGH && lightON1 == LOW)
      {
        pushed1 = 1 - pushed1;
      }

      lightON1 = val1[4];

      if (pushed1 == HIGH)
      {
        motor_state1 = 1;
        pushed = LOW;
      }
      if (pushed1 == LOW)
      {
        motor_state = 0;
        pushed = HIGH;
      }
    }
  }

  /* Analog acqusition */
  // vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for 100 ms
}

void vDoTaskLcd(void *pvParameters)
{
  char *pcTaskName;

  /* The string to print out is passed in via the parameter.  Cast this to a
  character pointer. */
  pcTaskName = (char *)pvParameters;
  Serial.println(pcTaskName);
  // vDoLCDInit();

  /* As per most tasks, this task is implemented in an infinite loop. */
  for (;;)
  {
    // vDoENC();
    //   vTaskDelay( 200 / portTICK_PERIOD_MS ); // wait for 200 ms
    // motorXinitspeed = potspeed;
    // motorZinitspeed = potspeed;
    motorXspeed = potspeed / 5;
    motorZspeed = potspeed;
    if (digitalRead(S2) == HIGH && digitalRead(S1) == LOW)
    {
      motorXspeed = (SPEED75 * motorXspeed);
      motorZspeed = (SPEED75 * motorZspeed);
    }
    if (digitalRead(S2) == HIGH && digitalRead(S1) == HIGH)
    {
      motorXspeed = (SPEED50 * motorXspeed);
      motorZspeed = (SPEED50 * motorZspeed);
    }
    if (digitalRead(S2) == LOW && digitalRead(S1) == HIGH)
    {
      state = Stop;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // wait for 200 ms
  }
}

void TaskBlink(void *pvParameters)
{
  // (void)pvParameters;
  // Serial.println("TaskBlink Started");

  /* The string to print out is passed in via the parameter.  Cast this to a
  character pointer. */
  int step;
  for (;;) // A Task shall never return or exit.
  {
    step = stepperX.getCurrentPositionInSteps();
    Serial.print(text1);
    Serial.print("  ");
    // Serial.println(motorXspeed);
    // Serial.println(motorZspeed);
    Serial.println(step);
    // Serial.println(analogRead(POT));
    potspeed = analogRead(POT) * 2;
    vTaskDelay(500 / portTICK_PERIOD_MS); // wait for one second
  }
}

void vDoTaskMotor(void *pvParameters)
{
  char *pcTaskName;

  pcTaskName = (char *)pvParameters;
  Serial.println(pcTaskName);

  for (;;)
  {
    vDoStepperX();
    vDoStepperZ();
  }
}

// void vDoTaskSensors(void *pvParameters)
// {
//   char *pcTaskName;

//   /* The string to print out is passed in via the parameter.  Cast this to a
//   character pointer. */
//   pcTaskName = (char *)pvParameters;
//   Serial.println(pcTaskName);
//   /* As per most tasks, this task is implemented in an infinite loop. */
//   for (;;)
//   {

//     // if (digitalRead(S2) == LOW)
//     // {
//     // sensors = 0;
//     //   vTaskDelay(200 / portTICK_PERIOD_MS); // wait for 200 ms
//     // }
//     // else
//     // {
//     //   sensors = 500;
//     //   vTaskDelay(200 / portTICK_PERIOD_MS); // wait for 200 ms
//     // }
//     // if (digitalRead(S1) == LOW)
//     // {
//     //   sensors = 0;
//     //   vTaskDelay(200 / portTICK_PERIOD_MS); // wait for 200 ms
//     // }
//     // else
//     // {
//     //   sensors = -500;
//     //   vTaskDelay(200 / portTICK_PERIOD_MS); // wait for 200 ms
//     // }
//     vTaskDelay(200 / portTICK_PERIOD_MS); // wait for 200 ms
//   }
// }