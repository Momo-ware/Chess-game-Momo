/**
* Fichier qui implemente la piece du Roi
* \file   Roi.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "Roi.h"
#include <iostream>

Roi::Roi(Couleur couleur, Position position) : Piece(couleur, position) {}

bool Roi::deplacer(Position emplacement) 
{
	Position delta = emplacement - position_;

	delta = Position(abs(delta.coordonne.first), abs(delta.coordonne.second));

	return (delta.coordonne.first <= 1) && (delta.coordonne.second <= 1);
}