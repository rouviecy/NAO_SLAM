import math
import numpy as np
class Robot(object):

	def __init__(self, robotID):
		self.Coord = np.array([0 , 0])
		self.Orient = 0
		self.robotid = robotID

		
	def updateCoordonate(self, Coor, Map):
		self.cgmtr = 0
		self.cgmtl = 0
		tmpCoor = Map.mapMat[self.Coord[0], self.Coord[1]]		
		print tmpCoor
		if tmpCoor != (1):	
			Map.setMapValue( 0, self.Coord)
		self.Coord = Coor
		
		if (self.Coord[0] < 0):
			Map.addLines( math.fabs(self.Coord[0]), 'f')
			self.Coord[0] = 0
			self.cgmtl = 1
		elif (self.Coord[0] >= Map.lines):
			Map.addLines( self.Coord[0] - Map.lines+1 , 'b')
		if (self.Coord[1] < 0):
			Map.addRows( math.fabs(self.Coord[1]), 'f')
			self.Coord[1] = 0
			self.cgmtr = 1
		elif (self.Coord[1] >= Map.rows):
			Map.addRows( self.Coord[1] - Map.rows+1, 'b')
			
			
		Map.setMapValue(self.robotid, self.Coord)		
		
	def updateOrientation(self, Orient):
		self.Orient = Orient
