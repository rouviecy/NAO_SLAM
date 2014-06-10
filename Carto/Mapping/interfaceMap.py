import Map
import Robot
import Obstacle
import numpy as np

class Interface(object):
	global obstacleID
	obstacleID =0

	def __init__(self, nbRobot):
		self.Mamap = Map.Map(10)
		self.listRobot = []
		self.nbRobot = nbRobot
		for i in range(nbRobot):
			nom = "Robot"+str(i)
			nom = Robot.Robot(i+2)
			self.listRobot.append(nom)
			nom.updateCoordonate(np.array([i+1,i+1]), self.Mamap)

	def CreateObstacle(self, Coord):
		self.nom = "Obstacle"+str(obstacleID)
		tmpline = self.Mamap.lines
		tmpRow = self.Mamap.rows
		self.nom = Obstacle.Obstacle(Coord, self.Mamap)
		tmpRowAf = self.Mamap.rows
		tmplineAf = self.Mamap.lines
		if self.nom.cgmtr == 1:
			for i in range(self.nbRobot):
				self.listRobot[i].updateCoordonate([self.listRobot[i].Coord[0], self.listRobot[i].Coord[1]+ (tmpRowAf - tmpRow)], self.Mamap)
		if self.nom.cgmtl == 1:
			for i in range(self.nbRobot):
				self.listRobot[i].updateCoordonate([self.listRobot[i].Coord[0]+ (tmplineAf - tmpline), self.listRobot[i].Coord[1]], self.Mamap)

	def updateRobot(self, Coord, robotID):
		tmpline = self.Mamap.lines
		tmpRow = self.Mamap.rows
		self.listRobot[robotID].updateCoordonate(Coord, self.Mamap)
		tmpRowAf = self.Mamap.rows
		tmplineAf = self.Mamap.lines
		if self.listRobot[robotID].cgmtr == 1:
			for i in range(self.nbRobot):
				if robotID<>i:
					self.listRobot[i].updateCoordonate([self.listRobot[i].Coord[0], self.listRobot[i].Coord[1]+ (tmpRowAf - tmpRow)], self.Mamap)
		if self.listRobot[robotID].cgmtl == 1:
			for i in range(self.nbRobot):
					if robotID<>i:
						self.listRobot[i].updateCoordonate([self.listRobot[i].Coord[0]+ (tmplineAf - tmpline), self.listRobot[i].Coord[1]], self.Mamap)

	def updateRobotOrientation(self, Orientation, robotID):
		self.listRobot[robotID].updateOrientation(Orientation)

	def getRobotOrientation(self, robotID):
		return self.listRobot[robotID].Orient
	def saveMap(self):
		f = ('MapSaved', 'w')
		for i in range(self.Mamap.lines):
			for j in range(self.Mamap.rows):
				f.write(self.Mamap.mapMat[i,j])
				f.write(' ')
			f.write('\n')
		f.close

