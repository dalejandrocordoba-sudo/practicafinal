#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <fstream>
#include <string>
#include <vector>
#include "particula.h"
#include "obstaculo.h"
#include "evento.h"


class gestorarchivos {
private:
    std::ofstream salidatrayectoria;

public:
    gestorarchivos() = default;
    ~gestorarchivos();

    bool abrirtrayectoria(const std::string& ruta);
    void registrarpaso(double tiempo,
                       const std::vector<Particula>& particulas, const std::vector<evento>& eventosdelpaso);
    void cerrartrayectoria();

    static bool guardareventos(const std::string& ruta, const std::vector<evento>& eventos);

    static bool guardarobstaculos (const std::string& ruta,const std::vector<obstaculo>& obs);
};



#endif // GESTORARCHIVOS_H
