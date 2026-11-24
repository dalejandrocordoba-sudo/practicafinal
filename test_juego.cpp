#include <cassert>
#include <cmath>
#include <iostream>
#include "juegologica.h"

static int fallos = 0;
#define check(c) do { if (!(c)) { std::cerr << "fallo linea" <<__LINE__ << ":" #c "\n"; ++fallos; }} while (0)

static double energia (const particula& p) {
    return 0.5 * p.getmasa() * (p.getvx() +p.getvy()*p.getvy());

}

int main() {
    {
        motorfisico m(100,100,0.0);
        m.agregarparticula(particula(1,5,50,-20,7,2.0,1.0));
        const double e0 = energia(m.getparticulas()[0]);
        for (int i = 0; i< 400; ++i)m.pasosimulacion(0.005);
        check(std::fabs(energia(m.getparticulas()[0])-e0)<1e-9);
        check(m.getparticulas()[0].getvx()> 0);
    }

    {
        motorfisico m(100,100,0.0);
        m.agregarparticula(particula(1,40,50,10,0,2.0,2.0));
        m.agregarparticula(particula(2,46,50,-4,0,4.0,2.0));
        const double px0 = 2.0*10 +4.0*(-4);
        for (int i = 0; i < 100; ++i) m.pasosimulacion(0.005);
        const auto& ps = m.getparticulas();
        check(!ps[1].isactiva());
        check(std::fabs(ps[0].getmasa()-6.0) < 1e-12);
        check(std::fabs(ps[0].getmasa()*ps[0].getvx() -px0)<1e-9);
        int fusiones=0;
        for(const auto& e : m.gethistorial()) if (e.tipo == tipoevento::fusion) ++fusiones;
        check(fusiones == 1);
    }

    {
        motorfisico m(100,100,0.0);
        m.agregarobstaculo(obstaculo(1,50,0,10,100,1e9,0.5,0, "muro"));
        m.agregarparticula(particula(1,40,50,20,6,1.0,1.0));
        for(int i = 0; i< 100; ++i) m.pasosimulacion(0.005);
        const auto& p = m.getparticulas()[0];
        check(std::fabs(p.getvx()-(-10.0)) < 1e-9);
        check(std::fabs(p.getvy() - 6.0) <1e-9);
        check(std::fabs(p.getvy()-6.0)< 1.e-9);
        bool lado = false;
        for (const auto& e : m.gethistorial())
            if (e.tipo == tipoevento::obstaculo && e.detalle == "izquierdo") lado = true;
        check(lado);
    }
    {
        juegologica j;
        check(j.getmotor().getobstaculos().size() == 6);
        check(j.getturno() == 1);
        check(j.getestado() == juegologica::estado::esperando);
        check(j.lanzar(45, 40));
        check(!j.lanzar(45,40));
    }
    {
        juegologica j;
        j.lanzar(80,10);
        for (int i = 0;i <400 &&j.getestado() == juegologica::estado::en_vuelo;++i) j.avanzar(0.05);
        check(j.getestado() == juegologica::estado::esperando);
        check(j.getturno()==2);
    }
    {
        juegologica j;
        double mejor = 0 ;
        j.lanzar(45,55);
        while (j.getestado() == juegologica::estado::en_vuelo) j.avanzar(0.05);
        for (const auto& o : j.getmotor().getobstaculos()) {
            if(o.getpropietario() == 1)
                check(o.getresistenciaactual() == o.getresistenciamaxima());
            else if (o.getresistenciaactual() < o.getresistenciamaxima()) mejor =1;

        }
        std::cout << "tiro 45/55 daño a 32: " << (mejor ? "si" : "no" ) << "\n";
    }
    {
        juegologica j;
        int tiros=0;

        while (j.getestado() != juegologica::estado::terminado && tiros< 400) {

            const double ang =20+(tiros*7) %60;
            const double vel = 25+(tiros * 133) %60;
            j.lanzar(ang,vel);
            while (j.getestado() == juegologica::estado::en_vuelo)j.avanzar(0.5);
                ++tiros;
            }
            std::cout << "partida de prueba " << tiros << "tiros, ganar j" << j.getganador()
                      << " (" << j.getmensaje()<< ")\n";
            check(j.getestado() == juegologica::estado::terminado);
            check(j.getganador() == 1 || j.getganador() == 2);
            j.reiniciar();
            check(j.getestado() == juegologica::estado::esperando);
            check(j.getganador() == 0);
        }

    if (fallos == 0 ) std::cout << "todas las pruebas pasaron\n";
    return fallos;

    }







