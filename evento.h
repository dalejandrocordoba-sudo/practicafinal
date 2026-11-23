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

    case TipoEvento::PARED_IZQUIERDA:    return "PARED_IZQUIERDA";
    case TipoEvento::PARED_DERECHA:      return "PARED_DERECHA";
    case TipoEvento::PISO:               return "PISO";
    case TipoEvento::TECHO:              return "TECHO";
    case TipoEvento::OBSTACULO:          return "OBSTACULO";
    case TipoEvento::FUSION:             return "FUSION";
    case TipoEvento::OBSTACULO_DESTRUIDO:return "OBSTACULO_DESTRUIDO";

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
