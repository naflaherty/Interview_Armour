//This code is supposed to remove an impluse noise present in the signa/
//It based on a tutorial found here: http://sam-koblenski.blogspot.com/2015/11/everyday-dsp-for-programmers-dc-and.html



#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
extern const int numSamples;

vector<int> imRemoved;

vector<int> INRemoval(vector<int> & filteredSignal ) 
{	
int filtSignal, numPos, numNeg;

vector<int> sumDiff;
imRemoved.clear();

int tempMean = accumulate(filteredSignal.begin(), filteredSignal.end(), 0); //mean of signal values

for (int i = 0; i<filteredSignal.size(); i++) //this should calculate the number of values greater and less than the mean
{ 
	if (filteredSignal[i] > tempMean) {
	 numPos++;
	 sumDiff.push_back(filteredSignal[i] - tempMean);
 }
	else {numNeg++;}
}

int Dpos = accumulate(sumDiff.begin(), sumDiff.end(), 0); 

int diff = numPos- numNeg; //this is numPos - numNeg 


filtSignal = tempMean + (numPos - numNeg) * diff / (filteredSignal.size())^2;

for (int i = 0; i<filteredSignal.size(); i++)
{
		imRemoved.push_back(filteredSignal[i] - filtSignal);
}

return imRemoved;
}
