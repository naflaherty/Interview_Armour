//This code calculates the number of peaks in the sensor data.
//It's based on a solution found here: https://stackoverflow.com/questions/29481346/c-finding-local-maxima-in-2d-array

#include <iostream>
#include <vector>
using namespace std;
extern const int numSamples;
vector<int> peaks;
vector<int> no_peaks;

vector<int> peak_finder(vector<int> & temp) 
{	
	peaks.clear();
	
	int before = 0, after = 0;
	


	for (int i = 0; i < numSamples; i++)
	{
		if ((i == 0 || temp[i] > temp[i - 1]) && (i == (numSamples - 1)|| temp[i] >= temp[i + 1]))
		{
			before = temp[i - 1];
			after = temp[i + 1];
			peaks.push_back(temp[i]);
		}
	}
		
	return peaks;
}
