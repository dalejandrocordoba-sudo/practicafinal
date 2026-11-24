#ifndef SIMULACION_H
#define SIMULACION_H

#include <fstream>
#include <string>
#include <vector>
#include "particula.h"

class Simulacion
{
public:
    Simulacion(float dt = 0.01f, float tMax = 10.0f, float g = -9.81f,
               float restitucion = 0.85f, float xMin = 0.0f, float xMax = 50.0f, float ySuelo = 0.0f);

    void ejecutar(std::vector<Particula>& particulas, const std::string& nombreArchivo);

private:
    float dt;
    float tMax;
    float g;
    float restitucion;
    float xMin;
    float xMax;
    float ySuelo;

    void calcularPaso(Particula& p);
    void resolverColisionBordes(Particula& p);
    void resolverColisionesParticulas(std::vector<Particula>& particulas);
    void escribirDatos(std::ofstream& archivo, const std::vector<Particula>& particulas, float tiempo);
};

#endif // SIMULACION_H