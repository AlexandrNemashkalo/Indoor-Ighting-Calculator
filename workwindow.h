#ifndef WORKWINDOW_H
#define WORKWINDOW_H

#include <QDialog>
#include "matrix.h"
#include "qdynamicbutton.h"

namespace Ui {
class WorkWindow;
}

class WorkWindow : public QDialog
{
    Q_OBJECT

public:
    Matrix *matrix = nullptr; //= Matrix(1,2);
    explicit WorkWindow(QWidget *parent = nullptr,Matrix *matrix = nullptr);
//    void setCurrButton(QDynamicButton * btn);
    ~WorkWindow();

private slots:
    void slotGetLamp();
    void on_SaveLampButton_clicked();
    void on_IsLed_clicked(bool checked);
    void on_WriteFileBtn_clicked();
    void on_CheckLightLevel_clicked();

    void on_CalcResultPowerBtn_clicked();

private:
    QDynamicButton * currButton = nullptr;
    Ui::WorkWindow *ui;
    void UpdateLampInfo(int m,int n);

};

#endif // WORKWINDOW_H
