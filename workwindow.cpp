#include "workwindow.h"
#include "ui_workwindow.h"
#include "matrix.h"
#include "qdynamicbutton.h"
#include "string.h"
#include "led.h"
#include "iostream"
#include <QFileDialog>
#include <QMessageBox>

WorkWindow::WorkWindow(QWidget *parent,Matrix  *m) :
    QDialog(parent),
    ui(new Ui::WorkWindow),
    matrix(m)
{
    ui->setupUi(this);

    ui->PowerInput->setMaximum(Lamp::MAX_POWER);
    ui->PowerInput->setMinimum(Lamp::MIN_POWER);
    ui->IntensityInput->setMaximum(Lamp::MAX_INTENSITY);
    ui->IntensityInput->setMinimum(Lamp::MIN_INTENSITY);
    ui->RedInput->setMaximum(Led::MAX_COLOR_VALUE);
    ui->RedInput->setMinimum(Led::MIN_COLOR_VALUE);

    for(int i=0;i<matrix->getSizeN();i++){
        QHBoxLayout *horisontLayout= new QHBoxLayout;
        for(int j=0;j<matrix->getSizeM();j++){
            QDynamicButton *button = new QDynamicButton(this,i,j);
            if(i==0 && j==0){
                button->setChecked(true);
                currButton = button;
            }
           if(matrix->getForUpdateLamp(i,j)->getType() ==0)
           {

            button->setStyleSheet(  "QRadioButton::indicator {width: 50px;height: 50px;}"
                                    "QRadioButton::indicator::unchecked{ image: url(:/resource/img/lamp.png)}"
                                  "QRadioButton::indicator::checked{image: url(:/resource/img/lampActive.png)}"
                                  );
            button->setText("P="+ QString::number( matrix->getLamp(i,j)->getPower())+"\n"
                            "I="+QString::number( matrix->getLamp(i,j)->getIntensity()));
           }
           else
           {
               button->setStyleSheet(  "QRadioButton::indicator {width: 50px;height: 50px;}"
                                    "QRadioButton::indicator::unchecked{ image: url(:/resource/img/lad.png)}"
                                  "QRadioButton::indicator::checked{image: url(:/resource/img/ladActive.png)}"
                                  );
               Led *led = dynamic_cast<Led* >(matrix->getForUpdateLamp(i,j));
               button->setText("P="+ QString::number( matrix->getLamp(i,j)->getPower())+"\n"
                               "I="+QString::number(led->currIntensity(*led)));
           }

            horisontLayout->addWidget(button);
            connect(button, SIGNAL(clicked()), this, SLOT(slotGetLamp()));
        }
        ui->verticalLayout->addLayout(horisontLayout);
    }

    UpdateLampInfo(0,0);

}


WorkWindow::~WorkWindow()
{
    delete ui;
}

void WorkWindow::slotGetLamp()
{
     QDynamicButton *button = (QDynamicButton*) sender();
     currButton = button;
     UpdateLampInfo(currButton->getN(),currButton->getM());
}

void WorkWindow::on_SaveLampButton_clicked()
{

    bool isLed = ui->IsLed->isChecked();
    if(isLed){
       Led * led = new Led(ui->PowerInput->value(),
                     ui->IntensityInput->value(),
                     ui->RedInput->value(),
                     ui->GreenInput->value(),
                     ui->BlueInput->value());
       matrix->setLamp(currButton->getN(),currButton->getM(),led);
       ui->CurrIntensity->setText(QString::number(led->currIntensity(*led)));

       currButton->setStyleSheet(  "QRadioButton::indicator {width: 50px;height: 50px;}"
                               "QRadioButton::indicator::unchecked{ image: url(:/resource/img/lad.png)}"
                             "QRadioButton::indicator::checked{image: url(:/resource/img/ladActive.png)}"
                             );

       currButton->setText("P="+ QString::number(ui->PowerInput->value())+"\n"
                       "I="+ui->CurrIntensity->text());
    }
    else
    {
       Lamp * lamp = new Lamp(ui->PowerInput->value(),ui->IntensityInput->value());
       matrix->setLamp(currButton->getN(),currButton->getM(),lamp);
       ui->CurrIntensity->setText("");

       currButton->setStyleSheet(  "QRadioButton::indicator {width: 50px;height: 50px;}"
                               "QRadioButton::indicator::unchecked{ image: url(:/resource/img/lamp.png)}"
                             "QRadioButton::indicator::checked{image: url(:/resource/img/lampActive.png)}"
                             );
       currButton->setText("P="+ QString::number(ui->PowerInput->value())+"\n"
                       "I="+QString::number(ui->IntensityInput->value()));
    }



}


void WorkWindow::UpdateLampInfo(int n_,int m_){
     ui->LampInfo->setTitle("Информация о лампе c координатами("+
                            QString::number(n_+1)+","+
                            QString::number(m_+1)+",?)");
     Lamp * lamp = matrix->getForUpdateLamp(n_,m_);

    bool isLed= false;
    Led *led = dynamic_cast<Led* >(lamp);
    if(led)
        isLed = true;

    ui->PowerInput->setValue(lamp->getPower());
    ui->IntensityInput->setValue(lamp->getIntensity());

    ui->IsLed->setChecked(isLed);

    ui->BlueInput->setEnabled(isLed);
    ui->RedInput->setEnabled(isLed);
    ui->GreenInput->setEnabled(isLed);
    if(isLed){
        ui->CurrIntensity->setText(QString::number(led->currIntensity(*led)));
        ui->BlueInput->setValue(led->getBlue());
        ui->RedInput->setValue(led->getRed());
        ui->GreenInput->setValue(led->getGreen());
    }
    else
    {
        ui->CurrIntensity->setText("");
        ui->BlueInput->setValue(0);
        ui->RedInput->setValue(0);
        ui->GreenInput->setValue(0);
    }
}



void WorkWindow::on_IsLed_clicked(bool checked)
{
    ui->BlueInput->setEnabled(checked);
    ui->RedInput->setEnabled(checked);
    ui->GreenInput->setEnabled(checked);
}



void WorkWindow::on_WriteFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Images (*.txt);;All files (*.*)");
if(!(fileName =="")){
       matrix->writeFile(fileName.toStdString());
       QMessageBox ::information(this,"Результат","Матрица была успешно загружена в файл");
}
}



void WorkWindow::on_CheckLightLevel_clicked()
{
    try{
        double result = matrix->checkLightLevel(ui->XInput->value(),
                                ui->YInput->value(),
                                ui->ZInput->value(),
                                ui->HeightInput->value());
        QMessageBox ::information(this,"Результат запроса","Уровень освещенности = "+QString::number(result));
    }
    catch(int e){
        QMessageBox ::warning(this,"Ошибка","Координаты выходят за помещение обьемом "+
                                  QString::number(matrix->getSizeN()+1) +"*"+QString::number(matrix->getSizeM()+1)+"*"+
                                  QString::number(ui->HeightInput->value()));
    }
}

void WorkWindow::on_CalcResultPowerBtn_clicked()
{
      QMessageBox ::information(this,"Результат","Затраты мощности = "+ QString::number(matrix->calcResultPower())+" Вт");
}
