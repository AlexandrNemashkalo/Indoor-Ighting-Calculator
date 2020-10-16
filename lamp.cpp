#include "lamp.h"


Lamp::Lamp()
{
    /* Конструктор по умолчанию
     * Входные параметры: мощность, интенсивность света
    */
    this->intensity =Lamp::DEFAULT_INTENSITY;
    this->power = Lamp::DEFAULT_POWER;
}

Lamp::Lamp(float power_ = Lamp::DEFAULT_POWER,
           float intensity_ = Lamp::DEFAULT_INTENSITY)
{
    /* Конструктор по умолчанию и конструктор инициализации
     * Входные параметры: мощность, интенсивность света
    */
    Lamp::setIntensity(intensity_);
    Lamp::setPower(power_);
}

float Lamp::MAX_POWER =1000 ;
float Lamp::MIN_POWER = 0 ;
float Lamp::DEFAULT_POWER = 100;

float Lamp::MAX_INTENSITY =1000;
float Lamp::MIN_INTENSITY = 0;
float Lamp::DEFAULT_INTENSITY = 50;


Lamp::Lamp(const Lamp& lamp)
{
    /* Конструктор копирования
    */
    this->power =lamp.power;
    this->intensity= lamp.intensity;
}

Lamp::~Lamp()
{
    /* Деструктор класса
    */
}

const float& Lamp::getPower() const
{
    /* Метод, возвращающий мощность лампы
    */
    return this->power;
}

const float& Lamp::getIntensity() const
{
    /* Метод, возвращаюший интенсивность света лампы
    */
    return this->intensity;
}

void Lamp::setPower(float power_)
{
    /* Метод, устанавливающий значение мощности лампы
     * Входные параметры: мощность
    */
    if(power_ < Lamp::MIN_POWER)
        this->power = Lamp::MIN_POWER;
    else if(power_ > Lamp::MAX_POWER)
        this->power = Lamp::MAX_POWER;
    else
        this->power =power_;
}

void Lamp::setIntensity(float intensity_)
{
    /* Метод, устанавливающий значение интенсивности света лампы
     * Входные параметры: интенсивность света
    */
    if(intensity_<Lamp::MIN_INTENSITY)
        this->intensity =Lamp::MIN_INTENSITY;
    else if(intensity_ > Lamp::MAX_INTENSITY)
        this->intensity=Lamp::MAX_INTENSITY;
    else
        this->intensity = intensity_;
}

LampType Lamp::getType()
{
    return lamp;
}


