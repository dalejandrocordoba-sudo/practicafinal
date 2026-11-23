#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include "particula.h"
#include "simulacion.h"
#include "MotorFisisco.h"

static void momentoTotal ()


using namespace std;


int main()
{

    vector<Particula> particulas;
    // Particula(x, y, vx, vy, masa, radio)
    particulas.emplace_back(2.0f, 1.0f, 18.0f, 22.0f, 2.0f, 0.8f);
    particulas.emplace_back(35.0f, 1.0f, -15.0f, 24.0f, 1.5f, 0.8f);

    // Simulacion(dt, tMax, g, restitucion, xMin, xMax, ySuelo)
    Simulacion s(0.01f, 8.0f, -9.81f, 0.85f, 0.0f, 40.0f, 0.0f);

    s.ejecutar(particulas, "trayectoria_colisiones.txt");

    return 0;
}
