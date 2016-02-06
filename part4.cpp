#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <fftw3.h>

using namespace std;

double xfunct(int n)
{
	double var,t,samp=200;
	t = n/samp;
	var = 2*exp((-2)*t)*sin((40)*t);
	return var;
}

int main( int argc, char** argv )
{
	long double samples[25], hsignal, t;
	ofstream fVarh;
	fVarh.open("samples_data_hn.txt");
	for(int n=0;n<25;n++)
	{
		double x1,x2,x3;
		x1 = xfunct(n);
		x2 = xfunct(n-1);
		x3 = xfunct(n-2);
		hsignal = (0.3)*(x1+x2+x3);	
		fVarh << n <<" "<< hsignal << endl;
	}
	fVarh.close();
	double *xVar,*hVar;
	const int N=25;
	fstream fVar,fVarh1;
	fVar.open("samples_data.txt");
	fVarh1.open("samples_data_hn.txt");
	xVar = new double[N]();
	hVar = new double[N]();
	int count=0,j=0;
	for(int i=0;i<N;i++)
	{	
		double tmp;
		fVar >> tmp;
		fVar >> xVar[j];
		count++;
		j++;
	}
	count=0;
	j=0;
	for(int i=0;i<N;i++)
	{	
		double tmp;
		fVarh1 >> tmp;
		fVarh1 >> hVar[j];
		count++;
		j++;
	}
	fVar.close();
	fVarh1.close();
	fftw_complex *x,*xOut,*h,*hOut,*fOut,*f;
	x = new fftw_complex[N]();
	h = new fftw_complex[N]();
	f = new fftw_complex[N]();
	xOut = new fftw_complex[N]();
	hOut = new fftw_complex[N]();
	fOut = new fftw_complex[N]();
	for(int i=0;i<N;i++)
	{
		x[i][0] = xVar[i];
		x[i][1] = 0;
	}
	for(int i=0;i<N;i++)
	{
		h[i][0] = hVar[i];
		h[i][1] = 0;
	}
	fftw_plan myPlan=fftw_plan_dft_1d(N,x,xOut,FFTW_FORWARD,FFTW_ESTIMATE);
	fftw_plan myPlan_h=fftw_plan_dft_1d(N,h,hOut,FFTW_FORWARD,FFTW_ESTIMATE);
	fftw_execute(myPlan);
	fftw_execute(myPlan_h);
	fftw_destroy_plan(myPlan);
	fftw_destroy_plan(myPlan_h);
	for (int m=0;m<N;m++)
	{
	f[m][0]=xOut[m][0]*hOut[m][0]-xOut[m][1]*hOut[m][1]; 
	f[m][1]=xOut[m][0]*hOut[m][1]+hOut[m][0]*xOut[m][1];
	}
	fftw_plan myPlan_f=fftw_plan_dft_1d(N,f,fOut,FFTW_BACKWARD,FFTW_ESTIMATE);
	fftw_execute(myPlan_f);
	fftw_destroy_plan(myPlan_f);
	ofstream fVarOut;
	fVarOut.open("samples_data_output_part4.txt");
	for(int k=0;k<N;k++)
	{
		fVarOut << k <<" "<< xVar[k] <<" "<< hVar[k] <<" "<< fOut[k][0]/N <<" " << endl;
	}
	return 0;
}