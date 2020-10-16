#ifndef MATRIX_H
#define MATRIX_H

#include "lamp.h"
#include <fstream>
#include <vector>

class Matrix
{
    private:
        std::vector<std::vector<Lamp*>> matrix;
        //std::vector<std::vector<Lamp>> vector;

    public:
        Matrix(int n_, int m_);
        Matrix(const Matrix& matrix);
        Matrix(const std::string& fileName);
        ~Matrix();

        const Lamp* getLamp(int n_,int m_) const;


        void setLamp(int n_,int m_, Lamp *lamp);
        Lamp* getForUpdateLamp(int n_,int m_);
        const int getSizeN() const;
        const int getSizeM() const;

        void writeFile(const std::string& fileName) const;

        double checkLightLevel(float x,float y,float z, float height) const;
        double calcResultPower()const;
};


/* Метод, который считывает данные из текстового файла
    * Данные файла должны содержатся в следующем ввиде
    * M[0][0].P  M[0][0].I
    * M[0][1].P  M[0][1].I
    * ...
    * M[0][m-1].P  M[0][m-1].I
    * (пустая строка)
    * M[1][0].P  M[1][0].I
    * ...
    * M[1][m-1].P  M[1][m-1].I
    * (пустая трока)
    * ...
    * M[n-1][0].P  M[n-1][0].I
    * ...
    * M[n-1][m-1].P  M[n-1][m-1].I
    *
    * где n и m размерность матрицы, P - мощность, I - интенсивность света
    * Входные параметры:  абсолютный путь к файлу
    */


#endif // MATRIX_H
