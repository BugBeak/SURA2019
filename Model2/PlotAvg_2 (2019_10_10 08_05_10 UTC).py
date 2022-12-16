import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

S = np.loadtxt('size.txt')

for i in S:
	X = np.loadtxt('result/x'+str(int(i))+'.txt')
	Y = np.loadtxt('result/fracyavg'+str(int(i))+'.txt')
	plt.plot(X,Y, label='size='+str(int(i)))
	plt.legend()
plt.title("Average Fraction v/s Applied Pressure for Different Sizes")
plt.xlabel("Applied pressure")
plt.ylabel("Fraction of open nodes(avg)")
plt.savefig('graph/AvgFraction'+'.png', bbox_inches='tight')
plt.close()

for i in S:
	X = np.loadtxt('result/x'+str(int(i))+'.txt')
	Y = np.loadtxt('result/flowyavg'+str(int(i))+'.txt')
	plt.plot(X,Y, label='size='+str(int(i)))
	plt.legend()
plt.title("Average Flowrate v/s Applied Pressure for Different Sizes")
plt.xlabel("Applied pressure")
plt.ylabel("Flow Rate(avg)")
plt.savefig('graph/AvgFlowrate.png', bbox_inches='tight')
plt.close()

#S = np.loadtxt('sizesq.txt')
Y = np.loadtxt('MaxPress.txt')
plt.plot(S,Y)
plt.scatter(S,Y)
plt.title("Pressure at which all nodes open vs Size")
plt.xlabel("Size")
plt.ylabel("Minimum Pressure required for all nodes with finite resistance to open")
plt.savefig('graph/AllNodesOpen.png', bbox_inches='tight')
plt.close()

Y = np.loadtxt('MinPress.txt')
plt.plot(S,Y)
plt.scatter(S,Y)
plt.title("Min Pressure required for percolation vs Size")
plt.xlabel("Size")
plt.ylabel("Minimum Pressure required for fluid to exit")
plt.savefig('graph/FirstFlowpathOpen.png', bbox_inches='tight')
plt.close()