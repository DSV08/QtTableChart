//https://riptutorial.com/qt/example/13705/a-simple-read-only-table-to-view-data-from-a-model
//https://www.bogotobogo.com/Qt/Qt5_QTableView_QItemDelegate_ModelView_MVC.php


#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QMainWindow>
#include <QList>
#include <QStandardItemModel>

namespace Ui {
	class MainWindow;
}



/** A Test class.
* Classe da janela principal. A interface que contém a tabela, e seu gráfico
*/
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	/*!
	*@brief Construtor
	*Construtor da Classe MainWindow
	* @param parent Ponteiro para um Widget da janela principal
	*/
	explicit MainWindow(QWidget *parent = nullptr);


	/*!
	* @brief Destrutor
	* Destrutor da Classe MainWindow
	*/
	~MainWindow();

private:


	/*!
	* @brief Variavel para armazenar o numero de linhas da tabela
	*/
	int row = 0;

	/*!
	* @brief Variavel para armazenar o numero de colunas da tabela
	*/
	int col = 2;

	/*!
	* @brief Ui
	* objetos de interface do Qt
	*/
	Ui::MainWindow *ui;


	/*!
	* @brief Criação dos conects
	* Método para estabelecer a relação de acão e reação dos botões e suas funcionalidades
	*/
	void criarConects();

	//criar tabela inicial
	void criarTabela(int row=0, int col=2);

	private slots:

	void slotAddLinha();

};

