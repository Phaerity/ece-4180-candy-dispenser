#include "mbed.h"
 
DigitalOut trigger(p6);
DigitalOut myled(LED1); //monitor trigger
DigitalOut myled2(LED2); //monitor echo
DigitalIn  echo(p7);
float distance = 0;
float correction = 0;
Timer sonar;
DigitalOut red(p10);
DigitalOut yellow(p11);
DigitalOut green(p12);

int main()
{
    sonar.reset();
// measure actual software polling timer delays
// delay used later in time correction
// start timer
    sonar.start();
// min software polling delay to read echo pin
    while (echo==2) {};
    myled2 = 0;
// stop timer
    sonar.stop();
// read timer
    correction = sonar.read_us();
    printf("Approximate software overhead timer delay is %f uS\n\r", correction);
    
//Loop to read Sonar distance values, scale, and print
    while(1) {
// trigger sonar to send a ping
        trigger = 1;
        myled = 1;
        myled2 = 0;
        sonar.reset();
        wait_us(5.0);
        trigger = 0;
        myled = 0;
//wait for echo high
        while (echo==0) {};
        myled2=echo;
//echo high, so start timer
        sonar.start();
//wait for echo low
        while (echo==1) {};
//stop timer and read value
        sonar.stop();
//subtract software overhead timer delay and scale to cm
        //printf("The time taken was %d seconds\n", sonar.read_us());
        ::distance = (sonar.read_us()-correction)/58.0;
        myled2 = 0;
        printf(" %f cm \n\r", ::distance);
        if (::distance <= 6.53) {
            green = 1;
            yellow = 0;
            red = 0;
            printf("GREEN \n\r");
        } else if ((::distance > 6.53) && (::distance <= 8.167)) {
            green = 0;
            yellow = 1;
            red = 0;
            printf("YELLOW \n\r");
        } else if ((::distance > 8.167) && (::distance <= 9.8)) {
            green = 0;
            yellow = 0;
            red = 1;
            printf("RED \n\r");
        } else if (::distance > 9.8) {
            green = 0;
            yellow = 0;
            red = 0;
            printf("ERROR: %f cm is larger than the box \n\r", ::distance);
        }
            
//wait so that any echo(s) return before sending another ping
        wait(0.2);
    }
}
 