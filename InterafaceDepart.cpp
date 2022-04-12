#include "InterfaceDepart.h"
#include  <iostream>
#include <QSizePolicy>

using namespace std;

//creation d une interface qui permet de commencer une partie
void interface::InterfaceDepart::demarrerPartie()
{
	fenetreDemarrage = new QWidget;
	fenetreDemarrage->setWindowTitle("Menu de d�part");

	menuDemarrage = new QHBoxLayout;

	butonsconfiguration = new QPushButton(" ");
	butonsconfiguration->setMinimumSize(QSize(200, 100));
	butonsconfiguration->setText("Nouvelle partie");

	connect(butonsconfiguration, &QPushButton::clicked, this, &InterfaceDepart::selectionDifficulte);

	menuDemarrage->addWidget(butonsconfiguration);

	fenetreDemarrage->setLayout(menuDemarrage);
	fenetreDemarrage->show();
	fenetreDemarrage->setFixedSize(fenetreDemarrage->size());
}

//creation d une interface qui permet de choisir la difficult�
void interface::InterfaceDepart::selectionDifficulte()
{
	fenetreDemarrage->close();

	fenetreConf = new QWidget;
	fenetreConf->setWindowTitle("Niveau de difficulte");

	initialiserBouttonsPosition();

	menuDifficulte = new QHBoxLayout;

	for(int i = 0; i < NOMBRE_DE_DIFFICULTE; i++)
	{
		menuDifficulte->addWidget(bouttonsConf[i]);
	}

	fenetreConf->setLayout(menuDifficulte);

	fenetreConf->show();

	fenetreConf->setFixedSize(fenetreConf->size());
}

//Ceci permet de faire r�apparaitre l' interface qui permet de choisir la difficult�
void interface::InterfaceDepart::montrerInterface()
{
	partieGui = nullptr;
	fenetreConf->show();
}

//Ceci permet de cr�er l'�chequier quand un des bouttons qui choisit la difficult� a �t� cliqu�.
void interface::InterfaceDepart::creationEchiquier(int configuration)
{
	using namespace interface;

	partieGui = new FenetreGui(configuration);
	connect(partieGui, &FenetreGui::afficherAutreFenetre, this, &InterfaceDepart::montrerInterface);
	fenetreConf->hide();
}

//Ceci permet de cr�er les 3 bouttons qui permettent de choisir la difficult� et les connecter au slot qui permettra de cr�er l'�chiquier.
void interface::InterfaceDepart::initialiserBouttonsPosition()
{
	using namespace interface;

	for (int i = 0; i < NOMBRE_DE_DIFFICULTE; i++)
	{
		bouttonsConf[i] = new QPushButton(" ");
		bouttonsConf[i]->setMinimumSize(QSize(200, 100));

		connect(bouttonsConf[i], &QPushButton::clicked, this, [=]() { creationEchiquier(i); });
	}

	bouttonsConf[0]->setText("Facile");
	bouttonsConf[1]->setText("Moyen");
	bouttonsConf[2]->setText("Impossible");
}
