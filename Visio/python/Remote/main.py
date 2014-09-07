from GUI				import GUI
from Interface_serveur	import Interface_serveur
from Interface_client	import Interface_client
from Actionneur			import Actionneur

if __name__ == '__main__':
	actionneur = Actionneur()
	client = Interface_client(actionneur)
	serveur = Interface_serveur(client)
	gui = GUI(serveur)
