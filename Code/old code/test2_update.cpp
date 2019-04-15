//https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-push-buttons-reading-gpio-input/
//https://www.npmjs.com/package/onoff

#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>   //this is the sleep function
#include <thread>
#include <vector>

#include "lux_calcs.cpp"


using namespace std;

int calculated_lux_value(vector<int> vect);
int test(vector<int>vect);

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
    
    unsigned int lux_value;

    while(true)    
    {
	if((digitalRead(INPUT_PIN) == HIGH) && (state == HIGH))
	{
	    printf("Button press - LEDs off?!\n");
	    state = LOW;		
	    
	    //switch off LEDs
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16
	    sleep(1);
	    exit(0);
		
	}
    
	else if((digitalRead(INPUT_PIN) == HIGH) && (state == LOW))
	{
	    printf("LEDs ON\n");//
	    state = HIGH;		
	    
	    //switch on LEDs
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16
	    sleep(1);
	    
	    //unsigned int inside_lux_calc = lux_calcs; this calls the function
	    //calculated_lux_value = lux_calcs();
	    auto temp = lux_calcs();
	    
	    
	   cout<<"main_values in the vector"<<endl;
	   for(vector<int>::const_iterator i =temp.begin(); i != temp.end(); ++i)
	   cout<<*i <<"woo hoo"<<endl;

	    

    }
    
    else if ((digitalRead(INPUT_PIN) == LOW) && (state == LOW))
    {
	    printf("idling!\n"); //
	    state = LOW;		
	    
	    //switch on LEDs
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16
	    sleep(1);
	    
		
    }
    
    //else if ((digitalRead(INPUT_PIN) == LOW) && (state == HIGH))
    //{
	//    printf("last else if!\n"); //
	//    state = LOW;		
	    
	    //switch on LEDs
	//    digitalWrite(0, state); //physical pin 11
	//    digitalWrite(3, state); //physical pin 15
	//    digitalWrite(4, state); //physical pin 16
	//    sleep(1);
		
    //}
}

    
   digitalWrite(0, LOW);
// Exit program
    return 0;
}
