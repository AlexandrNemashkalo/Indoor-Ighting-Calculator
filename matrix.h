#ifndef MATRIX_H
#define MATRIX_H

#include "lamp.h"
#include <fstream>
#include <vector>

class Matrix
{
    private:
        std::vector<std::vector<Lamp*>> matrix;

    public:
        Matrix(int n_, int m_);
        Matrix(const Matrix& matrix);
        Matrix(const std::string& fileName);
        ~Matrix();

        const Lamp* getLamp(int n_,int m_) const;
        Lamp* getForUpdateLamp(int n_,int m_) const;

        void setLamp(int n_,int m_, Lamp *lamp);

        const int getSizeN() const;
        const int getSizeM() const;

        void writeFile(const std::string& fileName) const;

        double checkLightLevel(float x,float y,float z, float height) const;
        double calcResultPower()const;
};





#endif // MATRIX_H
