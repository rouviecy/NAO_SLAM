class Interface_client(object):

	def __init__(self, actionneur):
		self.actionneur = actionneur

	def go_left(self, activer):		self.actionneur.go_left(activer)
	def go_right(self, activer):	self.actionneur.go_right(activer)
	def go_up(self, activer):		self.actionneur.go_up(activer)
	def go_down(self, activer):		self.actionneur.go_down(activer)
	def inhiber(self, activer):		self.actionneur.inhiber(activer)
