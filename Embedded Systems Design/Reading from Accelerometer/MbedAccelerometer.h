#include "mbed.h"
#include <stdio.h>
#include <cmath>
#include "math.h"

class MbedAccelerometer {
private:
    int accelAddress;
    int accelWriteAddress;
    int accelReadAddress;
    int ctrl1Address;
    int xAccel;
    int yAccel;
    int zAccel;
public:
    MbedAccelerometer();
    void setAccelAddress(int);
    void setWriteAddress(int);
    void setReadAddress(int);
    void setCtrl1Address(int);
    void accelerometerInit(I2C&);
    void accelerometerStandby(I2C&);
    void accelerometerActive(I2C&);
    int accelerometerRead(I2C&, char);
    int accelerometerRead(I2C&);
};