#include <msp430.h>

#define LEFT_PIN			(BIT0|BIT4)
#define RIGHT_PIN    (BIT6|BIT7)
#define MOTOR_PINS      (BIT4|BIT7)
#define PUSH_BUTTON_PIN  BIT3
#define WAIT_TIME   40000

unsigned int count = 0;
unsigned int driveCounter = 0;
unsigned int totalCounter = 0;
//unsigned char doFunction = 1;
//unsigned char power = 0;
//unsigned int driveTime = 0;
void wait(unsigned int pulses);
void motorOut(unsigned char pinhigh, unsigned int power);
void startup(void);
void driveMotors(unsigned int driveTime, unsigned char leftPower, unsigned char rightPower);

// This is where the movement data goes
// We need to connect left servo on P1.4 and right servo on P1.7
const unsigned int drivePathTime[]		=		{1700, 1500, 4000, 1500, 8000, 0};
const unsigned char drivePathLeft[]   =   {100, 100, 100, 100, 100, 0};
const unsigned char drivePathRight[]  =   {94, 0, 94,  0,  94,  0};

// This is the code that actually controls the robot.
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= LEFT_PIN;
    P1DIR |= RIGHT_PIN;
    P1OUT &= ~MOTOR_PINS);//off
    startup();
    for (totalCounter=0; 1; totalCounter++)
    {
        /*
            |= for on
            &= ~ for off
            ^= for toggle
        */

        if (drivePathTime[totalCounter] == 0 && drivePathLeft[totalCounter] == 0 && drivePathRight[totalCounter] == 0)
        {
            break;
        }
        driveMotors(drivePathTime[totalCounter],drivePathLeft[totalCounter],drivePathRight[totalCounter]);

    }
    P1OUT &= ~(MOTOR_PINS); // Turns bits 4 and 7 off
}

void wait(unsigned int pulses)
{
    for(count=0;count<pulses;count++);
}

void driveMotors(unsigned int drivingTime, unsigned char leftPower, unsigned char rightPower)
{
    for (driveCounter=0;driveCounter<drivingTime;driveCounter++)
    {
        motorOut(LEFT_PIN, leftPower);
        motorOut(RIGHT_PIN, rightPower);
    }
}

void motorOut(unsigned char pinhigh, unsigned int power)
{
    if (power>100)
    {
        power=100;
    }
    P1OUT |= pinhigh;//on
    wait(power);
    P1OUT &= ~pinhigh;//off
    wait(100-power);
}

void startup(void)
{
    P1REN |= PUSH_BUTTON_PIN;
    P1DIR &= ~PUSH_BUTTON_PIN;
    P1SEL&= ~PUSH_BUTTON_PIN;

    P1OUT |= BIT0+BIT6;//on
    while (((P1IN & PUSH_BUTTON_PIN) == PUSH_BUTTON_PIN));
    //P1OUT &= ~(BIT0+BIT6);//off
    //P1OUT |= BIT0+BIT6;//on
    P1OUT &= ~(BIT0+BIT6);//off
    P1OUT |= BIT0;//on
    wait(WAIT_TIME);
    P1OUT &= ~BIT0;//off
    wait(WAIT_TIME);
    P1OUT |= BIT0;//on
    wait(WAIT_TIME);
    P1OUT &= ~BIT0;//off
    wait(WAIT_TIME);
    P1OUT |= BIT0;//on
    wait(WAIT_TIME);
    P1OUT &= ~BIT0;//off
    wait(WAIT_TIME);
    P1OUT |= BIT6;//on
    wait(WAIT_TIME);
    P1OUT &= ~(BIT0+BIT6);//off
    wait(WAIT_TIME);
}
