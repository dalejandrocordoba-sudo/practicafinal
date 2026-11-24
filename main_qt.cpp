#include <QApplication>
#include "juegowindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    juegowindow window;
    window.show();
    return app.exec();

}