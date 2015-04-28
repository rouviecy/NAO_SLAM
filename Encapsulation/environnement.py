class Environnement :

	def __init__(self,xMax,yMax) :
		self.xMax = xMax
		self.yMax = yMax
		self.map = []
		for i in range(xMax) :
			self.map += [[]]
			for j in range(yMax) :
				self.map[i] += [0]

	def addObjet(self,x,y,taille) :
		for i in range(taille) :
			for j in range(taille) :
				self.map[x+i][y+j] = 1

"""
if __name__=="__main__":

# tests : OK

	e = Environnement(8,8)
	e.addObjet(2,2,2)
	for x in e.map :
		print x
"""
