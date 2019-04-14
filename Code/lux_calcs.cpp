//This code has been written as part of the ENG5220 Real Time Embedded Programming class at University of Glasgow.
//It is provide here without warranty and no updates will be issued.

//This program uses the code from the light sensor manufacturer, Texas Instruments LIGHT-TO-DIGITAL CONVERTER TSL2560 to calculate the lux values used.
//This code can be found here: https://cdn-shop.adafruit.com/datasheets/TSL2561.pdf

//This code was written with help from: https://www.controleverything.com/content/Light?sku=TSL2561_I2CS#tabs-0-product_tabset-2
#include <stdio.h>
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

#include "lux.cpp" 
using namespace std;
extern const int numSamples;
vector<int> calculated_value;

vector<int> lux_calcs() //vector<int> vect
{

calculated_value.clear();

	// Create I2C bus
	int file;
	
	const char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	
	// Get I2C device, TSL2561 I2C address is 0x39
	ioctl(file, I2C_SLAVE, 0x39);

	// Select control register(0x00 | 0x80)
	// Power ON mode(0x03)
	char config[2] = {0};
	config[0] = 0x00 | 0x80;
	config[1] = 0x03;
	write(file, config, 2);
	
	// Select timing register(0x01 | 0x80)
	// Nominal integration time = 402ms(0x02)
	config[0] = 0x01 | 0x80;
	config[1] = 0x11;
	write(file, config, 2);
	
	//define variables for lux calculation
	unsigned int iGain = 1; //16x gain value
	unsigned int tInt = 1; //integration time is 13mS
	unsigned int ch0; //raw data values...
	unsigned int ch1;
	int iType = 0; //this is the sensor type, set to T

	int count = 0;
	
	while (count<20) //<10
	{
	// Read 4 bytes of data from register(0x0C | 0x80)
	// ch0 lsb, ch0 msb, ch1 lsb, ch1 msb
	char reg[1] = {0x0C | 0x80};
	write(file, reg, 1);
	char data[4] = {0};
	
	//this is the sampling value to ensure that we can see a new reading from the sensor
	std::this_thread::sleep_for(std::chrono::milliseconds(102));
	
	if(read(file, data, 4) != 4)
	{
		printf("Error : Input/output Error \n");
	}
	else
	{
		// Convert the data
		ch0 = (data[1] * 256 + data[0]);
		ch1 = (data[3] * 256 + data[2]);
		
		//int lux_value = CalculateLux(iGain, tInt, ch0, ch1, iType);
		calculated_value.push_back(ch0); //lux_value
		//cout<<"lux value: "<<lux_value<<endl;
	}
	count++;	
}
return calculated_value;

}


