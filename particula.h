#ifndef PARTICULA_H
#define PARTICULA_H


class Particula
{
public:
    Particula(float x = 0.0f, float y = 0.0f, float vx = 10.0f, float vy = 10.0f,
              float masa = 1.0f, float radio = 0.5f);

    float getX() const;
    float getY() const;
    float getVX() const;
    float getVY() const;
    float getMasa() const;
    float getRadio() const;

    void setX(float x);
    void setY(float y);
    void setVX(float vx);
    void setVY(float vy);

private:
    float x;
    float y;
    float VX;
    float VY;
    float masa;
    float radio;
};

#endif // PARTICULA_H
