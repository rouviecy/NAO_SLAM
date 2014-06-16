# -*- coding: utf-8 -*-
from Tkinter import *
from tkMessageBox import *

#import fsm_solo_reseau as f
import socket
import interfaceMap
import numpy as numpy

# instanciation de la carte
mapInterface = interfaceMap.Interface(1)

# demarrage du serveur
server="127.0.0.1"
port=55042
mysock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
mysock.bind((server, port))


# fonctions de demarrage/arret du programme
def start() :
	mysock.sendto("start",client)
	showinfo('Démarrage', 'Le programme a démarré')

def stop() :
	showinfo('Arrêt', 'Le programme a été arrêté')

# fonction de mise a jour des donnees de NAO
jaugeBatterie = 100
def update() :
	global jaugeBatterie
	jaugeBatterie -= 0.1
	# reception des messages reseau
	global client
	msg, client = mysock.recvfrom(256) 
    	print "Client connected: ", client, " got message : ", msg
    	mysock.sendto(msg, client)

	if msg == "Stop" :
		mysock.close()
		sockMap.close()

	data.set("NAO1\nétat batterie : " + str(jaugeBatterie) + "\nétat courant : " + msg.split(',')[0])
	if "CLIENT DISPONIBLE" not in msg :
		print msg
		msgMap = msg.split(',')
		mapInterface.CreateObstacle(  numpy.array( [ int(msgMap[1]),int(msgMap[2]),int(msgMap[3]),int(msgMap[4]) ] )  )
		carte.create_rectangle(600*int(msgMap[1])/20,600*int(msgMap[2])/20,600*int(msgMap[3])/20,600*int(msgMap[4])/20, fill='red')
	#print mapInterface.Mamap.mapMat

	# AFFICHER SUR LE WIDGET LES DONNEES DE MAPINTERFACE

	l = len(mapInterface.Mamap.mapMat)
	#for i in range(l) :
	#	for j in range(l) :
	#		if int(mapInterface.Mamap.mapMat[i][j]) == 1 :
	#			carte.create_rectangle(i*600/l,j*600/l,i*600/l,j*600/l,fill="green")	
	window.after(500,update)

# creation de la fenetre
window = Tk()
window.configure(bg='black')
window.title('NAOSLAM monitoring')

# creation du widget d'affichage de la carte
largeur = 600
hauteur = 600
carte = Canvas(window, width = largeur, height = hauteur, bg = 'green')
carte.place(x = 10, y = 10)

# creation du label affichant les donnees de NAO
data = StringVar()
label = Label(window, textvariable = data, fg = 'white', bg = 'black')
label.place(x = largeur + 20, y = 10)

# creation du bouton de demarrage du programme
bstart = Button(window, text = 'START', command = start, fg = 'white', bg = 'black')
bstart.place(x = 10, y = hauteur + 20)

# creation du bouton d'arret du programme
bstart = Button(window, text = 'STOP', command = stop, fg = 'white', bg = 'black')
bstart.place(x = 100, y = hauteur + 20)

while(1):
	window.minsize(900,660)
	window.maxsize(900,660)
	update()
	window.mainloop()
