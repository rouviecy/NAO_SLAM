import fileinput

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


def DrawObstacle(CoorObstacle):
   
    
    tmpl=[k for k in range (CoorObstacle[1][1] + 1 -CoorObstacle[0][1])]

    for line_num, line in enumerate(fileinput.input('Map',inplace=1)):  
        if (CoorObstacle[0][1]<= line_num <= CoorObstacle[1][1]):
            tmp = line
            tmpl[line_num-CoorObstacle[0][1]] = tmp.split()
            j = CoorObstacle[0][0]
            while (j <= CoorObstacle[1][0]):
                    tmpl[line_num-CoorObstacle[0][1]][j] = '1'
                    j = j + 1
            new = ' '.join(tmpl[line_num-CoorObstacle[0][1]])
            new = new + ' \n'
            line = line.replace(tmp, new)
            
        print line
## Exemple pour voir comment ça marche.        
if __name__ == "__main__":

    
    CreateMap(100)
    obstacle = [[0,0],[10, 10]]
    DrawObstacle(obstacle)
