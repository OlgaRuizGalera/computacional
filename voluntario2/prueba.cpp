#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <complex>
#include <cstdlib>
#include <ctime>

/* En este caso tendre el mismo codigo que en el obligatorio pero añadiendo calculos
Voy a definir un vector probabilidad para poder buscar el maximo en un intervalode tiempo
Por tanto necesito tambine una funcion que me busque el maximo valor y lo asigne a un nd
Una vez encontrado nd empiezo un bucle que se evalue las veces que dice el pdf
Cada vez que el contador llegue a nd evaluo la probabilidad y sigo el paso 6*/

#define PI 3.14159


using namespace std;

int main (void) 
{

    int N, ncic, j, n, l, h, z, m;
    double lamb, k0, s, V[1000], a, norma[1000], prob, p;
    complex<double> A0[1000], alfa[1000], beta[10000], b, x[1000], fo[1000], i, gamma[1000];
    ofstream coeficiente,  probabilidad2;

    
    probabilidad2.open ("probabilidad_drch.dat");
    coeficiente.open ("coeficiente.dat");
    srand(time(NULL));

    /* Damos los valores iniciales a los datos que conocemos*/
    i=complex<double>(0.0,1.0);
    N=500;
    ncic=N/8;
    lamb=1.5;
    h=0;
    m=0;

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
    norma[0]=norm(fo[0]);
    for (j=1; j<N-1; j++)
    {
        a=exp(-8.0*(4.0*j-N*1.0)*(4.0*j-N*1.0)/(N*N*1.0));
        fo[j]=a*exp(i*k0*(j*1.0));
        norma[j]=norm(fo[j]);
    }
    norma[N-1]=norm(fo[N-1]);

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
    
    /*ESte primer bucle es para buscar el maximo local de la probabilidad*/
    while (h<1000)
    {
        
        z=0;  
        while (z<N/2)
        {
            /*Evaluo la funcion de onda*/
            
            for (j=0; j<N; j++)
            {
                fo[j]=x[j]-fo[j];
                norma[j]=norm(fo[j]);
            } 

            z=z+1;

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

            z=z+1;
        }

        /*Calculo prob(nd)*/
        prob=0.0;
        for (j=4*N/5; j<N+1; j++)
        {
            prob=prob+norma[j]*norma[j];
        }
        probabilidad2<<h<<" , "<< prob<<endl;
        p=rand()/(RAND_MAX*1.0);
        if (p>prob)
        {
            m=m+1;
        }
        
        h=h+1;
        
    }
    coeficiente<<lamb<< " , "<<m*1.0/h<<endl;
    
    probabilidad2.close();
    coeficiente.close();
    return 0;
}

