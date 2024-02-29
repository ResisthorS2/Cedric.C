/*
	ATTENTIONS SI + DE 20 ROOM NE PAS OUBLIER D'AUGMENTER MAXROOM
*/
#ifndef MAP_H
#define MAP_H

#include <vector>

const int nord=0;
const int sud=1;
const int est=2;
const int ouest=3;
const int maxRoom=20;

class Map
{
public:
	Map();
	~Map();
	void setCoordonne(int x, int y);
	void setOrientation(int orientation);
	int getCoordonneX();			//Donne la coordonne X
	int getCoordonneY();			//Donne la coordonne Y
	int getOrientation();			//Donne l'orientation
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();				
	void printMap();				//Affiche la map
	void addCle(int index);			//Permet d'ajouter l'acces à une piece
	void removeCle(int index);		//Permet d'enlever l'acces à une piece
	bool verifCle(int index);		//Permet de vérifier si la pièce est accessible
	void enterPiece();				//Sert à mes fonction de mouvement et exitPiece
	void exitPiece();				//Sert à sortir à la position précedente avant de rentrer dans une pièce. Met aussi la bonne orientation
private:
	int coXPiece;
	int coYPiece;
	int orientationPiece;
	int orientation; 
	int largeur;
	int hauteur;
	int **coordonne;				//Tableau de coordonne coordonne[Y][X]
	int coX;
	int coY;
	int cle[maxRoom];				//La cste maxROOM doit être changer si on fait plus de room que celle-si
};



#endif