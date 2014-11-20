/*Written by Travis Crumley.

Program Title: IR LED Communication

Text Description of Hardware Connections:

We are using PWMOut to send signals to an IR LED which are then picked up
by an IR Reciever.

Program Description:



* This program in addition to an opaque shield can be used to test whether everything is
hooked up properly and functional without using an LCD.*/

#include "mbed.h"
#include "Speaker.h"

PwmOut ir_mod(P0_21);

DigitalOut led1(P1_19);
DigitalOut led2(P1_20);
DigitalOut led3(P1_21);
DigitalOut led4(P1_22);

InterruptIn button1(P0_17);
InterruptIn button2(P0_18);

/*Don't be tempted to use the Serial Port on the USB. There is only one UART on the

LPC11U24 and it is connected both to the USB and Serial Data pin. A good work around

for debugging is printing things to an LCD.*/
Speaker speaker(P1_24);
Timeout randomTimeout;
Serial ir(P1_27, P1_26);
int musicNum = 1;
float speed = 1.0f;

int e=330, f=349, g=392, a=415, b=494, c=523, d=554, eh=659, fh=698, gh=784, ah=880;
float eighth=.25, quarter=.5, half=1.0;

bool receiving = false;
bool playing = false;

void callback()   //This callback function is executed when data is recieved
{
    if(ir.readable())
        musicNum = ir.getc(); //Get the status of the IR reciever
    //led2 = 1;//Light up LED 2 when I receive data

}

void button1Pressed()
{
    receiving = true;
    playing = false;
    led4 = 1;
}

void button2Pressed()
{
    playing = true;
    receiving = false;
    led3 = 1;
}

void randomTime() //Interupt function to set new play speed and reset interupt
{
    musicNum=rand()%10;
    speed=(musicNum+1)/5.0;
}

void playSong()
{
    randomTimeout.attach(&randomTime, rand() % 7);             //Interupt at random times to change play speed
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);       
    if(playing)
    {             //
    speaker.PlayNote(b, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(eh, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(b, half * speed, 0.5);
    ir.printf("%i", musicNum);   
    }     
    if(playing)
    {              //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    wait(0.1 * speed);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum);     
    }     
    if(playing)
    {                //
    speaker.PlayNote(g, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(b, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    wait(0.1 * speed);
    }     
    if(playing)
    { 
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(eh, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(fh, (half + quarter) * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(eh, eighth * speed, 0.5);
    ir.printf("%i", musicNum);
    }     
    if(playing)
    {                     //
    speaker.PlayNote(gh, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(fh, (quarter + half) * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(fh, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(gh, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(ah, quarter * speed, 0.5);
    ir.printf("%i", musicNum);   
    }     
    if(playing)
    {                  //
    speaker.PlayNote(gh, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(fh, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(eh, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(d, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, quarter * speed, 0.5);
    ir.printf("%i", musicNum);   
    }     
    if(playing)
    {                  //
    speaker.PlayNote(b, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(b, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);   
    }     
    if(playing)
    {                  //
    speaker.PlayNote(g, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, eighth * speed, 0.5);
    ir.printf("%i", musicNum);   
    }     
    if(playing)
    {                  //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(b, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    wait(0.1 * speed);
    }     
    if(playing)
    { 
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(e, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    wait(0.1 * speed);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum); 
    }     
    if(playing)
    {                    //
    speaker.PlayNote(e, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(e, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, quarter * speed, 0.5);
    ir.printf("%i", musicNum);  
    }     
    if(playing)
    {                   //
    speaker.PlayNote(a, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(e, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, quarter * speed, 0.5);
    ir.printf("%i", musicNum); 
    }     
    if(playing)
    {                    //
    wait(0.1 * speed);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(b, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    wait(0.1 * speed);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(c, eighth * speed, 0.5);
    ir.printf("%i", musicNum); 
    }     
    if(playing)
    {                    //
    speaker.PlayNote(eh, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(b, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    wait(0.1 * speed);
    ir.printf("%i", musicNum); 
    }     
    if(playing)
    {                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(e, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(e, eighth * speed, 0.5);
    ir.printf("%i", musicNum); 
    }     
    if(playing)
    {                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(e, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, eighth * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(g, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(a, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(e, quarter * speed, 0.5);
    ir.printf("%i", musicNum);                    //
    speaker.PlayNote(f, half * speed, 0.5);
    ir.printf("%i", musicNum); 
    }                        //
    randomTimeout.detach();
}

void recieveSong()
{
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    switch(musicNum) {
        case 0:
            break;
        case 1:
            led1 = 1;
            break;
        case 2:
            led2 = 1;
            break;
        case 3:
            led1 = 1;
            led2 = 1;
            break;
        case 4:
            led3 = 1;
            break;
        case 5:
            led3 = 1;
            led1 = 1;
            break;
        case 6:
            led3 = 1;
            led2 = 1;
            break;
        case 7:
            led3 = 1;
            led2 = 1;
            led1 = 1;
            break;
        case 8:
            led4 = 1;
            break;
        case 9:
            led4 = 1;
            led1 = 1;
            break;
    }
    wait(0.1);
}

int main()
{
    button1.mode(PullUp);
    button2.mode(PullUp);
    ir.baud(1200); //The max usable speed I found was 1200 pulses per second apparently

    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;

    ir.attach(&callback); //This sets up our callback function

    ir_mod.period_us(26);//26uS is the Mod kHz rate.

    ir_mod = 0.5; //Create a perfect modulation square wave

    button1.fall(&button1Pressed);
    button2.fall(&button2Pressed);

    wait(1);
    while(true) {
        //if(button1 == 0)
        //    led1 = 1;
        //else if(button1 == 1)
        //    led2 = 1;
        wait(0.2);
        led1 = led2 = led3 = led4 = 0;
        if (receiving) {
            recieveSong();
        }
        if(playing) {
            playSong();
        }
    }
}