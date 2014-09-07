from Interface_client	import Interface_client
from Actionneur			import Actionneur
import sys

if __name__ == '__main__':
	actionneur = Actionneur()
	ip_serveur = 'localhost' if len(sys.argv) < 2 else sys.argv[1]
	client = Interface_client(ip_serveur, actionneur)
