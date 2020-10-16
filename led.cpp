#include "led.h"


float Led::MAX_COLOR_VALUE = 255;
float Led::MIN_COLOR_VALUE = 0;
float Led::DEFAULT_COLOR_VALUE = 100;

Led::Led():Lamp()
{
    this->power = Lamp::DEFAULT_POWER;
    this->intensity = Lamp::DEFAULT_INTENSITY;
    this->red =Led::DEFAULT_COLOR_VALUE;
    this->blue =Led::DEFAULT_COLOR_VALUE;
    this->green =Led::DEFAULT_COLOR_VALUE;
}

Led::Led(float power_ = Lamp::DEFAULT_POWER, float intensity_ = Lamp::DEFAULT_INTENSITY,
         float red_= Led::DEFAULT_COLOR_VALUE,
         float green_ = Led::DEFAULT_COLOR_VALUE,
         float blue_ = Led::DEFAULT_COLOR_VALUE) : Lamp(power_, intensity_)
{
    Led::setBlue(blue_);
    Led::setGreen(green_);
    Led::setRed(red_);
}

Led::Led(const Led &led)
{
    this->power = led.power;
    this->intensity = led.intensity;
    this->red = led.red;
    this->green = led.green;
    this->blue = led.blue;
}

Led::~Led()
{

}

float Led::currIntensity(const Led & led) const
{
    float currI = led.intensity * (led.red + led.green + led.blue)/(3*Led::MAX_COLOR_VALUE);
    return currI;
}

const float& Led::getRed()const
{
    return this->red;
}

const float& Led::getGreen()const
{
    return this->green;
}

const float& Led::getBlue()const
{
    return this->blue;
}

void Led::setBlue(float blue_)
{
    if(blue_ < Led::MIN_COLOR_VALUE)
        this->blue = Led::MIN_COLOR_VALUE;
    else if(blue_ > Led::MAX_COLOR_VALUE)
        this->blue = Led::MAX_COLOR_VALUE;
    else
        this->blue =blue_;
}

void Led::setGreen(float green_)
{
    if(green_ < Led::MIN_COLOR_VALUE)
        this->green = Led::MIN_COLOR_VALUE;
    else if(green_ > Led::MAX_COLOR_VALUE)
        this->green = Led::MAX_COLOR_VALUE;
    else
        this->green =green_;
}

void Led::setRed(float red_)
{
    if(red_ < Led::MIN_COLOR_VALUE)
        this->red = Led::MIN_COLOR_VALUE;
    else if(red_ > Led::MAX_COLOR_VALUE)
        this->red = Led::MAX_COLOR_VALUE;
    else
        this->red =red_;
}

LampType Led::getType()
{
    return led;
}

