#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox" //модальные окна
#include "workwindow.h"
#include "matrix.h"
#include <QFileDialog>
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /* Конструктор по умолчанию
     * Входные параметры: родительский виджет
     */
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    /*Деструктор
     */
    delete ui;
}


void MainWindow::on_CreateMatrixButton_clicked()
{
    /* Метод, который создает дефолтную матрицу обьектов
     * и открывает рабочее окно
     */
    int n = ui->NValue->value();
    int m = ui->MValue->value();
    Matrix matrix(n,m);
    QWidget wid;

    WorkWindow window(&wid,&matrix);
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_clicked()
{
    /* Метод, который создает создает матрицу по значениям,
     * считанных из файла,
     * и открывает рабочее окно
     */
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "TXT File(*.txt)");
if(!(fileName =="")){

    try{
    Matrix matrix = Matrix(fileName.toStdString());
    QWidget wid;

    WorkWindow window(&wid,&matrix);
    window.setModal(true);
    window.exec();
    }
    catch(int e){
        if(e ==3)
            QMessageBox ::warning(this,"Заголовок","Не удалось загрузить файл");
    }
}
}
