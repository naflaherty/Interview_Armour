//https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-our-first-led-controlling-gpio-output/

//ENG 5055 : Real Time Embedded Programming
//This code is based on a tutorial found here:
//https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-our-first-led-controlling-gpio-output/

//This code will switch on the LED/Motors.
//It uses the WiringPi Library and Cmake



#include <stdio.h>
#include <wiringPi.h>

#include <unistd.h> // Required for Sleep();

int main(int argc, char** argv)
{
    // Intialize the wiringPi Library
    wiringPiSetup();

    // LED is connected on pin 0/GPIO 11. Ensure
    // this pin is set to be an Output.
    pinMode(0, OUTPUT);

    // Ensure the LED is ON initialitial
    int state = HIGH;

    for(int i = 0; i < 10; i++)
    {
        // Turn on or off depending on state
        digitalWrite(0, state);

        // Toggle to HIGH/LOW output
        state = (state == HIGH) ? LOW : HIGH;


// Wait 1 second
        sleep(1);
    }

    // Ensure we turn LED off
    digitalWrite(0, LOW);
    
    // Exit program
    return 0;
}
