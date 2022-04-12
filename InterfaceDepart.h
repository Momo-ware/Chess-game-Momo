#pragma once

#include "QObject"
#include "QApplication"
#include "QWidget"
#include "QPushButton"
#include "qmainwindow.h"
#include "QGridLayout"
#include "QMessageBox"
#include <memory>
#include "FenetreGui.h"


#define NOMBRE_DE_DIFFICULTE 3

namespace interface 
{
	class InterfaceDepart : public QMainWindow
	{
	public:
		void demarrerPartie();
		void initialiserBouttonsPosition();
		void creationEchiquier(int configuration);

		QWidget* obtenirFenetreConf()
		{
			return fenetreConf;
		};

		~InterfaceDepart()
		{
			for (int j = 0; j < NOMBRE_DE_DIFFICULTE; j++)
			{
				delete bouttonsConf[j];
			}

			delete menuDifficulte;
			delete fenetreConf;
			delete partieGui;

			delete butonsconfiguration;
			delete menuDemarrage;
			delete fenetreDemarrage;
		}

	public slots:
		void montrerInterface();
		void selectionDifficulte();

	private:
		QWidget* fenetreConf;
		QPushButton* bouttonsConf[NOMBRE_DE_DIFFICULTE];

		interface::FenetreGui* partieGui;

		QHBoxLayout* menuDifficulte;

		QWidget* fenetreDemarrage;

		QPushButton* butonsconfiguration;
		QHBoxLayout* menuDemarrage;
	};
};

