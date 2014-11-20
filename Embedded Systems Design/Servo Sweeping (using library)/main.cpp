// Continuously sweep the servo through it's full range
#include "mbed.h"
#include "Servo.h"

Servo myservo(p25);
DigitalIn clockwiseBtn(p18);
DigitalIn counterwiseBtn(p16);

int main()
{
    myservo.calibrate(.0008,180.0);
    float p = 0.0;
    while(1) {
        if(clockwiseBtn) {
            if(p > 120.0)
                p = 120.0;
            else
                p+= 2.0;
            myservo.position(p);
            wait(0.05);
        } else if(counterwiseBtn) {
            if(p < 0.0)
                p = 0.0;
            else
                p-= 2.0;
            myservo.position(p);
            wait(0.05);
        }
    }
}