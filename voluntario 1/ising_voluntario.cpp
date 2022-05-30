#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

void minimo (double T, double E, double& p);
void magnetizacion (double mag[], int N, int s[100][100], int b);
void promedio (double& prom, double var[], int b);
void error (int b, double& error, double varia[10000], double prom);
double energiaparaelpromedio (double Epalpromedio, int n, int m, int N, int s[100][100]);

using namespace std;

int main (void) 
{
    int i, j, n, m, o, k, l, N, y, b, h, s[100][100];
    double p, f, T, E, c, e[10000], cor, mag[10000], r[10000];
    double promE, promr, promm, errorE, errorr, errorm, Epalpromedio, Epalpromedio1;
    double ener, cal;
    ofstream ising;
    ofstream valores;
 /*Falta funcion de correlacion*/

    srand(time(NULL));
    N=16; 
    T=1.5;
    h=0;
    b=0;

 /* Configuracion ordenada*/
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            s[i][j]=1;
        }
    }

    ising.open ("voluntario.dat");
    valores.open ("valores.dat");


 /*Escribo los primeros valores en el fichero*/
    for (k=0; k<N; k++)
    {
        for (l=0; l<N-1; l++)
        {
            ising<<s[k][l]<<",";
        }
        ising<<s[k][N-1];
        ising<<endl;
    }
    ising<<endl;


    for (o=0; o<1000000; o++)
    {
        for (y=0; y<N*N; y++)
        {

            n=rand()%N;
            m=rand()%N;
 
 /*Calculo la energia segun simetria*/
            if (n+1==N)
            {
                if (m==0)
                {
                    E=2.0*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
                }
                else if (m+1==N)
                {
                    E=2.0*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
                }
                else
                { 
                    E=2.0*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
                }
            }
            else if (n==0)
            {
                if (m==0)
                {
                    E=2.0*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
                }
                else if (m+1==N)
                { 
                    E=2.0*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);
                }
                else
                {
                    E=2.0*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);
                } 
            }
            else 
            {
                if (m==0)
                {
                    E=2.0*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
                }
                else if (m+1==N)
                {
                    E=2.0*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
                } 
                else
                { 
                    E=2.0*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
                }
            }

            minimo(T, E, p);
            f=rand()/(RAND_MAX*1.0);
            if (f<p)
            {
                s[n][m]=-s[n][m];
            }
        }

 /*Escribo en el fichero los valores de spin por cada pM*/
        for (k=0; k<N; k++)
        {
            for (l=0; l<N-1; l++)
            {
                ising<<s[k][l]<<",";
            }
            ising<<s[k][N-1];
            ising<<endl;
        }
        ising<<endl;

 /*Aumento en 1 h que es contador para cuando llegue a 100 pM
 Compruebo si ha llegado o no a 100 para contribuir al calculo de promedios*/
        h=h+1;
        if(h==100)
        { 

            magnetizacion (mag, N, s, b);
 /*Voy a calcular la energia pero de nuevo teniendo en cuenta la simetria y todo eso*/
            Epalpromedio1=0.0;
            for (n=0; n<N; n++)
            {
                for (m=0; m<N; m++)
                {
                    Epalpromedio=energiaparaelpromedio (Epalpromedio, n, m, N, s);
                    Epalpromedio1=Epalpromedio1+Epalpromedio;
                }
            }
 
            e[b]=Epalpromedio1*1.0;
            r[b]=Epalpromedio1*Epalpromedio1*1.0;
            b=b+1;
 /*Falta la funcion de correlacion pero no la entiendo*/
            h=0;
        }
 
    }

    ising.close ();

 /* Calculo de promedios y errores de la energia*/
 /*ME FALTA LA F*/
 
    promedio (promE, e, b);
    promedio (promr, r, b);
    promedio (promm, mag, b);
    error (b, errorE, e, promE);
    error (b, errorr, r, promr);
    error (b, errorm, mag, promm);

 /*Calculo las magnitudes y los errores multiplicando por las constantes necesarias*/
 /*La magnetizacion es directamente el promedio de m, promm*/
 /*ESCRIBIR EN FICHERO Y CALCULAR LA F*/
    ener=promE/(2.0*N*N);
    cal=(promr-promE*promE)/(T*N*N*1.0);

 /*Calcular los errores por derivadas y eso*/

    valores<<"Magnetización: "<<promm<<endl;
    valores<<"Energia: "<<ener<<endl;
    valores<<"Calor especifico: "<<cal<<endl;

    valores.close ();

 
    return 0;
}


void minimo (double T, double E, double& p)
{
    double v;
    v=exp(-E/T);
    if (v<1.0)
    {
        p=v;
    }
    else p=1.0;
    return;
}

void magnetizacion (double mag[10000], int N, int s[100][100], int b)
{
    int i, j;
    double k;
    k=0.0;
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
        k=k+s[i][j];
        }
    }
    mag[b]=abs(k)/(N*N);
    return;
}

void promedio (double& prom, double var[10000], int b)
{
    int i;
    prom=0.0;
    for (i=0; i<b; i++)
    {
        prom=prom+var[i];
    }
    prom=prom/((b-1)*1.0);
    return;
}

void error (int b, double& error, double varia[10000], double prom)
{
    int i;
    double varianza, cua;
    cua=0.0;
    for (i=0; i<b+1; i++)
    {      
        cua=cua+(varia[i]-prom)*(varia[i]-prom);
    }
    varianza=sqrt(cua/(1.0*(b+1)));
    error=varianza/sqrt(b*1.0+1.0);
    return;
}

double energiaparaelpromedio (double Epalpromedio, int n, int m, int N, int s[100][100])
{
    Epalpromedio=0.0;
    if (n+1==N)
    {
        if (m==0)
        {
            Epalpromedio=-0.5*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
        }
        else if (m+1==N)
        {
            Epalpromedio=-0.5*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
        }
        else
        { 
            Epalpromedio=-0.5*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
        }
    }
    else if (n==0)
    {
        if (m==0)
        { 
            Epalpromedio=-0.5*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
        }
        else if (m+1==N)
        { 
            Epalpromedio=-0.5*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);
        }
        else
        {
            Epalpromedio=-0.5*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);
        } 
    }
    else 
    {
        if (m==0)
        {
            Epalpromedio=-0.5*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
        }
        else if (m+1==N)
        {
            Epalpromedio=-0.5*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
        } 
        else
        { 
            Epalpromedio=-0.5*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
        }
    }
    return Epalpromedio;

}
