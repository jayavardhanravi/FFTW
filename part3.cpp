#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

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
	fVarh.open("samples_data_hn_part3.txt");
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
	
	int fSize;
	const int N = 25;
	int	highCheck,lowCheck;
	double *xVar, *yVar, *fOutVar;
	
	fSize = (2*N)-1;
	xVar = new double[N]();
	yVar = new double[N]();
	fOutVar = new double[fSize]();
	
	fstream fVar_x,fVar_y;
	fVar_x.open("samples_data.txt");
	fVar_y.open("samples_data_hn_part3.txt");
	int count=0,j=0;
	for(int i=0;i<N;i++)
	{	
		double tmp;
		fVar_x >> tmp;
		fVar_x >> xVar[j];
		count++;
		j++;
	}
	count=0;
	j=0;
	for(int i=0;i<N;i++)
	{	
		double tmp;
		fVar_y >> tmp;
		fVar_y >> yVar[j];
		count++;
		j++;
	}
	fVar_x.close();
	fVar_y.close();
	
	for(int i=0;i<fSize;i++)
	{
		if(i<(N-1))
		{
			highCheck = i;
		}
		else
		{
			highCheck = (N-1);
		}
		if(i>=(N-1))
		{
			lowCheck = i-(N-1);
		}
		else
		{
			lowCheck = 0;
		}
		fOutVar[i] =0;
		for (int j=lowCheck;j<=highCheck;j++)
		{
			fOutVar[i] =fOutVar[i]+((xVar[i-j])*(yVar[j]));
		}
	}
	
	ofstream fVar_fOut;
	fVar_fOut.open("sample_data_part3.txt");
	for(int k=0;k<N;k++)
	{
		fVar_fOut << k <<" "<< xVar[k] <<" "<< yVar[k] <<" "<< fOutVar[k] << endl;
	}
	
	return 0;
}