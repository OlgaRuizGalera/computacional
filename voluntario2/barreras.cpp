#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <complex>
#include <cstdlib>
#include <ctime>


#define PI 3.14159

double montecarlo (double valor, double variable[],int contador);


using namespace std;

int main (void) 
{

    int N,  j, n, l, h, nd, z, k, m, q, Naux;
    double lamb, k0, s, V[2000], a, norma[2000], prob, prob2, p, normatotal, ncic;
    double coef[2000], errorcoef, coeftotal;
    complex<double> A0[2000], alfa[2000], beta[20000], b, x[2000], fo[2000], i, gamma[2000];
    ofstream coeficiente, probabilidad;

    probabilidad.open ("probabilidad.dat");
    coeficiente.open ("coeficiente803.dat");
    srand(time(NULL));

    /* Damos los valores iniciales a los datos que conocemos*/
    i=complex<double>(0.0,1.0);
    Naux=500;
    N=Naux+14*Naux/5;
    ncic=N/8;
    lamb=0.3;
    h=0;
    m=0;

    /*Doy valores iniciales evaluando con los parametros anteriores*/
    k0=2.0*PI*(1.0*ncic)/(1.0*N);
    s=1.0/(4.0*k0*k0);

    /*Creo el potencial*/
    for (j=0; j<N; j++)
    {
        if ((j>=(2*Naux/5)) && (j<=(3*Naux/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else if ((j>=(4*Naux/5)) && (j<=(Naux)))
        {
            V[j]=lamb*k0*k0;
        }
        else if ((j>=(6*Naux/5)) && (j<=(7*Naux/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else if ((j>=(8*Naux/5)) && (j<=(9*Naux/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else if ((j>=(10*Naux/5)) && (j<=(11*Naux/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else if ((j>=(12*Naux/5)) && (j<=(13*Naux/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else if ((j>=(14*Naux/5)) && (j<=(15*Naux/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else if ((j>=(16*Naux/5)) && (j<=(17*Naux/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else V[j]=0.0; 
    }

    /*Calculo la primera para buscar nd*/
    fo[0]=fo[N-1]=0.0+i*0.0;
    norma[0]=norm(fo[0]);
    for (j=1; j<N-1; j++)
    {
        a=exp(-8.0*(4.0*j-Naux*1.0)*(4.0*j-Naux*1.0)/(Naux*Naux*1.0));
        fo[j]=a*exp(i*k0*(j*1.0));
        norma[j]=norm(fo[j]);
    }
    norma[N-1]=norm(fo[N-1]);

    for (j=0; j<N; j++)
    {   
        A0[j]=-2.0+2.0*i/s-V[j];
    }

    alfa[N-2]=gamma[N-1]=0.0;
    for (l=N-2; l>=0; l--)
    {
        gamma[l]=A0[l]+1.0*alfa[l];
        alfa[l-1]=-1.0/gamma[l];
    }

    /*Evaluo beta usando gamma y el valor inicial de beta*/
    beta[N-2]=0.0;
    for (j=N-2; j>=0; j--)
    {
        beta[j-1]=(1.0/gamma[j])*(4.0*i*fo[j]/s-beta[j]);
    }

    /*Calculo x*/
    x[0]=0.0+i*0.0;
    for (j=0; j<N-1; j++)
    {
        x[j+1]=alfa[j]*x[j]+beta[j];
    }

    k=1;
    
    prob2=0.0;
    while (k<4500)
    {
        /*Evaluo la funcion de onda*/
        normatotal=0.0;
             
        for (j=0; j<N; j++)
        {
            fo[j]=x[j]-fo[j];
            norma[j]=norm(fo[j]);
            normatotal=normatotal+norma[j];
                
        } 

        /*Evalua aqui la probabilidad de encontrar la particula a la derecha*/
        /*La probabilidad la mido con h-1 porque el bucle empieza con h=1*/
        prob=0.0;
        for (j=18*Naux/5; j<N; j++)
        {
            prob=prob+norma[j];
        }


        if(prob/normatotal>prob2)
        {
            prob2=prob*1.0/normatotal;
            prob=0.0;
            nd=k;
        }

         /*Condicion para que no haga iteraciones de mas sin sentido*/
        /*if (k>nd)
        {
            k=2999;
        }*/
        
        probabilidad<<k<<" , "<< prob*1.0/normatotal*1.0 << endl;
    
        k=k+1;

        /*Evaluo beta usando gamma y el valor inicial de beta*/
        for (j=N-2; j>=0; j--)
        {
            beta[j-1]=(1.0/gamma[j])*(4.0*i*fo[j]/s-beta[j]);
        }

        /*Calculo x*/
        x[0]=0.0+0.0*i;
        for (j=0; j<N-2; j++)
        {
            x[j+1]=alfa[j]*x[j]+beta[j];
        }
    }
    /*DE este bucle saco la probabilidad y nd*/
    probabilidad<<endl;
    probabilidad<<"----------------------------"<<endl;
    probabilidad<<"El maximo es: "<<prob2<<endl;
    probabilidad<<"Se da para: "<< nd<<endl;
    probabilidad<<"NOrma total: "<<normatotal<<endl;

    /*Me voy a quedar con este valor de probablidad porque siempre sale el mismo*/
    /*Una vez q tengo nd y p(nd) calculo K*/
    q=0;
    /*LO calculo 70 veces para que me de algo decente*/
    while (q<70)
    {
       m=0;
       for (h=0; h<1000; h++)
       {
           p=rand()/(RAND_MAX*1.0);
            if (p<prob2)
            {
                m=m+1;
            }
       }
       coef[q]=m*1.0/1000.0;
        q=q+1;
        
    }
    /*Calculo k total*/

    for (j=0; j<70; j++)
    {
        coeftotal=coeftotal+coef[j];
    }
    
    coeftotal=coeftotal*1.0/70.0;
    errorcoef=montecarlo(coeftotal, coef, q);
    coeficiente<<lamb<< " , "<<coeftotal<<endl;
    coeficiente<<3.0*sqrt(errorcoef/70.0)<<endl;

    
    probabilidad.close();
    coeficiente.close();
    return 0;

}


double montecarlo (double valor, double variable[],int contador)
{
    int n;
    double error;
    for (n=0; n<contador; n++)
    {
        error=error+(variable[n]-valor)*(variable[n]-valor);
    }
    return error/(contador*1.0);
}
