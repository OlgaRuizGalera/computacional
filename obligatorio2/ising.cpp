#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

void minimo (double T, double E, double& p);

using namespace std;

int main (void) 
{
    int i, j, n, m, o, k, l, N, E, s[10][10];
    double p, f, T;
    ofstream ising;

    /*Inicializar cosillas, ¿T es real o entero?*/
    srand(time(NULL));
    N=10; 
    T=4.5;
    o=0;


    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            s[i][j]=1;
        }
    }

    ising.open ("ising.dat");

    while (o<50*N*N)
    {
        for (k=0; k<N; k++)
        {
            for (l=0; l<N-2; l++)
            {
                ising<<s[k][l]<<",";
            }
            ising<<s[k][N-1];
            ising<<endl;
        }
        ising<<endl;

        n=rand()%N;
        m=rand()%N;

        /*Calcular energia con simetria teniendo en cuenta que m supere N y que n supere N*/
        /*Son if*/
        if (n+1>N)
        {
            if (m==0)
            {
                E=2*s[n][m]*(s[1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else if (m+1>N)
            {
                E=2*s[n][m]*(s[1][m]+s[n-1][m]+s[n][1]+s[n][m-1]);
            }
            else
            {
                E=2*s[n][m]*(s[1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
            }
        }
        else if (n==0)
        {
           if (m==0)
            {
                E=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][1]+s[n][N-1]);
            }
            else if (m+1>N)
            {
                E=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][1]+s[n][m-1]);
            }
            else
            {
                E=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);
            } 
        }
        else 
        {
            if (m==0)
            {
                E=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else if (m+1>N)
            {
                E=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][1]+s[n][m-1]);
            }
            else
            {
                E=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
            }
        }


        minimo(T, E, p);
        f=rand()%1;
        if (f<p)
        {
            s[n][m]=-s[n][m];
        }
        o=o+1;

    }
    ising.close ();
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