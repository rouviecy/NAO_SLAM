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

mysock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
mysock2.bind((server, 55043))


# fonctions de demarrage/arret du programme
def start() :
	mysock.sendto("start",client1)
	mysock2.sendto("start",client2)
	showinfo('Démarrage', 'Le programme a démarré')

def stop() :
	showinfo('Arrêt', 'Le programme a été arrêté')

# fonction de mise a jour des donnees de NAO
jaugeBatterie = 100
def update() :
	global jaugeBatterie
	jaugeBatterie -= 0.1
	# reception des messages reseau
	global client1
	global client2
	msg1, client1 = mysock.recvfrom(256)
	msg2, client2 = mysock2.recvfrom(256)
    	print "Client1 connected: ", client1, " got message : ", msg1
	print "Client2 connected: ", client2, " got message : ", msg2
    	mysock.sendto(msg1, client1)
	mysock2.sendto(msg2, client2)

	if msg1 == "Stop" :
		mysock.close()
	if msg2 == "Stop" :
		mysock2.close()

	data.set("NAO1\nétat batterie : " + str(jaugeBatterie) + "\nétat courant : " + msg1.split(',')[0]
		+"\n\n\n\nNAO2\nétat batterie : " + str(jaugeBatterie) + "\nétat courant : " + msg2.split(',')[0])
	if "CLIENT DISPONIBLE" not in msg1 :
		print msg1
		msgMap = msg1.split(',')
		mapInterface.CreateObstacle(  numpy.array( [ int(msgMap[1]),int(msgMap[2]),int(msgMap[3]),int(msgMap[4]) ] )  )
		carte.create_rectangle(600*int(msgMap[1])/40,600*int(msgMap[2])/20,600*int(msgMap[3])/40,600*int(msgMap[4])/20, fill='red')

	if "CLIENT DISPONIBLE" not in msg2 :
		print msg2
		msgMap = msg2.split(',')
		mapInterface.CreateObstacle(  numpy.array( [ int(msgMap[1]),int(msgMap[2]),int(msgMap[3]),int(msgMap[4]) ] )  )
		carte.create_rectangle(600*(int(msgMap[1])+20)/40,600*int(msgMap[2])/20,600*(int(msgMap[3])+20)/40,600*int(msgMap[4])/20, fill='red')

	# AFFICHER SUR LE WIDGET LES DONNEES DE MAPINTERFACE
	
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
bstop = Button(window, text = 'STOP', command = stop, fg = 'white', bg = 'black')
bstop.place(x = 100, y = hauteur + 20)

while(1):
	window.minsize(1000,660)
	window.maxsize(1000,660)
	update()
	window.mainloop()
