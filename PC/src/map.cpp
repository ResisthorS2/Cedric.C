/*
	S'ASSURER QUE LA HAUTEUR ET LA LARGEUR SOIT BIEN DÉFINIS DANS MAP.TXT
*/

#ifndef MAP_H
#include "map.h"
#endif





#include <fstream>
#include <string>
#include <iostream>
#include <sstream>





Map::Map()
{
	std::ifstream carte("C:/Users/cedri/OneDrive/Bureau/S2/project/Code/Cedric.C/PC/map.txt");
	if (carte.fail()) {
    std::cerr << "Erreur d'ouverture du fichier" << std::endl;
    // Gérer l'erreur ici, peut-être en quittant la fonction ou en lançant une exception
}
	std::string lecture;



	std::getline(carte, lecture);
	//Ramasse la hauteur de la map dans le fichier map
		hauteur = std::stoi(lecture);	

	std::cout<< "Hauteur : " <<hauteur<<std::endl;

	std::getline(carte, lecture);

		largeur = std::stoi(lecture);				//Ramasse la largeur de la map dans les fichiers
	
	std::cout<< "Largeur : " <<largeur<<std::endl;

	// Créer un tableau de pointeurs
	this->cell = new Cell*[largeur];

	// Pour chaque pointeur, créer un tableau
	for(int i = 0; i < largeur; i++) 
	{
		cell[i] = new Cell[hauteur];
	}			//Cree le tableau de cellule de la map

	coordonne = new int*[hauteur];					//Cree le tableau des coordonne de cases de la map
	for (int i = 0; i < hauteur; ++i) 
	{
		coordonne[i] = new int[largeur];
	}

	for(int y=0; y<hauteur; y++)					//Assigne le fichier de map au tableau coordonne
	{
		for(int x=0; x<largeur;x++)
			{
				if(x==largeur-1)
				{
					std::getline(carte, lecture);
				}
				
				else if(x<largeur-1)
				{ 
					std::getline(carte, lecture, '\t');
				}
				coordonne[x][y] = std::stoi(lecture);
				int type = std::stoi(lecture);
				cell[x][y] = Cell(type);
				//cell[x][y].printCell();
				
				//std::cout<<coordonne[i][j]<<" "<<std::endl;
			}
	}

	
	coX=1;
	coY=0;

	for(int i=0;i<maxRoom;i++)
	{	
		cle[i]=0;
	}

}

Map::~Map()
{
	std::cout<<"Destruction de la map"<<std::endl;
	for (int i = 0; i < hauteur; ++i) 
	{
    	delete[] cell[i];
	}

	delete[] cell;
	
	for (int i = 0; i < hauteur; ++i) 
	{
    	delete[] coordonne[i];
	}

	delete[] coordonne;

}

void Map::setCoordonne(int x, int y)
{
	coX=x;

	coY=y;
}

void Map::enterPiece()
{
	coXPiece=coX;
	coYPiece=coY;
	orientationPiece=orientation;
}

void Map::exitPiece()
{
	coX = coXPiece;
	coY = coYPiece;
	orientation = orientationPiece;
}

void Map::printMap()
{
	//system("cls");
	

	
	for(int y=0;y<hauteur;y++)
	{
		for(int i=0;i<3;i++)
		{
			for(int x=0;x<largeur;x++)
			{
				std::cout << cell[x][y].getColor() << cell[x][y].printCellTerminal(i) << cell[x][y].getColor();
				
			}
			std::cout << std::endl;
		}
		
	}
	std::cout << "\x1b[0m" <<std::endl;
}

int Map::getCo_X()
{
	return coX;
}

int Map::getCo_Y()
{
	return coY;
}

int Map::getOrientation()
{
	return orientation;
}

void Map::addCle(int index)
{
	cle[index]=index;
}

void Map::removeCle(int index)
{
	cle[index]=0;
}

bool Map::verifCle(int index)
{
	if(index==cle[index])
	{
		return true;
	} else return false;
}

bool Map::moveUp()
{
	switch (orientation)
	{
	case nord:
		if(coY==0)		//Il est dans le top de la map et ne peux pas monter
		{
			return false;
		}

		if(coordonne[coY-1][coX]==1)	//Il a une case couloir devant lui
		{
			coY--;
			return true;
		}

		if(coordonne[coY-1][coX]==3)	//Il a une case intersection devant lui
		{
			if(coY==1)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY-2][coX]==1||coordonne[coY-2][coX]==2)	//Il y a une case couloir devant la case interception
			{
				coY--;
				coY--;
				return true;
			}

			if(coordonne[coY-2][coX]>3)	//Il y a une case couloir devant la case interception
			{
				if(verifCle(coordonne[coY-2][coX])==true)
				{
				enterPiece();
				coY--;
				coY--;
				return true;
				}
			}


			if(coordonne[coY-2][coX]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}			
			return true;
		}
		return false;
		break;


	case sud:
		if(coY==(hauteur-1))		//Il est dans le bas de la map et ne peux pas descendre
		{
			return false;
		}

		if(coordonne[coY+1][coX]==1||coordonne[coY+1][coX]==2)	//Il a une case couloir devant lui
		{
			coY++;
			return true;
		}

		if(coordonne[coY+1][coX]==3)	//Il a une case intersection devant lui
		{
			if(coY==hauteur-2)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY+2][coX]==1||coordonne[coY+2][coX]==2)	//Il y a une case couloir devant la case interception
			{
				coY++;
				coY++;
				return true;
			}
			if(coordonne[coY+2][coX]>3)	//Il y a une case couloir devant la case interception
			{
				if(verifCle(coordonne[coY+2][coX])==true)
				{
				enterPiece();
				coY++;
				coY++;
				return true;
				}
			}
			if(coordonne[coY+2][coX]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}
		}		
		return false;
		break;

	case est:
		if(coX==(largeur-1))		//Il est tout à droite de la map de la map et ne peux pas monter
		{
			return false;
		}
		
		if(coordonne[coY][coX+1]==1||coordonne[coY][coX+1]==2)	//Il a une case couloir devant lui
		{
			std::cout<<"pre"<<coX;
			coX++;
			std::cout<<"post"<<coX<<std::endl;
			return true;
		}

		if(coordonne[coY][coX+1]==3)	//Il a une case intersection devant lui
		{
			if(coX==largeur-2)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY][coX+2]==1||coordonne[coY][coX+2]==2)	//Il y a une case couloir devant la case interception
			{
				coX++;
				coX++;
				return true;
			}

			if(coordonne[coY][coX+2]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}			

			if(coordonne[coY][coX+2]>3)
			{
				if(verifCle(coordonne[coY][coX+2])==true)
				{
					enterPiece();
					coX++;
					coX++;
					return true;
				}	else return false;
			}
		}
		return false;
		break;
		
	case ouest:

		if(coX==0)		//Il est tout à gauche de la map de la map et ne peux pas monter
		{
			return false;
		}

		if(coordonne[coY][coX-1]==1||coordonne[coY][coX-1]==2)	//Il a une case couloir devant lui
		{
			coX--;
			return true;
		}

		if(coordonne[coY][coX-1]==3)	//Il a une case intersection devant lui
		{
			if(coX==1)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY][coX-2]==1||coordonne[coY][coX-2]==2)	//Il y a une case couloir devant la case interception
			{
				coX--;
				coX--;
				return true;
			}
			if(coordonne[coY][coX-2]>2)
			{
				if(verifCle(coordonne[coY][coX-2])==true)
				{
					enterPiece();
					coX--;
					coX--;
					return true;
				} else return false;
			}
			if(coordonne[coY][coX-2]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}			
		}
		return true;
		break;				

	default:
		return false;
		break;
	}
	return false;

}

bool Map::move180()
{
	switch (orientation)
	{
	case nord:
		orientation=sud;
		return true;
		break;

	case est:
		orientation=ouest;
		return true;
		break;

	case sud:
		orientation=nord;
		return true;
	case ouest:
		orientation=est;
		return true;

	default:
		return false;
		break;
	}
	return false;
}

bool Map::moveRight()
{

		switch (orientation)
		{
		case nord:

			if(coordonne[coY-1][coX]==2)				//si il y a une piece
			{
				if(coX==(largeur-1))					//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}
				if(verifCle(coordonne[coY-1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY--;
					coX++;
					orientation = est;
					return true;
				} else return false;
			} else if(coordonne[coY-1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == largeur-1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX+1]))	
						{
							enterPiece();
							coY--;
							coX++;
							orientation = est;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX+1]==1||coordonne[coY-1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX++;
						orientation = est;
						return true;
					}

				} else return false;

			break;

		case sud:

			if(coordonne[coY+1][coX]==2)				//si il y a une piece
			{
				if((coX)==0)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX-1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX--;
					orientation = ouest;
					return true;
				} else return false;
			} else if(coordonne[coY+1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX-1]))	
						{
							enterPiece();
							coY++;
							coX--;
							orientation = ouest;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX-1]==1||coordonne[coY+1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX--;
						orientation = ouest;
						return true;
					}

				} else return false;

			break;

		case est:

			if(coordonne[coY][coX+1]==2)				//si il y a une piece
			{
				if(coY== (hauteur -1))							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX++;
					orientation = sud;
					return true;
				} else return false;
			} else if(coordonne[coY][coX+1]==3) 		//Arrive à une intersection
				{
					if(coY == hauteur-1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX+1]))	
						{
							enterPiece();
							coY++;
							coX++;
							orientation = sud;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX+1]==1||coordonne[coY+1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX++;
						orientation = sud;
						return true;
					}

				} else return false;

			break;
		
		case ouest:

			if(coordonne[coY][coX-1]==2)				//si il y a une piece
			{
				if(coY== 0)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY-1][coX-1]))	//Verifie s'il peut rentrer
				{
					coY--;
					coX--;
					orientation = nord;
					return true;
				} else return false;
			} else if(coordonne[coY][coX-1]==3) 		//Arrive à une intersection
				{
					if(coY == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si il peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX-1]))	
						{
							coY--;
							coX--;
							orientation = nord;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX-1]==1||coordonne[coY-1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX--;
						orientation = nord;
						return true;
					}

				} else return false;

			break;

		default:
		return false;
			break;
		}	

	return false;
}

bool Map::moveLeft()
{
		switch (orientation)
		{
		case nord:

			if(coordonne[coY-1][coX]==2)				//si il y a une piece
			{
				if(coX==0)					//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}
				if(verifCle(coordonne[coY-1][coX-1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY--;
					coX--;
					orientation = ouest;
					return true;
				} else return false;
			} else if(coordonne[coY-1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX-1]))	
						{
							enterPiece();
							coY--;
							coX--;
							orientation = ouest;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX-1]==1||coordonne[coY-1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX--;
						orientation = ouest;
						return true;
					}

				} else return false;

			break;

		case sud:

			if(coordonne[coY+1][coX]==2)				//si il y a une piece
			{
				if((coX)== largeur - 1)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX++;
					orientation = est;
					return true;
				} else return false;
			} else if(coordonne[coY+1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == largeur - 1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX+1]))	
						{
							enterPiece();
							coY++;
							coX++;
							orientation = est;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX+1]==1||coordonne[coY+1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX++;
						orientation = est;
						return true;
					}

				} else return false;

			break;

		case est:

			if(coordonne[coY][coX+1]==2)				//si il y a une piece
			{
				if(coY== 0)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY-1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY--;
					coX++;
					orientation = nord;
					return true;
				} else return false;
			} else if(coordonne[coY][coX+1]==3) 		//Arrive à une intersection
				{
					if(coY == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX+1]))	
						{
							enterPiece();
							coY--;
							coX++;
							orientation = nord;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX+1]==1||coordonne[coY-1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX++;
						orientation = nord;
						return true;
					}

				} else return false;

			break;
		
		case ouest:

			if(coordonne[coY][coX-1]==2)				//si il y a une piece
			{
				if(coY== hauteur - 1)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX-1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX--;
					orientation = sud;
					return true;
				} else return false;
			} else if(coordonne[coY][coX-1]==3) 		//Arrive à une intersection
				{
					if(coY == hauteur - 1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si il peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX-1]))	
						{
							enterPiece();
							coY++;
							coX--;
							orientation = sud;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX-1]==1||coordonne[coY+1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX--;
						orientation = sud;
						return true;
					}

				} else return false;

			break;
			

		default:
		return false;
			break;
		}	
	
	return false;
}

void Map::setOrientation(int SETorientation)
{
	orientation=SETorientation;
}

void Map::updateMap()
{
	
	for(int y=0;y<this->hauteur;y++)
	{
		for(int x=0;x<this->largeur;x++)
		{
			//std::cout<<"coordonne["<< x << "]["<<y<<"]"<<coordonne[x][y]<<std::endl;
			cell[x][y].setImageCell(coordonne[x][y], NONE);
		}
	}
	
	std::cout<<"coordonne[coX][coY]"<<getCo_X()<<getCo_Y()<<std::endl;
	cell[getCo_X()][getCo_Y()].setImageCell(cell[getCo_X()][getCo_Y()].getType(), orientation); //mettre l'orientation dans le bonhomme
	
}

/*Cell* Map::operator[](int index)
{
	return cell[index];
}*/

/*
int main()
{
	Map map;
	map.printMap();
	map.setCoordonne(1,0);
	map.setOrientation(est);
	map.addCle(4);
}
*/