/**
* Fichier qui definie la piece du fou
* \file   Fou.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#ifndef FOU_H
#define FOU_H

#include "piece.h"

class Fou : public Piece
{
public:
	Fou(Couleur couleur, Position position);
	bool deplacer( Position destination) override;
};

#endif
