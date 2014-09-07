import serial

class Actionneur(object):

	def __init__(self):
		self.rotation = 0
		self.avance = 0
		self.inhibation = False
#		self.ssc = serial.Serial('/dev/ttyUSB0', 115200)

	def go_left(self, activer):		self.modifier_vitesse(-1 if activer else +1, 0)
	def go_right(self, activer):	self.modifier_vitesse(+1 if activer else -1, 0)
	def go_up(self, activer):		self.modifier_vitesse(0, +1 if activer else -1)
	def go_down(self, activer):		self.modifier_vitesse(0, -1 if activer else +1)
	def inhiber(self, activer):		self.inhibation = activer

	def modifier_vitesse(self, dx, dy):
		self.rotation += dx
		self.avance += dy
		str_rot = "reste dans l'axe"
		str_av = "reste sur place"
		if self.rotation < 0: str_rot = "va a gauche"
		if self.rotation > 0: str_rot = "va a droite"
		if self.avance < 0: str_av = "recule"
		if self.avance > 0: str_av = "avance"
		print str_rot + " et " + str_av
		str_serial = self.serial_order(self.inhibation)
		print str_serial
#		self.ssc.write(str_serial)
		print "------------------------------------------"

	def serial_order(self, immediat):
		tempo = "" if immediat else " T1000"
		if 		self.avance == +0 and self.rotation == -1:	return "#0 P1250" + tempo + " #1 P1750" + tempo + "\r"
		elif	self.avance == +0 and self.rotation == +0:	return "#0 P1500" + tempo + " #1 P1500" + tempo + "\r"
		elif	self.avance == +0 and self.rotation == +1:	return "#0 P1750" + tempo + " #1 P1250" + tempo + "\r"
		elif	self.avance == +1 and self.rotation == -1:	return "#0 P1750" + tempo + " #1 P2000" + tempo + "\r"
		elif	self.avance == +1 and self.rotation == +0:	return "#0 P2000" + tempo + " #1 P2000" + tempo + "\r"
		elif	self.avance == +1 and self.rotation == +1:	return "#0 P2000" + tempo + " #1 P1750" + tempo + "\r"
		elif	self.avance == -1 and self.rotation == -1:	return "#0 P1000" + tempo + " #1 P1250" + tempo + "\r"
		elif	self.avance == -1 and self.rotation == +0:	return "#0 P1000" + tempo + " #1 P1000" + tempo + "\r"
		elif	self.avance == -1 and self.rotation == +1:	return "#0 P1250" + tempo + " #1 P1000" + tempo + "\r"
