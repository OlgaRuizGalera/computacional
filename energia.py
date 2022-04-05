#Programa para plotear puntos

import matplotlib.pyplot as plt
import numpy as np
from scipy import optimize

data=np.loadtxt('energia.txt')

t=data[:,0]
Energia=data[:,1]


fig=plt.figure()
ax=fig.add_subplot(111)
ax.grid(True)


y_min = -10
y_max = 30

ax.set_ylim(y_min, y_max)

ax.set_ylabel("Energia", fontsize=14, fontname="Times New Roman")
ax.set_xlabel("Tiempo", fontsize=14, fontname="Times New Roman")
#ax.plot(t,mercurio, linestyle='dashed', linewidth=2, color='purple')
#ax.plot(t,venus, linestyle='dashed', linewidth=2, color='brown')
#ax.plot(t,tierra, linestyle='dashed', linewidth=2, color='green')
#ax.plot(t,marte, linestyle='dashed', linewidth=2, color='red')
#ax.plot(t,jupiter, linestyle='dashed', linewidth=2, color='orange')
#ax.plot(t,saturno, linestyle='dashed', linewidth=2, color='olive')
#ax.plot(t,urano, linestyle='dashed', linewidth=2, color='blue')
#ax.plot(t,neptuno, linestyle='dashed', linewidth=2, color='cyan')
ax.plot(t,Energia, linestyle='dashed', linewidth=2, color='black')
fig.savefig('energias.png',dpi=300)
plt.show()