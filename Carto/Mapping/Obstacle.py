
import math
import numpy as np
class Obstacle(object):

	def __init__(self, Coord, Map):
		self.Coord = Coord
		self.cgmtl = 0
		self.cgmtr = 0
		
		if (self.Coord[0] < 0):
			Map.addLines( math.fabs(self.Coord[0]), 'f')
			self.Coord[2] = self.Coord[2] + math.fabs(self.Coord[0]) 
			self.Coord[0] = 0
			self.cgmtl = 1

		if (self.Coord[2] >= Map.lines):
			Map.addLines( self.Coord[2] - Map.lines+1 , 'b')

		if (self.Coord[1] < 0):
			Map.addRows( math.fabs(self.Coord[1]), 'f')
			self.Coord[3] = self.Coord[3] + math.fabs(self.Coord[1])
			self.Coord[1] = 0
			self.cgmtr = 1

		if (self.Coord[3] >= Map.rows):
			Map.addRows( self.Coord[3] - Map.rows+1, 'b')
		
		for i in range(Coord[0], Coord[2]+1):
			for j in range(Coord[1], Coord[3]+1):	
				Map.setMapValue(1, np.array([i, j]))
