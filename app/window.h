// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include <GL/glut.h>
#include <QVector>
#include <QtConcurrentRun>
#include "particleswarmoptimization.h"

namespace Ui {
class Window;
}

using namespace std;

class Window : public QWidget
{
    Q_OBJECT

public:    
    explicit Window(QWidget *parent = 0);    
    ~Window();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:   

    void on_pushButton_aceptar_pso_clicked();

    void on_pushButton_ejecutar_clicked();

    void start_changed(double x, double y);

    void   end_changed(double x, double y);   

    void on_pushButton_escucha_clicked();

    void on_pushButton_escritura_clicked();   

    void on_radioButton_SAplicacion_clicked();

    void on_radioButton_SServer_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_EnjambreOK_clicked();   

    void doIt();

    void on_pushButton_reset_graph_clicked();

    void thread_finished();        

    void request_particle(unsigned int id, unsigned int enjambre);

    void command_particle(unsigned int id, double vx, double vy, double t);

private:   
    void update_problem();
    void update();
    void refresh();
    void obj_found(structxy vect);

    QMutex mutex;

    Ui::Window *ui;

    //Enjambres
    unsigned int NEnjambres;
    ParticleSwarmOptimization Colonia;        
    QVector<ParticleSwarmOptimization*> VEnjambres;

    //Rutas
    bool bRuta;
    vector<vector<structidxy>> target;
    vector<int> ntarget;

    //Tiempo Procesamiento
    QElapsedTimer elaptimer;


    //Hilo Refresco Opengl
    QThread *m_thread;
    vector<structxy> obsThread;
    vector<strucparticle> partThread;
    vector<structidxy> endThread;
    vector<structxy> CobsThread;
    vector<strucparticle> CpartThread;
    vector<structidxy> CendThread;
    unsigned int CurrentIterationThread;


    //Conexion
    MDRSServer packet;
    MDRSServer packet_send;
    MCommand *command;
    MRequestStatus *request;
    int nBytesRecieve;
    int nBytesSend;

    QByteArray datagram;
    QByteArray datagram_send;

    QByteArray receiveDatagram;

    MRobotStatus robotStatus;

    QUdpSocket *udpSocketSend;
    QUdpSocket *udpSocketReceive;


    QUdpSocket *udpSocketSend_Command;
    QHostAddress ip;
    quint16 port;

    QHostAddress ip_server;
    quint16 port_server;

    strucparticle responce_particle;
    structxy      responce_obstacle;

    //resultado conexión
    int result_request;

    //id objeto a localizar
    int idobs;   
};

#endif // WINDOW_H
