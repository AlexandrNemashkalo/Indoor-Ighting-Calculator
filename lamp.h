#ifndef LAMP_H
#define LAMP_H

enum LampType
{
    lamp,
    led
};

class Lamp
{
protected:
    float power ;
    float intensity ;

public:
    Lamp();
    Lamp(float power_, float intensity_);
    Lamp(const Lamp &lamp);
    ~Lamp();

    static float MAX_POWER ;
    static float MIN_POWER ;
    static float DEFAULT_POWER;

    static float MAX_INTENSITY;
    static float MIN_INTENSITY;
    static float DEFAULT_INTENSITY;

    const float& getPower()const;
    const float& getIntensity()const;

    void setPower(float power_);
    void setIntensity(float intensity_);

    virtual LampType getType() ;

};

#endif // LAMP_H
