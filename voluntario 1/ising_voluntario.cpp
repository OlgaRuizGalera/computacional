#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

void minimo (double T, double E, double& p);
void magnetizacion (double mag[10000], int N, int s[150][150], int b);
void promedio (double& prom, double var[10000], int b);
void error (int b, double& error, double varia[10000], double prom);
double energiaparaelpromedio (int n, int m, int N, int s[150][150]);
double funcioncorrelacion (int N, int i, int s[150][150]);
void promediomatriz (double prom[150], double var[150][10000], int b, int i);
void errormatriz (int b, double error[150], double varia[150][10000], double prom[150], int i);

using namespace std;

int main (void) 
{
    int i, j, n, m, o, k, l, N, y, b, h, s[150][150];
    double p, f, T, E, c;
    static double  e[10000], cor[150][10000], mag[10000], r[10000];
    double promE, promr, promm, errorE, errorr, errorm, Epalpromedioaux, Epalpromedio1, promf[150];
    double ener, cal, coraux, errorenergia, errorcalor, errorcor[150];
    ofstream valores;

    srand(time(NULL));
    N=16; 
    T=3.5;
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

    valores.open ("N128T35.dat");

    /*Inicio los pasos montecarlo*/
    for (o=0; o<1000000; o++)
    {
        /*ESte for constituye un paso montecarlo*/
        for (y=0; y<N*N; y++)
        {

            n=rand()%N;
            m=rand()%N;
 
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

 /*Aumento en 1 h que es contador para cuando llegue a 100 pM
 Compruebo si ha llegado o no a 100 para contribuir al calculo de promedios*/
        h=h+1;
        if(h==100)
        { 

            magnetizacion (mag, N, s, b);
            /*No me hace falta calcular la energia porque la he calculado en el bucle del PMc*/
            Epalpromedio1=0.0;
            for (n=0; n<N; n++)
            {
                for (m=0; m<N; m++)
                {
                    Epalpromedioaux=energiaparaelpromedio (n, m, N, s);
                    Epalpromedio1=Epalpromedio1+Epalpromedioaux;
                }
            }
            e[b]=Epalpromedio1*1.0;
            r[b]=Epalpromedio1*Epalpromedio1*1.0;
            for (i=0; i<N; i++)
            {
                coraux=funcioncorrelacion(N,i,s);
                cor[i][b]=coraux;
            }
            /*La b me sirve para poder calcular luego el valor promedio*/
            b=b+1;
            h=0;
        }
 
    }
 
    promedio (promE, e, b);
    promedio (promr, r, b);
    promedio (promm, mag, b);
    for (i=0; i<N; i++)
    {
        promediomatriz(promf, cor, b, i);
    }
    /*COn la funcion error lo que hago es calcular la varianza partido de raiz de N*/
    error (b, errorE, e, promE);
    error (b, errorr, r, promr);
    error (b, errorm, mag, promm);
    for (i=0; i<N; i++)
    {
        errormatriz (b, errorcor, cor, promf, i);
    }

    errorenergia=errorE/(2*N*N);
    errorcalor=sqrt(pow(errorr/(T*N*N),2)+pow(2*errorE*promE/(T*N*N),2));

    ener=promE/(2.0*N*N);
    cal=(promr-promE*promE)/(T*N*N*1.0);

    valores<<"Magnetización: "<<promm<<endl;
    valores<<"Error magnetizacion: "<<errorm<<endl;
    valores<<"Energia: "<<ener<<endl;
    valores<<"Error energia: "<<errorenergia<<endl;
    valores<<"Calor especifico: "<<cal<<endl;
    valores<<"Error calor especifico: "<<errorcalor<<endl;

    for (j=0; j<N; j++)
    {
        valores<<j<<"   "<<promf[j]/((N)*(N)*1.0)<<endl;
    }

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

void magnetizacion (double mag[10000], int N, int s[150][150], int b)
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
    prom=prom/((b)*1.0);
    return;
}

void error (int b, double& error, double varia[10000], double prom)
{
    int i;
    double varianza, cua;
    cua=0.0;
    for (i=0; i<b; i++)
    {      
        cua=cua+(varia[i]-prom)*(varia[i]-prom);
    }
    varianza=sqrt(cua/(1.0*(b)));
    error=varianza/sqrt(b*1.0);
    return;
}

double energiaparaelpromedio (int n, int m, int N, int s[150][150])
{
    double Epalpromedio1;
    Epalpromedio1=0.0;
    if (n+1==N)
    {
        if (m==0)
        {
            Epalpromedio1=-0.5*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
        }
        else if (m+1==N)
        {
            Epalpromedio1=-0.5*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
        }
        else
        { 
            Epalpromedio1=-0.5*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
        }
    }
    else if (n==0)
    {
        if (m==0)
        { 
            Epalpromedio1=-0.5*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
        }
        else if (m+1==N)
        { 
            Epalpromedio1=-0.5*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);
        }
        else
        {
            Epalpromedio1=-0.5*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);
        } 
    }
    else 
    {
        if (m==0)
        {
            Epalpromedio1=-0.5*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
        }
        else if (m+1==N)
        {
            Epalpromedio1=-0.5*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
        } 
        else
        { 
            Epalpromedio1=-0.5*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
        }
    }
    return Epalpromedio1;

}

double funcioncorrelacion (int N, int i, int s[150][150])
{
    int n, m;
    double correlacion;
    correlacion=0.0;
    for (n=0; n<N; n++)
    {
        for (m=0; m<N; m++)
        {
            correlacion=correlacion+s[n][m]*s[(n+i)%N][m];
        }
    }
    return correlacion;
}

void promediomatriz (double prom[150], double var[150][10000], int b, int i)
{
    int j;
    prom[i]=0.0;
    for (j=0; j<b; j++)
    {
        prom[i]=prom[i]+var[i][j];
    }
    prom[i]=prom[i]/((b-1)*1.0);
    return;
}

void errormatriz (int b, double error[150], double varia[150][10000], double prom[10000], int i)
{
    int j;
    double varianza, cua;
    cua=0.0;
    for (j=0; j<b; j++)
    {      
        cua=cua+(varia[i][j]-prom[i])*(varia[i][j]-prom[i]);
    }
    varianza=sqrt(cua/(1.0*(b)));
    error[i]=varianza/sqrt(b*1.0);
    return;
}

