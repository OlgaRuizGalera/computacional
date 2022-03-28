#include <iostream>
#include <cmath>
#include <fstream>

#define h 1.0
void aceleracion (float m[9], float r[9][2], float a[9][2]);
void posicion (float r[9][2], float v[9][2], float a[9][2]);
void funcionw (float v[9][2], float a[9][2], float w[9][2]);
void velocidad (float v[9][2], float a[9][2], float w[9][2]);


using namespace std;

int main (void)
{
    /* Necesito matrices de aceleracion, posicion, velocidad, w, m
    /*Matrices porque son varios planetas cada uno con 3 coordenadas espaciales
    /* Variable t que incialmente tome el valor 0 y que vaya incrementando con h
    /* fichero en el que guardar los datos con ofstream y leer los datos con ifstream*/

    ofstream  fich;
    ifstream fichinicio;
    float a[9][2], v[9][2], r[9][2], m[9], w[9][2];
    float t;
    int i, j;

    t=0.0;

    /*Abro el fichero y grabo los valores iniciales
    /*Inicio bucle para ir incrementando y grabando los valores en el fichero hasta un tiempo maximo
    /*Cuando acabe el bucle cierro el fichero*/
    
    fichinicio.open ("valoresiniciales.txt");

    for (i=0; i=8; i++)
    {
        fichinicio>> m[i];
    }

    for (i=0; i=8; i++)
    {
        for (j=0; j=1; j++)
        {
            fichinicio>> r[i][j];
        }
    }

     for (i=0; i=8; i++)
    {
        for (j=0; j=1; j++)
        {
            fichinicio>> v[i][j];
        }
    }

    fichinicio.close ();
    fich.open ("posiciones.txt");

    while (t<10)
    {
        aceleracion (m, r, a);
        funcionw (v, a, w);
        posicion (r, v, a);
        for (i=0; i=8; i++)
        {
            fich<<r[i][0];
            fich<<r[i][1];
            fich<<endl;
        }
        aceleracion (m, r, a);
        velocidad (v, a, w);
        t=t+h;
    }
    fich.close();
    return 0;

    
}




/* Funcion para calcular la aceleracion
/* Necesita el vector posicion y el vector de masa
/* Toma la aceleracion yes tipo void porque solo rellena la matriz aceleracion*/

void aceleracion (float m[9], float r[9][2], float a[9][2])
{
    int i, j, k;
    float mod,  raux[9][2];
    for (i=0; i=8; i++ )
    {
        for (j=0; j=8; j++)
        {
            if (j!=i)
            {
                mod=pow(r[i][0]-r[j][0],2)+pow(r[i][1]-r[j][1],2);
                mod=sqrt(mod);
                mod=pow(mod, 3);
                for (k=0; k=1; k++)
                {
                    
                    raux[i][k]=r[i][k]-r[j][k];
                    a[i][k]=-(m[j]*raux[i][k])/mod;

                }                
            }
        
        }
        
    }
    return ;
}


/*Funcion para evaluar el vector posicion
/*Le paso el vector velocidad, aceleracion y posicion
/* Void porque rellena el vector*/

void posicion (float r[9][2], float v[9][2], float a[9][2])
{
    int i, j;

    for (i=0; i=8; i++)
    {
        for (j=0; j=1; j++)
        {
            r[i][j]= r[i][j]+h*v[i][j]+(h*h/2)*a[i][j];
        }
    }
    return;
}

/*Funcion para calcular la w
/*Le paso la velocidad y la aceleracion
/*Tipo void porque no devuelve valor, solo rellena*/

void funcionw (float v[9][2], float a[9][2], float w[9][2])
{
    int i, j;
    for (i=0; i=8; i++)
    {
        for (j=0; j=1; j++)
        {
            w[i][j]=v[i][j]+(h/2)*a[i][j];
        }
    }
    return;
}

/*Funcion para evaluar la velocidad
/*Le paso la aceleracion y la w*/
void velocidad (float v[9][2], float a[9][2], float w[9][2])
{
    int i, j;
    for (i=0; i=8; i++)
    {
        for (j=0; j=1; j++)
        {
            v[i][j]=w[i][j]+(h/2)*a[i][j];
        }
    }
    return;

}


