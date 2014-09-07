class Interface_serveur(object):

	def __init__(self, client):
		self.client = client

	def go_left(self, activer):		self.client.go_left(activer)
	def go_right(self, activer):	self.client.go_right(activer)
	def go_up(self, activer):		self.client.go_up(activer)
	def go_down(self, activer):		self.client.go_down(activer)
	def inhiber(self, activer):		self.client.inhiber(activer)
