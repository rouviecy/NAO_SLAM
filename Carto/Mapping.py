import fileinput
import sys

## Crée la carte, par hypothèse carré
## CoefMap est la longueur de la carte, l'unité étant la longueur d'un pixel

def CreateMap(CoefMap):
    
    
    f = open('Map','w')
 
    for i in xrange (CoefMap):
        for j in xrange(CoefMap-1):
            f.write('0 ') 
        f.write('0 \n')   
    f.close()
    
    
##Dessine un obstacle sur la cate (une endroit sans obstacle est noté en tant que 0, avec un obstacle en tant que 1    
##CoorObstacle de la Forme: [xDebut yDebut ; xFin yFin]    


ef DrawObstacle(CoefMap, CoorObstacle):
   
    
    tmpl=[k for k in range (CoefMap)]

    for line_num, line in enumerate(fileinput.input('Map',inplace=1)):  
            tmp = line
            tmpl[line_num] = tmp.split()
            j = CoorObstacle[0][0]
            
            if (CoorObstacle[0][1]<= line_num <= CoorObstacle[1][1]):
                while (j <= CoorObstacle[1][0]):
                    tmpl[line_num][j] = '1'
                    j = j + 1
            new = ' '.join(tmpl[line_num])
            line = line.replace(tmp, new)
            print line
## Exemple pour voir comment ça marche.        
if __name__ == "__main__":

    a=100
    CreateMap(a)
    obstacle  = [[00,00],[10, 10]]
    obstacle2 = [[10,10],[20, 20]]
    obstacle3 = [[20,20],[30, 30]]
    obstacle4 = [[30,30],[40, 40]]
    obstacle5 = [[40,40],[50, 50]]
    DrawObstacle(a, obstacle)
    DrawObstacle(a, obstacle2)
    DrawObstacle(a, obstacle3)
    DrawObstacle(a, obstacle4)
    DrawObstacle(a, obstacle5)
