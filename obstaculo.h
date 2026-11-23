#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <string>


class obstaculo{
      private:

    int id;
    double x, y;
    double ancho, alto;
    double resistenciaactual;
    double resistenciamaxima;
    double coeficienterestitucion;
    int propietario;
    std::string nombre;
    bool destruido;


public:
    obstaculo(int id, double x, double y, double ancho, double alto,
              double resistencia, double e, int propietario = 0,
              const std::string& nombre = "obstaculo");

    bool recibirdano(double dano);

    int getid() const { return id; }
    double getx() const { return x; }
    double gety() const { return y; }
    double getancho() const { return ancho; }
    double getalto() const { return alto; }
    double getresistenciaactual() const { return resistenciaactual; }
    double getresistenciamaxima() const { return resistenciamaxima; }
    double fraccionresistencia() const;
    double getcoeficienterestitucion() const { return coeficienterestitucion; }
    int getpropietario() const { return propietario; }
    const std::string& getnombre() const { return nombre; }
    bool isdestruido() const { return destruido; }


};




#endif // OBSTACULO_H
