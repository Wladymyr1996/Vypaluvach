#include <TimerOne.h>

//Version 1.7-0
/*
    "Vypaluvach" - is control program for CNC wood burner "CNC Vypaluvach"
    Copyright (C) 2017 Volodymyr Stadnyk
    e-mail: Wladymyr1996@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#define Dir PD3
#define Step PD4
#define Sleep PD6
#define MS1 PD5
#define MS2 PD2

#define BtnPowerSig PB0
#define OPIPowerSig PB1
#define OPIPower PB2
#define HeadPower PB3
#define Buzzer PB5

//Макроси направлення руху двигунів
#define foward 1
#define back -1

//направлення
#define left 0x01
#define right 0x02
#define up 0x03
#define down 0x04

//Макроси команд
#define cnewline 0x01  //Нова лінія
#define creturn_to_zero 0x00 //Повернення в нуль
#define c_stop 0xFF //непередбачувана зупинка двигунів
#define creturntoXzero 0x0B //Повернутися до нуля по Х
#define cmove 0x02 //Рухати в ручному режимі
#define csetzero 0x03 //Встановлення поточного положення як нуль координатної сітки
#define ctestconnect 0x04 //Пінг
#define cendline 0x05 //перехід до наступного рядка
#define csetskippedysteps 0x07 //Кількість крокв пропуску на на одну передану лінію
#define ctestproportion 0x08 //Тест пропорцфї
#define csetLine 0x0A //Встановлення лінії
#define cmovesteps 0x0C //Рухати визначену кількість кроків
#define csetSendPos 0x0D //Встановити, чи повертати дані про положення
#define cheadOn 0x0E //Увімкнути голівку/двигуни
#define cheadOff 0x0F //Увімкнути голівку/двигуни
#define cBuzzerOn 0x10 //Увімкнути сповіщення
#define cBuzzerOff 0x11  //Вимкнути сповіщення
#define csetMS 0x12
#define cshutdownOPI 0x13
#define cprePrint 0x14
#define csetPrePrintingZero 0x15
#define cprintPause 0x16
#define cprintEnd 0x17

//Мінімальний проміжок між кроками для двигунів
#define minspeed_X 3
#define minspeed_Y 2

//BaudRate
#define BaudRate 57600

//Макрос для віссі
#define axis_X 0
#define axis_Y 1

//Пропорція
#define stepsForRectX 1000
#define stepsForRectY 7500

//Макроси для чищення
#define minBack -304
#define slowBack -50
#define slowSpeed 30

//Відповіді для відправки
#define msgEnd 'f'
#define msgError 'e'
#define msgOk 'o'
#define msgPos 0x09


//Структура для поточно налаштованої лінії
struct TLine {
  //Швидкість
  unsigned int spd_ms; //в мілісекундах
  unsigned int spd_us;  //в мікросекундах

  //До якої точки рухатися
  unsigned int to_x;
};

//Точка
struct TPoint {
  int X, Y;
};

TLine line;
char MS;
TPoint current_pos;
bool bSendPosOn = false;

//Масив послідовно формованих сигналів на портах
char steps_y[8] = {0x09, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01};

char step_axis_Y; //Поточний крок для віссі

int space_y; //Проміжок між рядками
int timer;
bool bSendPos, opiPower;
double proportion; //коефіцієнт пропорції

void sendPos() {
  if (bSendPosOn) {
    Serial.write(msgPos);
    Serial.write(current_pos.X);
    Serial.write(current_pos.X >> 8);
    Serial.write(current_pos.Y);
    Serial.write(current_pos.Y >> 8);
  }
}

//Виконати крок
void do_step(char direct, char axis, int count = 1, unsigned char mPause = 0) { //Виконати крок
  //Рухаємо axis у напрямку direct
  switch (axis) {
    case axis_X: //По Х
      if (direct == back) PORTD |= (1 << Dir);
      else PORTD &= ~(1 << Dir);

      for (int i = 0; i < count; i++) {
        PORTD |= (1 << Step);
        asm("nop");
        PORTD &= ~(1 << Step);
        current_pos.X += direct;
        delay(mPause);
      }
      break;
    case axis_Y: //По Y
      for (int i = 0; i < count; i++) {
        step_axis_Y += direct;
        if (step_axis_Y == 8) step_axis_Y = 0;
        if (step_axis_Y == -1) step_axis_Y = 7;
        PORTC = steps_y[step_axis_Y];
        current_pos.Y += direct;
        delay(mPause);
      }
      break;
  }
}

void beep() {
  PORTB |= 1 << Buzzer;
  delay(30);
  PORTB &= ~(1 << Buzzer);
}

void setMS(unsigned char newMS) {
  MS = newMS;
  PORTD &= ~((1 << MS1) | (1 << MS2));
  PORTD |= ((MS & 0x01) << MS1) | (((MS & 0x02) >> 1) << MS2);
}

void setup() {
  //Ініціалізація
  DDRC = 0xff;
  DDRB = 0xfc;
  PORTB = 0x00;
  DDRD = 0xff;
  step_axis_Y = 0;
  PORTD |= (1 << Sleep);
  setMS(0);
  opiPower = false;

  space_y = 0;

  current_pos.X = 0;
  current_pos.Y = 0;
  Timer1.initialize(100000);
  Serial.begin(BaudRate);
}

void loop() {
  if (Serial.available() > 0) {
    //Читаємо вміст першого байту
    byte command = Serial.read();

    if (command == cnewline) { //Обробка нової лінії
      byte l, h; //Тим часові змінні
      while (Serial.available() < 4); //Очікуємо (якщо потрібно) повного пакету даних

      //Швидкість в мілісекундах
      h = Serial.read();
      l = Serial.read();
      line.spd_ms = (h << 8) | l;

      //Кінцеве положення
      h = Serial.read();
      l = Serial.read();
      line.to_x = (h << 8) | l;
      //Рухаємо до кінця
      do_step(foward, axis_X, line.to_x - current_pos.X, line.spd_ms);

      //Передаємо інормацію про закінчення лінії
      Serial.write(msgEnd);
    }

    if (command == cprePrint) {
      do_step(back, axis_X, 304, minspeed_X);
    }

    if (command == csetskippedysteps) { //Встановлення пропусків по рядках
      while (Serial.available() < 2);
      byte l, h;

      h = Serial.read();
      l = Serial.read();
      space_y = (h << 8) | l;
    }

    if (command == csetSendPos) { //Відключення або включення функції повернення поточної позиції
      while (Serial.available() < 1);
      byte b;

      b = Serial.read();
      if (b) {
        bSendPosOn = true;
        Timer1.attachInterrupt(sendPos);
      }
      else {
        bSendPosOn = false;
        Timer1.detachInterrupt();
      }
    }

    if (command == csetLine) { //Встановлення Y для відновлення
      while (Serial.available() < 2);
      byte l, h;
      unsigned int tmp;

      h = Serial.read();
      l = Serial.read();
      tmp = (h << 8) | l;

      current_pos.Y = -(space_y * tmp);
    }

    if (command == cmove) { //Ручний рух
      while (Serial.available() < 1); //Очікуємо ще один байт для визначення напряму руху
      byte direct = Serial.read(); //Визначаємо напрям
      while (Serial.read() != c_stop) { //Рухаємо доки не прийде команда зупинки
        if (direct == left) do_step(back, axis_X, 1, minspeed_X);
        if (direct == right) do_step(foward, axis_X, 1, minspeed_X);
        if (direct == down) do_step(back, axis_Y, 1, minspeed_Y);
        if (direct == up) do_step(foward, axis_Y, 1, minspeed_Y);
      }
    }

    if (command == cmovesteps) { //Ручний рух
      while (Serial.available() < 3); //Очікуємо ще один байт для визначення напряму руху

      byte direct = Serial.read(); //Визначаємо напрям

      byte l, h;
      unsigned int tmp;
      h = Serial.read();
      l = Serial.read();
      tmp = (h << 8) | l;

      TPoint toPoint;
      toPoint.X = current_pos.X;
      toPoint.Y = current_pos.Y;
      if (direct == left) toPoint.X -= tmp;
      if (direct == right) toPoint.X += tmp;
      if (direct == down) toPoint.Y -= tmp;
      if (direct == up) toPoint.Y += tmp;
      while ((current_pos.X != toPoint.X) || (current_pos.Y != toPoint.Y)) { //Рухаємо доки не прийде команда зупинки
        if (direct == left) do_step(back, axis_X, 1, minspeed_X);
        if (direct == right) do_step(foward, axis_X, 1, minspeed_X);
        if (direct == down) do_step(back, axis_Y, 1, minspeed_Y);
        if (direct == up) do_step(foward, axis_Y, 1, minspeed_Y);
      }
    }

    if (command == csetzero) { //Новий нуль системии координат
      current_pos.X = 0; //Обнуляємо
      current_pos.Y = 0;
      sendPos();
    }

    if (command == cendline) { //Перехід на новий рядок
      //переміщення до 0 в край
      while (current_pos.X > minBack) {
        do_step(back, axis_X);
        delay(minspeed_X);
      }
      //Чищення жала
      while (current_pos.X < 0) {
        do_step(foward, axis_X);
        delay(minspeed_X);
      }
      while (current_pos.X > minBack) {
        do_step(back, axis_X);
        delay(minspeed_X);
      }
      while (current_pos.X < slowBack) {
        do_step(foward, axis_X);
        delay(minspeed_X);
      }
      while (current_pos.X < 0) {
        do_step(foward, axis_X);
        delay(slowSpeed);
      }

      //переміщення жала на новий рядок
      unsigned int to_y = current_pos.Y - space_y;
      while (current_pos.Y != to_y) {
        do_step(back, axis_Y);
        delay(minspeed_Y);
      }
      Serial.print(msgEnd); //Кінець операції
    }

    if (command == creturn_to_zero) { //Повернення жала в нуль системи координат
      //Рухаємо його до нуля
      while (current_pos.X != 0) {
        do_step(-current_pos.X / abs(current_pos.X), axis_X);
        delay(minspeed_X);
      }
      while (current_pos.Y != 0) {
        do_step(-current_pos.Y / abs(current_pos.Y), axis_Y);
        delay(minspeed_Y);
      }
      Serial.write(msgEnd);
    }

    if (command == cprintEnd) {
      //Рухаємо його до нуля
      while (current_pos.X != 0) {
        do_step(-current_pos.X / abs(current_pos.X), axis_X);
        delay(minspeed_X);
      }
      while (current_pos.Y != 0) {
        do_step(-current_pos.Y / abs(current_pos.Y), axis_Y);
        delay(minspeed_Y);
      }
      while (current_pos.X != minBack) {
        if (current_pos.X > minBack)
          do_step(back, axis_X);
        else
          do_step(foward, axis_X);
        delay(minspeed_X);
      }
      Serial.write(msgEnd);
    }

    //Тестування пропорційності, Малюємо квадрат 1000*1000 пікселів
    if (command == ctestproportion) {
      //обнуляємо
      current_pos.X = 0;
      current_pos.Y = 0;

      //Малюємо квадрат
      while (current_pos.X != stepsForRectX) {
        do_step(foward, axis_X);
        delay(minspeed_X);
      }
      while (current_pos.Y != stepsForRectY) {
        do_step(back, axis_Y);
        delay(minspeed_X);
      }
      while (current_pos.X != 0) {
        do_step(back, axis_X);
        delay(minspeed_X);
      }
      while (current_pos.Y != 0) {
        do_step(foward, axis_Y);
        delay(minspeed_X);
      }
      Serial.print(msgOk);
    }

    //Повернення до нуля
    if (command == creturntoXzero) {
      while (current_pos.X != 0) {
        if (current_pos.X > 0)
          do_step(back, axis_X);
        else
          do_step(foward, axis_X);
        delay(minspeed_X);
      }
      Serial.write(msgEnd);
    }

    if (command == cprintPause) {
      while (current_pos.X != minBack) {
        if (current_pos.X > minBack)
          do_step(back, axis_X);
        else
          do_step(foward, axis_X);
        delay(minspeed_X);
      }
      Serial.write(msgEnd);
    }

    if (command == cheadOn) {
      PORTB |= 1 << HeadPower;
    }

    if (command == cheadOff) {
      PORTB &= ~(1 << HeadPower);
    }

    if (command == cBuzzerOn) {
      while (Serial.available() < 1) {
        PORTB |= (1 << Buzzer);
        delay(30);
        PORTB &= ~(1 << Buzzer);
        delay(100);
        PORTB |= (1 << Buzzer);
        delay(30);
        PORTB &= ~(1 << Buzzer);
        delay(1000);
      }
    }

    if (command == csetMS) {
      while (Serial.available() < 1);
      setMS(Serial.read());
    }

    if (command == cshutdownOPI) {
      while (!(PINB & (1 << OPIPowerSig)));
      PORTB &= ~(1 << OPIPower);
      opiPower = false;
    }

    if (command == csetPrePrintingZero) {
      current_pos.X = minBack; //Обнуляємо
      current_pos.Y = 0;
      sendPos();
    }
  }

  if (PINB & (1 << BtnPowerSig)) {
    if (!opiPower) {
      PORTB |= 1 << OPIPower;
      opiPower = true;
      beep();
      delay(20);
      while (PINB & (1 << BtnPowerSig));
      delay(20);
    }
  }
  asm("nop");
}
