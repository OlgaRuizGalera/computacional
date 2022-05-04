#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <complex>

#define PI 3.1415

using namespace std;

int main (void) 
{

    
    int N, ncic, j, n, l;
    double lamb, k0, s, gamma, V[N], a;
    complex<double> A0, alfa[N], beta, b, x, fo[N][N], i;
    ofstream schrodinger;

    schrodinger.open ("schrodinger.txt");

    /* Damos los valores iniciales a los datos que conocemos*/
    i=complex<double>(0,1);
    N=1;
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
    /*Mirar bien que se evalue asi en N por la definicion de vectores*/
    fo[0][0]=fo[N][0]=0.0;
    for (j=1; j<N; j++)
    {
        a=exp(-8*(4*j-N)*(4*j-N)/(N*N));
        fo[j][0]=a*cos(k0*j)+i*a*sin(k0*j);
    }

    /* Evaluo alfa*/
    for (l=N-1; l=0; l--)
    {

    }

    schrodinger.close ();
    return 0;
}
