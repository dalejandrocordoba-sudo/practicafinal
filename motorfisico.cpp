#include "motorfisico.h"
#include <algorithm>
#include <cmath>

motorfisico::motorfisico(double ancho, double alto, double g, double factordano)
    :anchoescenario(ancho), altoescenario(alto), gravedad(g),
    factordano(factordano), tiempo(0.0){}

void motorfisico::agregarparticula(const particula &p) {particulas.push_back(p);}
void motorfisico::agregarobstaculo(const obstaculo &obs){obstaculos.push_back(obs);}
void motorfisico::limpiarparticulas(){particulas.clear();}

// segmento malo  ---void motorfisico::registrar(tipoevento t, int id1, int id2, double x, double y, double valor, const std::string &detalle)

void motorfisico::registrar(tipoevento t, int id1, int id2, double x, double y,
                            double valor, const std::string& detalle) {
    evento e{tiempo, t, id1, id2, x, y, valor, detalle};
    eventospaso.push_back(e);
    historial.push_back(e);
}

void motorfisico::pasosimulacion(double dt){
    eventospaso.clear();
    tiempo += dt;

    for (auto& p : particulas) {

        if (!p.isactiva())continue;
        p.actualizarposicion(dt, gravedad);
        resolvercolisionesparedes(p);
        resolvercolisionesobstaculos(p);
    }
    resolvercolisionesparticulas();
}


// Aqui se resulelve parte de las colisiones en las paredes


void motorfisico::resolvercolisionesparedes(particula& p) {
    const double r = p.getradio();

    if (p.getx() - r <= 0.0) {
        p.setposicion(r, p.gety());
        p.setvelocidad(std::fabs(p.getvx()), p.getvy());
        registrar(tipoevento::pared_izquierda, p.getid(), -1, p.getx() - r, p.gety());
    } else if (p.getx() + r >= anchoescenario) {
        p.setposicion(anchoescenario - r, p.gety());
        p.setvelocidad(-std::fabs(p.getvx()), p.getvy());
        registrar(tipoevento::pared_derecha, p.getid(), -1, p.getx() + r, p.gety());
    }

    if (p.gety() - r <= 0.0) {
        p.setposicion(p.getx(), r);
        p.setvelocidad(p.getvx(), std::fabs(p.getvy()));
        registrar(tipoevento::piso, p.getid(), -1, p.getx(), p.gety() - r);
    } else if (p.gety() + r >= altoescenario) {
        p.setposicion(p.getx(), altoescenario - r);
        p.setvelocidad(p.getvx(), -std::fabs(p.getvy()));
        registrar(tipoevento::techo, p.getid(), -1, p.getx(), p.gety() + r);
    }
}


// obstáculos: inelásticas. v'_perp = -e v_perp ; v'_par = v_par  y  se determina explícitamente con qué lado del rectángulo se choca


void motorfisico::resolvercolisionesobstaculos(particula& p) {
    if (!p.isactiva()) return;
    const double umbral_impacto = 0.5;  // m/s: por debajo no se registra impacto

    for (auto& obs : obstaculos) {
        if (obs.isdestruido()) continue;

        const double r = p.getradio();
        const double px = p.getx();
        const double py = p.gety();
        const double minx = obs.getx();
        const double maxx = obs.getx() + obs.getancho();
        const double miny = obs.gety();
        const double maxy = obs.gety() + obs.getalto();



        const double cx = std::max(minx, std::min(px, maxx));
        const double cy = std::max(miny, std::min(py, maxy));
        const double dx = px - cx;
        const double dy = py - cy;
        const double distsq = dx * dx + dy * dy;

        if (distsq > r * r) continue; // aqui no se tiene contacto

        double nx, ny;
        std::string lado;

        if (distsq > 1e-12) {

            const double dist = std::sqrt(distsq);
            nx = dx / dist;
            ny = dy / dist;
            p.setposicion(cx + nx * r, cy + ny * r);

            if (std::fabs(dx) < 1e-12)      lado = (dy > 0) ? "superior" : "inferior";
            else if (std::fabs(dy) < 1e-12) lado = (dx > 0) ? "derecho" : "izquierdo";
            else                            lado = "esquina";
        } else {
            // centro dentro del rectángulo: salir por el lado más cercano
            const double dizq = px - minx, dder = maxx - px;
            const double dinf = py - miny, dsup = maxy - py;
            const double m = std::min(std::min(dizq, dder), std::min(dinf, dsup));
            if (m == dizq)      { nx = -1; ny = 0; lado = "izquierdo"; p.setposicion(minx - r, py); }
            else if (m == dder) { nx = 1;  ny = 0; lado = "derecho";   p.setposicion(maxx + r, py); }
            else if (m == dinf) { nx = 0;  ny = -1; lado = "inferior"; p.setposicion(px, miny - r); }
            else                { nx = 0;  ny = 1;  lado = "superior"; p.setposicion(px, maxy + r); }
        }

        const double vx = p.getvx();
        const double vy = p.getvy();
        const double vn = vx * nx + vy * ny;   // componente normal

        if (vn >= 0.0) continue;  // se está alejando

        // restitución solo en la componente perpendicular
        const double e = obs.getcoeficienterestitucion();
        p.setvelocidad(vx - (1.0 + e) * vn * nx,
                       vy - (1.0 + e) * vn * ny);

        if (vn > -umbral_impacto) continue;  // contacto suave: sin evento ni daño

        // daño = factor * masa * |v_impacto|  (proporcional al momento lineal)
        // solo daña la infraestructura del rival.
        double dano = 0.0;
        const bool danable = (obs.getpropietario() == 0) ||
                             (obs.getpropietario() != p.getlanzador());
        if (danable) {
            dano = factordano * p.getmasa() * std::sqrt(vx * vx + vy * vy);
            const bool destruido = obs.recibirdano(dano);
            registrar(tipoevento::obstaculo, p.getid(), obs.getid(),
                      p.getx(), p.gety(), dano, lado);
            if (destruido) {
                registrar(tipoevento::obstaculo_destruido, p.getid(), obs.getid(),
                          p.getx(), p.gety(), 0.0, obs.getnombre());
            }
        } else {
            registrar(tipoevento::obstaculo, p.getid(), obs.getid(),
                      p.getx(), p.gety(), 0.0, lado);
        }
    }
}



// particula completamente inelastica

void motorfisico::resolvercolisionesparticulas() {
    for (size_t i = 0; i < particulas.size(); ++i) {
        if (!particulas[i].isactiva()) continue;
        for (size_t j = i + 1; j < particulas.size(); ++j) {
            if (!particulas[j].isactiva() || !particulas[i].isactiva()) continue;

            const double dx = particulas[j].getx() - particulas[i].getx();
            const double dy = particulas[j].gety() - particulas[i].gety();
            const double rs = particulas[i].getradio() + particulas[j].getradio();

            if (dx * dx + dy * dy <= rs * rs) {
                const int idi = particulas[i].getid();
                const int idj = particulas[j].getid();
                particulas[i].fusionarcon(particulas[j]);
                registrar(tipoevento::fusion, idi, idj,
                          particulas[i].getx(), particulas[i].gety(),
                          particulas[i].getmasa());
            }
        }
    }
}