#include <iostream>


#define CELL_H



#define LOCKED 1
#define UNLOCKED 0


#define VIDE 0
#define COULOIR 1
#define CLASSE_LOCKED 2
#define CLASSE_UNLOCKED 3

const int NONE=-1;
const int nord=0;
const int sud=1;
const int est=2;
const int ouest=3;
const int maxRoom=20;




struct Coordinate
{
    int x;
    int y;
};
typedef Coordinate Coordinate;

class Cell
{
    public:
        Cell();
        Cell(int type);
        ~Cell();
        /** @brief retourne le type de la Cell @return int{vide = 0, couloir = 1, classe = 2,}*/
        int getType();
        /** @brief retourne un int selon si la Cell est vérouillée @return 0 = UNLOCKED, 1 = LOCKED */
        void setType(int type);
        void setImageCell(int type, int orientation = NONE);
        std::string printCellTerminal(int line);
        void printCell();
        
        std::string imageCell[3][3];
        std::string getColor();
        

    private:
        int type;
        Coordinate coordonne;
        std::string typeColor;
        //Piece piece;
        //Minigame minigame[];
};
