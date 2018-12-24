/* Main code that links inputs and outputs with the help of librairies
 * by Yu Tong Liu and Kevin Li
 */


//Include Libraries
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <morseLib.h>


// OLED display TWI address
#define OLED_ADDR   0x3C
#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


#define PIXELSPACE 6 //Number of pixels for each character prints


//Input/Output String and Position
char stringToMorseCode = 0;
String fullString = "";
int place[] = {0, 20};


//Object Setups
Adafruit_SSD1306 display(-1);
Button button(2, 4);
ButtonLight buttonLight(2, 10, 9, 8);
Morselight morseLight(10, 9, 8);


void setup() {
  
  Serial.begin(9600);
  
  //initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();

  //display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  //display the the temporary menu screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,0);
  display.print("by Yu Tong and Kevin");
  display.setCursor(30,25);
  display.print("Welcome to");
  display.setCursor(47,40);
  display.print("Morse ");
  display.setCursor(15,55);
  display.print("Encoder/Decoder!");

  //update display with all of the above graphics
  display.display();
  delay(3000);
  display.setCursor(place[0],place[1]);
  
  display.clearDisplay();
}




void loop() {

  //Header of our display
  display.setCursor(0,0);
  display.print("Morse Encoder/Decoder");


  //Main Transmission of information (Input)  
  delay(150);
  button.requestButton();
  buttonLight.lightButton();
  stringToMorseCode = button.translateButton();

  
  //Erase function (to erase String displayed)
  if(button.eraseButton()){
    if(fullString){
      fullString.remove(fullString.length() - 1);
      display.clearDisplay();
      display.setCursor(0, 20);
      display.print(fullString);
      place[0] = (fullString.length() % 15) * PIXELSPACE;
      place[1] = (int)(fullString.length() / 15) * 10 + 20;
      display.setCursor(place[0], place[1]);
    }

    
  } else {
    if (stringToMorseCode){
      

      //Main Transmission of information (Ouput)  
      if (stringToMorseCode == '?') {
        morseLight.sendMessage(fullString, fullString.length());
        fullString.remove(0);
        display.clearDisplay();
        display.setCursor(0, 20);
        display.print(fullString);
        place[0] = 0;
        place[1] = 20;
      } else {


        //Printing on display functionality (the retrieved characters)
        fullString += String(stringToMorseCode); 
        display.setCursor(place[0],place[1]);
        display.print(String(stringToMorseCode));
        place[0] += PIXELSPACE;   
        Serial.print(fullString);
        Serial.print('\n');
      }
      stringToMorseCode = 0;
    }
  }
  

  // Update the display after every iteration
  display.display();
  

  //Functionality: To print to the next line after reaching the extreme right
  if(place[0] == 120){
    place[0] = 0;
    place[1] += 10;
  }
}
