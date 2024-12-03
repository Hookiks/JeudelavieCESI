#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <utility>
#

using namespace std; 

class Grille{
    public:
        int lignes;
        int colonnes;
        vector<vector<int>> cellules; //Ca définit une matrice comme sur python si on avait fait cellules = [[0]*colonnes]*lignes
        
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

class jeuDeLaVie{
    private:
        Grille grille;
        
    public:
        jeuDeLaVie(int lignes, int colonnes) : grille({lignes, colonnes, vector<vector<int>>(lignes, vector<int>(colonnes, 0))}) {} //CHAT GPTMieux étudier pour mieux comprendre pcq je capte pas 
        
        void EtatInitial(vector<pair<int, int>>& cellulesVivantes) { //--> C'est un vecteur de pair qui contient les coordonnées des cellules vivantes CHAT GPT
            for (auto& cellule : cellulesVivantes) {
                int x = cellule.first; //--> x est la première valeur de la pair
                int y = cellule.second; //--> y est la deuxième valeur de la pair
                if (x >= 0 && x < grille.lignes && y >= 0 && y < grille.colonnes) { //--> on utilise l'objet grille pour les lignes et colonnes qui sont deja dans la classe Grille
                    grille.cellules[x][y] = 1;
                }
            }
        }
        
        void print(){
            system("cls"); //--> C'est CLS sur windows et sur mac c'est clear au cas ou Amin 
            for (auto& ligne : grille.cellules) {
                for (auto& cellule : ligne) {
                    cout << (cellule ? "O" : " "); //--> O si vivant et " " si mort 
                    // cout << (cellule ? "1" : "0"); //--> 1 si vivant et 0 si mort
                }
                cout << endl;
            }
        }
        
        void update() {
            
            vector<vector<int>> nouvellesCellules = grille.cellules;
            for (int i = 0; i < grille.lignes; ++i) {
                for (int j = 0; j < grille.colonnes; ++j) {
                    int cellulesVivantesVoisines = compterCellulesVivantesVoisines(i, j);
                    if (grille.cellules[i][j] == 1) {
                        nouvellesCellules[i][j] = (cellulesVivantesVoisines == 2 || cellulesVivantesVoisines == 3) ? 1 : 0;
                    } else {
                        nouvellesCellules[i][j] = (cellulesVivantesVoisines == 3) ? 1 : 0;
                    }
                }
            }
            grille.cellules = nouvellesCellules;
        }

        int compterCellulesVivantesVoisines(int x, int y)  {
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

        void lancement(int iterations, int delai) {
            for (int i = 0; i < iterations; ++i) {
                print();
                update();
                if (!grille.VerifierCellulesVivante()) {
                    cout << "Toutes les cellules sont mortes" << endl;
                    break;
                }
                // this_thread::sleep_for(std::chrono::milliseconds(delai));
                
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
    jeu.lancement(500, 10000); // Lancement du jeu avec 500 itérations et un délai de 600 ms
    return 0;
};

// int main() {
//     jeuDeLaVie jeu(1000, 1000);

//     vector<pair<int, int>> test = {                                                            //Chat GPT
//         {5, 1}, {5, 2}, {6, 1}, {6, 2},
//         {5, 11}, {6, 11}, {7, 11}, {4, 12}, {8, 12}, {3, 13}, {9, 13}, {3, 14}, {9, 14},
//         {6, 15}, {4, 16}, {8, 16}, {5, 17}, {6, 17}, {7, 17}, {6, 18},
//         {3, 21}, {4, 21}, {5, 21}, {3, 22}, {4, 22}, {5, 22}, {2, 23}, {6, 23},
//         {1, 25}, {2, 25}, {6, 25}, {7, 25},
//         {3, 35}, {4, 35}, {3, 36}, {4, 36}
//     };

//     jeu.EtatInitial(test);
//     jeu.lancement(500, 600);
//     return 0;
// };

// int main() {
//     jeuDeLaVie jeu(50, 50); 

//     // Coordonnées des cellules vivantes
//     vector<pair<int, int>> cellulesVivantes = {
//         {495, 500}, {495, 501}, {495, 502}, {496, 500}, {497, 500},   
//         {500, 495}, {501, 495}, {502, 495}, {502, 496}, {502, 497},   
//         {505, 500}, {505, 501}, {505, 502}, {504, 502}, {503, 502},   
//         {500, 505}, {501, 505}, {502, 505}, {502, 504}, {502, 503}    
//     };

//     jeu.EtatInitial(cellulesVivantes); // Initialisation des cellules vivantes
//     jeu.lancement(10000, 50); // Lancement du jeu avec 10 000 itérations et un délai de 50 ms
//     return 0;
// };