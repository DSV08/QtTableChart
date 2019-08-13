#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	//exibindo a interface
    ui->setupUi(this);
	

	//criando os connets da app
	this->criarConects();


	//criando minha tabela inicial
	this->criarTabela();
	

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
}



void MainWindow::criarTabela(int _row, int _col) 
{

	// Create model:
	QStandardItemModel *model = new QStandardItemModel(_row, _col, this); ;
	model->setHeaderData(0, Qt::Horizontal, tr("x"));
	model->setHeaderData(1, Qt::Horizontal, tr("y"));

	//jogando o modelo que foi criado na tabela da interface
	this->ui->tableView->setModel(model);

}


void MainWindow::slotAddLinha() 
{
	this->row++;
	this->criarTabela(this->row, this->col);

}


void MainWindow::slotRemoveLinha()
{
	this->row--;
	this->criarTabela(this->row, this->col);
}


void MainWindow::slotAtualizaChart()
{
    int i;
    QLineSeries *series = new QLineSeries();
    QModelIndex index;
    for(i = 0;i<this->row;i++)
    {
        index = this->ui->graphicsView->index(i, i);
        series->append(index.row(),index.column());
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
