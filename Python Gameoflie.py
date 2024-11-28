                #Jeu de la vie#

class grille():
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.grille = [[0 for i in range(x)] for j in range(y)]

    def afficher(self):
        for i in range(self.x):
            for j in range(self.y):
                print(self.grille[i][j])
            print("\n")

    def vivant(self, x, y):
        if self.grille[x][y] == 1:
            return True
        return False
    
    def mort(self, x, y):
        if self.grille[x][y] == 0:
            return True
        return False
    
    def setVivant(self, x, y):
        self.grille[x][y] = 1

    def setMort(self, x, y):
        self.grille[x][y] = 0

    def nbvoisins(self, x, y):
        nb = 0
        for i in range(x-1, x+2):
            for j in range(y-1, y+2):
                if i < 0 or j < 0 or i >= self.x or j >= self.y:
                    nb += 1
        return nb

grille = grille(10, 10)
grille.setVivant(0, 0)
grille.setVivant(0, 1)
grille.setVivant(0, 2)
grille.afficher()
print(grille.nbvoisins(0, 0))
print(grille.nbvoisins(0, 1))
print(grille.nbvoisins(0, 2))
print(grille.nbvoisins(1, 0))
print(grille.nbvoisins(1, 1))
