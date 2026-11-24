#ifndef PARTICULA_H
#define PARTICULA_H

#include <cmath>


class particula {
private:
    int id;
    double x, y;
    double vx, vy;
    double masa;
    double radio;
    bool activa;
    int lanzador;

public:
    particula(int id, double x, double y, double vx, double vy,
              double masa, double radio, int lanzador = 0);


    void actualizarposicion(double dt, double g);

    void fusionarcon(particula& otra);

    int getid() const { return id; }
    double getx() const { return x; }
    double gety() const { return y; }
    double getvx() const { return vx; }
    double getvy() const { return vy; }
    double getmasa() const { return masa; }
    double getradio() const { return radio; }
    bool isactiva() const { return activa; }
    int getlanzador() const { return lanzador; }

    double rapidez() const { return std::sqrt(vx * vx + vy * vy); }
    double momentolineal() const { return masa * rapidez(); }

    void setposicion(double nx, double ny) { x = nx; y = ny; }
    void setvelocidad(double nvx, double nvy) { vx = nvx; vy = nvy; }
    void setactiva(bool a) { activa = a; }
};

#endif // PARTICULA_H
