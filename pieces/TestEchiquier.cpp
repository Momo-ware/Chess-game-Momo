/**
* Fichier qui contient les test unitaires pour verifier le mouvement des pieces
* \file   TestEchiquier.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 7 avril 2021
*/

#include "echiquier.h"
#include "Roi.h"
#include "Dame.h"
#include "Fou.h"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST
TEST(Echiquier, ajouterPiece)
{
	Echiquier echiquier;

	Position position(0, 1);
	EXPECT_TRUE(echiquier.ajouterPiece<Roi>(position, blanc));

	position = Position(-1, 0);
	EXPECT_FALSE(echiquier.ajouterPiece<Roi>(position, blanc));

	position = Position(0, 2);
	EXPECT_TRUE(echiquier.ajouterPiece<Dame>(position, blanc));
	
	position = Position(-1, 0);
	EXPECT_FALSE(echiquier.ajouterPiece<Dame>(position, blanc));

	position = Position(0, 3);
	EXPECT_TRUE(echiquier.ajouterPiece<Fou>(position, blanc));
	
	position = Position(-1, 0);
	EXPECT_FALSE(echiquier.ajouterPiece<Fou>(position, blanc));
}

TEST(Echiquier, trouverPiece)
{
	Echiquier echiquier;
	shared_ptr<Piece> pointeurVide;

	Position position(0, 1);
	echiquier.ajouterPiece<Roi>(position, blanc);

	EXPECT_NE(pointeurVide, echiquier.trouverPiece(position));

	position = Position(1, 1);
	EXPECT_EQ(pointeurVide, echiquier.trouverPiece(position));
}

TEST(Roi, mouvement) {
	Echiquier echiquier;
	Position position(0, 1);

	echiquier.ajouterPiece<Roi>(position, blanc);

	Position deplacement(0, 0);
	EXPECT_TRUE(echiquier.deplacerPiece(position, deplacement));

	deplacement = Position(0, 5);
	EXPECT_FALSE(echiquier.deplacerPiece(position, deplacement));

	deplacement = Position(0, -1);
	EXPECT_FALSE(echiquier.deplacerPiece(position, deplacement));
}

TEST(Dame, mouvement) {
	Echiquier echiquier;
	Position position(0, 1);

	echiquier.ajouterPiece<Dame>(position, blanc);

	Position deplacement(0, 7);
	EXPECT_TRUE(echiquier.deplacerPiece(position, deplacement));

	deplacement = Position(7, 0);
	EXPECT_TRUE(echiquier.deplacerPiece(position, deplacement));

	deplacement = Position(1, 5);
	EXPECT_FALSE(echiquier.deplacerPiece(position, deplacement));

	deplacement = Position(0, -1);
	EXPECT_FALSE(echiquier.deplacerPiece(position, deplacement));
}

TEST(Fou, mouvement) {
	Echiquier echiquier;
	Position position(0, 1);

	echiquier.ajouterPiece<Fou>(position, blanc);

	Position deplacement(2, 3);
	EXPECT_TRUE(echiquier.deplacerPiece(position, deplacement));

	deplacement = Position(3, 0);
	EXPECT_FALSE(echiquier.deplacerPiece(position, deplacement));

	deplacement = Position(0, -1);
	EXPECT_FALSE(echiquier.deplacerPiece(position, deplacement));
}
#endif