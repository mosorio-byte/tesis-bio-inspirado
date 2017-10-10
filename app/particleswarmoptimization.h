#ifndef PARTICLESWARMOPTIMIZATION_H
#define PARTICLESWARMOPTIMIZATION_H
#include <vector>
#include <QObject>
#include <QTest>
#include <stdlib.h>     /* rand */
#include <time.h>       /* time */
#include <algorithm>
#include <QHostAddress>
#include <QUdpSocket>
#include <QStringList>
#include <QtNetwork>
#include <unistd.h>
#include "fuctioncost.h"
#include "messages_DRSServer.pb.h"
#include <QDebug>

using namespace std;

class ParticleSwarmOptimization : public QThread
{
    Q_OBJECT
public:
    ParticleSwarmOptimization();
    void set_problem(unsigned int tid ,unsigned int max_iteraciones,unsigned int sizeParticle, double VelocidadLimite, unsigned int MaxObstaculos, unsigned int weight, double learnCoefficient, structxy SourceIn, vector<structidxy> TargetIn, unsigned int timeSimu);
    void set_objeto_localizar(int id);
    void set_limiteMapa(bool select);

    void set_new_obstacles(vector<structxy> obstacle);
    void set_new_obstacles(structxy obstacle);
    void set_new_position(strucparticle &particle);
    void set_new_target(vector<structidxy> target);
    void set_new_Particles_Thread(vector<structparticle> particle);
    void set_mode_of_simulation(int mode);
    void set_enjambre(unsigned int enjambre);
    void set_unlockmutex_a();
    void set_result_request(int result);
    void set_responce_particle(structparticle particle_responce);

    void reset_state_particle();    
    void run();   

    void exit_simulacion();
    void start_simulacion();

    int request_particle(unsigned int id);
    int command_particle(unsigned int id, double vx, double vy, double t);

    void generarProblema();
    void generarProblemaServidor();
    void resolverProblemaPSOA();
    void resolverProblemaPSOB();
    void resolverProblemaPSOC();

    void resolverProblemaPSOAServer();
    void resolverProblemaPSOBServer();
    void resolverProblemaPSOCServer();

    double randu();
    solucionTring FuncionTriangular(unsigned int ite, unsigned int fC, unsigned int AC, unsigned int fW, unsigned int AW);
    vector<structxy>      getObstaculos();
    vector<strucparticle> getParticle();
    vector<structidxy>    getZoneEnd();
    unsigned int          getCurrentIte();
    Best                  getGBest();
    bool                  getThread();
signals:

    void problema_generado(vector<structxy> obstaculos,vector<strucparticle> particulas, structxy inicio, vector<structidxy> fin, structMapa XYLimMapa, unsigned int CurrentIteration);

    void objeto_encontrado(structxy vect);

    void send_request_particle(unsigned int id, unsigned int enjambre);

    void send_command_particle(unsigned int id, double vx, double vy, double t);

private slots:

    //void readPendingDatagrams();

private:

    double randd(double a, double b);

    solucionTring Solucionado;

    unsigned int enjambre;
    unsigned int tid_range;
    int result_of_request;

    // Sorce Particles
    structxy Source;

    // Target Problem
    vector<structidxy> Target;

    double Weight_set;

    // Limits Map
    structMapa XYLimMapa;

    // Obstacle vector
    int MaxObstacles;
    vector<structxy> Obstacles;

    //Objeto a localizar
    int idObjeto;

    //Max interaciones
    unsigned int MaxIte;

    //Population Size
    unsigned int nPop;
    vector<strucparticle> Particle;

    GlobalBest GBest;

    //
    bool OutOfTheRange ;

    //boleano test emit
    bool mutex_a;

    //Properties triangulo
    double PuntoMaxTriangulo;
    double pendiente;
    double M;

    double PuntoMaxWeight;
    double pendientew;
    double N;

    double W1_1;
    double W1_2;
    double W;

    double C1_1;
    double C1_2;
    double C2_1;
    double C2_2;

    double C1;
    double C2;

    double learnCoefficient;

    //Funcion de Costo
    FuctionCost MyCost;

    //Velocity
    double MaxVelocity;
    double MinVelocity;

    const double distancia_seguridad = 0.3;

    double distancia_euclideo;

    unsigned int ite;
    unsigned int countSuccessful;
    bool MissionAccomplished;
    bool MissionAccomplishedPop;
    bool FirstOfAll;

    structxy testPos;
    structxy actuPos;

    structxy tempvect;

    double tempCostAct;
    double tempCostSig;

    //PP
    double funcion_min;
    static const int Ns = 32;
    const double landa = 0.2;
    double delta_teta;
    double delta_landa;
    structxy pos_siguiente;
    double theta[Ns];
    double gg;

    //heu
    structxy pos_siguiente2;
    structxy ResultHeu;
    double landaE  = 0.22;
    double landaEE = 0.11;
    double funcion_max;
    unsigned int angulo;
    int r;
    int Heu;


    //Simulacion
    unsigned int timetoSimu;
    int mode;
    bool bExitSimu;  

    //etc

    bool test_thread;

    strucparticle responce_particle;
    structxy      responce_obstacle;

};

#endif // PARTICLESWARMOPTIMIZATION_H
