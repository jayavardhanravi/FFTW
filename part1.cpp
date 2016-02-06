#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main( int argc, char** argv )
{
	double samples[256], signal, samplingTime, t, samplingRate = 200;
	int n;
	ofstream fVar;
	fVar.open("samples_data.txt");
	
	samplingTime = 1/samplingRate;
	
	for(n=0;n<256;n++)
	{
		t = n*samplingTime;	
		signal = 2*exp((-2)*t)*sin((40)*t);	
		fVar << n <<" "<< signal << endl;
	}
	
	return 0;
}