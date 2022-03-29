#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main (void)
{
    ifstream fichinicio;
    double m[9], v[9][2], r[9][2];
    int i, j, k, p;

    fichinicio.open("valoresiniciales.txt");
    for (i=0; i<9; i++)
    {
        fichinicio>> m[i];
        cout << m[i];
        cin>>p;
    }

    for (j=0; j<9; j++)
    {
        fichinicio>> r[j][0];
        fichinicio>> r[j][1];
        cout <<r[j][0];
        cout <<r[j][1];
        cin>>p;
    }

     for (k=0; k<9; k++)
    {
       fichinicio>> v[k][0];
       fichinicio>> v[k][1];
       cout <<v[k][0];
       cout <<v[k][1];
       cin>>p;
    }
    
    fichinicio.close ();
    
    return 0;    
}