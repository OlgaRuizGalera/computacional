#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#define G 6.67e-11
#define MT 5.9736e24
#define ML 0.07349e24
#define dtl 3.844e8
#define w 2.6617e-6
#define RT 6.378160e6
#define RL 1.7374e6
#define h 0.1

void coordenadar (double& r, double pr);
void coordenadaphi (double& phi, double pphi, double r);
void momentor (double& pr, double pphi, double r, double phi, double t, double tri, double mu);
void momentophi (double& pphi, double r, double phi, double t, double tri, double mu);

using namespace std;

int main (void)
{
    double k1[4], k2[4], k3[4], k4[4];
    double phi, r, pphi,  pr;
    double t, tri, mu;
    int o, i;
    
    /*Las variables que estan junto al tiempo son las que sirven para reescalar*/

    tri=G*MT/(dtl*dtl*dtl);
    mu=ML/MT;
    
    
    /*Doy valores iniciales*/
    phi=1.0;
    pphi=1.0;
    r=1.0;
    pr=1.0;
    t=1.0;

    o=0;
    while (o<=10000)
    {
        k1[0]=h*r;
        k1[1]=h*phi;
        k1[2]=h*pphi;
        k1[3]=h*pr;
        
        coordenadar(r, pr+k1[3]/2);
        coordenadaphi(phi, r+k1[0]/2, pphi+k1[2]/2);
        momentophi (pphi, r+k1[0]/2, phi+k1[1]/2, t+h/2, tri, mu);
        momentor (pr, pphi+k1[2]/2, r+k1[0]/2, phi+k1[1]/2, t+h/2, tri, mu);

        k2[0]=h*r;
        k2[1]=h*phi;
        k2[2]=h*pphi;
        k2[3]=h*pr;

        coordenadar(r, pr+k2[3]/2);
        coordenadaphi(phi, r+k2[0]/2, pphi+k2[2]/2);
        momentophi (pphi, r+k2[0]/2, phi+k2[1]/2, t+h/2, tri, mu);
        momentor (pr, pphi+k2[2]/2, r+k2[0]/2, phi+k2[1]/2, t+h/2, tri, mu);

        k3[0]=h*r;
        k3[1]=h*phi;
        k3[2]=h*pphi;
        k3[3]=h*pr;

        coordenadar(r, pr+k2[3]);
        coordenadaphi(phi, r+k2[0], pphi+k2[2]);
        momentophi (pphi, r+k2[0], phi+k2[1], t+h, tri, mu);
        momentor (pr, pphi+k2[2], r+k2[0], phi+k2[1], t+h, tri, mu);

        k4[0]=h*r;
        k4[1]=h*phi;
        k4[2]=h*pphi;
        k4[3]=h*pr;
        
    }
    return 0;

}

void coordenadar (double& r, double pr)
{
    r=pr;
    return;
}

void coordenadaphi (double& phi, double pphi, double r)
{
    phi=pphi/(r*r);
    return;
}

void momentor (double& pr, double pphi, double r, double phi, double t, double tri, double mu)
{
    double rprima;
    rprima=sqrt(1+r*r-2*r*cos(phi-w*t));
    pr=(pphi*pphi/(r*r*r)-tri*(1/(r*r)+mu/(rprima*rprima*rprima)*(r-cos(phi-w*t))));
    return;
}

void momentophi (double& pphi, double r, double phi, double t, double tri, double mu)
{
    double rprima2;
    rprima2=sqrt(1+r*r-2*r*cos(phi-w*t));
    pphi=(-tri*mu*r/(rprima2*rprima2*rprima2))*sin(phi-w*t);
    return;
}