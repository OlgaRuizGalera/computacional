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
    double k11[4], k21[4], k31[4], k41[4];
    double k12[4], k22[4], k32[4], k42[4];
    double k13[4], k23[4], k33[4], k43[4];
    double phi1, r1, pphi1,  pr1;
    double phi2, r2, pphi2,  pr2;
    double phi3, r3, pphi3,  pr3;
    double t, tri, mu;
    int o, i;
    ofstream fichero;
    
    /*Las variables que estan junto al tiempo son las que sirven para reescalar*/

    tri=G*MT/(dtl*dtl*dtl);
    mu=ML/MT;
    
    
    /*Doy valores iniciales*/
    /*Tierra*/
    phi1=0.0;
    pphi1=0.0;
    r1=0.0;
    pr1=0.0;

    /*Luna*/
    phi2=1.0;
    pphi2=1.0;
    r2=1.0;
    pr2=1.0;

    /*Cohete*/
    phi3=1.0;
    pphi3=1.0;
    r3=1.0;
    pr3=1.0;

    t=1.0;

    fichero.open ("cohete.dat");

    o=0;
    while (i<=300000)
    {
        /*Tierra*/
        k11[0]=h*r1;
        k11[1]=h*phi1;
        k11[2]=h*pphi1;
        k11[3]=h*pr1;

        /*Luna*/
        k12[0]=h*r2;
        k12[1]=h*phi2;
        k12[2]=h*pphi2;
        k12[3]=h*pr2;

        /*Cohete*/
        k13[0]=h*r3;
        k13[1]=h*phi3;
        k13[2]=h*pphi3;
        k13[3]=h*pr3;
        
        coordenadar(r1, pr1+k11[3]/2);
        coordenadaphi(phi1, r1+k11[0]/2, pphi1+k11[2]/2);
        momentophi (pphi1, r1+k11[0]/2, phi1+k11[1]/2, t+h/2, tri, mu);
        momentor (pr1, pphi1+k11[2]/2, r1+k11[0]/2, phi1+k11[1]/2, t+h/2, tri, mu);

        coordenadar(r2, pr2+k12[3]/2);
        coordenadaphi(phi2, r2+k12[0]/2, pphi2+k12[2]/2);
        momentophi (pphi2, r2+k12[0]/2, phi2+k12[1]/2, t+h/2, tri, mu);
        momentor (pr2, pphi2+k12[2]/2, r2+k12[0]/2, phi2+k12[1]/2, t+h/2, tri, mu);

        coordenadar(r3, pr3+k13[3]/2);
        coordenadaphi(phi3, r3+k13[0]/2, pphi3+k13[2]/2);
        momentophi (pphi3, r3+k13[0]/2, phi3+k13[1]/2, t+h/2, tri, mu);
        momentor (pr3, pphi3+k13[2]/2, r3+k13[0]/2, phi3+k13[1]/2, t+h/2, tri, mu);

        k21[0]=h*r1;
        k21[1]=h*phi1;
        k21[2]=h*pphi1;
        k21[3]=h*pr1;

        k22[0]=h*r2;
        k22[1]=h*phi2;
        k22[2]=h*pphi2;
        k22[3]=h*pr2;

        k23[0]=h*r3;
        k23[1]=h*phi3;
        k23[2]=h*pphi3;
        k23[3]=h*pr3;

        coordenadar(r1, pr1+k21[3]/2);
        coordenadaphi(phi1, r1+k21[0]/2, pphi1+k21[2]/2);
        momentophi (pphi1, r1+k21[0]/2, phi1+k21[1]/2, t+h/2, tri, mu);
        momentor (pr1, pphi1+k21[2]/2, r1+k21[0]/2, phi1+k21[1]/2, t+h/2, tri, mu);

        coordenadar(r2, pr2+k22[3]/2);
        coordenadaphi(phi2, r2+k22[0]/2, pphi2+k22[2]/2);
        momentophi (pphi2, r2+k22[0]/2, phi2+k22[1]/2, t+h/2, tri, mu);
        momentor (pr2, pphi2+k22[2]/2, r2+k22[0]/2, phi2+k22[1]/2, t+h/2, tri, mu);

        coordenadar(r3, pr3+k23[3]/2);
        coordenadaphi(phi3, r3+k23[0]/2, pphi3+k23[2]/2);
        momentophi (pphi3, r3+k23[0]/2, phi3+k23[1]/2, t+h/2, tri, mu);
        momentor (pr3, pphi3+k23[2]/2, r3+k23[0]/2, phi3+k23[1]/2, t+h/2, tri, mu);

        k31[0]=h*r1;
        k31[1]=h*phi1;
        k31[2]=h*pphi1;
        k31[3]=h*pr1;

        k32[0]=h*r2;
        k32[1]=h*phi2;
        k32[2]=h*pphi2;
        k32[3]=h*pr2;

        k33[0]=h*r3;
        k33[1]=h*phi3;
        k33[2]=h*pphi3;
        k33[3]=h*pr3;

        coordenadar(r1, pr1+k31[3]);
        coordenadaphi(phi1, r1+k31[0], pphi1+k31[2]);
        momentophi (pphi1, r1+k31[0], phi1+k31[1], t+h, tri, mu);
        momentor (pr1, pphi1+k31[2], r1+k31[0], phi1+k31[1], t+h, tri, mu);

        coordenadar(r2, pr2+k32[3]);
        coordenadaphi(phi2, r2+k32[0], pphi2+k32[2]);
        momentophi (pphi2, r2+k32[0], phi2+k32[1], t+h, tri, mu);
        momentor (pr2, pphi2+k32[2], r2+k32[0], phi2+k32[1], t+h, tri, mu);

        coordenadar(r3, pr3+k33[3]);
        coordenadaphi(phi3, r3+k33[0], pphi3+k33[2]);
        momentophi (pphi3, r3+k33[0], phi3+k33[1], t+h, tri, mu);
        momentor (pr3, pphi3+k33[2], r3+k33[0], phi3+k33[1], t+h, tri, mu);

        k41[0]=h*r1;
        k41[1]=h*phi1;
        k41[2]=h*pphi1;
        k41[3]=h*pr1;

        k42[0]=h*r2;
        k42[1]=h*phi2;
        k42[2]=h*pphi2;
        k42[3]=h*pr2;

        k43[0]=h*r3;
        k43[1]=h*phi3;
        k43[2]=h*pphi3;
        k43[3]=h*pr3;

        r1=r1+(1.0/6.0)*(k11[0]+2.0*k21[0]+2*k31[0]+k41[0]);
        phi1=phi1+(1.0/6.0)*(k11[1]+2.0*k21[1]+2*k31[1]+k41[1]);
        pphi1=pphi1+(1.0/6.0)*(k11[2]+2.0*k21[2]+2*k31[2]+k41[2]);
        pr1=pr1+(1.0/6.0)*(k11[3]+2.0*k21[3]+2*k31[3]+k41[3]);

        r2=r2+(1.0/6.0)*(k12[0]+2.0*k22[0]+2*k32[0]+k42[0]);
        phi2=phi2+(1.0/6.0)*(k12[1]+2.0*k22[1]+2*k32[1]+k42[1]);
        pphi2=pphi2+(1.0/6.0)*(k12[2]+2.0*k22[2]+2*k32[2]+k42[2]);
        pr2=pr2+(1.0/6.0)*(k12[3]+2.0*k22[3]+2*k32[3]+k42[3]);

        r3=r3+(1.0/6.0)*(k13[0]+2.0*k23[0]+2*k33[0]+k43[0]);
        phi3=phi3+(1.0/6.0)*(k13[1]+2.0*k23[1]+2*k33[1]+k43[1]);
        pphi3=pphi3+(1.0/6.0)*(k13[2]+2.0*k23[2]+2*k33[2]+k43[2]);
        pr3=pr3+(1.0/6.0)*(k13[3]+2.0*k23[3]+2*k33[3]+k43[3]);
        
        o=o+1;
        i=i+1;

        if(o==1000)
        {
            fichero<<r1*cos(phi1)<<","<<r1*sin(phi1)<<endl;
            fichero<<r2*cos(phi2)<<","<<r2*sin(phi2)<<endl;
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