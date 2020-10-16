#ifndef LED_H
#define LED_H

#include "lamp.h"
class Led : public Lamp
{
private:
    float red;
    float green;
    float blue;

public:
    Led();
    Led(float power_, float intensity_, float red_, float green_, float blue_);
    Led(const Led& led);
    ~Led();

    static float MAX_COLOR_VALUE ;
    static float MIN_COLOR_VALUE ;
    static float DEFAULT_COLOR_VALUE;

    float currIntensity(const Led &led) const;

    const float& getRed()const;
    const float& getGreen()const;
    const float& getBlue()const;

    void setRed(float red_);
    void setGreen(float green_);
    void setBlue(float blue_);

    virtual LampType getType() override;

};

#endif // LED_H
