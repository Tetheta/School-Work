/*
Lab Assignment 5 - Accelerometer
ENGR 355
by Travis Crumley
Rev 01.00 1/9/2014
*/

#include "MbedAccelerometer.h"

// Read acceleromter from MMA8452Q

I2C i2c(p28, p27);

//Create addresses to the Accelerometer
const int regAddr = 0x0D;
const int writeAddr = 0x3A;
const int readAddr = 0x3B;
const int ctrlAddr = 0x2A;

int main() {
    MbedAccelerometer accel;
    accel.setAccelAddress(regAddr);
    accel.setReadAddress(readAddr);
    accel.setWriteAddress(writeAddr);
    accel.setCtrl1Address(ctrlAddr);
    accel.accelerometerInit(i2c);
    accel.accelerometerStandby(i2c);
    accel.accelerometerActive(i2c);
    /*
    while (true)
    {
        accel.accelerometerRead(i2c, 'x');
        printf("\n");
        accel.accelerometerRead(i2c, 'y');
        printf("\n");
        accel.accelerometerRead(i2c, 'z');
        wait(0.5);
        printf("\033[2J");
    }
    */
    accel.accelerometerMovement(i2c, accel);
}