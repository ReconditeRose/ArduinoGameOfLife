#include "Configuration.h"
#include "preDefinedArrays.h"
#include "GameOfLifeExecution.h"
/*
---------------Setup and main loop---------------
 Main setup function for initializing input pins and main loop
 
 */

//Array that holds the current state of the cells
byte cell_Array[504];

void setup(void) {
  LCDInit(); //Init the LCD
  loadArray(gliderGun); //Arbitrary starting position
  //Configure pins
  pinMode(PIN_SWITCH_DISPLAY, INPUT);
  pinMode(PIN_LIGHT_SWITCH, INPUT);
  pinMode(PIN_LIGHT, OUTPUT);

  //Turn backlight on
  digitalWrite(PIN_LIGHT, HIGH);
}


void loop(void) {
  int i;
  handleInput();
  for (i = 0; i < (CellArray); i++) {
    LCDWrite(LCD_DATA, cell_Array[i]);
  }
  stepOfLife(cell_Array);
}

/*
---------------Input handling---------------
 Two buttons are present that needed to be checked for input. Both buttons should not
 be pressed together, so the light is prioritized. The inputs are one shotted.  Debouncing 
 is unnecessary since the event loop takes so long to execute, you would have to hold the 
 button for a very long time.
 
 */
byte pressed = 0;
byte displayLoop = 0;
byte light = 1;
int resetCountdown = 0;
void handleInput(void){


  if (digitalRead(PIN_LIGHT_SWITCH) == 1) {
    if (pressed == 0) {
      if (light == 1) {
        digitalWrite(PIN_LIGHT, HIGH);
        light = 0;
      } 
      else {
        digitalWrite(PIN_LIGHT, LOW);
        light = 1;
      }
    }
    pressed = 1;
  } 
  else if (digitalRead(PIN_SWITCH_DISPLAY) == 1) {
    if (pressed == 0){
      switch(displayLoop){
      case 0: 
        randomize(); 
        resetCountdown = 0;
        break;
      case 1: 
        loadArray(gliderGun);
        break;
      case 2: 
        loadArray(oscillators);
        break;
      case 3:
        loadArray(oscillate144);
        break;
      }
      displayLoop = (displayLoop+1)%4;
      pressed = 1;
    }
  } 
  else {
    pressed = 0;
  }

  if(displayLoop==0){
    resetCountdown++;
    if(resetCountdown == RANDOM_RESET){
      randomize();
      resetCountdown = 0; 
    }
  }

}
/*
---------------Pre-defined cell Arrangements---------------
 Handles updating the cell array to set new cell configurations. 
 
 */
void loadArray(prog_char * e){
  int i;
  for(i=0;i<CellArray;i++){
    cell_Array[i] = pgm_read_byte_near(e+i); 
  }
}


void randomize(void) {
  int i;
  //Seed randomization
  randomSeed((int) millis());
  for (i = 0; i < LCD_X * LCD_Y / 8; i++) {
    //Randomize each byte
    cell_Array[i] = random(32767);
  }
}


/*
---------------LCD Drivers---------------
 */
void LCDInit(void) {
  //Initialize pins
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);

  //Reset the LCD
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);

  //Initialize the LCD
  LCDWrite(LCD_COMMAND, 0x21);
  LCDWrite(LCD_COMMAND, 0x90); 
  LCDWrite(LCD_COMMAND, 0x04); 
  LCDWrite(LCD_COMMAND, 0x14); 
  LCDWrite(LCD_COMMAND, 0x0C);
  LCDWrite(LCD_COMMAND, 0x20); 
  LCDWrite(LCD_COMMAND, 0x0C); 
}

void LCDWrite(byte data_or_command, byte data) {
  //Indicate the type of data being sent
  digitalWrite(PIN_DC, data_or_command);

  //Send the data
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}









