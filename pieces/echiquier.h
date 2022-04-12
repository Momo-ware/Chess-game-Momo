/**
* Fichier qui definie la classe de l'echiquier
* \file   echiquier.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "piece.h"
#include "position.h"

#include <memory>

#define TAILLE 8

#pragma once
class Echiquier
{
private:
	shared_ptr<Piece> tableau[TAILLE][TAILLE];

public:
	shared_ptr<Piece> trouverPiece(Position emplacement);
	template<derived_from<Piece> T>
	bool ajouterPiece(Position emplacement, Couleur couleur)
	{
		if(trouverPiece(emplacement) == nullptr && Position::estDansTableau(emplacement, TAILLE))
		{
			tableau[emplacement.coordonne.first][emplacement.coordonne.second] = make_shared<T>(couleur, emplacement);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool deplacerPiece(Position emplacement, Position destination);
};

