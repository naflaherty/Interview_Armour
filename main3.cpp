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

    // Ensure the LED is ON initially
    int state = HIGH;
	
	
	const int INPUT_PIN = 1;
    // Read input on this pin
    pinMode(INPUT_PIN, INPUT);


    while(true)
    {
        // As soon as we dedect an input, log and quit.
        if(digitalRead(INPUT_PIN) == HIGH)
		{
			printf("Button is pressed!\n");	
			//break;
			  digitalWrite(0, state);
			  sleep(1);
		}
		else {
		     digitalWrite(0, LOW);
		     printf("else statement \n");
		     sleep(1);
		 }
		
    }
   
// Exit program
    return 0;
}
