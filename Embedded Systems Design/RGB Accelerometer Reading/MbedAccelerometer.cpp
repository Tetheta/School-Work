#include "MbedAccelerometer.h"

MbedAccelerometer::MbedAccelerometer() {
    accelAddress = 0x0D;
    accelWriteAddress = 0x3A;
    accelReadAddress = 0x3B;
    ctrl1Address = 0x2A;
}

void MbedAccelerometer::setAccelAddress(int addr) {
    printf("Entered setDeviceID method\r\n");
    accelAddress = addr;
}

void MbedAccelerometer::setWriteAddress(int addr) {
    printf("Entered setWriteAddress method\r\n");
    accelWriteAddress = addr;
}

void MbedAccelerometer::setReadAddress(int addr) {
    printf("Entered setReadAddress method\r\n");
    accelReadAddress = addr;
}

void MbedAccelerometer::setCtrl1Address(int addr) {
    printf("Entered setReadAddress method\r\n");
    ctrl1Address = addr;
}

void MbedAccelerometer::accelerometerInit(I2C& i2c) {
    //printf("Entered accelerometerInit method\r\n");
    i2c.start();
    //Send Write Address to Write the Register Number
    if (!i2c.write(accelWriteAddress))
    {
        error("\r\nError 0: No ACK returned\r\n");
    }
    //Read accelerometer Who Am I Register @ 0x0d
    if (!i2c.write(accelAddress))
    {
        error("\r\nError 1: No ACK returned\r\n");
    }
    //Send Read Address to Read the Who Am I Register byte.
    i2c.start();
    if (!i2c.write(accelReadAddress))
    {
        error("\r\nError 2: No ACK returned\r\n");
    }
    int who_am_i = i2c.read(0); //0 means send no ack
    printf("who_am_i: %x \r\n", who_am_i);
    i2c.stop();
    if (who_am_i != 0x2a)
    {
        error("\r\nError 3: Who_Am_I returned incorrectly. 0x%x\r\n", who_am_i);
    }
}

void MbedAccelerometer::accelerometerStandby(I2C& i2c) {
    printf("Entered accelerometerStandby method\r\n");
    i2c.start();
    //Send Write Address to Write the Register Number
    if (!i2c.write(accelWriteAddress))
    {
        error("\r\nError 0: No ACK returned\r\n");
    }
    //Read accelerometer Ctrl1 register @ 0x2a
    if (!i2c.write(ctrl1Address))
    {
        error("\r\nError 1: No ACK returned\r\n");
    }
    //Send Read Address to Read the Ctrl1 Register byte.
    i2c.start();
    if (!i2c.write(accelReadAddress))
    {
        error("\r\nError 2: No ACK returned\r\n");
    }
    int ctrl1 = i2c.read(0); //0 means send no ack
    i2c.stop();

    printf("Control1 is: %x \r\n", ctrl1);
    ctrl1 = ctrl1 & 0x10;
    printf("Control1 is: %x \r\n", ctrl1);

    i2c.start();
    if (!i2c.write(accelWriteAddress))
    {
        error("\r\nError 3: No ACK returned\r\n");
    } //Send Write Address to Write the Register Number
    if (!i2c.write(ctrl1Address)) {
        error("\r\nError 4: No ACK returned\r\n");
    } //Write to accelerometer Ctrl1 register @ 0x2a
    if (!i2c.write(ctrl1))
    {
        error("\r\nError 5: Cannot write new data to ctrlReg1, no ACK returned\r\n");
    }
    i2c.stop();
}

void MbedAccelerometer::accelerometerActive(I2C& i2c) {
    printf("Entered accelerometerActive method\r\n");
    i2c.start();
    //Send Write Address to Write the Register Number
    if (!i2c.write(accelWriteAddress))
    {
        error("\r\nError 0: No ACK returned\r\n");
    }
    //Read accelerometer Ctrl1 register @ 0x2a
    if (!i2c.write(ctrl1Address))
    {
        error("\r\nError 1: No ACK returned\r\n");
    }
    //Send Read Address to Read the Ctrl1 Register byte.
    i2c.start();
    if (!i2c.write(accelReadAddress))
    {
        error("\r\nError 2: No ACK returned\r\n");
    }
    int ctrl1 = i2c.read(0); //0 means send no ack
    i2c.stop();

    printf("Control1 is: %x \r\n", ctrl1);
    ctrl1 = (ctrl1 | 0x01);
    printf("Control1 is: %x \r\n", ctrl1);

    i2c.start();
    if (!i2c.write(accelWriteAddress))
    {
        error("\r\nError 3: No ACK returned\r\n");
    } //Send Write Address to Write the Register Number
    if (!i2c.write(ctrl1Address)) {
        error("\r\nError 4: No ACK returned\r\n");
    } //Write to accelerometer Ctrl1 register @ 0x2a
    if (!i2c.write(ctrl1))
    {
        error("\r\nError 5: Cannot write new data to ctrlReg1, no ACK returned\r\n");
    }
    i2c.stop();
}

int MbedAccelerometer::accelerometerRead(I2C& i2c, char axis) {
    //printf("Entered accelerometerRead method\r\n");
    int lsbAddr = 0;
    int msbAddr = 0;
    if (axis == 'x' || axis == 'X')
    {
        lsbAddr = 0x02;
        msbAddr = 0x01;
    }
    if (axis == 'y' || axis == 'Y')
    {
        lsbAddr = 0x04;
        msbAddr = 0x03;
    }
    if (axis == 'z' || axis == 'Z')
    {
        lsbAddr = 0x06;
        msbAddr = 0x05;
    }
    i2c.start();
    //Send Write Address to Write the Register Number
    if (!i2c.write(accelWriteAddress))
    {
        error("\r\nError 0: No ACK returned\r\n");
    }
    //Read accelerometer out_x_lsb register
    if (!i2c.write(msbAddr))
    {
        error("\r\nError 1: No ACK returned\r\n");
    }
    //Send Read Address to Read the Ctrl1 Register byte.
    i2c.start();
    if (!i2c.write(accelReadAddress))
    {
        error("\r\nError 2: No ACK returned\r\n");
    }
    int xMSB = i2c.read(0); //0 means send no ack
    i2c.stop();

    i2c.start();
    //Send Write Address to Write the Register Number
    if (!i2c.write(accelWriteAddress))
    {
        error("\r\nError 3: No ACK returned\r\n");
    }
    //Read accelerometer out_x_msb register
    if (!i2c.write(lsbAddr))
    {
        error("\r\nError 4: No ACK returned\r\n");
    }
    //Send Read Address to Read the Ctrl1 Register byte.
    i2c.start();
    if (!i2c.write(accelReadAddress))
    {
        error("\r\nError 5: No ACK returned\r\n");
    }
    int xLSB = i2c.read(0); //0 means send no ack
    i2c.stop();

    xMSB = xMSB<<4;
    xLSB = xLSB>>4;
    int xOut = xLSB | xMSB;
    //printf("xOut is: %x", xOut);
    if ((xOut >> 11) == 1)
    {
        //Number is negative
        xOut = xOut | 0xFFFFF000;
    }
    //printf("xOut is: %i", xOut);
    //printf("\r%x", xOut);
    return xOut;
}

int MbedAccelerometer::accelerometerRead(I2C& i2c)
{
    xAccel = accelerometerRead(i2c, 'x');
    yAccel = accelerometerRead(i2c, 'y');
    zAccel = accelerometerRead(i2c, 'z');
    return abs(xAccel) + abs(yAccel) + abs(zAccel);
}