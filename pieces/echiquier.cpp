/**
* Fichier qui implemente la classe de l'echiquier
* \file   echiquier.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "echiquier.h"
#include "position.h"

shared_ptr<Piece> Echiquier::trouverPiece(Position emplacement)
{
	shared_ptr<Piece> resultat;

	if (Position::estDansTableau(emplacement, TAILLE))
	{
		resultat = tableau[emplacement.coordonne.first][emplacement.coordonne.second];
	}

	return resultat;
}

bool Echiquier::deplacerPiece(Position emplacement, Position destination)
{
	bool resultat = false;

	if(Position::estDansTableau(emplacement, TAILLE) && Position::estDansTableau(destination, TAILLE))
	{
		shared_ptr<Piece> piece = trouverPiece(emplacement);

		if (piece != nullptr && piece->deplacer(destination))
		{
			piece->position_ = destination;
			resultat = true;
		}
	}

	return resultat;
}