#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	//exibindo a interface
	ui->setupUi(this);

	//criando minha tabela inicial
	this->criarTabela();
			

	//configura o grafico inicial
	this->configureChart();



	//criando os connets da app
	this->criarConects();


	//Configura a tabela para que os dados de entrada sejam doubles
	TableDelegate *itDelegate = new TableDelegate;
	this->ui->tableView->setItemDelegate(itDelegate);



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
	connect(this->ui->pushButtonRemoverTudo, SIGNAL(clicked()), this, SLOT(slotRemoverTudo()));
	connect(this->ui->pushButtonImportarArquivo, SIGNAL(clicked()), this, SLOT(slotImportarArquivo()));
	connect(this->ui->pushButtonExportarArquivo, SIGNAL(clicked()), this, SLOT(slotExportarArquivo()));


	connect(this->ui->tableView->model(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(slotTableChangeditemChanged(QModelIndex, QModelIndex)));

	connect(this->ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(slotLoadTransaction(const QItemSelection &, const QItemSelection &)));
	connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(slotCopiarTabela()));
	//connect(this->ui->pushButtonPaste, SIGNAL(clicked()), this, SLOT(slotTablePaste()));

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
		
		this->ui->tableView->model()->insertRow(this->row);	
	
		this->ui->tableView->model()->setData(this->ui->tableView->model()->index(this->row, 0), 0);
		this->ui->tableView->model()->setData(this->ui->tableView->model()->index(this->row, 1), 0);
	
		this->row = this->ui->tableView->model()->rowCount();
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
	//Criando o gráfico a partir dos pontos		
	QChart *chart = new QChart();
	chart->addSeries(series);

	chart->legend()->hide();
	chart->setTitle("Titulo do Grafico");
	//chart->setAnimationOptions(QChart::AllAnimations);
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


// Esse slot é excecutado quando o botão Remover Linha por Índice é clicado, removendo a linha selecionada
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


void MainWindow::slotRemoverTudo()
{
	this->ui->tableView->model()->removeRows(0, this->ui->tableView->model()->rowCount());
}


void MainWindow::slotImportarArquivo()
{

}


void MainWindow::slotExportarArquivo()
{

}


void MainWindow::slotTableChangeditemChanged( QModelIndex topLeft,  QModelIndex bottomRight)
{
	
	this->slotAtualizaChart();

}

void MainWindow::slotLoadTransaction(const QItemSelection &, const QItemSelection &)
{
	qDebug() << "oi selecao";
}

void MainWindow::slotTablePaste()
{
	//pegando os itens selecionados
	QAbstractItemModel * model = this->ui->tableView->model();
	QItemSelectionModel * selection = this->ui->tableView->selectionModel();
	QModelIndexList indexes = selection->selectedIndexes();

	
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

void MainWindow::keyPressEvent(QKeyEvent *event) 
{

	/*QModelIndexList selectedRows = this->ui->tableView->selectionModel()->selectedRows();
	// at least one entire row selected
	if (!selectedRows.isEmpty()) {
		if (event->key() == Qt::Key_Insert)
			this->ui->tableView->model()->insertRows(selectedRows.at(0).row(),
				selectedRows.size());
		else if (event->key() == Qt::Key_Delete)
			this->ui->tableView->model()->removeRows(selectedRows.at(0).row(),
				selectedRows.size());
	}


	// at least one cell selected
	QList<QModelIndex> indexes = this->ui->tableView->selectedIndexes();
	if (!indexes.isEmpty()) {
		if (event->key() == Qt::Key_Delete) {
			for (QModelIndex index : indexes)
			{
				this->ui->tableView->model()->setData(index, QString());
			}
		}
	}*/





		// If Ctrl-C typed
		/*if (event->key() == Qt::Key_C && (event->modifiers() & Qt::ControlModifier))
		{
			QModelIndexList cells = this->ui->tableView->selectionModel()->selectedIndexes();
			qSort(cells); // Necessary, otherwise they are in column order

			QString text;
			int currentRow = 0; // To determine when to insert newlines
			foreach(const QModelIndex& cell, cells) {
				if (text.length() == 0) {
					// First item
				}
				else if (cell.row() != currentRow) {
					// New row
					text += '\n';
				}
				else {
					// Next cell
					text += '\t';
				}
				currentRow = cell.row();
				text += cell.data().toString();
			}

			QApplication::clipboard()->setText(text);
		}*/




	QModelIndexList selectedRows = this->ui->tableView->selectionModel()->selectedRows();

	// at least one entire row selected
	if (!selectedRows.isEmpty()) {
		if (event->key() == Qt::Key_Insert)
			this->ui->tableView->model()->insertRows(selectedRows.at(0).row(),
				selectedRows.size());
		else if (event->key() == Qt::Key_Delete)
			this->ui->tableView->model()->removeRows(selectedRows.at(0).row(),
				selectedRows.size());
	}
	// at least one cell selected
	QList<QModelIndex> indexes = this->ui->tableView->selectionModel()->selectedIndexes();
	if (!indexes.isEmpty()) {
		if (event->key() == Qt::Key_Delete) {
			foreach(QModelIndex index, indexes)
				this->ui->tableView->model()->setData(index, QString());
		}
		else if (event->matches(QKeySequence::Copy)) {
			QString text;
			QItemSelectionRange range = this->ui->tableView->selectionModel()->selection().first();
			for (auto i = range.top(); i <= range.bottom(); ++i)
			{
				QStringList rowContents;
				for (auto j = range.left(); j <= range.right(); ++j)
					rowContents << this->ui->tableView->model()->index(i, j).data().toString();
				text += rowContents.join("\t");
				text += "\n";
			}
			QApplication::clipboard()->setText(text);
		}
		else if (event->matches(QKeySequence::Paste)) {
			

			QString text = QApplication::clipboard()->text();
			QStringList rowContents = text.split("\n", QString::SkipEmptyParts);

			//criando as linhas da tabela de acordo com o dado que estou copiando
			if(this->row < rowContents.size())
			{
				
				int rowsAdd = rowContents.size() - this->row;
				for (int i = 0; i < rowsAdd ;i++)
				{
					this->slotAddLinha();
				}
			}
			

			QModelIndex initIndex = indexes.at(0);
			auto initRow = initIndex.row();
			auto initCol = initIndex.column();

			for (auto i = 0; i < rowContents.size(); ++i) {
				QStringList columnContents = rowContents.at(i).split("\t");
				this->ui->tableView->blockSignals(true);
				for (auto j = 0; j < columnContents.size(); ++j) {
					this->ui->tableView->model()->setData(this->ui->tableView->model()->index(initRow + i, initCol + j), columnContents.at(j));
				}
				this->ui->tableView->blockSignals(false);
			}



		}
		//else
			//QTableView::keyPressEvent(event);
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
