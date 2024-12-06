#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Grille {
public:
    int lignes;
    int colonnes;
    vector<vector<int>> cellules;

    Grille(int lignes, int colonnes) : lignes(lignes), colonnes(colonnes) {
        cellules = vector<vector<int>>(lignes, vector<int>(colonnes, 0));
    }

    bool VerifierCellulesVivante() {
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                if (cellules[i][j] == 1) {
                    return true;
                }
            }
        }
        return false;
    }
};

class jeuDeLaVie {
private:
    Grille grille;
    const int TAILLE_CELLULE = 20; // Taille en pixels d'une cellule

public:
    jeuDeLaVie(int lignes, int colonnes) : grille(lignes, colonnes) {}

    void EtatInitial(vector<pair<int, int>>& cellulesVivantes) {
        for (auto& cellule : cellulesVivantes) {
            int x = cellule.first;
            int y = cellule.second;
            if (x >= 0 && x < grille.lignes && y >= 0 && y < grille.colonnes) {
                grille.cellules[x][y] = 1;
            }
        }
    }

    void update() {
        vector<vector<int>> nouvellesCellules = grille.cellules;

        for (int i = 0; i < grille.lignes; ++i) {
            for (int j = 0; j < grille.colonnes; ++j) {
                int voisinsVivants = compterCellulesVivantesVoisines(i, j);
                if (grille.cellules[i][j] == 1) {
                    nouvellesCellules[i][j] = (voisinsVivants == 2 || voisinsVivants == 3) ? 1 : 0;
                } else {
                    nouvellesCellules[i][j] = (voisinsVivants == 3) ? 1 : 0;
                }
            }
        }
        grille.cellules = nouvellesCellules;
    }

    int compterCellulesVivantesVoisines(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < grille.lignes && ny >= 0 && ny < grille.colonnes) {
                    count += grille.cellules[nx][ny];
                }
            }
        }
        return count - grille.cellules[x][y];
    }

    void lancementGraphique() {
        int largeurFenetre = grille.colonnes * TAILLE_CELLULE;
        int hauteurFenetre = grille.lignes * TAILLE_CELLULE;

        sf::RenderWindow window(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie - Graphique");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Mettre à jour les cellules
            update();

            // Afficher les cellules dans la fenêtre
            window.clear(sf::Color::Black);
            for (int i = 0; i < grille.lignes; ++i) {
                for (int j = 0; j < grille.colonnes; ++j) {
                    sf::RectangleShape cellule(sf::Vector2f(TAILLE_CELLULE - 1, TAILLE_CELLULE - 1));
                    cellule.setPosition(j * TAILLE_CELLULE, i * TAILLE_CELLULE);

                    if (grille.cellules[i][j] == 1) {
                        cellule.setFillColor(sf::Color::Green); // Cellules vivantes en vert
                    } else {
                        cellule.setFillColor(sf::Color::Black); // Cellules mortes en noir
                    }
                    window.draw(cellule);
                }
            }
            window.display();

            sf::sleep(sf::milliseconds(100)); // Pause pour contrôler la vitesse de l'animation
        }
    }
};

int main() {
    jeuDeLaVie jeu(20, 20); // Grille de taille 20x20

    // Coordonnées des cellules vivantes
    vector<pair<int, int>> cellulesVivantes = {
        {4, 5}, {4, 6}, {4, 7}, {5, 5}, {6, 5},
        {8, 2}, {8, 3}, {8, 4}, {9, 4}, {10, 4},
        {12, 5}, {12, 6}, {12, 7}, {11, 7}, {10, 7},
        {8, 8}, {8, 9}, {8, 10}, {7, 10}, {6, 10}
    };

    jeu.EtatInitial(cellulesVivantes); // Initialisation des cellules vivantes
    jeu.lancementGraphique();         // Lancement du jeu en mode graphique

    return 0;
}
