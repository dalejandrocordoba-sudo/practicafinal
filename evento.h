#ifndef EVENTO_H
#define EVENTO_H

#include <string>

enum class tipoevento
{

    pared_izquierda,
    pared_derecha,
    piso,
    techo,
    obstaculo,
    fusion,
    obstaculo_destruido

};

inline std::string nombreevento(tipoevento t){

    switch (t) {

    case tipoevento::pared_izquierda:    return "PARED_IZQUIERDA";
    case tipoevento::pared_derecha:      return "PARED_DERECHA";
    case tipoevento::piso:               return "PISO";
    case tipoevento::techo:              return "TECHO";
    case tipoevento::obstaculo:          return "OBSTACULO";
    case tipoevento::fusion:             return "FUSION";
    case tipoevento::obstaculo_destruido:return "OBSTACULO_DESTRUIDO";

    }

    return "DESCOCIDO";
}

struct evento {
    double tiempo;
    tipoevento tipo;
    int id1;
    int id2;
    double x, y;
    double valor;
    std::string detalle;


};







#endif // EVENTO_H
