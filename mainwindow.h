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
* Classe da janela principal. A interface que cont�m a tabela, e seu gr�fico
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
	* @brief Cria��o dos conects
	* M�todo para estabelecer a rela��o de ac�o e rea��o dos bot�es e suas funcionalidades
	*/
	void criarConects();


	//criar tabela inicial
	/*!
	* @brief Cria��o da tabela inicial
	* M�todo para iniciar a tabela com os valores inicialmente passados
	* @param row N�mero de linhas iniciais da tabela
	* @param col N�mero de colunas iniciais da tabela
	*/
	void criarTabela(int row=0, int col=2);



	/*!
	* @brief Configura o Chart Inicial
	*/
	void configureChart();


    /*!
    *@brief Desenha o Chart
    * Desenha o gr�fico com os pontos recebidos
    * @param Ptos Lista com os pontos que ser�o utilizados para formar o gr�fico
    */
    void desenhaChart(QList<QPointF> ptos);

	private slots:

	/*!
	* @brief Slot adicionar linha
	* Esse slot � excecutado quando o bot�o adicionar linha � clicado, adicionando uma linha na tabela
	*/
	void slotAddLinha();


	/*!
	* @brief Slot remover linha
	* Esse slot � excecutado quando o bot�o remover linha � clicado, eliminando  uma linha na tabela
	*/
	void slotRemoveLinha();


	/*!
	 * @brief Slot Atualizar Chart
	 * Esse slot � excecutado quando o bot�o Atualizar Chart � clicado, crindo ou atualizando
	 * o gr�fico com os pontos formados pelas cordenadas passadas na tabela
	 */
	void slotAtualizaChart();

	/*!
	 * @brief Slot Remover Linha por �ndice
	 * Esse slot � excecutado quando o bot�o Remover Linha por �ndice � clicado, removendo a linha selecionada
	 */
	void slotRemoverLinhaPorIndice();


	void slotTableChangeditemChanged(QModelIndex topLeft, QModelIndex bottomRight);

	void slotLoadTransaction(const QItemSelection &, const QItemSelection &);

	void slotAddZeros(QTableView *table);

signals:

	void sinal();
};

