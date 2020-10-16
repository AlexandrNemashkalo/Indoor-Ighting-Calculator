#include "matrix.h"
#include <vector>
#include "lamp.h"
#include <iostream>
#include <cmath>
#include "led.h"

Matrix::Matrix(int n, int m)
{
    /* Конструктор инициализации
     * Входные параметры: количество строк, количество столбцов
     */
    if(n<1 || m<1)
        throw 1;
    matrix.resize(n);
    for(int i =0; i<n;i++){
        matrix[i].resize(m);
        for(int j =0; j<m;j++)
            matrix[i][j] = new Lamp();
    }

}

Matrix::Matrix(const Matrix &M)
{
    /* Конструктор копирования
     */
    matrix.resize(M.matrix.size());
    for(int i =0; i<M.matrix.size();i++)
    {
        matrix[i].resize(M.matrix[0].size());
        for(int j =0; j<M.matrix[0].size();j++){
            matrix[i][j] = new Lamp(*M.matrix[i][j]);
        }
    }
}

Matrix::Matrix(const std::string & fileName)
{
    /* Метод, который считывает данные из текстового файла
        * Данные файла должны содержатся в следующем ввиде
        * M[0][0].P  M[0][0].I (M[0][0].Red M[0][0].Green M[0][0].Blue)
        * M[0][1].P  M[0][1].I
        * ...
        * M[0][m-1].P  M[0][m-1].I
        * (пустая строка)
        * M[1][0].P  M[1][0].I
        * ...
        * M[1][m-1].P  M[1][m-1].I
        * (пустая cтрока)
        * ...
        * M[n-1][0].P  M[n-1][0].I
        * ...
        * M[n-1][m-1].P  M[n-1][m-1].I
        *
        * где n и m размерность матрицы, P - мощность, I - интенсивность света,
        * если есть скобочки со значениями значит это светодиодная лампа, если нет - обычная
        * Входные параметры:  абсолютный путь к файлу
        */
   std::ifstream file(fileName);
   std::string buff;
   int i = 0;
   int j = 0;
   matrix.resize(1);

   if (file.is_open())
   {
       while (!file.eof())
       {
           std::getline(file, buff);
           if(!(buff==""))
           {
               if (!(buff=="-"))
               {
                   std::string power_in;
                   std::string intensity_in;
                   std::string red_in;
                   std::string green_in;
                   std::string blue_in;

                   int space = 0;
                   for (int a = 0; a < buff.length(); ++a)
                   {
                       if(buff[a]=='(' || buff[a]==')')
                           continue;

                       if (!(buff[a] == ' '))
                       {
                           switch(space)
                           {
                               case 0:
                                   power_in += buff[a];
                                   break;
                               case 1:
                                   intensity_in += buff[a];
                                   break;
                               case 2:
                                   red_in+=buff[a];
                                   break;
                               case 3:
                                   green_in +=buff[a];
                                   break;
                               case 4:
                                   blue_in += buff[a];
                                   break;
                           }
                       }
                       else
                           space += 1;
                   }

                   matrix[i].resize(j+1);
                   if(space==1)
                   {
                       matrix[i][j] = new Lamp(std::stof(power_in),std::stof(intensity_in));
                   }
                   else if(space==4){
                       matrix[i][j] = new Led(std::stof(power_in),
                                              std::stof(intensity_in),
                                              std::stof(red_in),
                                              std::stof(green_in),
                                              std::stof(blue_in));
                   }
                   else{
                       throw 3;
                   }
                   ++j;
               }
               else
               {
                   ++i;
                   matrix.resize(i+1);
                   j=0;
               }
           }
       }
   }
   file.close();
   int jmax = matrix[0].size();
   for(int k=0 ; k<matrix.size();k++){
       if(matrix[k].size()!= jmax)
           throw 3;
   }
}

Matrix::~Matrix()
{
    /* Деконструктор
     */
    for(int i =0;i<matrix.size();++i){
        for(int j =0;j<matrix[i].size();++j){
        delete matrix[i][j];
        }
    }
    matrix.clear();
}

const Lamp* Matrix::getLamp(int i_,int j_) const
{
    /* Метод, возвращающий элемент матрицы по индексу
     * Входные параметры: индекс элемента (строка,столбец)
     */
    if(i_ >= 0 && i_ <= matrix.size() &&
            i_ >= 0 && j_ <= matrix[0].size())
        return this->matrix[i_][j_];
}

void Matrix::setLamp(int n,int m,Lamp *l)
{
    /* Метод, возвращающий элемент матрицы по индексу
     * Входные параметры: индекс элемента (строка,столбец)
     */
    if(n >= 0 && n <= matrix.size() &&
            m >= 0 && m <= matrix[0].size())
    {
        matrix[n][m] = l;
    }
}

Lamp* Matrix::getForUpdateLamp(int n_,int m_) const
{
    /* Метод, возвращающий элемент матрицы по индексу
     * Входные параметры: индекс элемента (строка,столбец)
     */
    if(n_ >= 0 && n_ <= matrix.size() &&
            m_ >= 0 && m_ <= matrix[0].size())
    {
        return matrix[n_][m_];
    }
}


const int Matrix::getSizeN() const
{
    /* Возвращает количество строк;
     */
    return matrix.size();
}

const int Matrix::getSizeM() const
{
    /* Возвращает количество столбцов;
     */
    return matrix[0].size();
}


void Matrix::writeFile(const std::string &fileName) const
{
    /* Метод, считывающий данные из матрицы и записывает их в файл
     *Входные параметры: абсолютный путь к файлу
     */
    std::ofstream file;
    file.open(fileName);
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            Led *led = dynamic_cast<Led* >(matrix[i][j]);
            if(led){
                file << led->getPower() << " " <<
                led->getIntensity() << " "<<
                "("<<led->getRed()<<" "<<
                     led->getGreen()<<" "<<
                     led->getBlue() <<")"<<std::endl;
            }else{
                file << matrix[i][j]->getPower() << " " <<
                matrix[i][j]->getIntensity() << std::endl;
            }


        }
        if(i!= matrix.size()-1)
            file<<"-"<<std::endl;
    }
    file.close();
}

double Matrix::checkLightLevel(float x, float y, float z, float height) const
{
    /* Метод позволяющий рассчитать освещенность произвольной точуи помещения
     * Входные параметры: x,y,z(координаты точки) , высота помещения
     */
    if (z < height && z>=0 && x>=0 && x <= matrix.size()+1
            && y >= 0 && y <= matrix[0].size()+1)
    {
        float curIntensity;
        double illuminance = 0;
        for (int i = 0; i < matrix.size(); i++)
        {
            curIntensity =0;
            for (int j = 0; j < matrix[0].size(); j++)
            {

                Led *led = dynamic_cast<Led* >(matrix[i][j]);
                if(led)
                    curIntensity = led->currIntensity(*led);
                else{
                    curIntensity = matrix[i][j]->getIntensity();
                }
                illuminance += (curIntensity) * (height-z)/
                               pow((pow(i-x+1, 2) + pow(j-y+1, 2) +
                                    pow(height-z, 2)), 3/2);
            }
        }
        return illuminance;
    }
    else
        throw 2; //координаты выходят за рамки помещения
}

double Matrix::calcResultPower() const{
    double result = 0;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            result += matrix[i][j]->getPower();
        }
    }
    return result;
}

