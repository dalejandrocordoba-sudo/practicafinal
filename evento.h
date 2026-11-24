#ifndef EVENTO_H
#define EVENTO_H

#include <string>

enum class tipoevento
{

    PARED_IZQUIERDA,
    PARED_DERECHA,
    PISO,
    TECHO,
    OBSTACULO,
    FUSION,
    OBSTACULO_DESTRUIDO

};

inline std::string nombreevento(tipoevento t){

    switch (t) {

    case tipoevento::PARED_IZQUIERDA:    return "PARED_IZQUIERDA";
    case tipoevento::PARED_DERECHA:      return "PARED_DERECHA";
    case tipoevento::PISO:               return "PISO";
    case tipoevento::TECHO:              return "TECHO";
    case tipoevento::OBSTACULO:          return "OBSTACULO";
    case tipoevento::FUSION:             return "FUSION";
    case tipoevento::OBSTACULO_DESTRUIDO:return "OBSTACULO_DESTRUIDO";

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
