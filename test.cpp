#include "cassert"
#include "iostream"
#include "lamp.h"
#include <QRandomGenerator>
#include "float.h"
#include "matrix.h"
#include "led.h"

namespace Random
{
    float realNumber(float from = FLT_MIN/2, float to = FLT_MAX/2)
    {
        /* Данная функция генерирует случайное чило в указанном диапазоне
         */
        return from + (to - from) * QRandomGenerator::global()->generateDouble();
    }
}


void assertDefaultConstructorLamp(const Lamp& lamp)
{
    /* Проверяет конструктор по умолчанию
     */
    assert(lamp.getIntensity() - Lamp::DEFAULT_INTENSITY < 1e-6
           && lamp.getPower() - Lamp::DEFAULT_POWER < 1e-6);
}


void assertInitConstructorLamp(const Lamp& lamp)
{
    /* Проверяет конструктор инициализации
     */
    assert(lamp.getIntensity() <= Lamp::MAX_INTENSITY
           && lamp.getIntensity() >= Lamp::MIN_INTENSITY);
    assert(lamp.getPower() <= Lamp::MAX_POWER
           && lamp.getPower()>=Lamp::MIN_POWER);
}


void assertCopyConstructorLamp(const Lamp& first, const Lamp& second)
{
    /* Проверяет конструктор копирования
     * Входные параметры: первая и вторая лампа
     */
    assert(first.getPower() - second.getPower() < 1e-6);
    assert(first.getIntensity() - second.getIntensity() < 1e-6);
}


void assertStability(Lamp& object)
{
    /* Проверяет методы доступа полей класса
     * Проверяет корректность веденных данных при
     * правильных и  неверных вносимых значениях
     */
    float checkPower = 120;
    object.setPower(checkPower);
    assert((object.getPower() - checkPower < 1e-6));
    float errorPower = Random::realNumber(Lamp::MAX_POWER);
    object.setPower(errorPower);
    assert((object.getPower() - Lamp::MAX_POWER < 1e-6));

    float checkIntensity = 110;
    object.setIntensity(checkIntensity);
    assert((object.getIntensity() - checkIntensity < 1e-6));
    float errorIntensiry = Random::realNumber(Lamp::MAX_INTENSITY);
    object.setIntensity(errorIntensiry);
    assert((object.getIntensity()  - Lamp::MAX_INTENSITY < 1e-6));
}


void assertCopyConstructorMatrix(const Matrix& first, const Matrix& second)
{
    /* Проверяет конструктор копирования матрицы
     * Входные параметры: первая и вторая матрица
     */
    assert(first.getSizeN() == second.getSizeN());
    assert(first.getSizeM() == second.getSizeM());
    for (int i = 0 ; i < first.getSizeN(); ++i)
    {
        for (int j = 0; j < first.getSizeM(); ++j)
        {
            assert(first.getLamp(i,j)->getPower() - second.getLamp(i,j)->getPower() < 1e-6);
            assert(first.getLamp(i,j)->getIntensity() - second.getLamp(i,j)->getIntensity() < 1e-6);
        }
    }
}


void assertInitConstructorMatrix(Matrix& object, int n, int m)
{
    /* Проверяет конструктор инициализации матрицы
     * Входные парамерты: матрица, количество строк, количество столбцов
     */
    assert(object.getSizeN() == n);
    assert(object.getSizeM() == m);
}


void assertGetMatrix(const Matrix& example)
{
    /* Проверяет метод доступа к элементу:
     * Происхлдит вывод на экран всех хранимых объектов
     */
    for (int i = 0; i < example.getSizeN(); i++)
    {
        for (int j = 0; j < example.getSizeM(); j++)
        {
            std::cout << example.getLamp(i,j)->getPower() << " " <<
                                example.getLamp(i,j)->getIntensity() << "    ";
        }
        std::cout << std::endl;
    }
}


void startTests()
{
    Lamp defaultObject;
    assertDefaultConstructorLamp(defaultObject);
    assertStability(defaultObject);

    for (int i = 0; i < 1000; i++)
        {
            float random_p = Random::realNumber(Lamp::MIN_POWER - 100,
                                          Lamp::MAX_POWER + 100);

            float random_i = Random::realNumber(Lamp::MIN_INTENSITY - 100,
                                          Lamp::MAX_INTENSITY + 100);

            Lamp randomObject(random_p, random_i);
            assertInitConstructorLamp(randomObject);
            Lamp copyObject(randomObject);
            assertCopyConstructorLamp(randomObject,copyObject);
            assertStability(randomObject);
        }

    Matrix example = Matrix(2,3);
    assertInitConstructorMatrix(example,2,3);
    Matrix copyExample(example);
    assertCopyConstructorMatrix(example,copyExample);

    Matrix example3 = Matrix(3,3);
    try{
    //Matrix example2 = Matrix("/home/alexandr/Work/HSE/laba-qt/oop/test.txt");
    //example2.writeFile("/home/alexandr/Work/HSE/laba-qt/oop/output.txt");
    //assertGetMatrix(example2);
    }
    catch(int e){
        if(e==3)
              std::cout <<"не получилось"<<std::endl;
    }
    catch(std::invalid_argument q){
           std::cout <<"файл поврежден"<<std::endl;
    }

    std::cout<<"All tests completed"<<std::endl;
}
