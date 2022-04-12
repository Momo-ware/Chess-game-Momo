/**
* Fichier qui implemente la classe de la position 
* \file   position.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "position.h"

Position::Position(int x, int y) : coordonne(x, y) {}

Position Position::operator+(const Position& pos) const
{
	return Position(coordonne.first + pos.coordonne.first, coordonne.second + pos.coordonne.second);
}

Position Position::operator-(const Position& pos) const
{
	return Position(coordonne.first - pos.coordonne.first, coordonne.second - pos.coordonne.second);
}

bool Position::estDansTableau(Position position, int taille)
{
	return (position.coordonne.first >= 0) && (position.coordonne.first <= taille - 1)
		&& (position.coordonne.second >= 0) && (position.coordonne.second <= taille - 1);
}