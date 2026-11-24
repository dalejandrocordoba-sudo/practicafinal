#include "gestorarchivos.h"


gestorarchivos::~gestorarchivos(){
    cerrartrayectoria();
}

bool gestorarchivos::abrirtrayectoria(const std::string& ruta) {
    salidatrayectoria.open(ruta);
    if(!salidatrayectoria.is_open()) return false;

    salidatrayectoria << "tiempo,id,x,y,vx,vy,masa,radio,activa,evento\n";
    return true;
}


void gestorarchivos::registrarpaso(double tiempo, const std::vector<particula>& particulas,
                                   const std::vector<evento>& eventosdelpaso) {
    if (!salidatrayectoria.is_open()) return;

    for ( const auto& p : particulas) {

        std::string ev;
        for ( const auto& e: eventosdelpaso) {

            const bool participa = (e.id1 == p.getid()) ||
                                   (e.tipo == tipoevento::fusion && e.id2 == p.getid());
            if (!participa) continue;
            if (!ev.empty()) ev += "+";
            ev += nombreevento(e.tipo);
        }
        if (ev.empty()) ev = "-";

        salidatrayectoria << tiempo << ','<<p.getid() << ','
                          << p.getx() << ','<<p.gety()<< ','
                          << p.getvx() << ','<<p.getvy() << ','
                          << p.getmasa() << ',' << p.getradio()<< ','
                          << (p.isactiva() ? 1:0) <<',' << ev << '\n';
    }
}

void gestorarchivos::cerrartrayectoria() {
    if (salidatrayectoria.is_open()) salidatrayectoria.close();
}

bool gestorarchivos::guardareventos(const std::string& ruta, const std::vector<evento>& eventos) {
    std::ofstream f (ruta);
    if (!f.is_open()) return false;
    f<< "tiempo,tipo,id1,id2,x,y,valor,detalle\n";
    for ( const auto& e : eventos) {
        f << e.tiempo << ','<< nombreevento(e.tipo) << ',' << e.id1 << ',' << e.id2 << ','
          <<e.x << ',' << e.y << ','<<e.valor << ','
          << (e.detalle.empty() ? "-" : e.detalle) << '\n';
    }
    return true;
}

bool gestorarchivos::guardarobstaculos(const std::string& ruta, const std::vector<obstaculo>& obs ) {
    std::ofstream f (ruta);
    if(!f.is_open()) return false;
    f<< "id,x,y,ancho,alto\n";
    for (const auto& o : obs)

        f<< o.getid() << ',' << o.getx() << ',' << o.gety() <<','
          << o.getancho() << ',' << o.getalto() << '\n';
    return true;
}




