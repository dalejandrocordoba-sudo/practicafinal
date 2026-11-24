#include "juegologica.h"
#include <cmath>
#include <sstream>


namespace {
const double pi =3.14159265358979323846;
inline double arad(double g) { return g * pi / 180.0; }

}

juegologica::juegologica()
    : motor(ancho,alto,gravedad,factordano),
    estado(estado::esperando), turno(1),ganador(0),
    lanzamientos(0),tiempovuelo(0.0) {
    construirescenario();
}


void juegologica::reiniciar() {
    motor = motorfisico(ancho,alto,gravedad,factordano);
    estado = estado::esperando;
    turno = 1;
    ganador = 0;
    tiempovuelo = 0.0;
    mensaje.clear();
    construirescenario();
}

void juegologica::construirescenario() {
    crearinfraestructura(1);
    crearinfraestructura(2);

}

void juegologica::crearinfraestructura(int jugador) {
    const double x0 = estructura_x0;
    const double anchototal = 2 * pilar_ancho + hueco;
    const double xpilarizq = x0;
    const double xpilarder = x0 + pilar_ancho + hueco;



    auto xespejo = [&] (double x, double w) {
        return jugador == 1 ? x : ancho - (x + w);
    };

    const int base = (jugador - 1 ) * 3;
    motor.agregarobstaculo(obstaculo(base + 1, xespejo(xpilarizq, pilar_ancho),0.0,
                                     pilar_ancho,pilar_alto,res_pilar,0.5, jugador, "pilar"));
    motor.agregarobstaculo(obstaculo(base +2, xespejo(xpilarder,pilar_ancho), 0.0,
                                     pilar_ancho, pilar_alto, res_pilar, 0.5, jugador, "pilar"));
    motor.agregarobstaculo(obstaculo(base+ 3, xespejo (x0,anchototal), pilar_alto,
                                     anchototal,tejado_alto,res_tejado,0.4, jugador, "tejado"));
}

double juegologica::rivalx(int jugador) {
    const double centro = estructura_x0 + pilar_ancho + hueco / 2.0;
    return jugador == 1 ? centro : ancho-centro;
}

double juegologica::bocax( int jugador, double angulogrados) {
    const double d = largo_cañon * std::cos(arad(angulogrados));
    return jugador ==1 ? cañon_x + d : (ancho - cañon_x) - d;
}
double juegologica::bocay(double angulogrados) {
    return cañon_y + largo_cañon * std::sin(arad(angulogrados));
}

bool juegologica::lanzar(double angulogrados,double velocidad) {
    if (estado != estado::esperando) return false;
    if (angulogrados < 0.0)angulogrados = 0.0;
    if (angulogrados > 90.0) angulogrados = 90.0;
    if (velocidad < 0.0) velocidad = 0.0;

    const double a = arad(angulogrados);

    double vx = velocidad * std::cos(a);
    const double vy = velocidad * std::sin(a);
    if (turno == 2) vx = -vx;

    ++lanzamientos;
    motor.limpiarparticulas();
    motor.agregarparticula(particula(100+ lanzamientos,
                                     bocax(turno, angulogrados),bocay(angulogrados),
                                     vx,vy,masa_proyectil,radio_proyectil, turno));

    estado = estado::en_vuelo;
    tiempovuelo = 0.0;
    mensaje = "jugador" + std::to_string(turno) + " dispara.";
    return true;
}

void juegologica::terminarturno() {
    motor.limpiarparticulas();
    turno = (turno == 1) ? 2 : 1;
    estado = estado::esperando;
}

void juegologica::avanzar(double segundos) {
    if( estado != estado::en_vuelo) return;

    const int pasos = static_cast<int>(std::ceil(segundos / dt));
    for ( int i = 0; i < pasos && estado == estado::en_vuelo; ++i) {
        motor.pasosimulacion(dt);
        tiempovuelo += dt;

        for (const auto& e : motor.geteventospaso()) {
            std::ostringstream os;

            if (e.tipo == tipoevento::obstaculo && e.valor > 0.0) {
                const obstaculo& o =motor.getobstaculos()[e.id2 - 1];
                os << "¡"<< o.getnombre() << " del jugador " << o.getpropietario()
                   <<": -" << static_cast<int>(std::lround(e.valor))
                   << " destruido!";
                mensaje = os.str();
            }
        }
        const auto& ps = motor.getparticulas();
        if ( !ps.empty() && ps [0].isactiva()) {
            const int enemigo = (turno == 1 ) ? 2 : 1 ;
            const double dx = ps [0].getx() - rivalx(enemigo);
            const double dy = ps [0].gety() - rivaly();
            const double rs = ps [0].getradio() + radio_rival;
            if(dx *dx +dy * dy <= rs * rs) {
                ganador = turno;
                estado = estado::terminado;
                mensaje = "el jugador " + std::to_string(turno) + " ha eliminado al rival ";
                return;
            }
        }
        if(tiempovuelo >= tiempo_max_turno) {
            terminarturno();
            return;
        }
    }
}






