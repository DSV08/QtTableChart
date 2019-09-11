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
#include <QValueAxis>

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


	/*!
	 * @brief M�todo Set que guarda o caminho do arquivo que � editado
	 * @param arquivoCorrente Variavel com o caminho do arquivo que � editado.
	 * @return void
	 */
	void setArquivoCorrente(QString arquivoCorrente);

	/*!
	 * @brief M�todo para obter o caminho do arquivo que � editado
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
	* Variavel global que armazena o caminho do arquivo que est� sendo editado
	*/
	QString currentFileName;


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
	 * @brief Salvar
	 * M�todo para salvar o texto do bloco de notas em um arquivo em uso ou em um novo arquivo
	 *  que ser� criado caso n�o tenha um arquivo em uso
	 */
	//metodo para salvar os tipos de arquivo conforme escolhido pelo usuario, chamdo pelo slot save
	void salvarArquivo();


	/*!
	* @brief Configura o Chart Inicial
	*/
	void configureChart();


	/*!
	*@brief Desenha o Chart
	* Desenha o gr�fico com os pontos recebidos
	* @param Ptos Lista com os pontos que ser�o utilizados para formar o gr�fico
	*/
	//void desenhaChart(QList<QPointF> ptos);


	/*!
	* @brief Fun��o para capturar eventos de teclado
	* Captura eventos(copiar,colar,etc) de teclado e excecuta a determinada funcionalidade.
	* @param Event Evento realizado no teclado
	*/
	void keyPressEvent(QKeyEvent *event);


	private slots:


	/*!
	* @brief Slot adicionar linha
	* Esse slot � excecutado quando o bot�o adicionar linha � clicado, adicionando uma linha na tabela
	*/
	void slotAddLinha();


	/*!
	* @brief Slot adicionar coluna
	* Esse slot � excecutado quando o bot�o adicionar coluna � clicado, adicionando uma coluna na tabela
	*/
	void slotAddColuna();


	/*!
	* @brief Slot remover linha
	* Esse slot � excecutado quando o bot�o remover linha � clicado, eliminando  uma linha na tabela
	*/
	void slotRemoveLinha();


	/*!
	* @brief Slot remover coluna
	* Esse slot � excecutado quando o bot�o remover coluna � clicado, eliminando  uma coluna na tabela
	*/
	void slotRemoveColuna();


	/*!
	 * @brief Slot Atualizar Chart
	 * Esse slot � excecutado quando o bot�o Atualizar Chart � clicado, criando ou atualizando
	 * o gr�fico com os pontos formados pelas cordenadas passadas na tabela
	 */
	void slotAtualizaChart();


	/*!
	 * @brief Slot Remover Linha por �ndice
	 * Esse slot � excecutado quando o bot�o Remover Linha por �ndice � clicado, removendo a(s) linha(s) selecionada(s)
	 */
	void slotRemoverLinhaPorIndice();


	/*!
	* @brief Slot Remover Linha por �ndice
	* Esse slot � excecutado quando o bot�o Remover Linha por �ndice � clicado, removendo a(s) linha(s) selecionada(s)
	*/
	void slotRemoverColunaPorIndice();


	/*!
	* @brief Slot Remover Tudo
	* Esse slot � excecutado quando o bot�o Remover Tudo � clicado, removendo todas as linhas, todas as colunas e limpando o gr�fico.
	*/
	void slotRemoverTudo();


	/*!
	* @brief Slot Importar Arquivo
	* Esse slot � excecutado quando o bot�o Importar Arquivo � clicado, abrindo uma caixa de dialogo para selecionar um arquivo CSV 
	* que ser� exibido na tabela 
	*/
	void slotImportarArquivo();


	/*!
	* @brief Slot Exportar Arquivo
	* Esse slot � excecutado quando o bot�o Exportar Arquivo � clicado, abrindo uma caixa de dialogo para selecionar o lugar para salvar
	* os dados na tabela como um arquivo CSV
	*/
	void slotExportarArquivo();


	/*!
	* @brief Slot para detectar mudan�as
	* Esse slot � excecutado quando qualquer valor na tabela � alterado, atualizando assim o gr�fico a cada mudan�a 
	*/
	void slotTableChangeditemChanged(QModelIndex topLeft, QModelIndex bottomRight);


	/*!
	* @brief Slot para...Necess�rio?
	* Esse slot....
	*/
	void slotLoadTransaction(const QItemSelection &, const QItemSelection &);


	/*!
	* @brief Slot para...Necess�rio?
	* @param table ...
	*/
	void slotAddZeros(QTableView *table);


	/*!
	* @brief Slot para...Necess�rio?
	*/
	void slotTablePaste();

signals:


};

