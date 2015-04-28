from GUI				import GUI
from Interface_serveur	import Interface_serveur

if __name__ == '__main__':
	serveur = Interface_serveur()
	gui = GUI(serveur)
