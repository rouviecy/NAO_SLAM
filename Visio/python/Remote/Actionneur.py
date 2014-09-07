class Actionneur(object):

	def __init__(self):
		self.rotation = 0
		self.avance = 0

	def go_left(self, activer):
		self.resultat(-1 if activer else +1, 0)

	def go_right(self, activer):
		self.resultat(+1 if activer else -1, 0)

	def go_up(self, activer):
		self.resultat(0, +1 if activer else -1)

	def go_down(self, activer):
		self.resultat(0, -1 if activer else +1)

	def resultat(self, dx, dy):
		self.rotation += dx
		self.avance += dy
		str_rot = "reste dans l'axe"
		str_av = "reste sur place"
		if self.rotation < 0: str_rot = "va a gauche"
		if self.rotation > 0: str_rot = "va a droite"
		if self.avance < 0: str_av = "recule"
		if self.avance > 0: str_av = "avance"
		print str_rot + " et " + str_av
