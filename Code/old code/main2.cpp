//https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-push-buttons-reading-gpio-input/


#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char** argv)
{
    // Intialize the wiringPi Library
    wiringPiSetup();

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
                }
    }
// Exit program
    return 0;
}


