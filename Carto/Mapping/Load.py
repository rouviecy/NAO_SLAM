import interfaceMap
import sys
import numpy as np


f = open('MapSaved', 'r')
a = f.readlines(0)
Size = [len(a)+1, len(a[0].split(','))]
tmpMap = np.zeros((Size[0], Size[1]))
robotCount = 0
for i in range(len(a)):
	tmp = a[i].split(',')
	for j in range(len(tmp)-1):
		tmpMap[i,j] = int(tmp[j])
		if (int(tmp[j]) > 1):
			robotCount +=1

sys.argv[1] = interfaceMap.Interface(robotCount)
sys.argv[1].Mamap.mapMat = tmpMap
