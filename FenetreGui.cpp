/**
* Fichier qui implemente les methodes necessaires pour l'interface graphique
* \file   FenetreGUI.cpp
* \author Galibois et Ben Faras
* \date   9 mai 2021
* Créé le 14 avril 2021
*/

#include "FenetreGui.h"
#include "Dame.h"
#include "Fou.h"

#include <string>
#include <iostream>

#define DEBUT_NOM_CLASS 14

using namespace std;

//création de l'interface qui représente l'échiquier avec les 64 cases et les pieces.

void interface::FenetreGui::setupGui()
{
    fenetreJeu = new QWidget();
    fenetreJeu->setWindowTitle("Jeu Echec");

    initialisationGrilleBoutons();
    initialisationDesPieces();

    QGridLayout* gridLayout = new QGridLayout;
    for (int range = 0; range < TAILLE; range++) 
    {
        for (int colonne = 0; colonne < TAILLE; colonne++) 
        {
            gridLayout->addWidget(bouttons[colonne][range], 0 + range, colonne);
            gridLayout->setSpacing(0);
        }
    }

    // s'assure que l'echiquier ne change pas de taille
    boite = new  QBoxLayout(QBoxLayout::Direction(2));
    boite->addLayout(gridLayout);
    boite->setSpacing(0);

    boite2 = new  QBoxLayout(QBoxLayout::Direction(1));
    boite2->addLayout(boite);
    boite2->setContentsMargins(1, 1, 1, 1);

    QBoxLayout* boite3 = new  QBoxLayout(QBoxLayout::Direction(2));

    QPushButton* bouttonsConf[1];

    bouttonsConf[0] = new QPushButton(" ");
    bouttonsConf[0]->setMinimumSize(QSize(200, 100));

    bouttonsConf[0]->setText("Changer Difficulté");
    connect(bouttonsConf[0], &QPushButton::clicked, this, &FenetreGui::recommencerUnePartie);

    boite3->addWidget(bouttonsConf[0]);

    boite2->addLayout(boite3);
    fenetreJeu->setLayout(boite2);
    fenetreJeu->show();

    fenetreJeu->setFixedSize(fenetreJeu->size());
}

//Permet de montrer l 'interface qui change de difficuluté qui a seulement été caché dernierement.
void interface::FenetreGui::recommencerUnePartie()
{
    emit afficherAutreFenetre();

    fenetreJeu->close();
    delete this;
}

//Creation des 64 bouttons et la connections de ces bouttons.
void interface::FenetreGui::initialisationGrilleBoutons()
{
    const QSize tailleboutton = QSize(100, 100);

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++) 
        {
            // cree un bouton 
            bouttons[i][j] = new QPushButton(" ");
            bouttons[i][j]->setFixedSize(tailleboutton);
            bouttons[i][j]->setFlat(true);

            //determine la couleur du bouton
            if ((i + j) % 2 == 0)
            {
                QPalette pal = bouttons[i][j]->palette();
                pal.setColor(QPalette::Button, QColor(Qt::darkGreen));

                bouttons[i][j]->setAutoFillBackground(true);
                bouttons[i][j]->setPalette(pal);
                bouttons[i][j]->update();
            }

            // connect les evenements lie au bouton
            connect(bouttons[i][j], &QPushButton::clicked, this, &FenetreGui::enregistrerDeplacement);
            connect(bouttons[i][j], &QPushButton::clicked, this, &FenetreGui::realiserDeplacement);
        }
    }
}

//Message qui avertie lorsqu'un mouvement est non voulu et fait apparaitre une fenetre.
void interface::FenetreGui::messageAlert(string message)
{
    QMessageBox avertissementEchec;

    avertissementEchec.setText(QString::fromStdString(message));
    avertissementEchec.exec();
}

// fait le connection entre le modele et l'interface
void interface::FenetreGui::faireConnection()
{
    connect(echiquier, &modele::Echiquier::pieceAjouter, this, &FenetreGui::ajouterNouvellePiece);
}

modele::Position  interface::FenetreGui::trouverPostionBouttons(QPushButton* boutton)
{
    using namespace modele;

    Position position(-1, -1);

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (bouttons[i][j] == boutton)
            {
               position = Position(i, j);
            }
        }
    }  

    return position;
}

void interface::FenetreGui::realiserDeplacement() 
{
    QPushButton* PositionDepart;
    QPushButton* PositionFinal;

    modele::Position position1(0, 0);
    modele::Position position2(0, 0);

    PositionDepart = enregistrementDeplacement[0];

    if (PositionDepart != nullptr && enregistrementDeplacement.size() == 2)
    {
        PositionFinal = enregistrementDeplacement[1];

        position1 = trouverPostionBouttons(PositionDepart);

        position2 = trouverPostionBouttons(PositionFinal);

        if (echiquier->jouerTour(position1, position2))
        {
            PositionFinal->setText(PositionDepart->text());
            PositionDepart->setText("");

            enregistrementDeplacement.clear();
        }
        else
        {
            messageAlert("Mouvement impossible");

            if (position1 == position2)
            {
                enregistrementDeplacement.clear();
            }
            else 
            {
                PositionDepart->setText(PositionDepart->text());

                enregistrementDeplacement.clear();
            }
        }
    }
}

// enregistre le bouton qui sont appuye pour determiner un deplacement
void interface::FenetreGui::enregistrerDeplacement()
{
    QPushButton* bouttonAppuyer = qobject_cast<QPushButton*>(sender());

    if (enregistrementDeplacement.size() <= 2)
    {
        enregistrementDeplacement.push_back(bouttonAppuyer);
    }
}

void interface::FenetreGui::ajouterNouvellePiece(modele::Piece* piece)
{
    using namespace modele;

    string couleur = piece->couleur_ == blanc ? "Blanc" : "Noir";
    string className = typeid(*piece).name();

    // il faut retirer le debut du string sinon on optiens : class modele::NomDeLaPiece
    // et nous voulons seulement NomDeLaPiece
    string textCase = className.erase(0, DEBUT_NOM_CLASS) + couleur;

    bouttons[piece->position_.coordonne.first][piece->position_.coordonne.second]->setText(QString::fromStdString(textCase));
}

void interface::FenetreGui::initialisationDesPieces()
{
    using namespace modele;

    stringstream stream(configurationDesDifficulte_[configuration_]);
    string pieceCree;

    while(stream >> pieceCree)
    {
        Couleur couleurPiece = pieceCree[1] == 'b' ? modele::blanc : modele::noir;

        //Puisque la valeur ASCII de commence d une certaine valeur et augmenente , en faisant cette soustraiction on aura la valeur de char en int 
        int positionx = pieceCree[2] - '0';
        int positiony = pieceCree[3] - '0';

        //on ajoute une piece selon donnes obtenues auparavant
        switch (pieceCree[0])
        {
        case 'r':
        {
            modele::Position positionPieceRoi(positionx, positiony);
            echiquier->ajouterPiece<modele::Roi>(positionPieceRoi, couleurPiece);
            break;
        }
        case 'd':
        {
            modele::Position positionPieceDame(positionx, positiony);
            echiquier->ajouterPiece<modele::Dame>(positionPieceDame, couleurPiece);
            break;
        }    
        case 'f':
        {
            modele::Position positionPieceFou(positionx, positiony);
            echiquier->ajouterPiece<modele::Fou>(positionPieceFou, couleurPiece);
            break;
        }
        }
    }
}

