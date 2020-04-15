#include <Arduino.h>
#include <LiquidCrystal.h>             // Лобавляем необходимую библиотеку
LiquidCrystal lcd(12, 11, 4, 5, 6, 7); // (RS, E, DB4, DB5, DB6, DB7)
byte p[8] =
    {
        B11111,
        B10001,
        B10001,
        B10001,
        B10001,
        B10001,
        B10001,
        B00000,
};

byte y[8] =
    {
        B00100,
        B10001,
        B10001,
        B10001,
        B10011,
        B10101,
        B11001,
        B00000,
};
byte gh[8] =
    {
        B10101,
        B10101,
        B10101,
        B01110,
        B10101,
        B10101,
        B10101,
        B00000,
};
byte g[8] =
    {
        B11111,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B00000,
};
byte l[8] =
    {
        B00011,
        B00101,
        B01001,
        B10001,
        B10001,
        B10001,
        B10001,
        B00000,
};

byte ch[8] =
    {
        B10001,
        B10001,
        B10001,
        B11111,
        B00001,
        B00001,
        B00001,
        B00000,
};

byte smile[8] =
    {
        B00000,
        B01010,
        B00000,
        B00000,
        B10001,
        B01110,
        B00000,
        B00000,
};
byte thup[8] =
    {
        B11000,
        B11000,
        B11110,
        B10011,
        B10101,
        B10011,
        B10101,
        B01110,
};
byte heart[8] =
    {
        B00000,
        B00000,
        B01010,
        B11111,
        B11111,
        B01110,
        B00100,
        B00000,
};

String strData = "";
boolean recievedFlag;

//Initialise menu position
int menu_row = 0;
int menu_row_next = menu_row + 1;
//menu points
const char *menus[] = {
    "\1""OD""\5""OTOBKA", // 0
    "\1""POBEPKA", // 1
    "3A""\1""yCK", // 2
    "\6\1""OK!!!!!", // 3
};
//count menu size
byte menu_size = sizeof(menus)/sizeof(menus[0]);

//check menu position
void menu_check_row()
{
  menu_row_next = menu_row + 1;
  if (menu_row > menu_size-1)
  {
    menu_row = 0;
    menu_row_next = 1;
  }
  if (menu_row < 0)
  {
    menu_row = menu_size-1;
    menu_row_next = 0;
  }
  if (menu_row == menu_size-1)
  {
    menu_row_next = 0;
  }
}

//output menu on lcd
void menu_print()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.setCursor(1, 0);
  lcd.print(menus[menu_row]);
  lcd.setCursor(0, 1);
  lcd.print(menus[menu_row_next]);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2); // Задаем размерность экрана
  lcd.createChar(1, p);
  lcd.createChar(2, y);
  lcd.createChar(3, gh);
  lcd.createChar(4, l);
  lcd.createChar(5, g);
  lcd.createChar(6, ch);
  lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
  lcd.print("\1""OCETUTE CA""\2""T!");
  lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки
  lcd.print("https://mirv.top ");
  delay(5000);
  lcd.clear();
  menu_print();
}

void loop()
{

  while (Serial.available() > 0)
  {                                 // ПОКА есть что то на вход
    strData += (char)Serial.read(); // забиваем строку принятыми данными
    recievedFlag = true;            // поднять флаг что получили данные
    delay(2);                       // ЗАДЕРЖКА. Без неё работает некорректно!
  }

  if (recievedFlag)
  {                          // если данные получены
    Serial.println(strData); // вывести

    if (strData == "2")
    {
      menu_row++;
    }
    if (strData == "1")
    {
      menu_row--;
    }

    menu_check_row();
    menu_print();

    Serial.println("Номер пункта меню:" + String(menu_row));
    Serial.println("Название:" + String(menus[menu_row]));
    Serial.println("Номер след. пункта меню:" + String(menu_row_next));
    Serial.println("Название:" + String(menus[menu_row_next]));
    strData = "";         // очистить
    recievedFlag = false; // опустить флаг
  }
}