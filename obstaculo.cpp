#include "obstaculo.h"
#include <cmath>

obstaculo::Obstaculo(int id, double x, double y, double ancho, double alto,
                     double resistencia, double e, int propietario,
                     const std::string& nombre)
    : id(id), x(x), y(y), ancho(ancho), alto(alto),
    resistenciaActual(resistencia), resistenciaMaxima(resistencia),
    coeficienteRestitucion(e), propietario(propietario),
    nombre(nombre), destruido(false) {}