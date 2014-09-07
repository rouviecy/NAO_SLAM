# -*- coding: utf-8 -*-

import socket
import select
import time

class Interface_serveur(object):
	
	def __init__(self):
		host = ''
		port = 4242
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.bind((host, port))
		self.s.listen(5)
		print("Écoute sur le port {}".format(port))
		self.client, _ = self.s.accept()

	def go_left(self, activer):		self.envoyer("gl" + ("1" if activer else "0"))
	def go_right(self, activer):	self.envoyer("gr" + ("1" if activer else "0"))
	def go_up(self, activer):		self.envoyer("gu" + ("1" if activer else "0"))
	def go_down(self, activer):		self.envoyer("gd" + ("1" if activer else "0"))
	def inhiber(self, activer):		self.envoyer("in" + ("1" if activer else "0"))
	def quitter(self):
		self.envoyer("bye")
		time.sleep(1)
		self.s.close()

	def envoyer(self, message):
		self.client.send(message.encode())
		
