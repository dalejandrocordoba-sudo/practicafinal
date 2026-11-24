#include "obstaculo.h"
#include <cmath>

obstaculo::Obstaculo(int id, double x, double y, double ancho, double alto,
                     double resistencia, double e, int propietario,
                     const std::string& nombre)
    : id(id), x(x), y(y), ancho(ancho), alto(alto),
    resistenciaactual(resistencia), resistenciamaxima(resistencia),
    coeficienterestitucion(e), propietario(propietario),
    nombre(nombre), destruido(false) {}

bool obstaculo::recibirDano(double dano) {
    if (destruido) return true;
    resistenciaactual -= dano;
    if (resistenciaactual <= 0.0) {
        resistenciaactual = 0.0;
        destruido = true;
    }
    return destruido;
}

double obstaculo::fraccionresistencia() const {
    if (std::isinf(resistenciamaxima)) return 1.0;
    if (resistenciamaxima <= 0.0) return 0.0;
    return resistenciaactual / resistenciamaxima;
}