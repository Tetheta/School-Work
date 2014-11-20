/*
Homework 6 - Speaker
ENGR 355
by Travis Crumley
Rev 01.00 1/23/2014
Using Speaker.h class from mbed import library
*/

#include "mbed.h"
#include "Speaker.h"

Speaker spk(p25);
float A = 440.00;
float Ah = 880.00;
float Bb = 466.16;
float B = 493.88;
float C = 523.25;
float E = 329.63;
float Eh = 659.25;
float G = 392.00;
float Gh = 783.99;
float F = 698.46;
float array[50] = {Eh,Eh,Eh,C,Eh,Gh,G};

int main() {
    while(1) {
        //Super mario theme! (sort of)
        spk.PlayNote(array[0],0.1,1.0);
        //wait(0.5);
        spk.PlayNote(array[1],0.2,1.0);
        //wait(0.5);
        spk.PlayNote(array[2],0.1,1.0);
        wait(0.1);
        spk.PlayNote(array[3],0.1,1.0);
        wait(0.05);
        spk.PlayNote(array[4],0.1,1.0);
        wait(0.1);
        spk.PlayNote(array[5],0.2,1.0);
        wait(0.25);
        spk.PlayNote(array[6],0.2,1.0);
        wait(0.6);
        spk.PlayNote(array[7],0.4,1.0);
        wait(0.2);
        
    }    
}