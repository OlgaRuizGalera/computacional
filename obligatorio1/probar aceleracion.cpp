aceleracion (float m[9], float r[9][2], float a[9][2])
{
    int i, j, k;
    float mod,  raux[9][2];
    for (i=0; i<9; i++ )
    {
        for (j=0; j<9; j++)
        {
            if (j!=i)
            {
                mod=pow((r[i][0]-r[j][0]),2)+pow((r[i][1]-r[j][1]),2);
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