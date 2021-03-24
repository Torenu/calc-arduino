/*
atmega32 calculator project by Torenu :D

16x2 lcd connected to pins 8-13, no LED
5 rows of 4 buttons each connected to pins A0-A4 using resistor network to divide voltage
powered up with 9v battery: https://i.stack.imgur.com/7UVD8.png

feel free to use this program for non-commercial projects
borifed@yandex.ru

KEYMAP:
7 8 9 * C
4 5 6 / √
1 2 3 + 
. 0 = - 
AYAYA
*/

#include <LiquidCrystal.h>
#define NO_KEY '$'
#define int int32_t

LiquidCrystal lcd(8, 9, 10, 11, 12, 13); //SET YOUR OWN PINS

void setup()
{
  lcd.begin(16,2);
  lcd.print("=^_^="); 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  delay(2000);
  lcd.clear();
  lcd.print(0);
}

char getKey() //use this function to detect pressed button
{
  char ans = NO_KEY;
  int r1 = analogRead(A4);
  int r2 = analogRead(A3);
  int r3 = analogRead(A2);
  int r4 = analogRead(A1);
  int r5 = analogRead(A0);
  while (r1 > 1005) {delay(100); ans = '7'; r1 = analogRead(A4);}
  while (r1 > 950) {delay(100); ans = '4'; r1 = analogRead(A4);}
  while (r1 > 500) {delay(100); ans = '1'; r1 = analogRead(A4);}
  while (r1 > 400) {delay(100); ans = '.'; r1 = analogRead(A4);}
  while (r2 > 1005) {delay(100); ans = '8'; r2 = analogRead(A3);}
  while (r2 > 950) {delay(100); ans = '5'; r2 = analogRead(A3);}
  while (r2 > 500) {delay(100); ans = '2'; r2 = analogRead(A3);}
  while (r2 > 400) {delay(100); ans = '0'; r2 = analogRead(A3);}
  while (r3 > 1005) {delay(100); ans = '9'; r3 = analogRead(A2);}
  while (r3 > 950) {delay(100); ans = '6'; r3 = analogRead(A2);}
  while (r3 > 500) {delay(100); ans = '3'; r3 = analogRead(A2);}
  while (r3 > 400) {delay(100); ans = '='; r3 = analogRead(A2);}
  while (r4 > 1005) {delay(100); ans = '*'; r4 = analogRead(A1);}
  while (r4 > 950) {delay(100); ans = '/'; r4 = analogRead(A1);}
  while (r4 > 500) {delay(100); ans = '+'; r4 = analogRead(A1);}
  while (r4 > 400) {delay(100); ans = '-'; r4 = analogRead(A1);}
  while (r5 > 1005) {delay(100); ans = 'C'; r5 = analogRead(A0);}
  while (r5 > 950) {delay(100); ans = 'v'; r5 = analogRead(A0);}
  delay(50);
  return ans;
}

double first = 0; //first number for calculation
double typing = 0; //the number that we are currently typing in
byte operation = -1;
byte decimal = 0;
bool s = true; //clearing 0 before typing first number

void loop() //calculations and output
{
  char key = getKey();
  if (key >= '0' && key <= '9')
  {
    if (s) lcd.clear();
    s = false;
    typing *= 10;
    typing += key-'0';
    if (decimal) decimal++;
    lcd.print(key);
  }
  if (key == '*' || key == '/' || key == '+' || key == '-' || key == 'v')
  {
    if (typing && !first) 
    {
      first = typing;
      for (int i = 1; i<decimal; i++) first /= 10;
      typing = 0;
      decimal = 0;
    }
    if (key == '*') operation = 0;
    if (key == '/') operation = 1;
    if (key == '+') operation = 2;
    if (key == '-') operation = 3;
    if (key == 'v') operation = 4;
    lcd.setCursor(15, 0);
    lcd.print(key);
    lcd.setCursor(0, 1);
  }
  if (key == '.')
  {
    if(!decimal) decimal = 1;
    lcd.print(key);
  }
  if (key == '=')
  {
    for (int i = 1; i<decimal; i++) typing /= 10;
    lcd.clear();
    if (operation == 0)
    {
      lcd.print(first * typing);
    }
    if (operation == 1 && typing == 0)
    {
      lcd.print("no");
    }
    if (operation == 1 && typing != 0)
    {
      lcd.print(first / typing);
    }
    if (operation == 2)
    {
      lcd.print(first + typing);
    }
    if (operation == 3)
    {
      lcd.print(first - typing);
    }
    if (operation == 4)
    {
      lcd.print(sqrt(first));
    }
    first = 0;
    typing = 0;
    decimal = 0;
    operation = -1;
    s = true;
  }
  if (key == 'C')
  {
    lcd.clear();
    lcd.print(0);
    first = 0;
    typing = 0;
    decimal = 0;
    operation = -1;
    s = true;
  }
}
