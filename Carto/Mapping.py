import fileinput

## Cree la carte, par hypothese carre
## CoefMap est la longueur de la carte, l unite etant la longueur d'un pixel

def CreateMap(CoefMap):
	f = open('Map', 'w')
	for i in xrange(CoefMap):
		for j in xrange(CoefMap - 1):
			f.write('0 ')
		f.write('0 \n')
	f.close()


## Dessine un obstacle sur la cate (un endroit sans obstacle est note en tant que 0, avec un obstacle en tant que 1)    
## CoorObstacle de la Forme: [xDebut yDebut ; xFin yFin]

def DrawObstacle(CoefMap, CoorObstacle):
	if (0 <= CoorObstacle[0][0] <= CoorObstacle[1][0] <= CoefMap) & (0 <= CoorObstacle[0][1] <= CoorObstacle[1][1] <= CoefMap):
		tmpl = [k for k in range (CoefMap)]
		for line_num, line in enumerate(fileinput.input('Map', inplace = 1)):
			tmpl[line_num] = line.split()
			j = CoorObstacle[0][0]
			if (CoorObstacle[0][1]<= line_num <= CoorObstacle[1][1]):
				while (j <= CoorObstacle[1][0]):
					tmpl[line_num][j] = '1'
					j = j + 1
			new = ' '.join(tmpl[line_num])
			line = line.replace(line, new)
			print line
	else:
		print "Coordonnee de lobstacle en dehors de la carte"


##Dessine le robot sur le carte
##CoorRobot est de la forme : [x y]

def DrawRobot(CoefMap, CoorRobot):
	if (0 <= CoorRobot[1] <= CoefMap) & (0 <= CoorRobot[0] <= CoefMap):
		tmpl = [k for k in range (CoefMap)]
		for line_num, line in enumerate(fileinput.input('Map', inplace = 1)):
			tmpl[line_num] = line.split()
			if (CoorRobot[1] == line_num):
				tmpl[line_num][CoorRobot[0]] = '2'
			new = ' '.join(tmpl[line_num])
			line = line.replace(line, new)
			print line
	else:
		print "Coordonnee du Robot en dehors de la carte"


## Exemple pour voir comment ca marche
if __name__ == "__main__":

	a = 100
	CreateMap(a)

	obstacle =	[[00,00],
			[10, 10]]

	obstacle2 =	[[20,00],
			[50, 10]]

	obstacle3 =	[[20,20],
			[30, 30]]

	obstacle4 =	[[30,30],
			[40, 40]]

	obstacle5 =	[[40,40],
			[50, 50]]

	robot =		[10, 40]

	DrawObstacle(a, obstacle)
	print 1
	DrawObstacle(a, obstacle2)
	print 2
	DrawObstacle(a, obstacle3)
	print 3
	DrawObstacle(a, obstacle4)
	print 4
	DrawObstacle(a, obstacle5)
	print 5
	DrawRobot(a,robot)
