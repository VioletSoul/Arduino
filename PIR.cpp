
// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal_PCF8574.h"
#include "PIR.h"


// Pin Definitions
#define PIR_PIN_SIG	2
#define PIRMINI_PIN_DQ	3


#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
// object initialization
LiquidCrystal_PCF8574 lcdI2C;
PIR pir(PIR_PIN_SIG);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    // initialize the lcd
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT);
    menuOption = menu();

}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{


    if(menuOption == '1') {
    // LCD 16x2 I2C - Test Code
    // The LCD Screen will display the text of your choice.
    lcdI2C.clear();                          // Clear LCD screen.
    lcdI2C.print("  Circuito.io  ");                   // Print print String to LCD on first line
    lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
    lcdI2C.print("     Rocks!  ");                   // Print print String to LCD on second line
    delay(1000);

    }
    else if(menuOption == '2') {
    // Infrared PIR Motion Sensor Module - Test Code
    bool pirVal = pir.read();
    Serial.print(F("Val: ")); Serial.println(pirVal);

    }
    else if(menuOption == '3')
    {
    // Disclaimer: The Mini PIR - HC-SR505 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }

    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }

}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) LCD 16x2 I2C"));
    Serial.println(F("(2) Infrared PIR Motion Sensor Module"));
    Serial.println(F("(3) Mini PIR - HC-SR505"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available())
    {
        char c = Serial.read();
        if (isAlphaNumeric(c))
        {

            if(c == '1')
    			Serial.println(F("Now Testing LCD 16x2 I2C"));
    		else if(c == '2')
    			Serial.println(F("Now Testing Infrared PIR Motion Sensor Module"));
    		else if(c == '3')
    			Serial.println(F("Now Testing Mini PIR - HC-SR505 - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

