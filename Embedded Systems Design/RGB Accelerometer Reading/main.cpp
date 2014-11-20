/*
RGB Accelerometer - Assignment 10
ENGR 355
by Travis Crumley
Rev 01.00 2/9/2014
*/

#include "MbedAccelerometer.h"

//RGB Portions of LED
PwmOut Red(p25);
PwmOut Green(p26);
PwmOut Blue(p34);

// Read accelerometer from MMA8452Q
I2C i2c(p28, p27);

//Create addresses to the Accelerometer
const int regAddr = 0x0D;
const int writeAddr = 0x3A;
const int readAddr = 0x3B;
const int ctrlAddr = 0x2A;

int main()
{
    //Initialize LED to off
    Red = 1.0f;
    Green = 1.0f;
    Blue = 1.0f;

    int xAccel = 0;
    int yAccel = 0;
    int zAccel = 0;
    int totalAccel = 0;
    float mulFactor = 0;
    //Setup Accelerometer
    MbedAccelerometer accel;
    accel.setAccelAddress(regAddr);
    accel.setReadAddress(readAddr);
    accel.setWriteAddress(writeAddr);
    accel.setCtrl1Address(ctrlAddr);
    accel.accelerometerInit(i2c);
    accel.accelerometerStandby(i2c);
    accel.accelerometerActive(i2c);
    while (true) {
        xAccel = accel.accelerometerRead(i2c, 'x');
        if (xAccel >= 0x8000) {
            xAccel = (xAccel - 1) ^ 0xFFFF;
        }
        printf("\n");
        yAccel = accel.accelerometerRead(i2c, 'y');
        if (yAccel >= 0x8000) {
            yAccel = (yAccel - 1) ^ 0xFFFF;
        }
        printf("\n");
        zAccel = accel.accelerometerRead(i2c, 'z');
        if (zAccel >= 0x8000) {
            zAccel = (zAccel - 1) ^ 0xFFFF;
        }
        printf("\n");
        totalAccel = abs(xAccel) + abs(yAccel) + abs(zAccel);
        //Trying to find the percentage of acceleration for each
        /*
        if(totalAccel > 5000)
            mulFactor = 0.15f;
        else if(totalAccel > 3000 && totalAccel < 5000)
            mulFactor = 1.0f;
        else if(totalAccel < 3000)
            mulFactor = 1.5f;
        */
        mulFactor = 1.5 - totalAccel/5000;
        //Debug
        float rojo = mulFactor*(1 - abs((float)xAccel / (float)totalAccel))*.75;
        float azul = mulFactor*(1 - abs((float)yAccel / (float)totalAccel))*2.0;
        float verde = mulFactor*(1 - abs((float)zAccel / (float)totalAccel))*1.25;
        
        //Real
        Red = mulFactor*(1 - abs((float)xAccel / (float)totalAccel))*.75;
        Blue = mulFactor*(1 - abs((float)yAccel / (float)totalAccel))*2.0;
        Green = mulFactor*(1 - abs((float)zAccel / (float)totalAccel))*1.25;

        //Debug
        
        printf("Red is: %f\n", rojo);
        printf("Blue is: %f\n", azul);
        printf("Green is: %f\n", verde);
        printf("TotalAccel is %i\n", totalAccel);
        //printf("\033[2J");
        //wait(1);
    }
}