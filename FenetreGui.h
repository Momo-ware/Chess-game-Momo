/**
* Fichier qui definie les methodes necessaires pour l'interface graphique
* \file   FenetreGUI.h
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 14 avril 2021
*/

#pragma once

#include "QObject"
#include "QApplication"
#include "QWidget"
#include "QPushButton"
#include "QGridLayout"
#include "qmainwindow.h"
#include "echiquier.h"
#include "Roi.h"
#include "QMessageBox"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace interface
{
	class FenetreGui : public QMainWindow
	{
		Q_OBJECT
	public:
		FenetreGui(int configuration) {
			echiquier = new modele::Echiquier();

			faireConnection();
			configuration_ = configuration;
			
			setupGui();
		};
		
		void initialisationDesPieces();
		void messageAlert(std::string message);

		modele::Position trouverPostionBouttons(QPushButton* PositionDepart);

		~FenetreGui() {
			if (finDePartie == true)
			{
				for (int i = 0; i < TAILLE; i++)
				{
					for (int j = 0; j < TAILLE; j++)
					{
						delete bouttons[i][j];
					}
				}
					
				delete echiquier;
				while (!enregistrementDeplacement.empty())
				{
					delete enregistrementDeplacement.back();

					enregistrementDeplacement.pop_back();
				}

			}

			delete boite;
			delete boite2;
			delete fenetreJeu;
		}

	public slots:
		void ajouterNouvellePiece(modele::Piece* piece);
		void realiserDeplacement();
		void enregistrerDeplacement();
		void recommencerUnePartie();
	signals:
		void afficherAutreFenetre();

	private:
		void initialisationGrilleBoutons();
		void setupGui();
		void faireConnection();

		QPushButton* bouttons[TAILLE][TAILLE];
		vector<QPushButton*> enregistrementDeplacement;
		
		modele::Echiquier* echiquier;
		
		bool finDePartie = true;
		
		QBoxLayout* boite;
		QBoxLayout* boite2;
		QWidget* fenetreJeu;
		
		int configuration_;
		
		// les strings represente les pieces des positions initials 
		// le premier caractere represente quel piece initialise
		// le deuxieme caractere represente la couleur de la piece
		// les deux derniers caractere represente la position
		vector<string> configurationDesDifficulte_ = { "rb47 rn40 db37 dn30 fb27 fb57 fn20 fn50", 
												       "rb47 rn40 db37 dn30 fb27 fb57 fn20 fn60 fn10 fn70 fn00 fn50",
												       "rb47 rn40 dn30 fn20 fn60 fn10 fn70 fn00 fn50" };
	};
}
