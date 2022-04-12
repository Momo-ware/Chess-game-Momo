/**
* Fichier qui definie la classe position qui est utilise pour representer les position sur l'echiquier
* \file   position.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include <utility>

using namespace std;
#pragma once
class Position
{
public:
	pair<int, int> coordonne;
	Position(int x, int y);

	Position operator+(const Position &pos) const;
	Position operator-(const Position &pos) const;
	static bool estDansTableau(Position position, int taille);
};

