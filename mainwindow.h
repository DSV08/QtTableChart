//https://riptutorial.com/qt/example/13705/a-simple-read-only-table-to-view-data-from-a-model
//https://www.bogotobogo.com/Qt/Qt5_QTableView_QItemDelegate_ModelView_MVC.php
//https://stackoverflow.com/questions/48362864/how-to-insert-qchartview-in-form-with-qt-designer
//https://doc.qt.io/qt-5/qtcharts-linechart-example.html
//https://forum.qt.io/topic/62375/reading-a-value-from-tableview
//https://stackoverflow.com/questions/42487645/creating-a-qmodelindex

//https://www.walletfox.com/course/qtableviewcopypaste.php
//https://stackoverflow.com/questions/1230222/selected-rows-in-qtableview-copy-to-qclipboard
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


	/*!
	 * @brief Método Set que guarda o caminho do arquivo que é editado
	 * @param arquivoCorrente Variavel com o caminho do arquivo que é editado.
	 * @return void
	 */
	void setArquivoCorrente(QString arquivoCorrente);

	/*!
	 * @brief Método para obter o caminho do arquivo que é editado
	 * @return QString
	 */
	QString getArquivoCorrente();

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

	/*!
	* @brief Caminho do Arquivo em uso
	* Variavel global que armazena o caminho do arquivo que está sendo editado
	*/
	QString currentFileName;


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
	 * @brief Salvar
	 * Método para salvar o texto do bloco de notas em um arquivo em uso ou em um novo arquivo
	 *  que será criado caso não tenha um arquivo em uso
	 */
	//metodo para salvar os tipos de arquivo conforme escolhido pelo usuario, chamdo pelo slot save
	void salvarArquivo();

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


	void keyPressEvent(QKeyEvent *event);

	private slots:

	/*!
	* @brief Slot adicionar linha
	* Esse slot é excecutado quando o botão adicionar linha é clicado, adicionando uma linha na tabela
	*/
	void slotAddLinha();


	/*!
	* @brief Slot adicionar coluna
	* Esse slot é excecutado quando o botão adicionar coluna é clicado, adicionando uma coluna na tabela
	*/
	void slotAddColuna();

	/*!
	* @brief Slot remover linha
	* Esse slot é excecutado quando o botão remover linha é clicado, eliminando  uma linha na tabela
	*/
	void slotRemoveLinha();


	/*!
	* @brief Slot remover coluna
	* Esse slot é excecutado quando o botão remover coluna é clicado, eliminando  uma coluna na tabela
	*/
	void slotRemoveColuna();


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

	/*!
	* @brief Slot para...
	* Esse slot....
	*/
	void slotRemoverTudo();

	/*!
	* @brief Slot para...
	* Esse slot....
	*/
	void slotImportarArquivo();

	/*!
	* @brief Slot para...
	* Esse slot....
	*/
	void slotExportarArquivo();

	/*!
	* @brief Slot para...
	* Esse slot....
	*/
	void slotTableChangeditemChanged(QModelIndex topLeft, QModelIndex bottomRight);

	/*!
	* @brief Slot para...
	* Esse slot....
	*/
	void slotLoadTransaction(const QItemSelection &, const QItemSelection &);

	/*!
	* @brief Slot para...
	* @param table ...
	*/
	void slotAddZeros(QTableView *table);

	/*!
	* @brief Slot para...
	*/
	void slotTablePaste();

signals:


};

