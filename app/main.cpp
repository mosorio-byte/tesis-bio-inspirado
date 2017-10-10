// main.cpp

#include <QApplication>
#include <QDesktopWidget>
#include "window.h"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication app(argc, argv);
    Window window;    
    window.resize(window.sizeHint());
    window.setWindowTitle("Tesis: Localización de objetos a partir de técnicas bio-inspiradas usando múltiples agentes");
    //window.showMaximized();
    window.show();
    return app.exec();
}
