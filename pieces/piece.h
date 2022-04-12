/**
* Fichier qui definie la la classe de base pour toute les pieces
* \file   piece.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#ifndef PIECE_H
#define PIECE_H

#include "position.h"

enum Couleur
{
	blanc,
	noir
};

class Piece
{
public:
	Piece(Couleur couleur, Position position) : couleur_(couleur), position_(position) {}
	virtual bool deplacer(Position destination) = 0;
	virtual ~Piece() = default;

	Couleur couleur_;
	Position position_;
};

#endif // !PIECE_H
