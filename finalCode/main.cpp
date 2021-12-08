/*
 * Main code for automated candy dispenser.
 *
 * Adapted from RTOS, lidar, and sonar hello world code.
 */

#include "mbed.h"
#include "rtos.h"
#include "XNucleo53L0A1.h"
#include <stdio.h>
#include "uLCD_4DGL.h"
#include "SongPlayer.h"

Serial pc(USBTX,USBRX);
uLCD_4DGL uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;

//Set up notes and durations for sample song to play
// A 0.0 duration note at end terminates song play
float note[18]= {1568.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };
float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };

// For the sonar
DigitalOut trigger(p6);
DigitalIn  echo(p7);

float distance = 0;
float correction = 0;
Timer sonar;
DigitalOut red(p12);
DigitalOut yellow(p13);
DigitalOut green(p14);

// For the lidar
DigitalOut RGBred(p21);
DigitalOut RGBgreen(p22);
DigitalOut RGBblue(p23);

SongPlayer mySpeaker(p26);
volatile bool changed = false;

DigitalOut shdn(p25);
 
DigitalOut myled(LED1); // comment out later
DigitalOut Ctrl(p8);
// This VL53L0X board test application performs a range measurement in polling mode
// Use 3.3(Vout) for Vin, p28 for SDA, p27 for SCL, P26 for shdn on mbed LPC1768

//I2C sensor pins
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27

static XNucleo53L0A1 *board=NULL;

// Callback routine is interrupt activated by lidar
/*void pb_hit_callback (void) {

    //mySpeaker = 0.5;
    mySpeaker.PlaySong(note, duration, 0.1);
    RGBred = 1;
    RGBgreen = 1;
    RGBblue = 1;
    //Put uLCD stuff here
    uLCD.cls();
    uLCD.color(GREEN);
    //uLCD.locate(2,1);
    uLCD.printf("Remove hand to stop receiving candy\n");
    changed = true;
}*/

// Thread 1
// sonar detection
void thread1(void const *args)
{
    sonar.reset();
    // measure actual software polling timer delays
    // delay used later in time correction
    // start timer
    sonar.start();
    // min software polling delay to read echo pin
    while (echo==2) {};
    // stop timer
    sonar.stop();
    // read timer
    correction = sonar.read_us();
    //printf("Approximate software overhead timer delay is %f uS\n\r", correction);
    
    //Loop to read Sonar distance values, scale, and print
    while(1) {
    // trigger sonar to send a ping
        trigger = 1;
        sonar.reset();
        wait_us(5.0);
        trigger = 0;
    //wait for echo high
        while (echo==0) {};
    //echo high, so start timer
        sonar.start();
    //wait for echo low
        while (echo==1) {};
    //stop timer and read value
        sonar.stop();
    //subtract software overhead timer delay and scale to cm
        //printf("The time taken was %d seconds\n", sonar.read_us());
        ::distance = (sonar.read_us()-correction)/58.0;
        //printf(" %f cm \n\r", ::distance);
        if (::distance <= 6.53) {
            green = 1;
            yellow = 0;
            red = 0;
            //printf("GREEN \n\r");
        } else if ((::distance > 6.53) && (::distance <= 8.167)) {
            green = 0;
            yellow = 1;
            red = 0;
            //printf("YELLOW \n\r");
        } else if ((::distance > 8.167) && (::distance <= 9.8)) {
            green = 0;
            yellow = 0;
            red = 1;
            //printf("RED \n\r");
        } else if (::distance > 9.8) {
            green = 0;
            yellow = 0;
            red = 0;
            //printf("ERROR: %f cm is larger than the box \n\r", ::distance);
        }
            
    //wait so that any echo(s) return before sending another ping
        Thread::wait(5000);
    }
}

int main()
{
    int status;
    uint32_t distance;
    DevI2C *device_i2c = new DevI2C(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
    /* creates the 53L0A1 expansion board singleton obj */
    board = XNucleo53L0A1::instance(device_i2c, A2, D8, D2);
    shdn = 0; //must reset sensor for an mbed reset to work
    wait(0.1);
    shdn = 1;
    wait(0.1);
    /* init the 53L0A1 board with default values */
    status = board->init_board();
    while (status) {
        pc.printf("Failed to init board! \r\n");
        status = board->init_board();
    }
    
    // Setup Interrupt callback function for a pb hit
    //pb.attach_deasserted(&pb_hit_callback);
    
    // Init ulcd
    uLCD.cls();
    uLCD.baudrate(3000000); //jack up baud rate to max
    uLCD.text_height(2);
    uLCD.text_width(2);
    uLCD.color(RED);
    uLCD.printf("Place hand under dispenser to receive candy!\n");
    changed = false;
    
    // start threads
    Thread t1(thread1); //start thread1
    
    //loop taking and printing distance
    while (1) {
        status = board->sensor_centre->get_distance(&distance);
        if (status == VL53L0X_ERROR_NONE) {
            //pc.printf("D=%ld mm\r\n", distance);
            RGBred = 0;
            RGBgreen = 0;
            RGBblue = 0;
            mySpeaker.PlaySong(note, duration, 0.0);
            if (changed) {
                uLCD.cls();
                uLCD.color(RED);
                uLCD.printf("Place hand under dispenser to receive candy!\n");
                changed = false;
            }
            
            if (distance < 50) {
                Ctrl = 1;
                Thread::wait(40);
                Ctrl = 0;
                
                mySpeaker.PlaySong(note, duration, 0.1);
                RGBred = 1;
                RGBgreen = 1;
                RGBblue = 1;
                //Put uLCD stuff here
                uLCD.cls();
                uLCD.color(GREEN);
                uLCD.printf("Remove hand to stop receiving candy\n");
                changed = true;
                
                Thread::wait(4500);
            }
        }
    }
}
