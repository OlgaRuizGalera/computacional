#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <complex>

#define PI 3.14159

/*ESte programilla es para calcular los valores esperados*/
/*SE calculan desde o hasta N asique necesito un bucle
de N pasos cada vez que calculo la función de onda*/
/*Luego hago el promedio y calculo error por montecarlo*/

using namespace std;

int main (void) 
{

    int N, ncic, j, n, l, h;
    double lamb, k0, s, V[6000], a, norma, normadeto;
    complex<double> A0[6000], alfa[6000], beta[60000], b, x[6000], fo[6000], i, gamma[6000];
    complex<double> espep, espeec;
    double xespe, pespe, ecespe, epespe, etotalespe;
    ofstream posicion, momento, energiacinetica, energiapotencial, energiatotal;

    posicion.open ("alax.txt");
    momento.open ("alap.txt");
    energiacinetica.open ("alaec.txt");
    energiapotencial.open ("alaep.txt");
    energiatotal.open ("alaetot.txt");

    /* Damos los valores iniciales a los datos que conocemos*/
    i=complex<double>(0.0,1.0);
    N=2000;
    ncic=N/8;
    lamb=0.3;
    h=0;
    xespe=0.0;
    pespe=0.0;
    ecespe=0.0;
    epespe=0.0;
    etotalespe=0.0;

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
    normadeto=norma;
    for (j=1; j<N-1; j++)
    {
        a=exp(-8.0*(4.0*j-N*1.0)*(4.0*j-N*1.0)/(N*N*1.0));
        fo[j]=a*exp(i*k0*(j*1.0));
        norma=norm(fo[j]);
        normadeto=normadeto+norma;
    }
    norma=norm(fo[N-1]);
    normadeto=normadeto+norma;

    /*Con estos primeros valores de la función de onda calculo los primeros 
    valores esperados de los observable*/


    for (j=0; j<N; j++)
    {
        xespe=xespe+j*norm(fo[j])/normadeto;
        epespe=epespe+norm(fo[j])*V[j]/normadeto;
    }

    /*Para el resto hay que tener cuidado con el primer y ultimo termino*/

    espep=-0.5*i*conj(fo[0])*(fo[1]-fo[0]);
    pespe=sqrt(norm(espep));

    espeec=-1.0*conj(fo[0])*(fo[1]+fo[0]-2.0*fo[0]);
    ecespe=sqrt(norm(espeec));

    /*Calculo para el resto*/

    for(j=1; j<N-1; j++)
    {
       espep=-0.5*i*conj(fo[j])*(fo[j+1]-fo[j-1]);
        pespe=pespe+sqrt(norm(espep));

        espeec=-1.0*conj(fo[j])*(fo[j+1]+fo[j-1]-2.0*fo[j]);
        ecespe=ecespe+sqrt(norm(espeec)); 
    }

    /*Calculo para N*/
    espep=-0.5*i*conj(fo[N])*(fo[N]-fo[N-1]);
    pespe=pespe+sqrt(norm(espep));
    pespe=pespe/normadeto;

    espeec=-1.0*conj(fo[N])*(fo[N]+fo[N-1]-2.0*fo[N]);
    ecespe=ecespe+norm(espeec);
    ecespe=ecespe/normadeto;

    etotalespe=ecespe+epespe;

    /*Paso los valores a ficheros*/
    posicion<<h<<" "<<xespe<<endl;
    momento<<h<<" "<<pespe<<endl;
    energiacinetica<<h<<" "<<ecespe<<endl;
    energiapotencial<<h<<" "<<epespe<<endl;
    energiatotal<<h<<" "<<etotalespe<<endl;

    /* Evaluo alfa*/
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
    while (h<6000)
    {

        xespe=0.0;
        pespe=0.0;
        ecespe=0.0;
        epespe=0.0;
        etotalespe=0.0;
        /*Evaluo la funcion de onda*/
        normadeto=0.0;
       for (j=0; j<N; j++)
        {
            fo[j]=x[j]-fo[j];
            norma=norm(fo[j]);
            normadeto=normadeto+norma;
        } 

        h=h+1;

         for (j=0; j<N; j++)
        {
            xespe=xespe+j*norm(fo[j])/normadeto;
            epespe=epespe+norm(fo[j])*V[j]/normadeto;
        }

    /*Para el resto hay que tener cuidado con el primer y ultimo termino*/

        espep=-0.5*i*conj(fo[0])*(fo[1]-fo[0]);
        pespe=sqrt(norm(espep));

        espeec=-1.0*conj(fo[0])*(fo[1]+fo[0]-2.0*fo[0]);
        ecespe=sqrt(norm(espeec));

    /*Calculo para el resto*/

        for(j=1; j<N-1; j++)
        {
            espep=-0.5*i*conj(fo[j])*(fo[j+1]-fo[j-1]);
            pespe=pespe+sqrt(norm(espep));

            espeec=-1.0*conj(fo[j])*(fo[j+1]+fo[j-1]-2.0*fo[j]);
            ecespe=ecespe+sqrt(norm(espeec)); 
        }

    /*Calculo para N*/
        espep=-0.5*i*conj(fo[N])*(fo[N]-fo[N-1]);
        pespe=pespe+sqrt(norm(espep));
        pespe=pespe/normadeto;

        espeec=-1.0*conj(fo[N])*(fo[N]+fo[N-1]-2.0*fo[N]);
        ecespe=ecespe+sqrt(norm(espeec));
        ecespe=ecespe/normadeto;

        etotalespe=ecespe+epespe;

    /*Paso los valores a ficheros*/
        posicion<<h<<" "<<xespe<<endl;
        momento<<h<<" "<<pespe<<endl;
        energiacinetica<<h<<" "<<ecespe<<endl;
        energiapotencial<<h<<" "<<epespe<<endl;
        energiatotal<<h<<" "<<etotalespe<<endl;

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

    posicion.close ();
    momento.close ();
    energiacinetica.close ();
    energiapotencial.close ();
    energiatotal.close ();
    return 0;
}
