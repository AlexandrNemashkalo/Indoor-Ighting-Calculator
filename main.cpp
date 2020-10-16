#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include "tests.h"
#include "matrix.h"
#include "led.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    try
    {
        float height =5;
        Matrix matrix = Matrix(1,2);
        double ans = matrix.checkLightLevel(0,0,0,height);
        std::cout << "Illumination in (0,0,0) = " << ans << std::endl;
    }
    catch(int a)
    {
        switch (a)
        {
        case 1:
            std::cout<<"Введена неправильная размерность матрицы"<<std::endl;
            break;
        case 2:
            std::cout<<"Координаты точки выходят за рамки помещения"<<std::endl;
            break;
        default:
            break;
        }
    }
    startTests();

    return a.exec();

    //return 0;
}
