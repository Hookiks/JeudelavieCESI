import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as anim

class JeuDeLaVie:
    def __init__(self, taille, cellules_initiales):
        self.taille = taille
        self.grille = np.zeros((taille, taille), dtype=int)
        for x, y in cellules_initiales:
            if 0 <= x < taille and 0 <= y < taille:
                self.grille[x, y] = 1

    def evolution(self):
        nouvelle_grille = np.copy(self.grille)
        for i in range(self.taille):
            for j in range(self.taille):
                voisins = np.sum(self.grille[max(0, i-1):min(i+2, self.taille),
                                             max(0, j-1):min(j+2, self.taille)]) - self.grille[i, j]
                # Règles du jeu
                if self.grille[i, j] == 1:
                    nouvelle_grille[i, j] = 1 if voisins in (2, 3) else 0
                else:
                    nouvelle_grille[i, j] = 1 if voisins == 3 else 0
        self.grille = nouvelle_grille

    def afficher(self):
        plt.imshow(self.grille, cmap='binary')
        plt.show()

# Configuration initiale
taille_grille = 100
cellules_vivantes = [
    (50, 51), (50, 52), (50, 53), (51, 51), (52, 51),  # Motif en haut
    (54, 49), (54, 50), (54, 51), (53, 51), (52, 51),  # Motif à gauche
    (56, 51), (56, 52), (56, 53), (55, 53), (54, 53),  # Motif en bas
    (54, 55), (54, 56), (54, 57), (53, 57), (52, 57),  # Motif à droite
]

# Création du jeu
jeu = JeuDeLaVie(taille_grille, cellules_vivantes)

# anim avec Matplotlib
def update(frame):
    jeu.evolution()
    matrice.set_array(jeu.grille)
    return [matrice]

fig, ax = plt.subplots()
matrice = ax.matshow(jeu.grille, cmap='binary')
ani = anim.Funcanim(fig, update, frames=200, interval=50, blit=True)

plt.show()
