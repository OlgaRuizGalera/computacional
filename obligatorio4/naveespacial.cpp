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
#define h 1.0

void coordenadar (double& r, double pr);
void coordenadaphi (double& phi, double pphi, double r);
void momentor (double& pr, double pphi, double r, double phi, double t, double tri, double mu);
void momentophi (double& pphi, double r, double phi, double t, double tri, double mu);

using namespace std;

int main (void)
{
    double k1[4], k2[4], k3[4], k4[4];
    double phi3, r3, pphi3,  pr3;
    double phi1, r1, pphi1, pr1;
    double t, tri, mu;
    int o, i;
    ofstream fichero;

    /*Las variables que estan junto al tiempo son las que sirven para reescalar*/

    tri=G*MT/(dtl*dtl*dtl);
    mu=ML/MT;
    

    /*Cohete*/
    phi3=0.0;
    r3=6.37816e6/dtl;
    pphi3=r3*11.19e3*sin(0.26405)/dtl;
    pr3=11.19e3*cos(0.26405)/dtl;

    t=0.0;

    fichero.open ("cohete.dat");

    o=0;
    while (t<=300000)
    {
        coordenadar(r1, pr3);
        coordenadaphi(phi1, pphi3, r3);
        momentophi (pphi1, r3, phi3, t, tri, mu);
        momentor (pr1, pphi3, r3, phi3, t, tri, mu);
       
       /*Cohete*/
        k1[0]=h*r1;
        k1[1]=h*phi1;
        k1[2]=h*pphi1;
        k1[3]=h*pr1;
        
        coordenadar(r1, pr3+k1[3]/2.0);
        coordenadaphi(phi1, pphi3+k1[2]/2.0, r3+k1[0]/2.0);
        momentophi (pphi1, r3+k1[0]/2.0, phi3+k1[1]/2.0, t+h/2.0, tri, mu);
        momentor (pr1, pphi3+k1[2]/2.0, r3+k1[0]/2.0, phi3+k1[1]/2.0, t+h/2.0, tri, mu);

        k2[0]=h*r1;
        k2[1]=h*phi1;
        k2[2]=h*pphi1;
        k2[3]=h*pr1;

        coordenadar(r1, pr3+k2[3]/2.0);
        coordenadaphi(phi1, pphi3+k2[2]/2.0, r3+k2[0]/2.0);
        momentophi (pphi1, r3+k2[0]/2.0, phi3+k2[1]/2.0, t+h/2.0, tri, mu);
        momentor (pr1, pphi3+k2[2]/2.0, r3+k2[0]/2.0, phi3+k2[1]/2.0, t+h/2.0, tri, mu);

        k3[0]=h*r1;
        k3[1]=h*phi1;
        k3[2]=h*pphi1;
        k3[3]=h*pr1;

        coordenadar(r1, pr3+k3[3]);
        coordenadaphi(phi1, pphi3+k3[2], r3+k3[0]);
        momentophi (pphi1, r3+k3[0], phi3+k3[1], t+h, tri, mu);
        momentor (pr1, pphi3+k3[2], r3+k3[0], phi3+k3[1], t+h, tri, mu);

        k4[0]=h*r1;
        k4[1]=h*phi1;
        k4[2]=h*pphi1;
        k4[3]=h*pr1;

        r3=r3+(1.0/6.0)*(k1[0]+2.0*k2[0]+2.0*k3[0]+k4[0]);
        phi3=phi3+(1.0/6.0)*(k1[1]+2.0*k2[1]+2.0*k3[1]+k4[1]);
        pphi3=pphi3+(1.0/6.0)*(k1[2]+2.0*k2[2]+2.0*k3[2]+k4[2]);
        pr3=pr3+(1.0/6.0)*(k1[3]+2.0*k2[3]+2.0*k3[3]+k4[3]);
        
        o=o+1;
        t=t+h;

        if(o==1000)
        {
            fichero<<0.0<<","<<0.0<<endl;
            fichero<<cos(w*t)<<","<<sin(w*t)<<endl;
            fichero<<r3*cos(phi3)<<","<<r3*sin(phi3)<<endl;
            fichero<<endl;
            o=0;
        }

        
    }
    fichero.close();
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
    rprima=sqrt(1.0+r*r-2.0*r*cos(phi-w*t));
    pr=(pphi*pphi/(r*r*r)-tri*(1.0/(r*r)+mu/(rprima*rprima*rprima)*(r-cos(phi-w*t))));
    return;
}

void momentophi (double& pphi, double r, double phi, double t, double tri, double mu)
{
    double rprima2;
    rprima2=sqrt(1.0+r*r-2.0*r*cos(phi-w*t));
    pphi=(-tri*mu*r/(rprima2*rprima2*rprima2))*sin(phi-w*t);
    return;
}