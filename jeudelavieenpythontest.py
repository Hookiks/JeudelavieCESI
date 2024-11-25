class jeu_de_la_vie:
    
    def __init__(self, taille_y_grille, taille_x_grille):
        self.taille_y_grille = taille_y_grille
        self.taille_x_grille = taille_x_grille
        self.grille = [[0 for i in range(self.taille_x_grille)] for j in range(self.taille_y_grille)]

    def compter_les_voisines(self):
        for i in range(self.taille_y_grille):
            for j in range(self.taille_x_grille):
                pass