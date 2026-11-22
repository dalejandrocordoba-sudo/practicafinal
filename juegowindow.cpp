#include "juegowindow.h"

#include <QBrush>
#include <QColor>
#include <QDoubleSpinBox>
#include <QFont>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>

juegowindow::juegowindow(QWidget *parent)
    :QMainWindow(parent),
    escena(nullptr), vista(nullptr), timer(nullptr),
    spinangulo(nullptr), spinvelocidad(nullptr),
    btnlanzar(nullptr), btnreiniciar(nullptr),
    lblturno(nullptr), lblmensaje(nullptr),
    proyectilitem(nullptr), trayectoriaitem(nullptr), apuntadoitem(nullptr) {
    construirui();
    construirescena();

    timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, &QTimer::timeout,ehis, &juegowindow::tick);
}

void juegowindow::construirui() {
    QWidget* central = new QWidget(this);
    QVBoxLayout* principal = new QVBoxlayout(central);

    escena = new QGraphicsScene(0,0, px(juegologica::ANCHO), px (juegologica::alto), this);
    vista = new QGraphicsView (escena,central);
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setFixedSize(static_cast<int>(px(juegologica::ancho))+4,
                        static_cast<int>(px(juegologica::alto))+ 4);
    lblturno = new QLabel(central);
    QFont f = lblTurno->font();
    f.setBold(true);
    f.setPointSize(12);
    lblTurno->setfont(f);

    spinangulo = new QDoubleSpinBox(central);
    spinangulo->setrange(0.0,90.0);4
        spinangulo->setvalue(45.0);
    spinangulo->setSuffix(" °");

    spinvelocidad = new QDoublespinbox(central);
    spinvelocidad->setrange(5.0, 100.0);
    spinvelocidad->setvalue(45.0);
    spinvelocidad->setsuffix("m/s");

    btnlanzar = new QPushButton("lanzar proyectil", central);
    btnreiniciar = new QPushButton("reiniciar", central);
    lblmensaje = new QLabel("destruye la infraestructura rival y elimina a su representante", central);

    QHBoxLayout* controles = new QHBoxLayout();
    controles->addWidget(lblturno);
    controles->addStretch();
    controles->addWidget(new QLabel("angulo: ", central));
    controles->addWidget(spinangulo);
    controles->addWidget(new QLabel("velocidad:", central));
    controles->addWidget(spinvelocidad);
    controles->addWidget(btnlanzar);
    controles->addWidget(btnreiniciar);
    controles->addWidget(vista);
    controles->addLayout(controles);
    controles->addWidget(lblmensaje);
    setCentralWidget(central);
    setWindowTitle("juego de estrategia por turnos ");

    connect(btnlanzar, &QPushButton::clicked, this, &juegowindow::lanzarproyectil);
    connect(btnreiniciar, &QPushButton::clicked, this, &juegowindow::reiniciarjuego);
    connect(spinangulo, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,[this](double) { actualizarapuntado(); });

}

void juegowindow::dibujarrival(int jugador) {
    const double cx = px(juegologica::rivalx(jugador));
    const double base = py(0.0);
    const QPen lapiz(Qt::black,2);


    escena->addEllipse(cx-6,base-46,12,12, lapiz, QBrush(Qt::white));
    escena->addLine(cx,base -34,cx, base -16, lapiz);
    escena->addLine(cx - 10, base-28,cx +10, base - 28,lapiz);
    escena->addLine(cx, base -16, cx -8,base -2,lapiz);
    escena->addLine(cx, base -16,cx+8,base-2,lapiz);

    QGraphicsSimpleTextItem* t = escena->addSimpleText("Rival");
    t->setFont(QFont("Arial",8));
    t->setPos(cx-t->boundingRect().width()/2.0,  base -14+0);
    t->setZValue(5);
}

void juegowindow::construirescena() {
    rectobstaculos.clear();
    textoobstaculos.clear();
    proyectilitem = nullptr;
    trayectoriaitem = nullptr;
    apuntadoitem = nullptr;
    escena->clear();
    trayectoria = QPainterPath();

    escena->setBackgroundBrush(Qt::white);
    escena->addRect(0,0, px(juegologica::ancho), px(juegologica::alto), QPen(Qt::black,3));


    for (int j = 1; j<= 2 ; ++j){
        const QColor color = (j==1) ? QColor(30,90,200) : QColor(200,40,40);
        const double cx = px(juegologica::canonx(j));
        const double cy = py(juegologica::canon_y);
        const double rep = px(8.0);
        const double xrep = (j == 1) ? 0.0 : px(juegologica::ancho) - rep;
        escena->addRect(xrep, cy + 6,rep,4, QPen(Qt::black),QBrush(Qt::white));
        escena->addEllipse(cx-7,cy-7,14,14,QPen(Qt::black),QBrush(color));
    }

    const auto& obs = logica.getmotor().getobstaculos();
    for (const auto& o : obs) {
        QColor base = (o.getnombre() == "tejado") ? QColor(225,225,225) : QColor(255,224,190);
        QGraphicsRectItem* r = escena->addRect(px(o.getx()),py(o.gety() +o.getalto()),
                                                px(o.getancho()), px(o.getalto()),
                                               QPen(QColor(190,130,40),1.5), QBrush(base));
        r->setData(0,base);
        rectobstaculos.push_back(r);

        QGraphicsSimpleTextItem* t = escena->addSimpleText("");
        QFont ft("Arial", 10);
        ft.setBold(true);
        t->setFont(ft);
        t-setZValue(3);
        textoobstaculos.push_back(t);
    }
    dibujarrival(1);
    dibujarrival(2);

    trayectoriaitem = escena->addPath(QPainterPath(),QPen(QColor(220,60,60,170),1.5,Qt::DashLine));
    const double rp = px(juegologica::radio_proyectil);
    proyectilitem = escena->addEllipse(-rp,-rp,2* rp,2 * rp, QPen(Qt::black),QBrush(Qt::red));
    proyectilitem->setZValue(10);
    proyectilitem->setVisible(false);
    apuntadoitem = escena->addline(0,0,0,0, QPen(Qt::black, 4));
    apuntadoitem->setZValue(6);

    actualizarobstaculos();
    actualizarturno();
    actualizarapuntado();

}

void juegowindow::actualizarobstaculos() {
    const auto& obs = logica.getmotor().getobstaculos();
    for (size_t i = 0; i< obs.size() && i < rectobstaculos.size(); ++i) {
        if (obs [i].isdestruido()) {
            rectobstaculos[i]setVisible(false);
            textoobstaculos[i]->setVisible(false);
            continue;
        }
        QColcor c = rectobstaculos[i]->data(0).value<QColor>();
        c.setAlpha(static_cast<int>(90+165*obs[i].fraccionresistencia()));
        rectobstaculos[i]->setBrush(QBrush(c));

        textoobstaculos[i]->settext(QString::number(static_cast<int>(std::ceil(bs[i].getresistenciaactual()))));
        const QRectF br = textoobstaculos[i]->boundingrect();
        textoobstaculos[i]-setpos(px(obs[i].getx() +obs [i].getancho()/ 2.0)-br.width() / 2.0,
                                    py(obs[i].gety() + obs[i].getalto()/2.0)- br.height()/2.0);

        }
    }
void juegowindow::actualizarturno(){
    const int j = logica.getturno();
    lblturno->setText(QString("Turno: jugador %1").arg(j));
    lblturno->setStyleSheet(j == 1 ? "color: rgb (30,90,200);": "color: rgb(200,40,40);");
}

void juegowindow::actualizarapuntado() {
    if (!logica.lanzar(spinangulo->value(),spinvelocidad->value(),spinvelocidad->()))
        return;

    const auto& p = logica.getmotor().getparticulas().front();
    trayectoria = QPainterPath(QPointF(px(p.getx()),py(p.gety())));
    trayectoriaitem->setPath(trayectoria);
    proyectilitem->setPos(px(p.getx()),py(p.gety()));
    proyectilitem->setVisible(true);
    apuntadoitem->setVisible(false);

    btnlanzar->setEnabled(false);
    lblmensaje->setText(QString::fromStdString(logica.getMensaje()));
    timer->start();

}

void juegowindow::tick() {
    logica.avanzar(0.032);

    const auto& ps = logica.getmotor().getparticulas();
    if(!ps.empty() && ps[0].isactiva()) {
        const QPintF pos(px(ps[0].getx()),py(ps[0].gety()));
        proyectilitem->setPos(pos);
        trayectoria.lineTo(pos);
        trayectoriaitem->setPath(trayectoria);
    }
    actualizarobstaculos();
    lblmensaje->setText(QString::fromStdString(logica.getMensaje()));


    if(logica.getEstado() == juegologica::estado::terminado) {
        timer->stop();
        QMessageBox::information(this,"¡victoria!",
            QString("el jugador %1 ha eliminado al representante enemigo.").arg(logica.getganador()));
        reiniciarjuego();
    } else if (logica.getEstado() == juegologica::estado::esperando) {
            timer->stop();
            proyectilitem->setVisible(false);
            btnlanzar->setEnabled(true);
            actualizarturno();
            actualizarapuntado();
        }
}

void juegowindow::reiniciarjuego(){
    timer->stop();
    logica.reiniciar();
    btnlanzar->setEnabled(true);
    construirescena();
    lblmensaje->setText("Nueva partida. destruye la infraestructura rival ");
}





