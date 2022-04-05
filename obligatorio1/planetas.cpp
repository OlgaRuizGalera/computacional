#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>

#define h 0.1
#define G 6.67e-11
#define M 1.99e30
#define c 1.49e11
void aceleracion (float m[9], float r[9][2], float a[9][2]);
void posicion (float r[9][2], float v[9][2], float a[9][2]);
void funcionw (float v[9][2], float a[9][2], float w[9][2]);
void velocidad (float v[9][2], float a[9][2], float w[9][2]);
void energia (float m[9], float v[9][2], float r[9][2], float& etot);
void normalizacion (float r[9][2], float v[9][2], float m[9]);

using namespace std;

int main (void)
{
    ofstream  fich, fichenergia, periodo;
    ifstream fichinicio;
    float a[9][2], v[9][2], r[9][2], m[9], w[9][2];
    float t, etot;
    bool per[9], cond1[9], cond2[9];
    int i, j, k, l, z[9];

    t=0.0;

    fichinicio.open ("valoresiniciales.txt");

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
       fichinicio>>v[k][1];
    }

    for (i=0; i<9; i++)
    {
        per[i]=false;
        cond1[i]=false;
        cond2[i]=false;
        z[i]=0;
    }

    fichinicio.close ();
    normalizacion (r, v, m);
    fich.open ("planets_data.dat");
    fichenergia.open ("energia.txt");
    periodo.open ("periodos.dat");

    /* Primeros cálculos*/

    aceleracion (m, r, a);
    funcionw (v, a, w);
    energia (m, v, r, etot);
    fichenergia<<t<<" "<<etot<<endl;
    for (l=0; l<9; l++)
        {
            fich<<r[l][0] << "," << r[l][1]<< endl;
        }
    fich<<endl;

    /*Empiezo el bucle*/

    while (t<10000)
    {
        posicion (r, v, a);
        for (i=0; i<9; i++)
        {
            if (per[i]==false)
            {
                if (r[i][1]>0 && cond2[i]==false)
                {
                    z[i]=z[i]+1;
                    cond1[i]=true;
                }
                else if (r[i][1]<0 && cond1[i]==true)
                {
                    z[i]=z[i]+1;
                    cond2[i]=true;
                }
                else if (r[i][1]>0 && cond1[i]==true && cond2[i]==true)
                {
                    per[i]=true;
                    periodo<<z[i]*h*sqrt(pow(c,3)/(G*M))/(60*60*24)<<endl;
                }
            }
        }
        aceleracion (m, r, a);
        velocidad (v, a, w);
        funcionw (v, a, w);
        energia (m, v, r, etot);
        fichenergia<<t<<" "<<etot<<endl;
        for (l=0; l<9; l++)
        {
            fich<<r[l][0] << "," << r[l][1]<< endl;
        }
        fich<<endl;
        t=t+h;
    }
    fich.close();
    fichenergia.close ();
    periodo.close();
    return 0;
}

void aceleracion (float m[9], float r[9][2], float a[9][2])
{
    int i, j, k, z, l;
    float mod;
    for (l=0;l<9; l++)
    {
        for (z=0;z<2;z++)
        {
            a[l][z]=0;
        }
    }
    for (i=0; i<9; i++ )
    {
        for (j=0; j<9; j++)
        {
            if (j!=i)
            {
               mod=sqrt(pow((r[i][0]-r[j][0]),2)+pow((r[i][1]-r[j][1]),2));
                for (k=0; k<2; k++)
                {
                    a[i][k]=a[i][k]-m[j]*(r[i][k]-r[j][k])/pow(abs(mod),3);

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

void energia (float m[9], float v[9][2], float r[9][2], float& etot)
{
    int i;
    float modv, modr;
    float e;
    etot=0.0;
    for (i=1; i<9; i++)
    {
       modv=pow(v[i][0],2)+pow(v[i][1],2); 
       modr=sqrt(pow((r[i][0]-r[0][0]),2)+pow((r[i][1]-r[0][1]),2));      
       e=0.5*m[i]*modv-m[i]*m[0]/modr;
       etot=etot+e;      
    }
    return;
}

void normalizacion (float r[9][2], float v[9][2], float m[9])
{
    int i, j;
    for (i=0; i<9; i++)
    {
        m[i]=m[i]/M;
        for (j=0; j<2; j++)
        {
            v[i][j]=v[i][j]*(sqrt(c/(G*M)));
            r[i][j]=r[i][j]/c;
        }
    }
    return;
}


