/*
Lab 2 - 5 LED Knight Rider
ENGR 355
by Travis Crumley
Rev 01.00 1/8/2014
*/

#include "mbed.h"

DigitalIn buttonIncrement(p20); //Button to increment counter/switch to next stage
DigitalIn buttonMode(p18); //Button for switching from auto to manual

DigitalOut testLED1(LED1); //Used for button testing function

PwmOut GreenLED1(p5);
PwmOut YellowLED1(p6);
PwmOut YellowLED2(p25);
PwmOut YellowLED3(p26);
PwmOut GreenLED2(p34);

//bool mode = 0; //Set the mode to automatic initially
int counter = 0;
int bounceCounter = 0;
int i = 0;
int sampleSize = 150000;

int main() {
    //Reset all LEDs
    GreenLED1 = 0.0f;
    YellowLED1 = 0.0f;
    YellowLED2 = 0.0f;
    YellowLED3 = 0.0f;
    GreenLED2 = 0.0f;
    
    testLED1 = 0;
    
    while(1) {  
        /*
        //Button Testing Function
        if(buttonMode) {
            testLED1 = 1;
        }
        else {
            testLED1 = 0;
        }
        wait(0.1);
        */
        /*
        //LED Testing Function
            counter++; //Increment counter
            //Basically a switch statement, choose which frame to display.
            if(counter == 1) {
                GreenLED1 = 0.1f;
                YellowLED1 = 0.2f;
                YellowLED2 = 0.3f;
                YellowLED3 = 0.5f;
                GreenLED2 = 1.0f;
            }
            if(counter == 2) {
                GreenLED1 = 0.1f;
                YellowLED1 = 0.1f;
                YellowLED2 = 0.2f;
                YellowLED3 = 1.0f;
                GreenLED2 = 0.5f;
            }
            if(counter == 3) {
                GreenLED1 = 0.1f;
                YellowLED1 = 0.2f;
                YellowLED2 = 1.0f;
                YellowLED3 = 0.5f;
                GreenLED2 = 0.3f;
            }
            if(counter == 4) {
                GreenLED1 = 0.1f;
                YellowLED1 = 1.0f;
                YellowLED2 = 0.5f;
                YellowLED3 = 0.3f;
                GreenLED2 = 0.2f;
            }
            if(counter == 5) {
                GreenLED1 = 1.0f;
                YellowLED1 = 0.5f;
                YellowLED2 = 0.3f;
                YellowLED3 = 0.2f;
                GreenLED2 = 0.1f;
            }
            if(counter == 6) {
                GreenLED1 = 0.5f;
                YellowLED1 = 1.0f;
                YellowLED2 = 0.2f;
                YellowLED3 = 0.1f;
                GreenLED2 = 0.1f;
            }
            if(counter == 7) {
                GreenLED1 = 0.3f;
                YellowLED1 = 0.5f;
                YellowLED2 = 1.0f;
                YellowLED3 = 0.1f;
                GreenLED2 = 0.1f;
            }
            if(counter == 8) {
                GreenLED1 = 0.2f;
                YellowLED1 = 0.3f;
                YellowLED2 = 0.5f;
                YellowLED3 = 1.0f;
                GreenLED2 = 0.1f;
                counter = 0;
            }
            wait(0.1);
        */
        //Manual incrementation function
        
        //Check to see if the increment button is pressed
        bounceCounter = 0;  
        if(!buttonIncrement) {
            for(i = 0;i < sampleSize; i++) {
                if(buttonIncrement) {
                    bounceCounter++;
                }
            }
        }
        //Read in the debounced input
        if((bounceCounter > (sampleSize/3))) {
            counter++; //Increment counter
            //Basically a switch statement, choose which frame to display.
            if(counter == 1) {
                GreenLED1 = 0.1f;
                YellowLED1 = 0.2f;
                YellowLED2 = 0.3f;
                YellowLED3 = 0.5f;
                GreenLED2 = 1.0f;
            }
            if(counter == 2) {
                GreenLED1 = 0.1f;
                YellowLED1 = 0.1f;
                YellowLED2 = 0.2f;
                YellowLED3 = 1.0f;
                GreenLED2 = 0.5f;
            }
            if(counter == 3) {
                GreenLED1 = 0.1f;
                YellowLED1 = 0.2f;
                YellowLED2 = 1.0f;
                YellowLED3 = 0.5f;
                GreenLED2 = 0.3f;
            }
            if(counter == 4) {
                GreenLED1 = 0.1f;
                YellowLED1 = 1.0f;
                YellowLED2 = 0.5f;
                YellowLED3 = 0.3f;
                GreenLED2 = 0.2f;
            }
            if(counter == 5) {
                GreenLED1 = 1.0f;
                YellowLED1 = 0.5f;
                YellowLED2 = 0.3f;
                YellowLED3 = 0.2f;
                GreenLED2 = 0.1f;
            }
            if(counter == 6) {
                GreenLED1 = 0.5f;
                YellowLED1 = 1.0f;
                YellowLED2 = 0.2f;
                YellowLED3 = 0.1f;
                GreenLED2 = 0.1f;
            }
            if(counter == 7) {
                GreenLED1 = 0.3f;
                YellowLED1 = 0.5f;
                YellowLED2 = 1.0f;
                YellowLED3 = 0.1f;
                GreenLED2 = 0.1f;
            }
            if(counter == 8) {
                GreenLED1 = 0.2f;
                YellowLED1 = 0.3f;
                YellowLED2 = 0.5f;
                YellowLED3 = 1.0f;
                GreenLED2 = 0.1f;
                counter = 0;
            }
            /*       //Check to see if the mode button is pressed (comment this code)
            bounceCounter = 0;  
            if(!buttonMode) {
                for(i = 0;i < sampleSize; i++) {
                    if(buttonMode) {
                        bounceCounter++;
                    }
                }
                mode = !mode;
            }
            */
        }
        //*/
    }
}
