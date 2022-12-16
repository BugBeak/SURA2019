import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
for i in range(10):
	X = np.loadtxt('result1/flowx'+str(i)+'.txt')
	Y = np.loadtxt('result1/flowy'+str(i)+'.txt')
	plt.plot(X,Y,linestyle = '--')
X = np.loadtxt('result1/flowxavg.txt')
Y = np.loadtxt('result1/flowyavg.txt')
plt.plot(X,Y, color='black', label='average', linewidth = 2)
plt.title("No. of nodes = 10000, No. of lines = 10, Interval = 0.01")
plt.xlabel("Applied pressure")
plt.ylabel("Flow Rate")
#X = np.loadtxt('Xavg.txt')
#Y = np.loadtxt('Yavg.txt')
#plt.plot(X,Y, linestyle = '--')
plt.savefig('graph1/Flowrate10000'+'.png', bbox_inches='tight')
#linestyle = '--',