#include "particula.h"

Particula::Particula(float x, float y, float vx, float vy, float masa, float radio)
    : x(x), y(y), VX(vx), VY(vy), masa(masa), radio(radio) {}

float Particula::getX() const { return x; }
float Particula::getY() const { return y; }
float Particula::getVX() const { return VX; }
float Particula::getVY() const { return VY; }
float Particula::getMasa() const { return masa; }
float Particula::getRadio() const { return radio; }

void Particula::setX(float x) { this->x = x; }
void Particula::setY(float y) { this->y = y; }
void Particula::setVX(float vx) { this->VX = vx; }
void Particula::setVY(float vy) { this->VY = vy; }