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
    /* Конструктор инициализации 
     * Входные параметры: указатель на родительский виджет, указатель матрицу
     */
{
    ui->setupUi(this);

    ui->PowerInput->setMaximum(Lamp::MAX_POWER);
    ui->PowerInput->setMinimum(Lamp::MIN_POWER);
    ui->IntensityInput->setMaximum(Lamp::MAX_INTENSITY);
    ui->IntensityInput->setMinimum(Lamp::MIN_INTENSITY);
    ui->RedInput->setMaximum(Led::MAX_COLOR_VALUE);
    ui->RedInput->setMinimum(Led::MIN_COLOR_VALUE);

    for(int i=0;i<matrix->getSizeN();i++)
    {
        QHBoxLayout *horisontLayout= new QHBoxLayout;
        for(int j=0;j<matrix->getSizeM();j++)
        {
            QDynamicButton *button = new QDynamicButton(this,i,j);
            if(i==0 && j==0){
                button->setChecked(true);
                currButton = button;
            }
            if(matrix->getForUpdateLamp(i,j)->getType() ==0)
            {
                button->setText(QString::number( matrix->getLamp(i,j)->getPower())+" Вт\n"
                             +QString::number( matrix->getLamp(i,j)->getIntensity())+" кд");
            }
            else
            {
                Led *led = dynamic_cast<Led* >(matrix->getForUpdateLamp(i,j));
                button->setText(QString::number( matrix->getLamp(i,j)->getPower())+" Вт\n"
                                "I="+QString::number(led->currIntensity(*led))+" кд");
            }

            button->setStyleSheet(getStyleStringForButton(matrix->getForUpdateLamp(i,j)->getType()));
            horisontLayout->addWidget(button);
            connect(button, SIGNAL(clicked()), this, SLOT(slotGetLamp()));
        }
        ui->verticalLayout->addLayout(horisontLayout);
    }
    updateLampInfo(0,0);
}


WorkWindow::~WorkWindow()
{
    /* Деструктор
     */
    delete currButton;
    delete ui;
}

void WorkWindow::slotGetLamp()
{
    /* Метод, который вызывается при нажатии на радиокнопку с лампой
     */
    currButton =(QDynamicButton*) sender();
    updateLampInfo(currButton->getN(),currButton->getM());
}

void WorkWindow::on_SaveLampButton_clicked()
{
    /* Метод который редактирует значение определенного источника света
     */
    bool isLed = ui->IsLed->isChecked();
    if(isLed)
    {
       Led * led = new Led(ui->PowerInput->value(),
                     ui->IntensityInput->value(),
                     ui->RedInput->value(),
                     ui->GreenInput->value(),
                     ui->BlueInput->value());
       matrix->setLamp(currButton->getN(),currButton->getM(),led);
       float resultIntensity =led->currIntensity(*led);
       ui->CurrIntensity->setText(QString::number(resultIntensity)+" кд");

       currButton->setStyleSheet(getStyleStringForButton(LampType::led));
       currButton->setText(QString::number(ui->PowerInput->value())+" Вт\n"
                       +QString::number(resultIntensity) +" кд");
    }
    else
    {
       Lamp * lamp = new Lamp(ui->PowerInput->value(),ui->IntensityInput->value());
       matrix->setLamp(currButton->getN(),currButton->getM(),lamp);
       ui->CurrIntensity->setText("");

       currButton->setStyleSheet(getStyleStringForButton(LampType::lamp));
       currButton->setText(QString::number(ui->PowerInput->value())+" Вт\n"
                       +QString::number(ui->IntensityInput->value()) +" кд");
    }
}


void WorkWindow::updateLampInfo(int n_,int m_) const
{
    /* Метод, который устанавливает значения в редакторе лампы
     * Входные параметры: позиция источника света в матрице
     */
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
        ui->CurrIntensity->setText(QString::number(led->currIntensity(*led))+" кд");
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

QString WorkWindow::getStyleStringForButton(LampType type) const
    /* Метод  возвращает строку с стилями для кнопки
     * Входные параметры: тип источника света
     */
{
    if(type ==led){
        return "QRadioButton::indicator {width: 50px;height: 50px;}"
               "QRadioButton::indicator::unchecked{ image: url(:/resource/img/lad.png)}"
               "QRadioButton::indicator::checked{image: url(:/resource/img/ladActive.png)}";
    }
    else{
        return "QRadioButton::indicator {width: 50px;height: 50px;}"
               "QRadioButton::indicator::unchecked{ image: url(:/resource/img/lamp.png)}"
               "QRadioButton::indicator::checked{image: url(:/resource/img/lampActive.png)}";
    }
}



void WorkWindow::on_IsLed_clicked(bool checked)
{
    /* Метод, который устанавлиет Enable
     * Входные параметры: bool
     */
    ui->BlueInput->setEnabled(checked);
    ui->RedInput->setEnabled(checked);
    ui->GreenInput->setEnabled(checked);
}



void WorkWindow::on_WriteFileBtn_clicked()
{
    /* Метод, который отрывает окно с выбором файла 
     * и вызывает функцию для записи матрицы в файл
     */
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
    /* Метод, который вызывает функцию по подсчету уровня освещенности
     * и выводит значение в модальном окне
     */
    try{
        double result = matrix->checkLightLevel(ui->XInput->value(),
                                ui->YInput->value(),
                                ui->ZInput->value(),
                                ui->HeightInput->value());
        QMessageBox ::information(this,"Результат запроса","Уровень освещенности = "+QString::number(result) +" люкс");
    }
    catch(int e){
        QMessageBox ::warning(this,"Ошибка","Координаты выходят за помещение обьемом "+
                                  QString::number(matrix->getSizeN()+1) +"*"+QString::number(matrix->getSizeM()+1)+"*"+
                                  QString::number(ui->HeightInput->value())+" м³");
    }
}

void WorkWindow::on_CalcResultPowerBtn_clicked()
{
    /* Метод, который выводит в мадальном окне
     * результат подсчета результирующей мощности
     */
      QMessageBox ::information(this,"Результат","Затраты мощности = "+ QString::number(matrix->calcResultPower())+" Вт");
}
