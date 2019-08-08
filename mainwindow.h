#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
     * @brief Ui
     * objetos de interface do Qt
     */
    Ui::MainWindow *ui;


    /*!
     * @brief Criação dos conects
     * Método para estabelecer a relação de acão e reação dos botões e suas funcionalidades
     */
    void criarConects();
};

#endif // MAINWINDOW_H
