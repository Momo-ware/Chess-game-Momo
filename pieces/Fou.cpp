/**
* Fichier qui implemente la piece du fou
* \file   Fou.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "Fou.h"
#include <iostream>
#include <vector>
using namespace std;

Fou::Fou(Couleur couleur, Position position) : Piece(couleur, position) {}

bool Fou::deplacer(Position destination)
{
	Position delta = destination - position_;

	delta = Position(abs(delta.coordonne.first), abs(delta.coordonne.second));

	return delta.coordonne.first == delta.coordonne.second;
}
