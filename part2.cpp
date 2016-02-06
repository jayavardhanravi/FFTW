#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <fftw3.h>

using namespace std;

int main( int argc, char** argv )
{
	double *xVar, samplingTime, samplingRate = 200;
	const int N=256;
	samplingTime = 1/samplingRate;
	fstream fVar;
	fVar.open("samples_data.txt");
	xVar = new double[N]();
	int count,j=0;
	for(int i=0;i<N;i++)
	{	
		double tmp;
		fVar >> tmp;
		fVar >> xVar[j];
		count++;
		j++;
	}
	fVar.close();
	fftw_complex *x,*xOut;
	x = new fftw_complex[N]();
	xOut = new fftw_complex[N]();
	for(int i=0;i<N;i++)
	{
		x[i][0] = xVar[i];
		x[i][1] = 0;
	}
	fftw_plan myPlan=fftw_plan_dft_1d(N,x,xOut,FFTW_FORWARD,FFTW_ESTIMATE);
	fftw_execute(myPlan);
	fftw_destroy_plan(myPlan);
	ofstream fVarOut,fVarOut1;
	fVarOut.open("samples_data_output.txt");
	for(int k=0;k<N;k++)
	{
		fVarOut << k <<" "<< xOut[k][0] << endl;
	}
	fVarOut1.open("samples_data_output1.txt");
	for(int k1=0;k1<N;k1++)
	{
		fVarOut1 << (2*(3.14))/(k1*samplingTime) <<" "<< xOut[k1][0] << endl;
	}
}