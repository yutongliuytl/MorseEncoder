/*
 * morseLib.h - Library for Morse Code Translator Bot.
 * Created by Kevin Li and Yu Tong Liu, November 13th, 2018.
 * In use for Software Engineering Project.
 */

#ifndef morseLib_h
#define morseLib_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif


class ButtonLight
{
  public:
    ButtonLight(int pinButton, int ledR, int ledG, int ledB);
    void lightButton();
    void setColor(int greenValue, int blueValue, int redValue);
    void colors(int control);
    void printMessage(String message);
  private:
    int _ledR;
    int _ledG;
    int _ledB;
    int _pinLight;
    int _pinButton;
    int _buttonState = 0;     // current state of the button
    int _lastButtonState = 0; // previous state of the button
    int _startPressed = 0;    // the time button was pressed
    int _endPressed = 0;      // the time button was released
    int _timeHold = 0;        // the time button is hold
    int _timeReleased = 0;    // the time button is released
};


class Button
{
  public:
    Button(int pinButton1, int pinButton2);
    void requestButton();
    char translateButton();
    char interpret(String code);
    int eraseButton();
  private:
    int _pinButton1;
    int _pinButton2;
    int _buttonState1 = 0;     // current state of the button
    int _lastButtonState1 = 0; // previous state of the button
    int _startPressed1 = 0;    // the time button was pressed
    int _endPressed1 = 0;      // the time button was released
    int _timeHold1 = 0;        // the time button is hold
    int _timeReleased1 = 0;    // the time button is released
    int _buttonState2 = 0;     // current state of the button
    int _lastButtonState2 = 0; // previous state of the button
    int _startPressed2 = 0;    // the time button was pressed
    int _endPressed2 = 0;      // the time button was released
    int _timeHold2 = 0;        // the time button is hold
    int _timeReleased2 = 0;    // the time button is released
    String _code = "";
    String _copycode = "";
    String _dot = ".";
    String _dash = "-";
    //Upper Bounds
    int _dotLengthUpper = 500;
    int _dashLengthUpper = 1500;    //dotLength * 3;
    int _elemPauseUpper = 500;     //dotLength;
    int _charPauseUpper = 1500;     //dotLength * 3;
    int _wordPauseUpper = 3500;    //dotLength * 7;
    int _spaceUpper = 1500;
    int _eraseUpper = 3000;
};

class Morselight
{
  public:
    Morselight(int ledR, int ledG, int ledB);
    void sendMessage(String arr, int size);
    void dot();
    void dash();
    void getChar(char temp);
    void LightsOff(int delayTime);
    void LightsEnd();
  private:
    int _ledR;
    int _ledG;
    int _ledB;
    int _dotLen = 250;           // length of the morse code 'dot'
    int _dashLen = _dotLen * 3;   // length of the morse code 'dash'
    int _elemPause = _dotLen;     // length of the pause between elements of a character
    int _spaces = _dotLen * 3;    // length of the spaces between characters
    int _wordPause = _dotLen * 7; // length of the pause between words
};


#endif
