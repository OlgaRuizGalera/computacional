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
    int i, j, n, m, o, N;
    double p, E, f, T, s[7][7];
    ifstream inicial;
    ofstream ising;

    /*Inicializar cosillas, ¿T es real o entero?*/
    srand(time(NULL));
    N=7; 
    T=4.5;
    o=0;
    inicial.open ("valoresiniciales.dat");


    for (i=0; i<7; i++)
    {
        for (j=0; j<7; j++)
        {
            inicial>>s[i][j];
        }
    }

    inicial.close ();

    ising.open ("ising.dat");

    while (o<N*N)
    {
        n=rand()%N;
        m=rand()%N;

        /*Aqui un buclecillo tontorron para escribir s en un fichero*/

        /*Calcular energia con simetria teniendo en cuenta que m supere N y que n supere N*/
        /*Son if*/
        E=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);


        minimo(T, E, p);
        f=rand()%1;
        if (f<p)
        {
            s[n][m]=-s[n][m];
        }
        ising<<s[n][m];
        o=o+1;

    }
    return 0;

}


void minimo (double T, double E, double& p)
{
    double v;
    v=exp(-E/T);
    if (v<1)
    {
        p=v;
    }
    else p=1;
    return;
}