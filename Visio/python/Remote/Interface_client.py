import socket

class Interface_client(object):

	def __init__(self, host, actionneur):
		self.actionneur = actionneur
		port = 4242
		self.ouvert = True
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.connect((host, port))
		while self.ouvert:
			msg_in = self.s.recv(1024)
			self.decodage(msg_in)

		self.s.close()

	def decodage(self, msg):
		c = msg.decode()
		for i in range(len(c) / 3):
			if c == "bye":			self.ouvert = False
			elif c[3*i+0] == 'g':
				if		c[3*i+1] == 'l' :	self.go_left(c[3*i+2] == '1')
				elif	c[3*i+1] == 'r' :	self.go_right(c[3*i+2] == '1')
				elif	c[3*i+1] == 'u' :	self.go_up(c[3*i+2] == '1')
				elif	c[3*i+1] == 'd' :	self.go_down(c[3*i+2] == '1')
			elif c[3*i+0] == 'i':
				if c[3*i+1] == 'n' :		self.inhiber(c[3*i+2] == '1')

	def go_left(self, activer):		self.actionneur.go_left(activer)
	def go_right(self, activer):	self.actionneur.go_right(activer)
	def go_up(self, activer):		self.actionneur.go_up(activer)
	def go_down(self, activer):		self.actionneur.go_down(activer)
	def inhiber(self, activer):		self.actionneur.inhiber(activer)
