//https://riptutorial.com/qt/example/13705/a-simple-read-only-table-to-view-data-from-a-model
//https://www.bogotobogo.com/Qt/Qt5_QTableView_QItemDelegate_ModelView_MVC.php
//https://stackoverflow.com/questions/48362864/how-to-insert-qchartview-in-form-with-qt-designer
//https://doc.qt.io/qt-5/qtcharts-linechart-example.html
//https://forum.qt.io/topic/62375/reading-a-value-from-tableview
//https://stackoverflow.com/questions/42487645/creating-a-qmodelindex


#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QMainWindow>
#include <QList>
#include <QStandardItemModel>
#include <QLineSeries>
#include <QtCharts>
#include <QModelIndex>

#include "tableDelegate.h"

QT_CHARTS_USE_NAMESPACE


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
	QChart *chart;;
	QChartView *chartView;

	/*!
	* @brief Variavel para armazenar o numero de linhas da tabela
	*/
	int row = 0;

	/*!
	* @brief Variavel para armazenar o numero de colunas da tabela
	*/
	int col = 2;


	//QStandardItemModel *model;

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
	/*!
	* @brief Criação da tabela inicial
	* Método para iniciar a tabela com os valores inicialmente passados
	* @param row Número de linhas iniciais da tabela
	* @param col Número de colunas iniciais da tabela
	*/
	void criarTabela(int row=0, int col=2);



	/*!
	* @brief Configura o Chart Inicial
	*/
	void configureChart();


    /*!
    *@brief Desenha o Chart
    * Desenha o gráfico com os pontos recebidos
    * @param Ptos Lista com os pontos que serão utilizados para formar o gráfico
    */
    void desenhaChart(QList<QPointF> ptos);

	private slots:

	/*!
	* @brief Slot adicionar linha
	* Esse slot é excecutado quando o botão adicionar linha é clicado, adicionando uma linha na tabela
	*/
	void slotAddLinha();


	/*!
	* @brief Slot remover linha
	* Esse slot é excecutado quando o botão remover linha é clicado, eliminando  uma linha na tabela
	*/
	void slotRemoveLinha();


	/*!
	 * @brief Slot Atualizar Chart
	 * Esse slot é excecutado quando o botão Atualizar Chart é clicado, crindo ou atualizando
	 * o gráfico com os pontos formados pelas cordenadas passadas na tabela
	 */
	void slotAtualizaChart();

	/*!
	 * @brief Slot Remover Linha por índice
	 * Esse slot é excecutado quando o botão Remover Linha por Índice é clicado, removendo a linha selecionada
	 */
	void slotRemoverLinhaPorIndice();


	void slotTableChangeditemChanged(QModelIndex topLeft, QModelIndex bottomRight);

	void slotLoadTransaction(const QItemSelection &, const QItemSelection &);

	void slotAddZeros(QTableView *table);

signals:

	void sinal();
};

