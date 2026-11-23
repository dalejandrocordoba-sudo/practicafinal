#ifndef MOTORFISICO_H
#define MOTORFISICO_H
#include <vector>
#include "particula.h"
#include "obstaculo.h"
#include "evento.h"


class motorfisico{

private:
    double anchoesenario;
    double altoesenario;
    double gravedad;
    double factordano;  // dano= factorDano * masa |velocidad de impacto|
    double tiempo;


    std::vector<Particula> particulas;
    std::vector<obstaculo> obstaculos;
    std::vector<evento> eventosPaso;   // eventos del último paso
    std::vector<evento> historial;     // todos los eventos

    void registrar(tipoevento t, int id1, int id2, double x, double y, double valor = 0.0, const std::string& detalle = "");


public:
    motorfisico(double ancho, double alto, double g = 9.81, double factordano = 0.5);

    void agregarparticula(const Particula& p);
    void agregarobstaculo(const obstaculo& obs);

    void limpiarparticulas();



    //sebas aqui se soluciona parte del error


    void pasosimulacion(double dt);

    void resolvercolisionesparedes(Particula& p);
    void resolvercolisionesobstaculos(Particula& p);
    void resolvercolisionesParticulas();

    double gettiempo() const { return tiempo; }
    double getancho() const { return anchoescenario; }
    double getalto() const { return altoescenario; }
    double getgravedad() const { return gravedad; }
    double getfactorDano() const { return factordano; }

    std::vector<Particula>& getparticulas() { return particulas; }
    const std::vector<Particula>& getparticulas() const { return particulas; }
    std::vector<obstaculo>& getobstaculos() { return obstaculos; }
    const std::vector<obstaculo>& getobstaculos() const { return obstaculos; }
    std::vector<evento>& geteventospaso() const { return eventosPaso; }
    const std::vector<evento>& gethistorial() const { return historial; }




};

#endif // MOTORFISICO_H
