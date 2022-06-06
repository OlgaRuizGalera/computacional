#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <complex>

#define PI 3.14159

using namespace std;

int main (void) 
{

    int N, ncic, j, n, l, h;
    double lamb, k0, s, V[1000], a, norma, normadeto;
    complex<double> A0[1000], alfa[1000], beta[10000], b, x[1000], fo[1000], i, gamma[1000];
    ofstream schrodinger, fichero;

    schrodinger.open ("schrodinger.txt");
    fichero.open ("norma.txt");

    /* Damos los valores iniciales a los datos que conocemos*/
    i=complex<double>(0.0,1.0);
    N=200;
    ncic=N/8;
    lamb=0.0;
    h=0;

    /*Doy valores iniciales evaluando con los parametros anteriores*/
    k0=2.0*PI*(1.0*ncic)/(1.0*N);
    s=1.0/(4.0*k0*k0);

    /*Creo el potencial como un vector para luego poder identificarlo punto a punto del espacio
    y no tener qu edarle valores todo el rato*/
    for (j=0; j<N; j++)
    {
        if ((j>=(2*N/5)) && (j<=(3*N/5)))
        {
            V[j]=lamb*k0*k0;
        }
        else V[j]=0.0; 
    }

    /*Evaluamos la funcion de onda en todo j desde 0 hasta N usando las condiciones de contorno*/
    fo[0]=fo[N-1]=0.0+i*0.0;
    norma=norm(fo[0]);
    schrodinger<<0<<" , "<<norma<<" , "<<V[0]<<endl;
    normadeto=norma;
    for (j=1; j<N-1; j++)
    {
        a=exp(-8.0*(4.0*j-N*1.0)*(4.0*j-N*1.0)/(N*N*1.0));
        fo[j]=a*exp(i*k0*(j*1.0));
        norma=norm(fo[j]);
        schrodinger<<j<<" , "<<norma<<" , "<<V[j]<<endl;
        normadeto=normadeto+norma;
    }
    norma=norm(fo[N-1]);
    schrodinger<<N-1<<" , "<<norma<<" , "<<V[N-1]<<endl;
    schrodinger<<endl;
    normadeto=normadeto+norma;
    fichero<<h<<" "<<normadeto/22.1557<<endl;

    /* Evaluo alfa*/
    /*A- es siempre 1 y A+ tambien asi que solo tengo que evaluar A0*/
    /*Gamma y alfa se calculan en un mismo bucle*/
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

    /*Empiezo bucle evaluando la funcion de onda y vuelvo a calcular el resto de parametros
    al final del bucle tomo sumo 1 al contador*/

    h=h+1;
    while (h<1000)
    {
        /*Evaluo la funcion de onda*/
        normadeto=0.0;
       for (j=0; j<N; j++)
        {
            fo[j]=x[j]-fo[j];
            norma=norm(fo[j]);
            schrodinger<<j<<" , "<<norma<<" , "<<V[j]<<endl;
            normadeto=normadeto+norma;
        } 
        schrodinger<<endl;
        fichero<<h<<" "<<normadeto/22.1557<<endl;

        h=h+1;

        /*Evaluo beta usando gamma y el valor inicial de beta*/
        /*No tengo que evaluar el primero todo el rato porque siempre vale 0*/
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

    schrodinger.close ();
    fichero.close ();
    return 0;
}
