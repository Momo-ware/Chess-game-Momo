/**
* Fichier qui definie la piece de la dame
* \file   Dame.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#ifndef DAME_H
#define DAME_H

#include "position.h"
#include "piece.h"

class Dame : public Piece
{
public:
	Dame(Couleur couleur, Position position);
	bool deplacer(Position destination) override;
};

#endif
