#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	//exibindo a interface
	ui->setupUi(this);




	//criando minha tabela inicial
	this->criarTabela();


	//Configura a tabela para que os dados de entrada sejam doubles
	this->ui->tableView->setItemDelegate(new TableDelegate());


	//configura o grafico inicial
	this->configureChart();



	//criando os connets da app
	this->criarConects();

	///////////////////////////////////////////////


	//![1]
//	QLineSeries *series = new QLineSeries();
//
//
//	//![1]
//
//	//![2]
//	series->append(0, 6);
//	series->append(2, 4);
//	series->append(3, 8);
//	series->append(7, 4);
//	series->append(10, 5);
//	*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
	//![2]

	//![3]
	
	//this->chart->legend()->hide();
	//this->chart->addSeries(series);

	

}
	
	

MainWindow::~MainWindow()
{
	//delete ui;
}

void MainWindow::criarConects()
{
	//slots para tabela
	connect(this->ui->pushButton_addLinha, SIGNAL(clicked()), this, SLOT(slotAddLinha()));
	connect(this->ui->pushButton_removeLinha, SIGNAL(clicked()), this, SLOT(slotRemoveLinha()));
	connect(this->ui->pushButton_removeLinhaIndice, SIGNAL(clicked()), this, SLOT(slotRemoverLinhaPorIndice()));


	connect(this->ui->tableView->model(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(slotTableChangeditemChanged(QModelIndex, QModelIndex)));

	connect(this->ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(slotLoadTransaction(const QItemSelection &, const QItemSelection &)));

	//slots para o chart
	connect(this->ui->pushButton_updateChart, SIGNAL(clicked()), this, SLOT(slotAtualizaChart()));


}



void MainWindow::criarTabela(int _row, int _col) 
{
	QStandardItemModel *model = new QStandardItemModel(_row, _col, this);
	this->ui->tableView->setModel(model);
	this->ui->tableView->model()->setHeaderData(0, Qt::Horizontal, tr("x"));
	this->ui->tableView->model()->setHeaderData(1, Qt::Horizontal, tr("y"));

	//this->model = new QStandardItemModel(_row, _col, this);
	// Create model:

	/*if (this->ui->tableView->model() == nullptr)
	{

		this->model = new QStandardItemModel(_row, _col, this);
		model->setHeaderData(0, Qt::Horizontal, tr("x"));
		model->setHeaderData(1, Qt::Horizontal, tr("y"));

		//jogando o modelo que foi criado na tabela da interface
		//this->ui->tableView->setModel(model);
		this->ui->tableView->setModel(model);
		this->ui->tableView->model()->setHeaderData(0, Qt::Horizontal, tr("x"));
		this->ui->tableView->model()->setHeaderData(1, Qt::Horizontal, tr("y"));


	}
	else
	{
		//QStandardItemModel item = this->ui->tableView->model()->item(_row, _col);
		//bool ok = this->ui->tableView->model()->insertRow(_row);
		//this->ui->tableView->model()->appendRow(this->model->item(_row, _col));
		//this->ui->tableView->model()->insertRow(this->ui->tableView->model()->rowCount());

	}*/
	
}


void MainWindow::slotAddLinha() 
{
	if (this->ui->tableView->model() == nullptr)
	{
		this->criarTabela(this->row, this->col);
	}
	else
	{
		this->row = this->ui->tableView->model()->rowCount();
		this->ui->tableView->model()->insertRow(this->row);	
	
		//this->slotAddZeros(this->ui->tableView);

		this->ui->tableView->model()->setData(this->ui->tableView->model()->index(this->row, 0), 0);
		this->ui->tableView->model()->setData(this->ui->tableView->model()->index(this->row, 1), 0);
	}
	
}


void MainWindow::slotRemoveLinha()
{
	if (this->row > 0) {
		
		this->ui->tableView->model()->removeRow(this->ui->tableView->model()->rowCount()-1);
		this->row = this->ui->tableView->model()->rowCount();
		this->slotAtualizaChart();
	}
	else {
	
		QMessageBox::warning(this, "Warning", "Tabela Vazia");
	
	}
}


void MainWindow::slotAtualizaChart()
{
	  
	//Pesquisando a tabela para captura os valores de x e y
	int _rows = this->ui->tableView->model()->rowCount();
	int _cols = this->ui->tableView->model()->columnCount();

	//Criando uma estrutura para armazenar os pontos da tabela
	QList<QPointF> ptos;
	ptos.clear();

	if (_rows > 0) {

		//pesquisando na tabela para capturar os pontos x e y
		for (int i = 0; i < _rows; i++)
		{
			QPointF p;
			double x = this->ui->tableView->model()->data(this->ui->tableView->model()->index(i, 0)).toDouble();
			double y = this->ui->tableView->model()->data(this->ui->tableView->model()->index(i, 1)).toDouble();

			//Adicionando os ptos x e y a minha lista de pontosB
			p.setX(x);
			p.setY(y);
			ptos.append(p);

		}

		//
		// CRIANDO O CHART COM OS DADOS DA TABELA
		//	
		this->desenhaChart(ptos);
	}

}


void MainWindow::desenhaChart(QList<QPointF> ptos)
{
	//Juntando os pontos em uma lineSeries
	QLineSeries* series = new QLineSeries();

	series->append(ptos);

	/*for (QPointF ponto : ptos)
	{
		series->append(ponto);
	}
*/
	//Criando o gr�fico a partir dos pontos		
	QChart *chart = new QChart();
	chart->addSeries(series);

	chart->legend()->hide();
	chart->setTitle("Titulo do Grafico");
	chart->setAnimationOptions(QChart::AllAnimations);
	chart->createDefaultAxes();

	this->ui->chartview->setChart(chart);
	this->ui->chartview->update();
}



void MainWindow::configureChart()
{
	//criando o Chart
	QChart *chart = new QChart();
	chart->createDefaultAxes();
	chart->setAnimationOptions(QChart::AllAnimations);

	//enviando o objeto chart para a UI da Interface
	this->ui->chartview->setChart(chart);
	this->ui->chartview->setRenderHint(QPainter::Antialiasing);

}


// Esse slot � excecutado quando o bot�o Remover Linha por �ndice � clicado, removendo a linha selecionada
void MainWindow::slotRemoverLinhaPorIndice()
{
	QItemSelectionModel *selectionModel = this->ui->tableView->selectionModel();
	QList<QModelIndex> indexes = selectionModel->selectedIndexes();

	for (QModelIndex index : indexes) {
		selectionModel->model()->removeRow(index.row());
		this->row = ui->tableView->model()->rowCount();
	}
	this->slotAtualizaChart();
}


void MainWindow::slotTableChangeditemChanged( QModelIndex topLeft,  QModelIndex bottomRight)
{
	
	this->slotAtualizaChart();

}

void MainWindow::slotLoadTransaction(const QItemSelection &, const QItemSelection &)
{
	qDebug() << "oi selecao";
}

void MainWindow::slotAddZeros(QTableView * table)
{
	//Pesquisando a tabela para captura os valores de x e y
	int _rows = table->model()->rowCount();
	int _cols = table->model()->columnCount();

	//pesquisando na tabela para capturar os pontos x e y
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			table->model()->setData(table->model()->index(i, j), 0);
		}
	}

}




//this->ui->tableView->model()->setData(this->ui->tableView->model()->index(0, 0), contactNames.at(0));
//this->ui->tableView->model()->setData(this->ui->tableView->model()->index(1, 0), contactNames.at(1));
//this->ui->tableView->model()->setData(this->ui->tableView->model()->index(2, 0), contactNames.at(2));


//this->ui->tableView->model()->setData(this->ui->tableView->model()->index(0, 1), contactPhoneNums.at(0));
//this->ui->tableView->model()->setData(this->ui->tableView->model()->index(1, 1), contactPhoneNums.at(1));
//this->ui->tableView->model()->setData(this->ui->tableView->model()->index(2, 1), contactPhoneNums.at(2));



//// Generate data
//for (int i = 0; i < row  ; i++)
//{

//	for (int j = 0; j < col; j++)
//	{
//		this->ui->tableView->model()->setData(this->ui->tableView->model()->index(i, j), contactNames.at(0));
//		this->ui->tableView->model()->setData(this->ui->tableView->model()->index(i, 1), contactPhoneNums.at(0));

//		//		QModelIndex index = PhoneBookModel->index(i, j, QModelIndex());
//		//		// 0 for all data
//		//		
//		//		//PhoneBookModel->setData(index, QString(QString::number(i) +","+ QString::number(j)));
//		//		PhoneBookModel->setData(index, contactNames.at(i));
//		//		PhoneBookModel->setData(index, contactPhoneNums.at(j));
//	}
//}
