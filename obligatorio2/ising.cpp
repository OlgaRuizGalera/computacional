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
    int i, j, n, m, o, k, l, N, y, s[100][100];
    double p, f, T, E;
    ofstream ising;

    srand(time(NULL));
    N=100; 
    T=4.5;

    /*Configuracion desordenada
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            s[i][j]=rand()%2;
            if(s[i][j]==0)
            {
                s[i][j]=-1;
            }
        }
    }*/

    /* Configuracion ordenada*/
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            s[i][j]=1;
        }
    }

    ising.open ("ising_ordenado.dat");

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

    for (o=0; o<200; o++)
    {
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