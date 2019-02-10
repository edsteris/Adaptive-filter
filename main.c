
#include <iostream>		
#include <fstream>		
#include <stdio.h>      



using namespace std;


float miu=0.1; //adaptation step
int M=15; //filter order
float xa[15]; //filter reference vector
float w[15]; //filter coeficients
float name; //input variable
int l=176000; //signal length
float s1[176000]; //signal 
float s2[176000]; //noise
float xiv[176000]; //signal mulitplied by coeficients
float siv[176000]; // signal
long i,j,p1,p2; //variables

//------------------Functions-----------------------//

float* cshift(int l, int n, float x[]) 
{ 

// cshift function shifts x variables in circular way by number of n

   float y[l]; 
	int j,i;
	for (i=0;i<l;i++)
	{
		

	j=l-n+i;
	
	y[i]=x[j];
	
	if(n-i<=0)
	{
		y[i]=x[i-n];
	}
			
}
return y;
} 

//----------------------------------------------------------------//
float multiply(int l,float x[],float y[])
{

// vector multiplication by x and y vectors

	float z;
	float z1=0; //int r;
	int i;
	for (i=0;i<l;i++)
	{
		z=x[i]*y[i];
	    z=z+z1;
		z1=z;	
	}
	
	return z;
}
//--------------------------------------------------------------------//

float* wcoef(int l, float a[],float b[], float c)
{
	// filter w coeficients
	
	float  wc[l]; int i;
	
	for (i=0;i<l;i++)
	{
		wc[i]=a[i]+(2*miu*c*b[i]);
	}
	
	return wc;
}


//---------------------MAIN-------------------------//
int main()
{


//------------Signal input--------------------------------------//


ifstream theFile("signal_noise.txt"); //input file

	while(theFile >>name)


{

// this part is used to load the signal from txt file//

if(i<=l)
{
	s1[i]=name;
	i=i+1;
	p1=p1+1;	
}
	
		
	if(i>l)
		{
	s2[j]=name;	
	j=j+1;
	p2=p2+1;
	
}	
		}
	

cout<<"p1="<<p1<<endl; // to check is loaded signal correct length
cout<<"p2="<<p2<<endl;

//-----------------------------------------------------------------------//

//loading coefients by 0

	for(i=0;i<M;i++)
{
	xa[i]=0; w[i]=0;
}

//------------------------Signal processing----------------//

for(i=0;i<l;i++)
{
	   float* xv =cshift(M,1,xa); // circular shifting by 1 xa 
	  
	    xv[0]=s1[i]; //uploading signal variable as xv[0] variable
		xiv[i]=multiply(M,xv,w); // vector multiplication 
		siv[i]=s2[i]-xiv[i]; // input signal - mulitplied vector
		float* w1=wcoef(M,w,xa,siv[i]); // coeficient update
		
		//because of a different variable name, variables have to be updated
		for (j=0;j<M;j++)
		{
			xa[j]=xv[j];
			w[j]=w1[j];
		}
	

				
}
	
	
	ofstream text("filtered_signal_1.txt"); //output file

	for(i=0;i<l;i++)
	{

	
	text <<siv[i]<<endl;
	
	
	}
	
	cout<<"Filtering have been finished!"<<endl;		
}
