import math, time

class Nao :

	def __init__(self,posX,posY,cap,r) :
		self.x = posX
		self.y = posY
		self.cap = cap
		self.rVision = r

	def getX(self) :
		return self.x

	def getY(self) :
		return self.y

	def getCap(self) :
		return self.cap

	def getAll(self) :
		return self.x, self.y, self.cap

	def setX(self,x) :
		self.x = x

	def setY(self,y) :
		self.y = y

	def setCap(self,cap) :
		self.cap = cap

	def marche(self,cap,vitesse,temps) :
		self.cap = cap
		i = 0
		while i<temps :
			print self.getAll()
			self.x += vitesse*math.cos(cap)
			self.y += vitesse*math.sin(cap)
			i+=1
			time.sleep(1)

"""
if __name__=="__main__" :

# tests : OK

	n = Nao(0,0,0)
	print n.getAll()
	n.setX(2)
	print n.getX()
	n.marche(-1,1,4)
"""
