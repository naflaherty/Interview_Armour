//ENG 5220: Real Time Embedded Programming
//Final Submission code
//Author: Natalie Flaherty

//This code will calculate the BPM of a person using a TSL2561 luminosity sensor. 

//This code is a disaster. It's been cobbled together from different sources as best I can manage.
//Due to difficulties in analysing the signal the BPM is an approximation based on the number of peaks identified in the lux values produced by the sensor.

//Some websites used as the basis of this code are:

//https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-push-buttons-reading-gpio-input/
//https://www.npmjs.com/package/onoff

#include <stdio.h>
#include <wiringPi.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <linux/i2c-dev.h>
//#include <sys/ioctl.h>
//#include <fcntl.h>
//#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>   //this is the sleep function
#include <thread>
#include <vector>

#include "lux_calcs.cpp"
#include "peak_finder.cpp"
#include "DC_ComponentRemoval.cpp"

const int numSamples = 20;

using namespace std;

int main(int argc, char** argv)
{
    
    // Intialize the wiringPi Library
    wiringPiSetup();
     
    pinMode(0, OUTPUT); // LED is connected on physical pin 11.
    pinMode(3, OUTPUT); // LED is connected on physical pin 15.
    pinMode(4, OUTPUT); // LED is connected on physical pin 16.

    // Ensure the LED is OFF initially
    int state = LOW;
	
	
    const int INPUT_PIN = 1; //This the physical pin the switch is connected to Pin 12
    
    // Read input on this pin
    pinMode(INPUT_PIN, INPUT);    
    
    while(true)    
    {
	if((digitalRead(INPUT_PIN) == HIGH) && (state == HIGH))
	{
	    cout<<"Thank you for using Interview Armour"<<endl;
	    state = LOW;		
	    
	    //switch off LEDs
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16
	    exit(0);
		
	}
    
	else if((digitalRead(INPUT_PIN) == HIGH) && (state == LOW))
	{
	    //printf("LEDs ON\n");//
	    state = HIGH;		
	    cout<<"Please wait while we gather data..."<<endl;
	    
	    while(state = HIGH)
	    {
	   
	    auto temp = lux_calcs(); //Get the lux values from the sensor
	    
	    auto filteredSignal = DC_ComponentRemoval(temp); //this function attempts to do DC component filtering on the signal
	    
	    auto numberPeaks = peak_finder(filteredSignal); //get the number of peaks in filtered signal
	    
	    int numPeaks = numberPeaks.size();
	    
	    int BPM = numPeaks *5;
	    cout<<"BPM: "<<BPM <<endl;
	    temp.clear();
	    numberPeaks.clear();
	    
	    ofstream outfile;
	    outfile.open("BPM.txt", ios_base::app);
	    outfile<<BPM;
	  
	    
	     outfile.close();
	    	   
	   if (BPM<=30){
		digitalWrite(0, LOW); //physical pin 11
		digitalWrite(3, LOW); //physical pin 15
		digitalWrite(4, LOW); //physical pin 16
	   }
	   
	   else if (BPM>30 && BPM <60){
	        cout<<"Your stress levels are rising. Try to relax!"<<endl;
		cout<<"One bank of vibration motors activated"<<endl;	  
		digitalWrite(0, state); //physical pin 11 
		digitalWrite(3, LOW); //physical pin 15
		digitalWrite(4, LOW); //physical pin 16
	     
	  }
	  
	  else if(BPM>=60 && BPM <90){
	      
	      cout<<"Your heart rate s continuing to rise. Remember to breathe!"<<endl;
	      cout<<"Two bank of vibration motors activated"<<endl;	 
	      digitalWrite(0, state); //physical pin 11
	      digitalWrite(3, state); //physical pin 15
	      digitalWrite(4, LOW); //physical pin 16   
	      }
	      
	 else{
		 	     
	    cout<<"Your heart rate is too high. Take a minute... "<<endl;
	    cout<<"All vibration motors activated"<<endl;
	    
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16
	   
	}
	    // need this condition to s top the code if the button is pressed again.
	    if((digitalRead(INPUT_PIN) == HIGH) && (state = HIGH))
	    break;
	    
	    }

    }
    
    else if ((digitalRead(INPUT_PIN) == LOW) && (state == LOW))
    {
	   // waiting for a button press
	    state = LOW;		
	    
	    //switch on LEDs
	    digitalWrite(0, state); //physical pin 11
	    digitalWrite(3, state); //physical pin 15
	    digitalWrite(4, state); //physical pin 16		
    }

}
   
    //Turn GPIO ports off
   digitalWrite(0, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
// Exit program
    return 0;
}
