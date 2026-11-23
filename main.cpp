#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include <string>
#include "particula.h"
#include "simulacion.h"
#include "motorfisico.h"

using namespace std;

static void momentototal(const motorfisico& m, double& px, double& py, double& masa){

    px = py = masa = 0.0;
    for (const auto& p : m.getparticulas()){

        if(!p.isactiva()) continue;
        px += p.getmasa() * p.getvx();
        py += p.getmasa() * p.getvy();
        masa += p.getmasa();
    }

}





int main()
{

    std::cout <<"Colisiones multiples"<<endl;

    motorfisico motor(100.0, 60.0, 9.81);



    const double INF = std::numeric_limits<double>::infinity();
    motor.agregarobstaculo(obstaculo(1, 20.0, 10.0, 8.0, 8.0, INF, 0.7, 0, "cuadrado 1"));
    motor.agregarobstaculo(obstaculo(2, 45.0, 28.0, 8.0, 8.0, INF, 0.6, 0, "cuadrado 2"));
    motor.agregarobstaculo(obstaculo(3, 70.0,  8.0, 8.0, 8.0, INF, 0.8, 0, "cuadrado 3"));
    motor.agregarobstaculo(obstaculo(4, 80.0, 38.0, 8.0, 8.0, INF, 0.5, 0, "cuadrado 4"));



    motor.agregarparticula(Particula(1,  5.0, 30.0,  38.0,  8.0, 2.0, 1.6));
    motor.agregarparticula(Particula(2, 95.0, 40.0, -34.0,  6.0, 3.0, 1.9));
    motor.agregarparticula(Particula(3, 50.0, 52.0,  14.0, -4.0, 1.5, 1.4));
    motor.agregarparticula(Particula(4, 30.0,  5.0, -27.0, 25.0, 2.5, 1.7));
    motor.agregarparticula(Particula(5, 60.0, 15.0, -30.0, 18.0, 1.0, 1.2));
    motor.agregarparticula(Particula(6, 15.0, 22.0,  29.0, -2.0, 1.8, 1.5));


    gestorarchivos gestor;
    if (!gestor.abrirtrayectoria("trayectoria_simulacion.txt")){
        std::cerr <<"error, no se puede abrir el archivo";
        return 1;

    }

    double px0, py0, m0;
    momentototal(motor, px0, py0, m0);

    const double dt = 0.005;
    const double duracion = 10.0;
    const long pasos = static_cast<long>(duracion / dt);


    s.ejecutar(particulas, "trayectoria_colisiones.txt");

    return 0;


    }





