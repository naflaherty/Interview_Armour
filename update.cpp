//https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-push-buttons-reading-gpio-input/
//https://www.npmjs.com/package/onoff

#include <stdio.h>
#include <wiringPi.h>

#include <unistd.h>
int main(int argc, char** argv)
{
    // Intialize the wiringPi Library
    wiringPiSetup();

    //DEAL WITH LED SET UP FIRST
	
    // LED is connected on physical pin 11. Ensure
    // this pin is set to be an Output.
    pinMode(0, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

    // Ensure the LED is ON initially
    int state = HIGH;
	
	
	const int INPUT_PIN = 1;
    // Read input on this pin
    pinMode(INPUT_PIN, INPUT);

    int flag = 0;
    //while(true)
    //{
        // As soon as we dedect an input, log and quit.
    if(digitalRead(INPUT_PIN) == HIGH){
	int flag = 1;
    }
    
	while(flag ==1)
	{
	printf("Button is pressed!\n");	
	//break;
			
	//switch on LEDs
	digitalWrite(0, state); //physical pin 11
	digitalWrite(3, state); //physical pin 15
	digitalWrite(4, state); //physical pin 16
	sleep(1);
	}
    
    if (digitalRead(INPUT_PIN) == LOW) {
	flag ==0;
	digitalWrite(0, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	printf("else statement \n");
	sleep(1);
    }
		
    //}
   
// Exit program
    return 0;
}
