#ifndef FFT3_H
#define FFT3_H
#include<complex>
#include <iostream>
std::complex<double>* FFT3(std::complex<double> *Arr,int N)
{
    if(N<=1) return Arr;
    std::cout << "ФФТ ОТРАБОТАЛО" << std::endl;
    std::complex<double> OmegaN(cos(2.0*(M_PI/N)), sin(2.0*(M_PI/N)));
    std::complex<double> Omega(1.0, 0.0);
    std::complex<double> *A0= new std::complex<double>[N/2];
    std::complex<double> *A1= new std::complex<double>[N/2];
    int k=0;
    int m=0;
    for(int i=0;i<N;i++)
    {
        if(i%2==0)
        {
            A0[k]=Arr[i];
            k++;
        }
        else
        {
            A1[m]=Arr[i];
            m++;
        }
    }
    std::complex<double> *Y0=FFT3(A0,N/2);
    std::complex<double> *Y1=FFT3(A1,N/2);
    std::complex<double> *Y=new std::complex<double>[N];
    for(k=0;k<N/2;k++)
    {
        std::complex<double> temp;
        temp=Y1[k]*Omega;
        Y[k]=Y0[k]+temp;
        Y[k+(N/2)]=Y0[k]-temp;
        Omega=Omega*OmegaN;
    }
    delete [] A0;
    delete [] A1;
    return Y;
}
#endif // FFT3_H
