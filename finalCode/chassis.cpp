#include "mbed.h"
#include "Motor.h"
#include "rtos.h"

Motor DC_Motor_Left(p21, p22, p23);
Motor DC_Motor_Right(p24, p25, p26);
Serial Blue(p28, p27);
Serial pc(USBTX, USBRX);
Thread MotorThread;

#define SPEED1 0.25f
#define SPEED2 0.50f
#define SPEED3 0.75f
#define SPEED4 1.0f

float curr_speed = SPEED1;
float left_speed = 0.0f;
float right_speed = 0.0f;
float direction = 1.0f;

void startMotors() {
    float inten = 0.0f;
    while (inten < 1.0f) {
        DC_Motor_Left.speed(inten * direction * left_speed);
        DC_Motor_Right.speed(inten * direction * right_speed);
        inten+=0.10f;
        Thread::wait(200);
    }
}

int main() {
    char bnum = 0;
    while(1) {
        if (Blue.getc()=='!') {
            if (Blue.getc()=='B') {
                bnum = Blue.getc();
                if (Blue.getc() == '1') {
                    switch(bnum) {
                        case '1':
                            curr_speed = SPEED1;
                            break;
                        case '2':
                            curr_speed = SPEED2;
                            break;
                        case '3':
                            curr_speed = SPEED3;
                            break;
                        case '4':
                            curr_speed = SPEED4;
                            break;
                        case '5':
                            left_speed = curr_speed;
                            right_speed = curr_speed;
                            direction = 1.0f;
                            printf("UP\n");
                            break;
                        case '6':
                            left_speed = curr_speed;
                            right_speed = curr_speed;
                            direction = -1.0f;
                            printf("DOWN\n");
                            break;
                        case '7':
                            left_speed = curr_speed * -1.0f;
                            right_speed = curr_speed;
                            printf("LEFT\n");
                            break;
                        case '8':
                            left_speed = curr_speed;
                            right_speed = curr_speed * -1.0f;
                            printf("RIGHT\n");
                            break;
                    }
                    if (bnum == '5' || bnum == '6' || bnum == '7'|| bnum == '8') {
                        MotorThread.start(startMotors);
                    }
                } else {
                    MotorThread.terminate();
                    DC_Motor_Left.speed(0);
                    DC_Motor_Right.speed(0);
                }
            }
        }
    }
}