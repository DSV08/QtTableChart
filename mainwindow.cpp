#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	//exibindo a interface
	ui->setupUi(this);


	//criando os connets da app
	this->criarConects();


	//criando minha tabela inicial
	//this->criarTabela();

	this->ui->tableView->setItemDelegate(new TableDelegate());

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
	this->chart = new QChart();
	//this->chart->legend()->hide();
	//this->chart->addSeries(series);
	this->chart->createDefaultAxes();
	this->chart->setTitle("Simple line chart example");
	//![3]

	//![4]
	
	//this->chartView = new QChartView(chart);
	
	this->ui->chartview->setChart(this->chart);
	this->ui->chartview->setRenderHint(QPainter::Antialiasing);

	

	


	//this->ui->horizontalLayout->addWidget(this->chartView);


	//QStandardItemModel *model = new QStandardItemModel(this->row, this->col, this);
	//this->model = new QStandardItemModel(this->row, this->col, this);
	

}
	
	

MainWindow::~MainWindow()
{
	//delete ui;
}

void MainWindow::criarConects()
{
	//botao criar linha da tabela
	connect(this->ui->pushButton_addLinha, SIGNAL(clicked()), this, SLOT(slotAddLinha()));
	connect(this->ui->pushButton_removeLinha, SIGNAL(clicked()), this, SLOT(slotRemoveLinha()));
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
		this->ui->tableView->model()->insertRow(this->ui->tableView->model()->rowCount());
	}
	this->row++;

}


void MainWindow::slotRemoveLinha()
{
	if (this->row > 0) {
		this->row--;
		this->criarTabela(this->row, this->col);
	}
	else {
	
		QMessageBox::warning(this, "Warning", "Tabela Vazia");
	
	}
	this->ui->tableView->model()->removeRow(this->ui->tableView->model()->rowCount());
}


void MainWindow::slotAtualizaChart()
{
	
	
	//Pesquisando a tabela para captura os valores de x e y
	int _rows = this->ui->tableView->model()->rowCount();
	int _cols = this->ui->tableView->model()->columnCount();


	QList<QPointF> ptos;
	ptos.clear();

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
