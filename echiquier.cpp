/**
* Fichier qui implemente la classe de l'echiquier
* \file   echiquier.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "echiquier.h"
#include "position.h"
#include "Roi.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;

//permet de trouver une piece selon la position
shared_ptr<modele::Piece> modele::Echiquier::trouverPiece(Position emplacement)
{
	shared_ptr<Piece> resultat;

	if (Position::estDansTableau(emplacement, TAILLE))
	{
		for(shared_ptr<Piece> piece : pieces)
		{
			if(piece->position_ == emplacement)
			{
				resultat = piece;
			}
		}
	}

	return resultat;
}

// permet de deplacer les pieces et de capturer des pieces
bool modele::Echiquier::deplacerPiece(Position emplacement, Position destination)
{
	bool resultat = false;

	// s'assure que les positions se trouve dans le tableau
	if (Position::estDansTableau(emplacement, TAILLE) && Position::estDansTableau(destination, TAILLE) && emplacement != destination)
	{
		shared_ptr<Piece> piece = trouverPiece(emplacement);

		if (piece != nullptr && piece->deplacer(destination, this))
		{		
			shared_ptr<Piece> pieceCapture = capturerPiece(destination);
			piece->position_ = destination;
			
			if(verifierEchec(piece->couleur_) || (pieceCapture != nullptr && pieceCapture->couleur_ == piece->couleur_))
			{
				// replace la piece qui a ete capture si il y a un echec
				if(pieceCapture != nullptr )
				{
					pieces.push_back(pieceCapture);
				}

				// remet la piece a sa position initial
				piece->position_ = emplacement;
			}
			else
			{
				resultat = true;
			}
		}
	}

	return resultat;
}

// permet de verifier si un roi est en echec
bool modele::Echiquier::verifierEchec(Couleur couleur)
{
	bool resultat = false;

	shared_ptr<Piece> roi = trouverRoi(couleur);

	if(roi != nullptr)
	{
		for (shared_ptr<Piece> piece : pieces)
		{
			// verifie pour voire si une piece de la couleur oppose peut atteindre le roi
			if (piece->couleur_ != roi->couleur_ && piece->deplacer(roi->position_ , this))
			{
				resultat = true;
			}
		}
	}

	return resultat;
}

// permet de trouver le roi d'une certaine couleur
shared_ptr<modele::Piece> modele::Echiquier::trouverRoi(Couleur couleur)
{
	shared_ptr<Piece> roi;

	for(shared_ptr<Piece> piece : pieces)
	{
		// verifie si la piece est le roi de la bonne couleur
		if(dynamic_cast<Roi*>(piece.get()) && piece->couleur_ == couleur)
		{
			roi = piece;
			break;
		}
	}

	return roi;
}

// La fonction retourne la piece qui as ete capturer pour la replacer en cas d'echec
shared_ptr<modele::Piece> modele::Echiquier::capturerPiece(Position emplacement)
{
	shared_ptr<Piece> piece = trouverPiece(emplacement);

	//retire la piece trouve du tableau
	auto it = remove_if(pieces.begin(), pieces.end(), [piece](shared_ptr<Piece> p) {return p == piece; });
	pieces.erase(it, pieces.end());

	return piece;
}

// La fonction retourne si le tour a ete jouer
bool modele::Echiquier::jouerTour(Position emplacement, Position destination)
{
	shared_ptr<Piece> piece = trouverPiece(emplacement);
	bool resultat = false;

	// verifie si la piece selectionne est de la bonne couleur
	if (piece != nullptr && piece->couleur_ == tourCourant) 
	{
		resultat = deplacerPiece(emplacement, destination);
	}
	else if(piece != nullptr)
	{
		string couleurCourante = tourCourant == blanc ? "blancs" : "noirs";
		cout << "C'est le tour des " << couleurCourante << endl;
	}

	// verifie si le tour as reussi
	if(resultat)
	{
		// ceci change la couleur pour le tour courant
		tourCourant = (Couleur)(((int)tourCourant + 1) % 2);
	}

	return resultat;
}