#ifndef JUEGOLOGICA_H
#define JUEGOLOGICA_H

#include <string>
#include "motorfisico.h"


class juegologica {
public:

    static constexpr double ancho = 180.0;
    static constexpr double alto = 100.0;
    static constexpr double gravedad = 9.81;

    static constexpr double masa_proyectil =2.0;
    static constexpr double radio_proyectil =1.2;
    static constexpr double factor_daño = 0.5;
    static constexpr double cañon_x = 4.0;
    static constexpr double cañon_y = 58.0;
    static constexpr double largo_cañon = 6.0;
    static constexpr double pilar_ancho = 14.0;
    static constexpr double pilar_alto = 30.0;
    static constexpr double tejado_alto = 15.0;
    static constexpr double hueco = 22.0;
    static constexpr double estructura_x0 = 9.0;
    static constexpr double res_pilar = 200.0;
    static constexpr double res_tejado = 100.0;
    static constexpr double radio_rival = 4.0;
    static constexpr double dt = 0.005;
    static constexpr double tiempo_max_turno = 8.0;

    enum class estado { esperando,en_vuelo, terminado };


private:
    motorfisico motor;
    estado estado;
    int turno;
    int ganador;
    int lanzamientos;
    double tiempovuelo;
    std::string mensaje;

    void construirescenario();
    void crearinfraestructura(int jugador);
    void terminarturno();

public:
    juegologica();

    void reiniciar();

    bool lanzar (double angulogrados, double velocidad);

    void avanzar(double segundos);

    estado getestado() const { return estado; }
    int getturno() const { return turno; }
    int getganador() const { return ganador; }
    const std::string& getmensaje() const {return mensaje;}
    const motorfisico& getmotor() const {return motor;}
    double gettiempovuelo() const { return tiempovuelo; }

    static double bocax(int jugador, double angulogrados);
    static double bocay(double angulogrados);
    static double rivalx(int jugador);
    static double rivaly() {return radio_rival; }
    static double cañonx (int jugador) {return jugador == 1 ? cañon_x : ancho - cañon_x; }
};

#endif // JUEGOLOGICA_H
