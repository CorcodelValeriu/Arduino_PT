#include <LiquidCrystal_I2C.h>
#include <arduino.h>
//#include <Encoder.h>
#include "GyverEncoder.h"
#include "main.h"
#include "utility.h"
//#include <LiquidCrystal_I2C_Menu.h>
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
// Encoder myEnc(CLK, DT);
int value = 0;

Encoder enc1(CLK, DT, SW, TYPE2); // для работы c кнопкой и сразу выбираем тип

int speed;
int vals[SETTINGS_AMOUNT]; // массив параметров
int8_t arrowPos = 0;
int8_t screenPos = 0; // номер "экрана"
const char *settingsNames[] = {
    "Speed",
    "Home",
};

void vDoLCDInit(void)
{
  while (lcd.begin(COLUMS, ROWS) != 1) // colums - 20, rows - 4
  {
    // Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
  }
  printGUI();
}

void vDoLCD(void)
{
  /* prints static text */
  lcd.setCursor(0, 0); // set 1-st colum & 2-nd row, 1-st colum & row started at zero
}



void vDoENC(void)
{
  enc1.tick();

  if (enc1.isTurn())
  {
    int increment = 0; // локальная переменная направления
    // получаем направление
    if (enc1.isRight())
      increment = 1;
    if (enc1.isLeft())
      increment = -1;
    arrowPos += increment;                                  // двигаем курсор
    arrowPos = constrain(arrowPos, 0, SETTINGS_AMOUNT - 1); // ограничиваем
    increment = 0;                                          // обнуляем инкремент
    if (enc1.isRightH())
      increment = 1;
    if (enc1.isLeftH())
      increment = -1;
    if (arrowPos == 0)
      vals[arrowPos] += increment * 100;
    if (arrowPos == 1)
      vals[arrowPos] += increment;
    // vals[arrowPos] += increment;  // меняем параметры
    speed = vals[0];
    printGUI();
  }
}

void printGUI()
{
  lcd.clear();
  screenPos = arrowPos / LINES; // ищем номер экрана (0..3 - 0, 4..7 - 1)

  for (byte i = 0; i < LINES; i++)
  {                      // для всех строк
    lcd.setCursor(0, i); // курсор в начало
    // если курсор находится на выбранной строке
    if (arrowPos == LINES * screenPos + i)
      lcd.write(126); // рисуем стрелку
    else
      lcd.write(32); // рисуем пробел
    // если пункты меню закончились, покидаем цикл for
    if (LINES * screenPos + i == SETTINGS_AMOUNT)
      break;
    // выводим имя и значение пункта меню
    lcd.print(settingsNames[LINES * screenPos + i]);
    lcd.print(": ");
    lcd.print(vals[LINES * screenPos + i]);
  }
}