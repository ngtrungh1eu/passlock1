#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define Password_Length 7

Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int pos = 0;

char Data[Password_Length];
char Master[Password_Length] = "123456";
byte data_count = 0, master_count = 0;

bool Pass_is_good;
bool door = false; // Giá trị ban đầu của cửa
char customKey;


/*---Chuẩn bị hệ thống Keypad---*/

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup()
{
  myservo.attach(9, 2000, 2400);
  ServoClose();
  lcd.begin(16, 2);
  lcd.print("Khoa so dien tu");
  loading("IOT102-Team8");
  lcd.clear();
}


void loop()
{
  if (door == true)
  {
    customKey = customKeypad.getKey();
    if (customKey == '#')
    {
      lcd.clear();
      ServoClose();
      lcd.print("Cua da dong");
      delay(3000);
      door = false;
    }
  }
  else
    Open();

}

void loading (char msg[]) {
  lcd.setCursor(0, 1);
  lcd.print(msg);

  for (int i = 0; i < 5; i++) {
    delay(1000);
    lcd.print(".");
  }
}

void clearData()
{
  while (data_count != 0)
  { 
    Data[data_count--] = 0;
  }
  return;
}

void ServoClose()
{
  for (pos = 90; pos >= 0; pos -= 10) { 
    myservo.write(pos);
  }
}

void ServoOpen()
{
  for (pos = 0; pos <= 90; pos += 10) {
    myservo.write(pos);  
  }
}

void Open()
{
  lcd.setCursor(0, 0);
  lcd.print("Nhap mat khau: ");
  
  customKey = customKeypad.getKey();
  if (customKey)
  {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    //lcd.print(Data[data_count]); (Hiện mật khẩu)
    lcd.print("*"); // Chuyển mật khẩu thành ****
    data_count++;
  }

  if (data_count == Password_Length - 1)
  {
    if (!strcmp(Data, Master))
    {
      lcd.clear();
      ServoOpen();
      lcd.print(" Da mo khoa ");
      door = true;
      delay(1000);
      lcd.clear();
      lcd.print(" TG cua mo: 5s ");
      delay(1000);
      lcd.clear();
      lcd.print(" TG cua mo: 4s ");
      delay(1000);
      lcd.clear();
      lcd.print(" TG cua mo: 3s ");
      delay(1000);
      lcd.clear();
      lcd.print(" TG cua mo: 2s ");
      delay(1000);
      lcd.clear();
      lcd.print(" TG cua mo: 1s ");
      delay(1000);
      lcd.clear();
      lcd.print(" Het thoi gian ");
      delay(1000);
      ServoClose();
      door = false;      
    }
    else
    {
      lcd.clear();
      lcd.print(" Sai mat khau ");
      door = false;
    }
    delay(1000);
    lcd.clear();
    clearData();
  }
}