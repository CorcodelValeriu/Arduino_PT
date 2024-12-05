#ifndef MAIN_h
#define MAIN_h
#include "FreeRTOS_ARM.h"

#define X_step 5 //step motor mic  
#define Z_step 2 //step motor mare   
#define X_dir 4 //dir motor mic   
#define Z_dir 1 //step motor mare
#define SW1  7 //End trip right  
#define SW2  6  //End trip left   
#define SW3  8  // Run/Stop switch   
#define S1   10   //Acum high
#define S2   11   //Acum low
#define CLK 26 //pinul clk la encoder
#define DT  24 //pinul dt la encoder
#define SW 22  //pinul sw la encoder
#define POT A0  //pinul sw la encoder
#define COLUMS           16
#define ROWS             2
#define LINES 2   // количество строк дисплея
#define SETTINGS_AMOUNT 2  // количество настроек
#define SPEED75           0.75 //setarea 75% din viteza
#define SPEED50           0.5 //setarea 50% din viteza
#define SPEED25           0.25 //setarea 25% din viteza

extern TaskHandle_t TaskHandle_1;
// ------------------------------------ End ---------------------------------
#endif

