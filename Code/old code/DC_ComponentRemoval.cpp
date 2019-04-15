//This code is base on a tutorial found here:https://morf.lv/implementing-pulse-oximeter-using-max30100 and http://sam-koblenski.blogspot.com/2015/11/everyday-dsp-for-programmers-dc-and.html
//it's horrible code - sorry about that.


#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;
extern const int numSamples;
vector<int> DC_remove;

vector<int> DC_ComponentRemoval(vector<int> & temp)
{
	vector<int> DC_remove;
	vector<int> w_t;
	vector<int> filtSig;
	double alpha = 0.9;

	
	for (int i = 0; i<temp.size(); i++)
	{
		if ((i == 0) || i == temp.size())
		{
			int before = temp[1];
			int after = temp[2];
			int weetemp = after + (alpha * before);

			w_t.push_back(weetemp);
		}
		else {
			int weetemp = temp[i] + (alpha * temp[i - 1]);
			w_t.push_back(weetemp);
			int output = weetemp - w_t[i - 1];
			DC_remove.push_back(output);
		}
	}

		return DC_remove;
}
