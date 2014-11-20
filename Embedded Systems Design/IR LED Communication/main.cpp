/*Written by Travis Crumley.

Program Title: IR LED Communication

Text Description of Hardware Connections:

We are using PWMOut to send signals to an IR LED which are then picked up
by an IR Reciever.

Program Description:

This program quite simply senses if there is data being transmitted via IR LED 
If there is data being recieved the 2nd LED will light up, if there is data being
transmitted, the first LED will light up.

* This program in addition to an opaque shield can be used to test whether everything is
hooked up properly and functional without using an LCD.*/

#include "mbed.h"

PwmOut ir_mod(p36);

DigitalOut led1(LED1);

DigitalOut led2(LED2);

/*Don't be tempted to use the Serial Port on the USB. There is only one UART on the

LPC11U24 and it is connected both to the USB and Serial Data pin. A good work around

for debugging is printing things to an LCD.*/

Serial ir(p9, p10);

void callback() { //This callback function is executed when data is recieved

    ir.getc(); //Get the status of the IR reciever

    led2 = 1;//Light up LED 2 when I receive data

}

int main() {

    ir.baud(1200); //The max usable speed I found was 1200 pulses for second apparently

    led1 = 0;

    led2 = 0;

    ir.attach(&callback); //This sets up our callback function

    ir_mod.period_us(26);//26uS is the Mod kHz rate.

    ir_mod = 0.5; //Create a perfect modulation square wave

    wait(1);

    while (1){

        led1 = 1; //Light LED 1 while transmitting

        ir.printf("abcdefghijklmnopqrstuvwxyz");//Transmit a pile of characters 

        led1 = 0; //Done Transmitting, turn off LED1

        wait(0.5);

        led2 = 0;

        //Don’t wait and turn off LED2 in callback() because the callback could get called
        //again which would end up with very odd situations. Always make your callback
        //as short as possible.
    }
}