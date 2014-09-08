# -*- coding: utf-8 -*-

import pygame
from pygame.locals import *
from Configuration import Configuration as c

class GUI(object):

	def __init__(self, serveur):
		self.joystick_WE = 0
		self.joystick_NS = 0
		self.clock = pygame.time.Clock()
		self.serveur = serveur
		self.initialisation()
		self.rafraishissement()
		self.bouclage()
		self.serveur.quitter()

	def initialisation(self):
		pygame.init()
		fenetre = pygame.display.set_mode((640, 480))
		nb = pygame.joystick.get_count()
		print str(nb) + " joystick(s) détectés"
		if(nb > 0):
			print "Activation du 1er joystick"
			mon_joystick = pygame.joystick.Joystick(0)
			mon_joystick.init()
			return True
		return False

	def rafraishissement(self):
		pygame.display.flip()

	def action_clavier(self, downing, key):
		if		key == c.K_QUIT:	return False
		elif	key == c.K_LEFT:	self.serveur.go_left(downing)
		elif	key == c.K_RIGHT:	self.serveur.go_right(downing)
		elif	key == c.K_UP:		self.serveur.go_up(downing)
		elif	key == c.K_DOWN:	self.serveur.go_down(downing)
		elif	key == c.K_INHIB:	self.serveur.inhiber(downing)
		return True

	def action_joystick_bouton(self, bouton):
		if		bouton == c.J_BUTTON_A:	print "A"
		elif	bouton == c.J_BUTTON_B:	print "B"
		return True

	def action_joystick_axe(self, axe, valeur):
		if axe == c.J_AXIS_WE:
			if		c.J_INTERVAL_L[0] <= valeur <= c.J_INTERVAL_L[1]:
				if		self.joystick_WE == 0:
					self.joystick_WE = -1
					self.serveur.go_left(True)
				elif	self.joystick_WE == 1:
					self.joystick_WE = -1
					self.serveur.go_right(False)
					self.serveur.go_left(True)
			elif	c.J_INTERVAL_R[0] <= valeur <= c.J_INTERVAL_R[1]:
				if		self.joystick_WE == 0:
					self.joystick_WE = +1
					self.serveur.go_right(True)
				elif	self.joystick_WE == -1:
					self.joystick_WE = +1
					self.serveur.go_left(False)
					self.serveur.go_right(True)
			elif	c.J_INTERVAL_0WE[0] <= valeur <= c.J_INTERVAL_0WE[1]:
				if		self.joystick_WE == -1:
					self.joystick_WE = 0
					self.serveur.go_left(False)
				elif	self.joystick_WE == +1:
					self.joystick_WE = 0
					self.serveur.go_right(False)
		if		axe == c.J_AXIS_NS:
			if c.J_INTERVAL_U[0] <= valeur <= c.J_INTERVAL_U[1]:
				if		self.joystick_NS == 0:
					self.joystick_NS = -1
					self.serveur.go_up(True)
				elif	self.joystick_NS == 1:
					self.joystick_NS = -1
					self.serveur.go_down(False)
					self.serveur.go_up(True)
			elif	c.J_INTERVAL_D[0] <= valeur <= c.J_INTERVAL_D[1]:
				if		self.joystick_NS == 0:
					self.joystick_NS = +1
					self.serveur.go_down(True)
				elif	self.joystick_NS == -1:
					self.joystick_NS = +1
					self.serveur.go_up(False)
					self.serveur.go_down(True)
			elif	c.J_INTERVAL_0NS[0] <= valeur <= c.J_INTERVAL_0NS[1]:
				if		self.joystick_NS == -1:
					self.joystick_NS = 0
					self.serveur.go_up(False)
				elif	self.joystick_NS == +1:
					self.joystick_NS = 0
					self.serveur.go_down(False)
		return True

	def bouclage(self):
		continuer = True
		while continuer:
			for event in pygame.event.get():
				if		event.type == QUIT:				continuer = False
				elif	event.type == KEYDOWN:			continuer = self.action_clavier(True, event.key)
				elif	event.type == KEYUP:			continuer = self.action_clavier(False, event.key)
				elif	event.type == JOYBUTTONDOWN:	continuer = self.action_joystick_bouton(event.button)
				elif	event.type == JOYAXISMOTION:	continuer = self.action_joystick_axe(event.axis, event.value)
			self.clock.tick(20)
