#include <iostream>
#include <cmath>
#include <fstream>

/* h es el paso que quiero usar, y le doy un valor incial que yo quiera
/* puedo declarar h aqui fuera o dentro del int main
/*PROBAR LOS DOS*/

#define h 0.5
void aceleracion (float m[9], float r[9][2], float a[9][2]);
void posicion (float r[9][2], float v[9][2], float a[9][2]);


using namespace std;

int main (void)
{
    /* Necesito matrices de aceleracion, posicion, velocidad, w, m
    /*Matrices porque son varios planetas cada uno con 3 coordenadas espaciales
    /* Variable t que incialmente tome el valor 0 y que vvaya incrementando con h
    /* fichero en el que guardar los datos*/

    ofstream fichero;
    float a[9][2], v[9][2], r[9][2], m[9], w[9][2];
    float t;
    int i, j;


    /* Funcion para calcular la aceleracion_1 en t, abro fichero y grabo valor inicial de posicion
    /* Bucle: 
    /* Calculo aceleración_1 en t 
    /* Evaluo r (t+h) y w(t)
    /* Paso r(t+h) al fichero
    /* Evaluo a(t+h) y v(t+h)
    /* Incremento t*/


    
    
}




/* Funcion para calcular la aceleracion
/* Necesita el vector posicion y el vector de masa
/* Toma la aceleracion yes tipo void porque solo rellena la matriz aceleracion*/

void aceleracion (float m[], float r[9][2], float a[9][2])
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

void funcionw (float v[9][2], float a[9][2])
