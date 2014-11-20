/*
Homework 3 - RGB LED
ENGR 355
by Travis Crumley
Rev 01.00 1/9/2014
*/

#include "mbed.h"

PwmOut Red(p25);
PwmOut Green(p26);
PwmOut Blue(p34);

int main() {
    while(1) {/*
        Red = 1.0f;
        Green = 0.0f;
        Blue = 0.0f;
        wait(0.5);
        Red = 0.0f;
        Green = 1.0f;
        Blue = 0.0f;
        wait(0.5);
        Red = 0.0f;
        Green = 0.0f;
        Blue = 1.0f;
        wait(0.5);
        */
        Red = 1.0f;
        Green = 1.0f;
        Blue = 1.0f;
    }    
}