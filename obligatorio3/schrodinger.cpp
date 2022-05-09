#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <complex>

#define PI 3.1415

using namespace std;

int main (void) 
{

    int N, ncic, j, n, l, h;
    double lamb, k0, s, V[N], a;
    complex<double> A0[N], alfa[N], beta[N], b, x[N], fo[N], i, gamma[N];
    ofstream schrodinger;

    schrodinger.open ("schrodinger.txt");

    /* Damos los valores iniciales a los datos que conocemos*/
    i=complex<double>(0.0,1.0);
    N=10;
    ncic=1;
    lamb=1.;

    /*Doy valores iniciales evaluando con los parametros anteriores*/
    k0=2*PI*ncic/N;
    s=1/(4*k0*k0);

    /*Creo el potencial como un vector para luego poder identificarlo punto a punto del espacio
    y no tener qu edarle valores todo el rato*/
    for (j=0; j<N; j++)
    {
        if (j>=2*N/5 && j<=3*N/5)
        {
            V[j]=lamb*k0*k0;
        }
        else V[j]=0.0; 
    }

    /*Evaluamos la funcion de onda en todo j desde 0 hasta N usando las condiciones de contorno*/
    fo[0]=fo[N-1]=0.0;
    schrodinger<<fo[0]<<",";
    for (j=1; j<N-1; j++)
    {
        a=exp(-8*(4*j-N)*(4*j-N)/(N*N));
        fo[j]=a*1.0*exp(i*k0*(j*1.0));
        schrodinger<<fo[j]<<",";
    }
    schrodinger<<fo[N-1];
    schrodinger<<endl;

    /* Evaluo alfa*/
    /*A- es siempre 1 y A+ tambien asi que solo tengo que evaluar A0*/
    /*Gamma y alfa se calculan en un mismo bucle*/
    for (j=0; j<N; j++)
    {
        A0[j]=-2.0+2.0*i/s-V[j];
    }

    alfa[N-2]=gamma[N-1]=0.0;
    for (l=N-2; l=1; l--)
    {
        gamma[l]=A0[l]+alfa[l];
        alfa[l-1]=-gamma[l];
    }

    /*Evaluo beta usando gamma y el valor inicial de beta*/
    beta[N-2]=0.0;
    for (j=N-2; j=1; j--)
    {
        beta[j-1]=gamma[j]*(4.0*i*fo[j]/s);
    }

    /*Calculo x*/
    x[0]=0.0;
    for (j=0; j<N-1; j++)
    {
        x[j+1]=alfa[j]*x[j]+beta[j];
    }

    /*Empiezo bucle evaluando la funcion de onda y vuelvo a calcular el resto de parametros
    al final del bucle tomo sumo 1 al contador*/

    h=0;
    while (h<10)
    {
        /*Evaluo la funcion de onda*/
       for (j=0; j<N-1; j++)
        {
            fo[j]=x[j]-fo[j];
            schrodinger<<fo[j]<<",";
        } 
        fo[N-1]=x[N-1]-fo[N-1];
        schrodinger<<fo[N-1];
        schrodinger<<endl;

        h=h+1;

        /*Evaluo beta usando gamma y el valor inicial de beta*/
        /*No tengo que evaluar el primero todo el rato porque siempre vale 0*/
        for (j=N-2; j=1; j--)
        {
            beta[j-1]=gamma[j]*(4.0*i*fo[j]/s);
        }

        /*Calculo x*/
        x[0]=0.0;
        for (j=0; j<N-2; j++)
        {
            x[j+1]=alfa[j]*x[j]+beta[j];
        }


    }

    schrodinger.close ();
    return 0;
}
