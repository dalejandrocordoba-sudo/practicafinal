#ifndef SIMULACION_H
#define SIMULACION_H
#include <fstream>
#include <string>
#include <vector>
#include "particula.h"

class Simulacion {
private:
    double dt;
    double tMax;
    double g;
    double restitucion;
    double xMin;
    double xMax;
    double ySuelo;

    void resolverColisionBordes(Particula& p);
    void resolverColisionesParticulas(std::vector<Particula>& particulas);
    void escribirDatos(std::ofstream& archivo, const std::vector<Particula>& particulas, double tiempo);

public:
    Simulacion(double dt = 0.01, double tMax = 10.0, double g = 9.81,
               double restitucion = 0.8, double xMin = 0.0, double xMax = 50.0, double ySuelo = 0.0);

    void ejecutar(std::vector<Particula>& particulas, const std::string& nombreArchivo);
};


#endif // SIMULACION_H
