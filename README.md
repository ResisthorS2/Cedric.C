Le fichier map.txt est le fichier qui définis la map en elle même. 

La première ligne est la hauteur de la carte.
La deuxième ligne est la largeur de la carte

Chaque case dans la matrice qui contient un 0 est une case vide.
Les cases 1 sont des cases de couloir ou il est possible d'y naviguer sans limitations
Les cases 2 annoncent qU'il y a une pièces d'accessible
Les cases 3 sont placés aux intersection
Les cases>3 sont les cases de pièces

COMPILATION:
g++ .\main.cpp .\include\serial\SerialPort.cpp .\src\map.cpp .\src\cell.cpp
./a.exe
