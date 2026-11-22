#ifndef JUEGOWINDOW_H
#define JUEGOWINDOW_H

#include <QMainWindow>
#include <QPainterPath>
#include <vector>
#include "juegologica.h"



class QGraphicsScene;
class QGraphicsView;
class QGraphicsEllipseItem;
class QGraphicsRectItem;
class QGraphicsLineItem;
class QGraphicsPathItem;
class QGraphicsSimpleTextItem;
class QDoubleSpinBox;
class QPushButton;
class QLabel;
class QTimer;

class juegowindow : public  QMainWindow {
    Q_OBJECT

public :
    explicit juegowindow(QWidget *parent = nullptr);

private slots:
    void lanzarproyectil();
    void tick();
    void reiniciarjuego();
    void actualizarapuntado();

private:
    static constexpr double escala = 5.0;
    juegologica logica;

    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;

    QDoubleSpinBox* spinangulo;
    QDoubleSpinBox* vista;
    QPushButton* btnlanzar;
    QPushButton* btnreiniciar;
    QLabel* lblturno;
    QLabel* lblmensaje;

    std::vector<QGraphicsRectItem*> rec0bstaculos;
    std::vector<QGraphicsSimpleTextItem*>texto0bstaculos;
    QGraphicsEllipseItem* proyectilitem;
    QGraphicsPathItem* trayectoriaitem;
    QGraphicsLineItem* apuntadoitem;
    QPainterPath trayectoria;



    double px (double x) const { return x * escala;}
    double py(double y ) const { return (juegologica::alto-y)*escala;}

    void construirui();
    void construirescena();
    void dibujarrival(int jugador);
    void actualizar0bstaculos();
    void actualizarturno();

};
#endif // JUEGOWINDOW_H
