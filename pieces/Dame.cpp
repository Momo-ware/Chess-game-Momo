/**
* Fichier qui implemente la piece de la dame
* \file   Dame.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "Dame.h"
#include <vector>
#include <iostream>

Dame::Dame(Couleur couleur, Position position) : Piece(couleur, position) {}

bool Dame::deplacer(Position destination)
{
	Position delta = destination - position_;

	delta = Position(abs(delta.coordonne.first), abs(delta.coordonne.second));

	return (delta.coordonne.first == delta.coordonne.second) ||
			(delta.coordonne.first == 0) ||
			(delta.coordonne.second == 0);
}
