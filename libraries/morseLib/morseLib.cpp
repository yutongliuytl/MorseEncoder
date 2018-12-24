/*
 * morseLib.cpp - Library for Morse Code Translator Bot.
 * Created by Kevin Li and Yu Tong Liu, November 13th, 2018.
 * In use for Software Engineering Project.
 */

#include "Arduino.h"
#include "morseLib.h"

Button::Button(int pinButton1, int pinButton2)
{
  pinMode(pinButton1, INPUT);
  pinMode(pinButton2, INPUT);
  _pinButton1 = pinButton1;
  _pinButton2 = pinButton2;
}


int Button::eraseButton()
{
  if ((int)digitalRead(_pinButton1) == 0 && (int)digitalRead(_pinButton2) == 1) {
    _code.remove(0);
    return 1;
  }
  return 0;
}

void Button::requestButton()
{
  if (digitalRead(_pinButton2) != 1){
    _buttonState1 = digitalRead(_pinButton1);
    if (_buttonState1 != _lastButtonState1){
      if(_buttonState1 == LOW) {
        _startPressed1 = millis();
        _timeReleased1 = _startPressed1 - _endPressed1;
      }
      else if(_buttonState1 == HIGH){
        _endPressed1 = millis();
        _timeHold1 = _endPressed1 - _startPressed1;

         if (_timeHold1 <= _dotLengthUpper) {
          _code += _dot;
        }
        else if (_timeHold1 <= _dashLengthUpper) {
          _code += _dash;
        }
      }
      _lastButtonState1 = _buttonState1;
    }
  }
}

char Button::translateButton()
{
  if (digitalRead(_pinButton2) == HIGH){
    if (_code == '\0'){
      _copycode += ' ';
      return ' ';
    }
    else{
      char character = interpret(_code);
      _copycode += character;
      _code.remove(0);
      return character;
    }
  }
  return 0;
}

char Button::interpret(String code)
{
  if (code == ".-")         return 'A';
  else if (code == "-...")  return 'B';
  else if (code == "-.-.")  return 'C';
  else if (code == "-..")   return 'D';
  else if (code == ".")     return 'E';
  else if (code == "..-.")  return 'F';
  else if (code == "--.")   return 'G';
  else if (code == "....")  return 'H';
  else if (code == "..")    return 'I';
  else if (code == ".---")  return 'J';
  else if (code == "-.-")   return 'K';
  else if (code == ".-..")  return 'L';
  else if (code == "--")    return 'M';
  else if (code == "-.")    return 'N';
  else if (code == "---")   return 'O';
  else if (code == ".--.")  return 'P';
  else if (code == "--.-")  return 'Q';
  else if (code == ".-.")   return 'R';
  else if (code == "...")   return 'S';
  else if (code == "-")     return 'T';
  else if (code == "..-")   return 'U';
  else if (code == "...-")  return 'V';
  else if (code == ".--")   return 'W';
  else if (code == "-..-")  return 'X';
  else if (code == "-.--")  return 'Y';
  else if (code == "--..")  return 'Z';

  else if (code == ".----")  return '1';
  else if (code == "..---")  return '2';
  else if (code == "...--")  return '3';
  else if (code == "....-")  return '4';
  else if (code == ".....")  return '5';
  else if (code == "-....")  return '6';
  else if (code == "--...")  return '7';
  else if (code == "---..")  return '8';
  else if (code == "----.")  return '9';
  else if (code == "-----")  return '0';

  else if (code == "......") return '?';
}


ButtonLight::ButtonLight(int pinButton, int ledR, int ledG, int ledB)
{
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(pinButton, INPUT);
  _ledR = ledR;
  _ledG = ledG;
  _ledB = ledB;
  _pinButton = pinButton;
}


void ButtonLight::setColor(int greenValue, int blueValue, int redValue)
{
  analogWrite(_ledG, greenValue);
  analogWrite(_ledB, blueValue);
  analogWrite(_ledR, redValue);
}

void ButtonLight::colors(int control)
{
  if(control){
    setColor(0, 0, 0); // White Color
  }
  else{
    setColor(255, 255, 255); // No Color
  }
 }


 void ButtonLight::lightButton(void)
 {
    _buttonState = digitalRead(_pinButton);

    if (_buttonState != _lastButtonState){
      if(_buttonState == LOW) {
        _startPressed = millis();
        colors(1);
      }

      else if(_buttonState == HIGH){
        _endPressed = millis();
        _timeHold = _endPressed - _startPressed;
        colors(0);
      }
      _lastButtonState = _buttonState;
    }
 }


Morselight::Morselight(int ledR, int ledG, int ledB)
{
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  _ledR = ledR;
  _ledG = ledG;
  _ledB = ledB;
}

void Morselight::sendMessage(String arr, int size)
{
  // Loop through the string and get each character one at a time until the end is reached
  for (int i = 0; i < size; i++)
  {
    char tmpChar = arr[i];
    tmpChar = toLowerCase(tmpChar);
    getChar(tmpChar);
  }
}

void Morselight::dot()
{
  digitalWrite(_ledR, LOW);
  digitalWrite(_ledG, LOW);
  digitalWrite(_ledB, LOW);
  delay(_dotLen);
}

void Morselight::dash()
{
  digitalWrite(_ledR, LOW);
  digitalWrite(_ledG, LOW);
  digitalWrite(_ledB, LOW);
  delay(_dashLen);
}

void Morselight::LightsOff(int delayTime)
{
  digitalWrite(_ledR, HIGH);
  digitalWrite(_ledG, HIGH);
  digitalWrite(_ledB, HIGH);
  delay(delayTime);
}
void Morselight::LightsEnd()
{
  digitalWrite(_ledR, HIGH);
  digitalWrite(_ledG, HIGH);
  digitalWrite(_ledB, HIGH);
}

void Morselight::getChar(char temp)
{
  switch (temp) {
    case 'a':
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'b':
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'c':
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'd':
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'e':
      dot();
      LightsOff(_elemPause);
      break;
    case 'f':
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
      case 'g':
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'h':
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'i':
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'j':
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
      case 'k':
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'l':
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
      case 'm':
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'n':
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'o':
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'p':
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 'q':
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'r':
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 's':
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      break;
    case 't':
      dash();
      LightsOff(_elemPause);
      break;
    case 'u':
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'v':
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'w':
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'x':
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'y':
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      break;
    case 'z':
      dash();
      LightsOff(_elemPause);
      dash();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      dot();
      LightsOff(_elemPause);
      LightsOff(_spaces);
      break;
    default:
    LightsOff(_wordPause);
  }
}
