#include <iostream>
#include <cmath>
#include <fstream>

#define h 1.0
void aceleracion (float m[9], float r[9][2], float a[9][2]);
void posicion (float r[9][2], float v[9][2], float a[9][2]);
void funcionw (float v[9][2], float a[9][2], float w[9][2]);
void velocidad (float v[9][2], float a[9][2], float w[9][2]);
void energia (float m[9], float v[9][2], float e[9], float r[9][2]);


using namespace std;

int main (void)
{
    ofstream  fich, fichenergia;
    ifstream fichinicio;
    float a[9][2], v[9][2], r[9][2], m[9], w[9][2], e[9];
    float t;
    int i, j, k, l;

    t=0.0;

    fichinicio.open ("valoresiniciales");

    for (i=0; i<9; i++)
    {
        fichinicio>> m[i];
    }

    for (j=0; j<9; j++)
    {
        fichinicio>> r[j][0];
        fichinicio>> r[j][1];
    }

     for (k=0; k<9; k++)
    {
       fichinicio>> v[k][0];
       fichinicio>> v[k][1];
    }

    fichinicio.close ();
    fich.open ("posiciones.txt");
    fichenergia.open ("energia.txt");

    while (t<10)
    {
        aceleracion (m, r, a);
        funcionw (v, a, w);
        posicion (r, v, a);
        energia (m, v, e, r);
        for (l=0; l<9; l++)
        {
            fich<<r[l][0];
            fich<<r[l][1];
            fich<<endl;
            fichenergia<<e[i];
        }
        aceleracion (m, r, a);
        velocidad (v, a, w);
        t=t+h;
    }
    fich.close();
    fichenergia.close ();
    return 0;

    
}


void aceleracion (float m[9], float r[9][2], float a[9][2])
{
    int i, j, k;
    float mod,  raux[9][2];
    for (i=0; i<9; i++ )
    {
        for (j=0; j<9; j++)
        {
            if (j!=i)
            {
                mod=pow(r[i][0]-r[j][0],2)+pow(r[i][1]-r[j][1],2);
                mod=sqrt(mod);
                mod=pow(mod, 3);
                for (k=0; k<2; k++)
                {
                    
                    raux[i][k]=r[i][k]-r[j][k];
                    a[i][k]=-(m[j]*raux[i][k])/mod;

                }                
            }
        
        }
        
    }
    return ;
}


void posicion (float r[9][2], float v[9][2], float a[9][2])
{
    int i, j;

    for (i=0; i<9; i++)
    {
        for (j=0; j<2; j++)
        {
            r[i][j]= r[i][j]+h*v[i][j]+(h*h/2)*a[i][j];
        }
    }
    return;
}


void funcionw (float v[9][2], float a[9][2], float w[9][2])
{
    int i, j;
    for (i=0; i<9; i++)
    {
        for (j=0; j<2; j++)
        {
            w[i][j]=v[i][j]+(h/2)*a[i][j];
        }
    }
    return;
}


void velocidad (float v[9][2], float a[9][2], float w[9][2])
{
    int i, j;
    for (i=0; i<9; i++)
    {
        for (j=0; j<2; j++)
        {
            v[i][j]=w[i][j]+(h/2)*a[i][j];
        }
    }
    return;

}

void energia (float m[9], float v[9][2], float e[9], float r[9][2])
{
    int i, j, modv, modr;
    for (i=1; i<9; i++)
    {
       modv=pow(v[i][0],2)+pow(v[i][1],2); 
       modr=pow(r[i][0],2)+pow(r[i][1],2);
       e[i]=0.5*m[i]*modv-m[i]/modr;      
    }
return;
}


