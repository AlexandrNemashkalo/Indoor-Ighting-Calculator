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
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//QMessageBox ::information(this,"Заголовок","текст")
//QMessageBox ::critical(this,"Заголовок","текст")
//QMessageBox ::warning(this,"Заголовок","текст")
//QMessageBox::StandardButton reply= QMessageBox ::question(this,"Заголовок","текст", QMessageBox::Yes|QMessageBox::NO)


void MainWindow::on_CreateMatrixButton_clicked()
{
  int n = ui->NValue->value();
  int m = ui->MValue->value();
  //float height = ui->Height->value();
  Matrix matrix(n,m);
  QWidget wid;

  WorkWindow window(&wid,&matrix);
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_clicked()
{
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
