#include <msp430.h> 

#define leftPin	BIT0+BIT4
#define rightPin	BIT6+BIT7
#define pushButton	BIT3
#define waitForGo	40000

unsigned int count=0;
unsigned int driveCounter=0;
unsigned int totalCounter=0;
//unsigned char doFunction=1;
//unsigned char power=0;
//unsigned int driveTime=0;
void wait(unsigned int pulses);
void motorOut(unsigned char pinhigh, unsigned int power);
void startup(void);
void driveMotors(unsigned int driveTime, unsigned char leftPower, unsigned char rightPower);

//This is where the data goes
//We need to connect left servo on P1.4 and right servo on P1.7
const unsigned int drivePathTime[]=		{1700,	1500,	4000,	1500,	8000,	0	};
const unsigned char drivePathLeft[]=	{100,	100,	100,	100,	100,	0	};
const unsigned char drivePathRight[]=	{94,	0,		94,		0,		94,		0	};
//This is where the data stops

















void main(void)
{

	WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= leftPin;
    P1DIR |= rightPin;
	P1OUT &= ~(BIT4+BIT7);//off
	startup();
    for (totalCounter=0;1;totalCounter++)
    {
    	/*
    	|= for on
		&= ~ for off
    	^= for toggle
    	*/

    	//P1OUT ^= leftPin;//toggle
        //P1OUT &= 0x00;//off
        /*for(i=0; i< 200; i++)
        {
        	P1OUT |= BIT0;//on
        	    for(i=0; i< 200; i++);
        	    P1OUT &= 0x00;//off
        }*/


    	if (drivePathTime[totalCounter]==0 && drivePathLeft[totalCounter]==0 && drivePathRight[totalCounter]==0)
    	{
    		break;
    	}
    	driveMotors(drivePathTime[totalCounter],drivePathLeft[totalCounter],drivePathRight[totalCounter]);

     }
	P1OUT &= ~(BIT4+BIT7);//off
}

void wait(unsigned int pulses)
{
	for(count=0;count<pulses;count++);
}

void driveMotors(unsigned int drivingTime, unsigned char leftPower, unsigned char rightPower)
{
	for (driveCounter=0;driveCounter<drivingTime;driveCounter++)
	{
		motorOut(leftPin, leftPower);
		motorOut(rightPin, rightPower);
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


	P1REN |= pushButton;
	P1DIR &= ~pushButton;
	P1SEL&= ~pushButton;

	P1OUT |= BIT0+BIT6;//on
	while (((P1IN & pushButton) == pushButton));
	//P1OUT &= ~(BIT0+BIT6);//off
	//P1OUT |= BIT0+BIT6;//on
	P1OUT &= ~(BIT0+BIT6);//off
	P1OUT |= BIT0;//on
	wait(waitForGo);
	P1OUT &= ~BIT0;//off
	wait(waitForGo);
	P1OUT |= BIT0;//on
	wait(waitForGo);
	P1OUT &= ~BIT0;//off
	wait(waitForGo);
	P1OUT |= BIT0;//on
	wait(waitForGo);
	P1OUT &= ~BIT0;//off
	wait(waitForGo);
	P1OUT |= BIT6;//on
	wait(waitForGo);
	P1OUT &= ~(BIT0+BIT6);//off
	wait(waitForGo);
}
