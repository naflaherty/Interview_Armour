//https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-push-buttons-reading-gpio-input/
//https://www.npmjs.com/package/onoff

#include <stdio.h>
#include <wiringPi.h>

#include <unistd.h>

int main(int argc, char** argv)
{
    // Intialize the wiringPi Library
    wiringPiSetup();
     
    pinMode(0, OUTPUT); // LED is connected on physical pin 11.
    pinMode(3, OUTPUT); // LED is connected on physical pin 15.
    pinMode(4, OUTPUT); // LED is connected on physical pin 16.

    // Ensure the LED is ON initially
    int state = LOW;
	
	
    const int INPUT_PIN = 1; //This the physical pin the switch is connected to. Pin 12
    // Read input on this pin
    pinMode(INPUT_PIN, INPUT);    
	  
    while(true)    
    {
        // As soon as we dedect an input, log and quit.
       if((digitalRead(INPUT_PIN) == HIGH) && (state == HIGH))
	{
	    printf("LEDs ON\n");
	    state = LOW;		
	    
	    //switch on LEDs
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16
	    sleep(1);
		
	}
    
	else if((digitalRead(INPUT_PIN) == HIGH) && (state == LOW))
	{
	    printf("LEDs OFF\n");//
	    state = HIGH;		
	    
	    //switch on LEDs
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16
	    sleep(1);

    }
    
    else if ((digitalRead(INPUT_PIN) == LOW) && (state == LOW))
    {
	    printf("idling!\n"); //
	    //state = LOW;		
	    
	    //switch on LEDs
	   // digitalWrite(0, state); //physical pin 11
	   // digitalWrite(3, state); //physical pin 15
	    //digitalWrite(4, state); //physical pin 16
	   // sleep(1);
		
    }
}

    
   digitalWrite(0, LOW);
// Exit program
    return 0;
}
