import numpy as np



class Map(object):

	def __init__(self, IndiceDepart):
		self.lines = IndiceDepart
		self.rows = IndiceDepart
		self.mapMat = np.zeros((self.lines, self.rows))


	def getMapValue(self, coor):
		return self.mapMat[coor]

	def setMapValue(self, value, coor):
		self.mapMat[coor[0], coor[1]] = value

	def getLines(self):
		return self.lines

	def setLines(self, nbLines):
		self.lines = self.lines + nbLines

	def getRow(self):
		return self.rows

	def setRow(self, nbRow):
		self.rows = self.rows + nbRow

	def addRows(self, nbRows, where):
		rowAdder = np.zeros((self.lines , nbRows))
		if (where == 'f' ):
			self.mapMat = np.column_stack([ rowAdder, self.mapMat])
			self.setRow(nbRows)
		elif(where == 'b'):
			self.mapMat = np.column_stack([ self.mapMat, rowAdder])
			self.setRow(nbRows)
		

	def addLines(self,nbLines, where):
		lineAdder = np.zeros((nbLines, self.rows ))
		if (where == 'f'):
			self.mapMat = np.concatenate((lineAdder, self.mapMat), axis = 0)
			self.setLines(nbLines)
		elif(where == 'b' ):
			self.mapMat = np.concatenate((self.mapMat, lineAdder), axis = 0)
			self.setLines(nbLines)
