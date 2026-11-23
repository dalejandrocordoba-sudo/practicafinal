#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include "particula.h"
#include "simulacion.h"
#include "motorfisico.h"

using namespace std;

static void momentototal(const motorfisico m, double& px, double& py, double& masa){

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


    gestor.registrarpaso(0.0, motor.getparticulas(), {});
    for (long i =0; i < pasos; ++i){

        motor.pasosimulacion(dt);
        gestor.registrarpaso(motor.gettiempo(), motor.getparticulas(), motor.geteventospaso());

    }


    gestor.cerrartrayectoria();

    gestorarchivos::guardareventos("evento_simulacion.txt", motor.gethistorial());
    gestorarchivos::guardarobstaculos("obtaculos.txt", motor.getobstaculos());


    std::map<std::string, int> conteo;
    for (const auto& e : motor.gethistorial()) conteo[nombreevento(e.tipo)]++;
    std::cout << "\ncolisiones registradas:\n";
    for (const auto& kv : conteo) std::cout << "  " << kv.first << ": " << kv.second << "\n";

    std::cout << "Fusiones (instante, particulas, masa resultante):";
    for (const auto& e : motor.gethistorial())
        if (e.tipo == tipoevento::FUSION)
            std::cout << "  t=" << e.tiempo << " s  P" << e.id1 << " + P" << e.id2
                      << "  -> M=" << e.valor << " kg\n";

    double px1, py1, m1;
    momentoTotal(motor, px1, py1, m1);
    std::cout << "\nMasa total: " << m0 << " -> " << m1 << " kg (se conserva)\n";
    std::cout << "\nParticulas activas al final:\n";
    for (const auto& p : motor.getParticulas())
        if (p.isactiva())
            std::cout << "  P" << p.getid() << " m=" << p.getmasa() << " pos=("
                      << p.getX() << ", " << p.getY() << ")\n";

    std::cout << "\nArchivos generados: trayectoria_simulacion.txt, "
                 "eventos_simulacion.txt, obstaculos.txt\n";
    return 0;


    }








}
