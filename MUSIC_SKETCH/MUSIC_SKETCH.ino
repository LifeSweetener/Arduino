#include <LiquidCrystal.h>
#define LCD_RS 13
#define LCD_E 12
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7
#define BTN_1 2
#define BTN_2 8
#define LED_1 3
#define LED_2 10
#define ZUMMER 9

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);  // создать компьютерный объект LCD-экрана

void setup() {
  lcd.begin(16, 2);  // инициализировать LCD-экран
  lcd.setCursor(0,0);  // установить начальное положение вывода текста на экран
  lcd.display();  // сделать текст на экране видимым

  pinMode(BTN_1, INPUT_PULLUP);  // установить пин с первой кнопкой как входной сигнал
  pinMode(BTN_2, INPUT_PULLUP);  // установить пин со второй кнопкой как входной сигнал
  pinMode(LED_1, OUTPUT);  // установить пин с зелёным индикатором как выходной сигнал
  pinMode(LED_2, OUTPUT);  // установить пин с жёлтым индикатором как выходной сигнал
  pinMode(ZUMMER, OUTPUT);  // установить пин с зуммером как выходной сигнал
}

bool Gis = false;  // проиграть ноту Соль-диез
bool A = false;  // проиграть ноту Ля
bool D = false;  // проиграть ноту Ре
bool E = false;  // проиграть ноту Ми

void show() {
  if (Gis)
    lcd.print("Gis");
  else if (A) {
    lcd.print("A");
  }
  else if (D) {
    lcd.print("D");
  }
  else if (E) {
    lcd.print("E");
  }
}

void playNote(int note) {
  switch(note) {
    case 1:  // 1-ая ступень (тоника - A) гаммы ля мажор
      tone(ZUMMER, 220, 1000);
      break;
    case 7:  // 7-ая ступень (Gis; на ней строится уменьшенное трезвучие) гаммы ля мажор
      tone(ZUMMER, 207, 1000);
      break;
    case 4:  // 4-ая ступень (субдоминанта - D) гаммы ля мажор
      tone(ZUMMER, 293.66, 1000);
      break;
    case 5:  // 5-ая ступень (доминанта - E) гаммы ля мажор
      tone(ZUMMER, 329.63, 1000);
      break;
    default:
      analogWrite(ZUMMER, 0);  // выключить зуммер (пьезопищалку)
  }
}

void loop() {
  bool btn1State = !digitalRead(BTN_1);  // нажата ли первая кнопка
  bool btn2State = !digitalRead(BTN_2);  // нажата ли вторая кнопка
  bool btn12StateOn = !digitalRead(BTN_1) && !digitalRead(BTN_2);  // зажаты ли обе кнопки
  bool btn12StateOff = digitalRead(BTN_1) && digitalRead(BTN_2);  // не тронуты ли обе кнопки
  
  //===================================================================
  
  if (btn12StateOn && !btn12StateOff) {  // ЕСЛИ ЗАЖАТЫ СРАЗУ ДВЕ КНОПКИ, ТО...
    digitalWrite(LED_1, HIGH);  // включить первый индикатор (зеленый)
    digitalWrite(LED_2, HIGH);  // включить второй индикатор (желтый)
    Gis = true;  // установить ноту, которую нужно высветить на экране
    A = false;
    D = false;
    E = false;
    playNote(7);  // сыграть ноту G# (седьмую ступень гаммы Ля мажор)
    return;
  }
  if (!btn12StateOn && !btn12StateOff && !btn1State && btn2State) {  // ЕСЛИ ЗАЖАТА ЛЕВАЯ КНОПКА (С ЖЕЛТЫМ ИНДИКАТОРОМ), ТО...
    digitalWrite(LED_1, LOW);  // выключить первый индикатор (зеленый)
    digitalWrite(LED_2, HIGH);  // включить второй индикатор (желтый)
    Gis = false;
    A = false;
    D = true;  // установить ноту, которую нужно высветить на экране
    E = false;
    playNote(4);  // сыграть ноту D (четвертую ступень гаммы Ля мажор)
    return;
  }
  if (!btn12StateOn && !btn12StateOff && btn1State && !btn2State) {  // ЕСЛИ ЗАЖАТА ПРАВАЯ КНОПКА (С ЗЕЛЕНЫМ ИНДИКАТОРОМ), ТО...
    digitalWrite(LED_1, HIGH);  // включить первый индикатор (зеленый)
    digitalWrite(LED_2, LOW);  // выключить второй индикатор (желтый)
    Gis = false;
    A = false;
    D = false;
    E = true;  // установить ноту, которую нужно высветить на экране
    playNote(5);  // сыграть ноту E (пятую ступень гаммы Ля мажор)
    return;
  }
  if (!btn12StateOn && btn12StateOff) {  // ЕСЛИ НИКАКИЕ КНОПКИ НЕ НАЖАТЫ, ТО...
    digitalWrite(LED_1, LOW);  // выключить первый индикатор (зеленый)
    digitalWrite(LED_2, LOW);  // выключить второй индикатор (желтый)
    Gis = false;
    A = true;  // установить ноту, которую нужно высветить на экране
    D = false;
    E = false;
    playNote(1);  // сыграть ноту A (первую ступень гаммы Ля мажор)
    return;
  }
  
  show();  // ВЫСВЕТИТЬ НАЗВАНИЕ ПРОИГРЫВАЕМОЙ НОТЫ НА ЭКРАНЕ (LCD-ЭКРАНЕ)
}
