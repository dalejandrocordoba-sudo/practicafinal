#ifndef PARTICULA_H
#define PARTICULA_H


class Particula
{
public:
    Particula(float x = 0.0f, float y = 0.0f, float vx = 10.0f, float vy = 10.0f,
              float masa = 1.0f, float radio = 0.5f);

    float getx() const;
    float gety() const;
    float getvx() const;
    float getvy() const;
    float getmasa() const;
    float getradio() const;

    void setx(float x);
    void sety(float y);
    void setvx(float vx);
    void setvy(float vy);

private:
    float x;
    float y;
    float vx;
    float vy;
    float masa;
    float radio;
};

#endif // PARTICULA_H
