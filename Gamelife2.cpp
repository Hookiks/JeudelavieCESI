#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <utility>

using namespace std;

class Grille{
    public:
        int lignes;
        int colonnes;
        vector<vector<int>> cellules;
        
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
        

//test commentaire 
};