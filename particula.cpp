#include "particula.h"

particula::particula(int id, double x, double y, double vx, double vy,
                     double masa, double radio, int lanzador)
    : id(id), x(x), y(y), vx(vx), vy(vy), masa(masa), radio(radio),
    activa(true), lanzador(lanzador) {}

void particula::actualizarposicion(double dt, double g) {
    if (!activa) return;
    x += vx * dt;
    y += vy * dt - 0.5 * g * dt * dt;
    vy -= g * dt;
}

void particula::fusionarcon(particula& otra) {
    if (!activa || !otra.activa) return;

    const double M = masa + otra.masa;

    // Conservación del momento lineal
    vx = (masa * vx + otra.masa * otra.vx) / M;
    vy = (masa * vy + otra.masa * otra.vy) / M;

    // centro de masa
    x = (masa * x + otra.masa * otra.x) / M;
    y = (masa * y + otra.masa * otra.y) / M;

    // Conservación del área del círculo
    radio = std::sqrt(radio * radio + otra.radio * otra.radio);
    masa = M;

    otra.activa = false;
    otra.vx = otra.vy = 0.0;
}