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


}



