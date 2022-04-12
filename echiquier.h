/**
* Fichier qui definie la classe de l'echiquier
* \file   echiquier.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#pragma once

#include "piece.h"
#include "position.h"
#include "Couleur.h"
#include "Qobject"
#include <memory>
#include <stdexcept>
#include <iostream>
#include <vector>

#define TAILLE 8

namespace modele
{
	// la ligne suivante evite des erreurs de compilation, puisque la piece n'a pas ete encore compile
	class Piece;

	class Echiquier : public QObject
	{
		Q_OBJECT

	private:
		std::vector<std::shared_ptr<Piece>> pieces;
		Couleur tourCourant = blanc;

	public:
		template<std::derived_from<Piece> T>
		bool ajouterPiece(Position emplacement, Couleur couleur)
		{
			using namespace std;
			bool resultat = false;

			if (trouverPiece(emplacement) == nullptr && Position::estDansTableau(emplacement, TAILLE))
			{
				// on s'assure qu'il n'y a pas plus de roi
				try
				{
					shared_ptr<T> piece = std::make_shared<T>(couleur, emplacement);
					pieces.push_back(piece);

					resultat = true;

					//permet d'afficher la piece
					emit pieceAjouter(dynamic_cast<Piece*>(piece.get()));
				}
				catch(logic_error& erreur)
				{
					cout << erreur.what() << endl;
				}
			}
			return resultat;
		}

		~Echiquier() {
			pieces.erase(pieces.begin(), pieces.end());
		}

		std::shared_ptr<Piece> trouverPiece(Position emplacement);
		std::shared_ptr<Piece> trouverRoi(Couleur couleur);
		std::shared_ptr<Piece> capturerPiece(Position emplacement);

		bool jouerTour(Position emplacement, Position destination);
		bool deplacerPiece(Position emplacement, Position destination);
		bool verifierEchec(Couleur couleur);
	signals:
		void pieceAjouter(Piece* piece);
	};
}
