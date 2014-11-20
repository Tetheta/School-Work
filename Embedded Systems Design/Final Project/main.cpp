/*
Written by Travis Crumley.

Program Title: J. S. Joust Implementation

Text Description of Hardware Connections:

Using an IR LED, RGB LED, Accelerometer, 2 buttons, a reset switch,
an IR Reciever, and four simple LEDs

Program Description:

* This program implements the game J.S. Joust, it was designed for a project
at Walla Walla University in the Embedded Systems Design class ENGR 355
Winter Quarter 2014
*/

#include "Speaker.h"
#include "MbedAccelerometer.h"

/*******************************************/
//BASIC INITIALIZATION
/*******************************************/

//RGB Portions of LED
PwmOut Red(P0_9);
PwmOut Green(P0_8);
PwmOut Blue(P1_15);

//Initialize Speaker
Speaker speaker(P1_24);

//Iniialize Serial
Serial ir(P1_27, P1_26);
PwmOut ir_mod(P0_21);

//Initialize LEDs
DigitalOut led1(P1_19);
DigitalOut led2(P1_20);
DigitalOut led3(P1_21);
DigitalOut led4(P1_22);

//Initialize Buttons
InterruptIn button1(P0_17);
InterruptIn button2(P0_18);


// Read accelerometer from MMA8452Q
I2C i2c(P0_5, P0_4);

//Initialize Interrupt
Ticker randomTicker;
Ticker sendIRTicker;

//Setting up Accelerometer

//Create addresses to the Accelerometer
const int regAddr = 0x0D;
const int writeAddr = 0x3A;
const int readAddr = 0x3B;
const int ctrlAddr = 0x2A;

//Initialize Accelerometer values
int xAccel = 0;
int yAccel = 0;
int zAccel = 0;
int totalAccel = 0;
int newAccel = 0;

//Setup Accelerometer
MbedAccelerometer accel;

/*******************************************/
//INITIALIZATION OF GLOBAL VARIABLES
/*******************************************/

static const int e = 330, f = 349, g = 392, a = 415, b = 494, c = 523, d = 554, eh = 659, fh = 698, gh = 784, ah = 880;
static const float eighth = .25, quarter = .5, half = 1.0;

//Initialize values for main function
bool isOn = false;
bool recieving = false;
bool masterExists = false;
bool gameRunning = false;
bool playing = false;
bool startGame = false;
bool isSlave = false;

int musicNum = 0;
int count = 0;
int buttonHold = 0;
int accelThreshold = 0;
float speed = 1;
char x = 'M'; //Only used in master so initalized for that
char curReading;


/*******************************************/
//INITIALIZATION OF FUNCTIONS
/*******************************************/

void rgbLEDColor(char);
void sendIR();
void randomTime();
void playLoseSound();
void playErrorSound();
void playSong();
char readIR();
void setAccelThreshold(char);
bool accelWithinThreshold();
bool isButtonHeld(int);
void button1Pressed();
void button2Pressed();

int main()
{
    /*******************************************/
    //INITIALIZATION OF BASE VALUES
    /*******************************************/
    //Set up accelerometer
    accel.setAccelAddress(regAddr);
    accel.setReadAddress(readAddr);
    accel.setWriteAddress(writeAddr);
    accel.setCtrl1Address(ctrlAddr);
    accel.accelerometerInit(i2c);
    accel.accelerometerStandby(i2c);

    //Initialize IR stuff
    ir.baud(1200); //The max usable speed I found was 1200 pulses for second apparently
    ir_mod.period_us(2);//2uS is the Mod kHz rate.
    ir_mod = 0.5; //Create a perfect modulation square wave

    //Set PullUp, 0 is pressed, 1 is off
    button1.mode(PullUp);
    button2.mode(PullUp);

    //Initialize LEDs to off
    Red = 0.0f;
    Green = 0.0f;
    Blue = 0.0f;

    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;

    /*******************************************/
    //COMMENCE ACTUAL FUNCTION OF PROGRAM
    /*******************************************/

    button1.fall(&button1Pressed);
    button2.fall(&button2Pressed);
    while (true)
    {
        //See if we want to actually turn on
        //if (isButtonHeld(1))
        //{
        isOn = true;
        //}

        while (isOn)
        {
            //Check for master
            
            for (int i = 0; i < 20; i++)
            {
                if ((readIR() > 64) && (readIR() < 91)) //check for capital letter
                {
                    masterExists = true;
                }
                wait(0.05);
            }
            
            //masterExists = true;

            if (masterExists) //Code for slave
            {
                isSlave = true;
                while (isSlave)
                {
                    rgbLEDColor('w');
                    led2 = 1;
                    led1 = 0;
                    //TEST CODE ONLY
                    //x = 'M';
                    //END TEST CODE
                    while (readIR() != 'M')
                    {
                        led4 = 1;
                        wait(0.1);
                        led4 = 0;
                        wait(0.1);
                    }
                    if (readIR() == 'M')
                    {
                        rgbLEDColor('p');
                        while (readIR() != 'S')
                        {
                            wait(0.1);
                            //Don't move on
                        }
                        //Moving on, recieving S
                        rgbLEDColor('g');
                        accel.accelerometerActive(i2c); //Starting up our accelerometer
                        //x = 'C';
                        led1 = 1;
                        while ((readIR() < 65) || (readIR() > 69))
                        {
                            wait(0.1);
                            //Don't move on
                        }
                        //Actually starting the game at this point, this is the main game loop
                        gameRunning = true;
                        
                        led3 = 1;
                        do
                        {
                            if (ir.readable()) //Check to see if we're recieving
                            {
                                //We're recieving (again?)! Make sure count is 0
                                count = 0;
                                //Set accelerometer threshold level
                                curReading = readIR();
                                if ((curReading > 64) && (curReading < 71))
                                {
                                    setAccelThreshold(curReading);
                                }
                                else
                                {
                                    led1 = 1;
                                    led2 = 1;
                                    led3 = 1;
                                    led4 = 1;
                                    wait(1);
                                    led1 = 0;
                                    led2 = 0;
                                    led3 = 0;
                                    led4 = 0;
                                    wait(1);
                                }

                                //Checking to see if it's within threshold
                                if (!accelWithinThreshold())
                                {
                                    //We lose! 
                                    playLoseSound();
                                    rgbLEDColor('r');
                                    gameRunning = false;

                                    led1 = 1;
                                    led2 = 0;
                                    led3 = 1;
                                    led4 = 0;
                                    wait(1);
                                    led1 = 0;
                                    led2 = 1;
                                    led3 = 0;
                                    led4 = 1;
                                    wait(1);
                                }
                            }
                            else
                            {
                                //We can't see the master or the master stopped, see if we get back to the master in time;
                                while (!ir.readable() && gameRunning ) //Keep looping this while we're not getting anything from the IR
                                {
                                    playErrorSound();
                                    rgbLEDColor('o');
                                    led4 = 1;
                                    led3 = 0;
                                    led2 = 0;
                                    led1 = 0;
                                    count++;
                                    wait(0.1);
                                    if (count >= 20) //How exactly will we see if count >= 2 seconds, put a wait command somewhere?
                                    {
                                        playLoseSound();
                                        rgbLEDColor('r');
                                        gameRunning = false;
                                    }
                                }
                            }
                        } while (gameRunning);
                    }
                    accel.accelerometerStandby(i2c);
                }
                //Game is no longer running, so we set rgb to red and check if we want to turn off
                //If we don't turn off, we run through the isOn loop again
                rgbLEDColor('r');
                if (isButtonHeld(2))
                {
                    isOn = false;
                }
            }
            //Code for master
            else
            {
                led1 = 1;
                led2 = 0;
                srand(time(0));
                gameRunning = true;
                sendIRTicker.attach(&sendIR, 0.01);

                while (gameRunning)
                {
                    rgbLEDColor('b');

                    //Setup the IR to send x
                    x = 'M';
                    //Seed Random
                    while (!startGame)
                    {
                        wait(0.1);//Pause our function until it is
                    }
                    startGame = false;
                    //Start game!
                    rgbLEDColor('w');
                    x = 'S';
                    wait(3);

                    //Play sing normal tempo once
                    //Attach Interrupt
                    playing = true;
                    while (playing)//While the button isn't pressed
                    {
                        //Play the song, interrupts for different tempos built in
                        rgbLEDColor('p');
                        playSong();
                    }
                    if (button2 == 0)
                    {
                        if (isButtonHeld(2))
                        {
                            isOn = false;
                            gameRunning = false;
                        }
                    }
                }
            }
        }
    }
}

/*******************************************/
//IMPLEMENTATION OF FUNCTIONS
/*******************************************/

//Function for setting RGB colors
void rgbLEDColor(char color)
{
    if (color == 'r' || color == 'R')
    {
        Red = 1.0f;
        Green = 0.0f;
        Blue = 0.0f;
    }

    if (color == 'g' || color == 'G')
    {
        Red = 0.0f;
        Green = 1.0f;
        Blue = 0.0f;
    }

    if (color == 'b' || color == 'B')
    {
        Red = 0.0f;
        Green = 0.0f;
        Blue = 1.0f;
    }

    if (color == 'p' || color == 'P')
    {
        Red = 1.0f;
        Green = 0.0f;
        Blue = 1.0f;
    }

    if (color == 'o' || color == 'O')
    {
        Red = 1.0f;
        Green = 0.4f;
        Blue = 0.0f;
    }

    if (color == 'w' || color == 'W')
    {
        Red = 1.0f;
        Green = 1.0f;
        Blue = 1.0f;
    }
}

//Create interrupt functions
void sendIR()
{
    //Send whatever x is currently set to
    ir.printf("%c", x);
}

void randomTime() //Interupt function to set new play speed and reset interupt
{
    musicNum = rand() % 5;
    speed = (musicNum + 1) * 0.3;
    x = musicNum + 65;
}

void playErrorSound()
{
    speaker.PlayNote(e, eighth, 0.5);
    speaker.PlayNote(f, eighth, 0.5);
    speaker.PlayNote(e, eighth, 0.5);
    speaker.PlayNote(f, eighth, 0.5);
    speaker.PlayNote(e, eighth, 0.5);
}

void playLoseSound()
{
    speaker.PlayNote(eh, eighth, 0.5);
    speaker.PlayNote(c, eighth, 0.5);
    speaker.PlayNote(a, eighth, 0.5);
}

//Function for sending song
void playSong()
{
    randomTicker.attach(&randomTime, (rand() % 7 + 1));             //Interupt at random times to change play speed
    x = 'C';
    speaker.PlayNote(f, eighth * speed, 0.5);
    speaker.PlayNote(g, eighth * speed, 0.5);
    speaker.PlayNote(a, half * speed, 0.5);
    speaker.PlayNote(a, eighth * speed, 0.5);
    if (playing)
    {             //
        speaker.PlayNote(b, eighth * speed, 0.5);
        speaker.PlayNote(c, half * speed, 0.5);
        speaker.PlayNote(c, eighth * speed, 0.5);
        speaker.PlayNote(eh, eighth * speed, 0.5);
        speaker.PlayNote(b, half * speed, 0.5);
    }
    if (playing)
    {              //
        speaker.PlayNote(a, eighth * speed, 0.5);
        speaker.PlayNote(g, eighth * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
        wait(0.1 * speed);
        speaker.PlayNote(f, eighth * speed, 0.5);
    }
    if (playing)
    {                //
        speaker.PlayNote(g, eighth * speed, 0.5);
        speaker.PlayNote(a, half * speed, 0.5);
        speaker.PlayNote(a, eighth * speed, 0.5);
        speaker.PlayNote(b, eighth * speed, 0.5);
        speaker.PlayNote(c, half * speed, 0.5);
        wait(0.1 * speed);
    }
    if (playing)
    {
        speaker.PlayNote(c, eighth * speed, 0.5);
        speaker.PlayNote(eh, eighth * speed, 0.5);
        speaker.PlayNote(fh, (half + quarter) * speed, 0.5);
        speaker.PlayNote(eh, eighth * speed, 0.5);
    }
    if (playing)
    {                     //
        speaker.PlayNote(gh, eighth * speed, 0.5);
        speaker.PlayNote(fh, (quarter + half) * speed, 0.5);
        speaker.PlayNote(fh, eighth * speed, 0.5);
        speaker.PlayNote(gh, eighth * speed, 0.5);
        speaker.PlayNote(ah, quarter * speed, 0.5);
    }
    if (playing)
    {                  //
        speaker.PlayNote(gh, quarter * speed, 0.5);
        speaker.PlayNote(fh, quarter * speed, 0.5);
        speaker.PlayNote(eh, quarter * speed, 0.5);
        speaker.PlayNote(d, quarter * speed, 0.5);
        speaker.PlayNote(c, quarter * speed, 0.5);
    }
    if (playing)
    {                  //
        speaker.PlayNote(b, half * speed, 0.5);
        speaker.PlayNote(a, eighth * speed, 0.5);
        speaker.PlayNote(c, eighth * speed, 0.5);
        speaker.PlayNote(b, half * speed, 0.5);
        speaker.PlayNote(a, eighth * speed, 0.5);
    }
    if (playing)
    {                  //
        speaker.PlayNote(g, eighth * speed, 0.5);
        speaker.PlayNote(a, half * speed, 0.5);
        speaker.PlayNote(a, eighth * speed, 0.5);
        speaker.PlayNote(g, eighth * speed, 0.5);
        speaker.PlayNote(a, half * speed, 0.5);
        speaker.PlayNote(g, eighth * speed, 0.5);
    }
    if (playing)
    {                  //
        speaker.PlayNote(a, eighth * speed, 0.5);
        speaker.PlayNote(b, quarter * speed, 0.5);
        speaker.PlayNote(a, quarter * speed, 0.5);
        speaker.PlayNote(g, quarter * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
        wait(0.1 * speed);
    }
    if (playing)
    {
        speaker.PlayNote(f, eighth * speed, 0.5);
        speaker.PlayNote(e, eighth * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
        wait(0.1 * speed);
        speaker.PlayNote(f, eighth * speed, 0.5);
    }
    if (playing)
    {                    //
        speaker.PlayNote(e, eighth * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
        speaker.PlayNote(e, eighth * speed, 0.5);
        speaker.PlayNote(f, eighth * speed, 0.5);
        speaker.PlayNote(g, quarter * speed, 0.5);
    }
    if (playing)
    {                   //
        speaker.PlayNote(a, quarter * speed, 0.5);
        speaker.PlayNote(e, quarter * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
        speaker.PlayNote(a, eighth * speed, 0.5);
        speaker.PlayNote(g, eighth * speed, 0.5);
        speaker.PlayNote(a, quarter * speed, 0.5);
    }
    if (playing)
    {                    //
        wait(0.1 * speed);
        speaker.PlayNote(a, quarter * speed, 0.5);
        speaker.PlayNote(b, quarter * speed, 0.5);
        speaker.PlayNote(c, half * speed, 0.5);
        wait(0.1 * speed);
        speaker.PlayNote(c, eighth * speed, 0.5);
    }
    if (playing)
    {                    //
        speaker.PlayNote(eh, eighth * speed, 0.5);
        speaker.PlayNote(b, quarter * speed, 0.5);
        speaker.PlayNote(a, quarter * speed, 0.5);
        speaker.PlayNote(g, quarter * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
        wait(0.1 * speed);
    }
    if (playing)
    {                    //
        speaker.PlayNote(f, eighth * speed, 0.5);
        speaker.PlayNote(e, eighth * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
        speaker.PlayNote(f, eighth * speed, 0.5);
        speaker.PlayNote(e, eighth * speed, 0.5);
    }
    if (playing)
    {                    //
        speaker.PlayNote(f, half * speed, 0.5);
        speaker.PlayNote(e, eighth * speed, 0.5);
        speaker.PlayNote(f, eighth * speed, 0.5);
        speaker.PlayNote(g, quarter * speed, 0.5);
        speaker.PlayNote(a, quarter * speed, 0.5);
        speaker.PlayNote(e, quarter * speed, 0.5);
        speaker.PlayNote(f, half * speed, 0.5);
    }                        //
    randomTicker.detach();
}
//Function for reading IR
char readIR()
{
    //This will check the IR for a signal and return said signal in char form
    if (ir.readable() == 1)
    {
        return ir.getc(); //Get the status of the IR reciever
    }
    else
    {
        return '\0';
    }
}

void setAccelThreshold(char threshold)
{
    //This will take in the read IR value and adjust the accelerometer threshold accordingly
    if (threshold == 'A')
    {
        accelThreshold = 0x50000;
    }
    else if (threshold == 'B')
    {
        accelThreshold = 0x50000;
    }
    else if (threshold == 'C')
    {
        accelThreshold = 0x50000;
    }
    else if (threshold == 'D')
    {
        accelThreshold = 0x50000;
    }
    else if (threshold == 'E')
    {
        accelThreshold = 0x50000;
    }
    else
    {
        led1 = 1;
        led2 = 1;
        led3 = 1;
        led4 = 1;
        accelThreshold = 1000000;
    }
}

bool accelWithinThreshold()
{
    totalAccel = accel.accelerometerRead(i2c);
    wait(0.03);
    newAccel = accel.accelerometerRead(i2c);
    totalAccel = abs(newAccel - totalAccel);
    if (totalAccel < accelThreshold)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isButtonHeld(int button)
{
    if (button == 0)
    {
        buttonHold = 0;
        for (int i = 0; i < 20; i++)
        {
            wait(0.1);
            if (button1 == 0) //0 is on for pullup
            {
                buttonHold++;
            }
        }
        if (buttonHold >= 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (button == 2)
    {
        buttonHold = 0;
        for (int i = 0; i < 20; i++)
        {
            wait(0.1);
            if (button2 == 0) //0 is on for pullup
            {
                buttonHold++;
            }
        }
        if (buttonHold >= 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void button1Pressed()
{
    startGame = true;
    led3 = 1;
    wait(0.05);
    led3 = 0;
}

void button2Pressed()
{
    playing = false;
    led4 = 1;
    wait(0.05);
    led4 = 0;
}