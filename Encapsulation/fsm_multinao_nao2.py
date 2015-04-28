# -*- coding: utf-8 -*-
import fsm, nao, environnement
import math, random, socket, time
import numpy as numpy


# mise en place des sockets

global msgout
mysock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server = "127.0.0.1"
port = 55043
msgout = "CLIENT DISPONIBLE"
mysock.sendto(msgout, (server, port))
msgin, rserver = mysock.recvfrom(255)
print "Received:", msgin, " from ", rserver

# AUTOMATE FINI - SIMULATION DE CARTOGRAPHIE ET LOCALISATION SIMULTANEES POUR VALIDATION DE LA DEMARCHE


f = fsm.fsm()
n = nao.Nao(3,1,0,12)
e = environnement.Environnement(20,20)
# a cause des rayons de detection, placer les objets a une distance minimale de 4 du bord de l'environnement
e.addObjet(8,16,2)
e.addObjet(16,2,2)


# limites de l'environnement
xMax = e.xMax
yMax = e.yMax


# rayon de "vision" du NAO
n.rVision = 12
# initialisation du cap du NAO
n.cap = 0.5

# simulation de la carte
carte = []



# definition des fonctions de l'automate

def scan() :
	global x, y 	# coordonnees de l'objet detecte
	b = False
	for i in range(n.rVision) :
		for j in range(n.rVision) :
			# parcours des 4 quarts de la carte "visibles" pour le NAO
			if ( (int(n.x)+i < e.xMax) & (int(n.y)+j < e.yMax) ) :
				if e.map[int(n.x)+i][int(n.y)+j] == 1 :
					x = n.x+i
					y = n.y+j
					b = True
			if ( (int(n.x)+i < e.xMax) & (int(n.y)-j > 0) ) :
				if e.map[int(n.x)+i][int(n.y)-j] == 1 :
					x = n.x+i
					y = n.y-j
					b = True
			if ( (int(n.x)-i > 0) & (int(n.y)+j < e.yMax) ) :
				if e.map[int(n.x)-i][int(n.y)+j] == 1 :
					x = n.x-i
					y = n.y+j
					b = True
			if ( (int(n.x)-i > 0) & (int(n.y)-j > 0) ) :
				if e.map[int(n.x)-i][int(n.y)-j] == 1 :
					x = n.x-i
					y = n.y-j
					b = True
	if b :
		print x, y
		return "Detection_OK"
	else :
		return "Detection_KO"


def stop() :
	print "Mission terminee"
	return None


def marcheVers() :
	n.x = x
	n.y = y
	print x, y
	return "Objet_proche"


def marcheAleatoire() :
	# definition de coordonnees aleatoires
	xrand = 0
	yrand = 0
	xrand = random.randint(0,xMax-1)
	yrand = random.randint(0,yMax-1)
	n.x = xrand
	n.y = yrand
	return "Deplacement_fait"

def reconnaissance() :	# a revoir
	size = 0
	b = False
	for i in range(3) :
		for j in range(3) :
			if e.map[int(n.x)+i][int(n.y)+j] == 1 :
				b = True	# test pour savoir si la reconnaissance a ete effectuee
				size += 1	# enregistrer les dimensions de l'objet
				e.map[int(n.x)+i][int(n.y)+j] = 2	# marquer l'objet deja reconnu
			if e.map[int(n.x)+i][int(n.y)-j] == 1 :
				b = True	# test pour savoir si la reconnaissance a ete effectuee
				size += 1	# enregistrer les dimensions de l'objet
				e.map[int(n.x)+i][int(n.y)-j] = 2	# marquer l'objet deja reconnu
			if e.map[int(n.x)-i][int(n.y)+j] == 1 :
				b = True	# test pour savoir si la reconnaissance a ete effectuee
				size += 1	# enregistrer les dimensions de l'objet
				e.map[int(n.x)-i][int(n.y)+j] = 2	# marquer l'objet deja reconnu
			if e.map[int(n.x)-i][int(n.y)-j] == 1 :
				b = True	# test pour savoir si la reconnaissance a ete effectuee
				size += 1	# enregistrer les dimensions de l'objet
				e.map[int(n.x)-i][int(n.y)-j] = 2	# marquer l'objet deja reconnu
	if b :
		carte.append("obstacle en " + str(n.x) + ", " + str(n.y) + " de taille " + str(size/2))
		print carte
		coord = str(int(n.x))+','+str(int(n.y))+','+str( int(n.x)+size/2-1 )+','+str( int(n.y)+size/2-1 )
		mysock.sendto("COORD,"+coord, (server, port))
		if len(carte) == 2 :
			return "Carte_etablie"
		return "Reconnaissance_faite"


# definition de l'automate

if __name__ == "__main__" :

#def main() :

	f.add_state("Idle")
	f.add_state("Scan")
	f.add_state("Marche")
	f.add_state("Reconnaissance")
	f.add_state("Stop")

	f.add_event("Demarrage")
	f.add_event("Carte_etablie")
	f.add_event("Detection_OK") 	# objet detecte lors de la phase de scan
	f.add_event("Detection_KO") 	# aucun objet detecte lors de la phase de scan
	f.add_event("Deplacement_fait")
	f.add_event("Objet_proche")
	f.add_event("Reconnaissance_faite")
	f.add_event("Objet_non_atteint")

	f.add_transition("Idle","Scan","Demarrage",scan)
	f.add_transition("Scan","Marche","Detection_OK",marcheVers)
	f.add_transition("Scan","Marche","Detection_KO",marcheAleatoire)
	f.add_transition("Marche","Scan","Deplacement_fait",scan)
	f.add_transition("Marche","Marche","Objet_non_atteint",marcheAleatoire)
	f.add_transition("Marche","Reconnaissance","Objet_proche",reconnaissance)
	f.add_transition("Reconnaissance","Scan","Reconnaissance_faite",scan)
	f.add_transition("Reconnaissance","Stop","Carte_etablie",stop)

	f.set_state("Idle")
	f.set_event("Demarrage")

	while(1) :
		mysock.sendto(msgout, (server, port))
		msgin, rserver = mysock.recvfrom(255)
		if msgin == "start" :
			while (f.curState != "Stop") :
				funct = f.run()
				newEvent = funct()
				print "New Event : ",newEvent
				f.set_event(newEvent)
				msgout = f.curState + ',' + msgout
				mysock.sendto(msgout, (server, port))
				msgout = "CLIENT DISPONIBLE"
