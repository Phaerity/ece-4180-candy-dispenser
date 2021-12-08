#include "mbed.h"
#include "SongPlayer.h"
#include "PinDetect.h"
#include "uLCD_4DGL.h"

// Song test program - plays a song using PWM and timer interrupts
// for documentation see http://mbed.org/users/4180_1/notebook/using-a-speaker-for-audio-output/
// can be used to play a song, if you have the notes and durations
// for musical note frequencies see http://en.wikipedia.org/wiki/Piano_key_frequencies

//Set up notes and durations for sample song to play
// A 0.0 duration note at end terminates song play
float note[18]= {1568.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };
float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };

DigitalOut red(p21);
DigitalOut green(p22);
DigitalOut blue(p23);
PinDetect pb(p8);
DigitalOut led(LED1);
uLCD_4DGL uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;
// setup instance of new SongPlayer class, mySpeaker using pin 26
// the pin must be a PWM output pin
SongPlayer mySpeaker(p26);
volatile bool changed = false;

// Callback routine is interrupt activated by a debounced pb hit
void pb_hit_callback (void) {

    //mySpeaker = 0.5;
    mySpeaker.PlaySong(note, duration, 0.1);
    red = 1;
    green = 1;
    blue = 1;
    //Put uLCD stuff here
    uLCD.cls();
    //uLCD.baudrate(3000000); //jack up baud rate to max
    //uLCD.text_height(2);
    //uLCD.text_width(2);
    uLCD.color(GREEN);
    //uLCD.locate(2,1);
    uLCD.printf("Remove hand to stop receiving candy\n");
    changed = true;
}
int main() {
 
    // Use internal pullup for pushbutton
    pb.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.001);
    // Setup Interrupt callback function for a pb hit
    pb.attach_deasserted(&pb_hit_callback);
    // Start sampling pb input using interrupts
    pb.setSampleFrequency();
    

    uLCD.cls();
    uLCD.baudrate(3000000); //jack up baud rate to max
    uLCD.text_height(2);
    uLCD.text_width(2);
    uLCD.color(RED);
    //uLCD.locate(2,1);
    uLCD.printf("Place hand under dispencer to receive candy!\n");
    changed = false;
    
    //mySpeaker.period(1.0/800.0);

// Start song and return once playing starts
    
    // loops forever while song continues to play to end using interrupts
    while(1) {
        //led = !led;
        //wait(.5);
        if (pb) {
            red = 0;
            green = 0;
            blue = 0;
            //mySpeaker = 0;
            mySpeaker.PlaySong(note, duration, 0.0);
            if (changed) {
                uLCD.cls();
                //uLCD.baudrate(3000000); //jack up baud rate to max
                //uLCD.text_height(2);
                //uLCD.text_width(2);
                uLCD.color(RED);
                //uLCD.locate(2,1);
                uLCD.printf("Place hand under dispencer to receive candy!\n");
                changed = false;
            }
            //changed = true;
        } /*else if (!pb) { // && changed) {
            uLCD.cls();
            //uLCD.baudrate(3000000); //jack up baud rate to max
            //uLCD.text_height(2);
            //uLCD.text_width(2);
            uLCD.color(GREEN);
            //uLCD.locate(2,1);
            uLCD.printf("Remove hand to stop receiving candy\n");
            //changed = false;
        }*/
    }
}
