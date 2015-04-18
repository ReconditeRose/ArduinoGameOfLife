/*----- Define Section ------*/
//Needed for bug fixing
#define byte uint8_t


#define PIN_SCE   6 //Pin 3 on LCD
#define PIN_RESET 7 //Pin 4 on LCD
#define PIN_DC    5 //Pin 5 on LCD
#define PIN_SDIN  4 //Pin 6 on LCD
#define PIN_SCLK  3 //Pin 7 on LCD

#define PIN_LIGHT  12 //Pin for light
#define PIN_SWITCH_DISPLAY 8 //Pin for switching displays
#define PIN_LIGHT_SWITCH 2 //Pin for toggling light

//The DC pin tells the LCD if we are sending a command or data
#define LCD_COMMAND 0 
#define LCD_DATA  1

//Dimensions of the LCD
#define LCD_X     84
#define LCD_Y     48
#define CellArray (LCD_X * LCD_Y)/8

//Number of pre_defined arrays
#define PRE_DEFINED 4

//Number of Cycles before the screen is randomized when on randomize mode. 
#define RANDOM_RESET 360


