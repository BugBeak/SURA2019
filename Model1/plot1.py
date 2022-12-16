import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
size=800
lines=10
X = np.loadtxt('result1/x'+str(size)+'.txt')
for i in range(lines):
	Y = np.loadtxt('result1/fracy'+str(i)+'.txt')
	plt.plot(X,Y,linestyle = '--')
Y = np.loadtxt('result1/fracyavg'+str(size)+'.txt')
plt.plot(X,Y, color='black', label='average', linewidth = 2)
plt.title("No. of nodes = "+str(size)+"*"+str(size)+", No. of lines = "+str(lines))
plt.xlabel("Applied pressure")
plt.ylabel("Fraction of open nodes")
#X = np.loadtxt('Xavg.txt')
#Y = np.loadtxt('Yavg.txt')
#plt.plot(X,Y, linestyle = '--')
plt.savefig('graph1/Fraction'+str(size)+'.png', bbox_inches='tight')
plt.close()

for i in range(lines):
	Y = np.loadtxt('result1/flowy'+str(i)+'.txt')
	plt.plot(X,Y,linestyle = '--')
Y = np.loadtxt('result1/flowyavg'+str(size)+'.txt')
plt.plot(X,Y, color='black', label='average', linewidth = 2)
plt.title("No. of nodes = "+str(size)+"*"+str(size)+", No. of lines = "+str(lines))
plt.xlabel("Applied pressure")
plt.ylabel("Flow Rate")
#X = np.loadtxt('Xavg.txt')
#Y = np.loadtxt('Yavg.txt')
#plt.plot(X,Y, linestyle = '--')
plt.savefig('graph1/Flowrate'+str(size)+'.png', bbox_inches='tight')
#linestyle = '--',
plt.close()