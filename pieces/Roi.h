/**
* Fichier qui definie la piece du Roi
* \file   Roi.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#ifndef ROI_H
#define ROI_H

#include "piece.h"

#pragma once
class Roi : public Piece
{
public:
	Roi(Couleur couleur, Position position);
	bool deplacer(Position emplacement) override;
};

#endif
