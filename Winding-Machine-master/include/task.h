#ifndef TASK_h
#define TASK_h

void vDoTaskfstm( void *pvParameters );
void vDoTaskButon( void *pvParameters );
void vDoTaskLcd( void *pvParameters );
//void vDoTaskSensors( void *pvParameters );
void TaskBlink( void *pvParameters );
void vDoTaskMotor( void *pvParameters );
extern int motor_state;
extern int motor_state1;
extern int val[10];
extern int sensors;
extern int motorXspeed;
extern int motorZspeed;
extern int potspeed;

#endif  // TASK_h