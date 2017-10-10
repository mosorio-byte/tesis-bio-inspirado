#include "particleswarmoptimization.h"

ParticleSwarmOptimization::ParticleSwarmOptimization()
{
    srand (time(NULL));
    FirstOfAll = false;

    for(int i = 0; i < Ns ; i++){
        theta[i] = (i) * (2*PI)/Ns;
        //qDebug("theta : %f",theta[i]);
    }
    timetoSimu = 30;
    bExitSimu = true;

    //udpSocketReceive  = new QUdpSocket();

    test_thread = true;
    mode = -1;

    ite = 0;
    //connect(udpSocketReceive, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void ParticleSwarmOptimization::set_problem(unsigned int tid, unsigned int max_iteraciones, unsigned int sizeParticle, double VelocidadLimite, unsigned int MaxObstaculos, unsigned int weight, double learnCoefficient, structxy SourceIn, vector<structidxy> TargetIn, unsigned int timeSimu)
{
    this->MaxIte  = max_iteraciones;
    this->nPop = sizeParticle;
    this->MaxVelocity = VelocidadLimite;
    this->MinVelocity = -MaxVelocity;
    this->MaxObstacles = MaxObstaculos;
    this->Source = SourceIn;
    this->Target = TargetIn;
    this->Weight_set = weight;
    this->learnCoefficient = learnCoefficient;
    this->timetoSimu = timeSimu;
    this->tid_range = tid;
}

void ParticleSwarmOptimization::generarProblemaServidor()
{
    Obstacles.clear();
    Particle.clear();

    strucparticle empy_particle;    
    MyCost.set_new_target(Target, 0);
    MyCost.set_new_Obstacle(Obstacles);

    empy_particle.id        = -1;
    empy_particle.Position.x = 0;
    empy_particle.Position.y =-5;
    empy_particle.Velocity.x = 0;
    empy_particle.Velocity.y = 0;
    empy_particle.Cost = 0;
    empy_particle.PBest.Cost = 0;
    empy_particle.PBest.Position.x = 0;
    empy_particle.PBest.Position.y = 0;
    empy_particle.MissionAccomplished = false;
    empy_particle.NoBestIte = 0;
    empy_particle.NoBestIteHeu = 0;
    empy_particle.Estancado = false;
    empy_particle.StateFistTime = false;

    for(unsigned int i = 0; i < nPop ; i++){
        Particle.push_back(empy_particle);
    }

    for( unsigned int i = 0; i < nPop; i++) {
        if(request_particle(i + tid_range)==-1){
            qDebug("Error! robot no encontrado");
        }else {
            Particle[i].id          = responce_particle.id;
            Particle[i].Position.x  = responce_particle.Position.x;
            Particle[i].Position.y  = responce_particle.Position.y;
        }
    }

    GBest.Cost = numeric_limits<double>::infinity();

    for(unsigned int i = 0; i < nPop ; i++) {

        empy_particle.id = Particle[i].id;

        empy_particle.MissionAccomplished = false;

        empy_particle.Position.x = Particle[i].Position.x;
        empy_particle.Position.y = Particle[i].Position.y;

        empy_particle.Velocity.x = 0;
        empy_particle.Velocity.y = 0;

        empy_particle.Cost = MyCost.potential_field(empy_particle.Position);

        empy_particle.PBest.Cost = empy_particle.Cost;
        empy_particle.PBest.Position = empy_particle.Position;

        if (empy_particle.PBest.Cost < GBest.Cost){
            GBest = empy_particle.PBest;
        }

        Particle[i] = empy_particle;
    }

    emit problema_generado(Obstacles, Particle, Source, Target, XYLimMapa, 0);


}

void ParticleSwarmOptimization::set_limiteMapa(bool select)
{
    if(select){
        XYLimMapa.x[0] = -3.7;
        XYLimMapa.x[1] = +3.7;
        XYLimMapa.y[0] = -3.0;
        XYLimMapa.y[1] = +3.0;

    }else{
        XYLimMapa.x[0] = -3.7;
        XYLimMapa.x[1] = +0.0;
        XYLimMapa.y[0] = -3.0;
        XYLimMapa.y[1] = +3.0;
    }
}



void ParticleSwarmOptimization::set_objeto_localizar(int id)
{
    idObjeto = id;
}

void ParticleSwarmOptimization::set_new_obstacles(vector<structxy> obstacle)
{
    MyCost.set_new_Obstacle(obstacle);    
}

void ParticleSwarmOptimization::set_new_obstacles(structxy obstacle)
{
    MyCost.set_new_Obstacle(obstacle);
    Obstacles.push_back(obstacle);
}

void ParticleSwarmOptimization::set_new_position(strucparticle &particle)
{
    int check = request_particle(particle.id);
    if(check == 0){
        particle.Position = responce_particle.Position;
    }
}

void ParticleSwarmOptimization::set_new_target(vector<structidxy> target)
{
    this->Target = target;
    MyCost.set_new_target(Target, 0);
    ParticleSwarmOptimization::reset_state_particle();
}

void ParticleSwarmOptimization::set_new_Particles_Thread(vector<structparticle> particle)
{
    MyCost.set_new_Particles_Thread(particle);
}

void ParticleSwarmOptimization::set_mode_of_simulation(int mode)
{
    this->mode = mode;
}

void ParticleSwarmOptimization::set_enjambre(unsigned int enjambre)
{
    this->enjambre = enjambre;
}

void ParticleSwarmOptimization::set_unlockmutex_a()
{
    mutex_a = false;
}

void ParticleSwarmOptimization::set_result_request(int result)
{
    this->result_of_request = result;
}

void ParticleSwarmOptimization::set_responce_particle(structparticle particle_responce)
{
    this->responce_particle = particle_responce;
}

void ParticleSwarmOptimization::exit_simulacion()
{
    bExitSimu = false;
}

void ParticleSwarmOptimization::start_simulacion()
{
    bExitSimu = true;
}

int ParticleSwarmOptimization::request_particle(unsigned int id)
{
    //qDebug("lock");
    mutex_a = true;
    emit send_request_particle(id, enjambre);
    while(mutex_a){};
    //qDebug("unlock");
    return result_of_request;
}

void ParticleSwarmOptimization::reset_state_particle()
{
    GBest.Cost = numeric_limits<double>::infinity();
    for(unsigned int i = 0; i < nPop ; i++){

        Particle[i].MissionAccomplished = false;
        Particle[i].NoBestIte = 0;
        Particle[i].NoBestIteHeu = 0;
        Particle[i].Estancado = false;
        Particle[i].StateFistTime = false;

        Particle[i].Cost = MyCost.potential_field(Particle[i].Position);

        Particle[i].PBest.Cost = Particle[i].Cost;
        Particle[i].PBest.Position = Particle[i].Position;

        if (Particle[i].PBest.Cost < GBest.Cost){
            GBest = Particle[i].PBest;
        }        
    }
}

void ParticleSwarmOptimization::run()
{
    switch(mode){
    case 0:
        ParticleSwarmOptimization::resolverProblemaPSOA();
        break;
    case 1:
        ParticleSwarmOptimization::resolverProblemaPSOB();
        break;
    case 2:
        ParticleSwarmOptimization::resolverProblemaPSOC();
        break;
    case 3:
        ParticleSwarmOptimization::resolverProblemaPSOAServer();
        break;
    case 4:
        ParticleSwarmOptimization::resolverProblemaPSOBServer();
        break;
    case 5:
        ParticleSwarmOptimization::resolverProblemaPSOCServer();
        break;
    case 6:
        break;
    }
}

void ParticleSwarmOptimization::generarProblema(){
    structxy randpos;
    strucparticle empy_particle;
    int x, y;    

    MyCost.set_new_target(Target, 0);

    //GenerarObstaculos    
    Obstacles.clear();
    for(int i = 0; i < MaxObstacles; i++){        
        randpos.x = randd(XYLimMapa.x[0] + distancia_seguridad, XYLimMapa.x[1] - distancia_seguridad);
        randpos.y = randd(XYLimMapa.y[0] + distancia_seguridad, XYLimMapa.y[1] - distancia_seguridad);
        Obstacles.push_back(randpos);
    }

    MyCost.set_new_Obstacle(Obstacles);

    //Generar Particulas en Origen
    Particle.clear();

    empy_particle.id         =-1;
    empy_particle.Position.x = 0;
    empy_particle.Position.y = 0;
    empy_particle.Velocity.x = 0;
    empy_particle.Velocity.y = 0;
    empy_particle.Cost = 0;
    empy_particle.PBest.Cost = 0;
    empy_particle.PBest.Position.x = 0;
    empy_particle.PBest.Position.y = 0;
    empy_particle.MissionAccomplished = false;
    empy_particle.NoBestIte = 0;
    empy_particle.NoBestIteHeu = 0;
    empy_particle.Estancado = false;
    empy_particle.StateFistTime = false;

    for(unsigned int i = 0; i < nPop ; i++){
        Particle.push_back(empy_particle);
    }


    GBest.Cost = numeric_limits<double>::infinity();

    for(unsigned int i = 0; i < nPop ; i++){
        x = rand() % 1000  - 500;
        y = rand() % 1000  - 500;
        randpos.x = (float)(x)/1000 + Source.x;
        randpos.y = (float)(y)/1000 + Source.y;

        empy_particle.id = i + tid_range;

        empy_particle.MissionAccomplished = false;       

        empy_particle.Position.x = randpos.x;
        empy_particle.Position.y = randpos.y;

        empy_particle.Velocity.x = 0;
        empy_particle.Velocity.y = 0;

        empy_particle.Cost = MyCost.potential_field(empy_particle.Position);

        empy_particle.PBest.Cost = empy_particle.Cost;
        empy_particle.PBest.Position = empy_particle.Position;        

        if (empy_particle.PBest.Cost < GBest.Cost){
            GBest = empy_particle.PBest;
        }

        Particle[i] = empy_particle;
    }

    emit problema_generado(Obstacles, Particle, Source, Target, XYLimMapa, 0);
}

void ParticleSwarmOptimization::resolverProblemaPSOA()
{
    ite = 0;
    MissionAccomplished    = false;
    MissionAccomplishedPop = false;

    ParticleSwarmOptimization::reset_state_particle();
    while ( MissionAccomplished != true && ite < MaxIte && bExitSimu){
        ite = ite + 1;
        countSuccessful = 0;
        Solucionado = this->FuncionTriangular(ite, 50, learnCoefficient ,50 , Weight_set);

        for(unsigned int i = 0; i < nPop ; i++){
           //Update Velocity
           Particle[i].Velocity.x = Solucionado.W*Particle[i].Velocity.x
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.x - Particle[i].Position.x)
                    + Solucionado.C2*randu()*(GBest.Position.x             - Particle[i].Position.x);

           Particle[i].Velocity.y = Solucionado.W*Particle[i].Velocity.y
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.y - Particle[i].Position.y)
                    + Solucionado.C2*randu()*(GBest.Position.y             - Particle[i].Position.y);
           //Update Velocity Bounds
           Particle[i].Velocity.x = max(Particle[i].Velocity.x, MinVelocity);
           Particle[i].Velocity.x = min(Particle[i].Velocity.x, MaxVelocity);

           Particle[i].Velocity.y = max(Particle[i].Velocity.y, MinVelocity);
           Particle[i].Velocity.y = min(Particle[i].Velocity.y, MaxVelocity);

           //Update Position
           Particle[i].Position.x =  Particle[i].Position.x + Particle[i].Velocity.x;
           Particle[i].Position.y =  Particle[i].Position.y + Particle[i].Velocity.y;

           //Velocity Mirroring
           OutOfTheRange =(  Particle[i].Position.x  < (XYLimMapa.x[0] + distancia_seguridad) || Particle[i].Position.x > (XYLimMapa.x[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.x= -1*Particle[i].Velocity.x;
                 qDebug("warning! , %f", Particle[i].Velocity.x);
           }

           OutOfTheRange =(  Particle[i].Position.y  < (XYLimMapa.y[0] + distancia_seguridad) || Particle[i].Position.y > (XYLimMapa.y[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.y= -1*Particle[i].Velocity.y;
                 qDebug("warning! , %f", Particle[i].Velocity.y);
           }


            //Update Position Bounds;
            Particle[i].Position.x = max(Particle[i].Position.x, XYLimMapa.x[0] + distancia_seguridad);
            Particle[i].Position.x = min(Particle[i].Position.x, XYLimMapa.x[1] - distancia_seguridad);

            Particle[i].Position.y = max(Particle[i].Position.y, XYLimMapa.y[0] + distancia_seguridad);
            Particle[i].Position.y = min(Particle[i].Position.y, XYLimMapa.y[1] - distancia_seguridad);

           //Evaluation
           Particle[i].Cost = MyCost.potential_field(Particle[i].Position);

           //Update Personal Best
           if(Particle[i].Cost < Particle[i].PBest.Cost){
               Particle[i].PBest.Cost = Particle[i].Cost;
               Particle[i].PBest.Position = Particle[i].Position;
           }

           //Update Global Best
           if(Particle[i].PBest.Cost < GBest.Cost){
               GBest = Particle[i].PBest;
           }

           distancia_euclideo = sqrt( pow(abs(Particle[i].Position.x - Target[0].x),2) + pow(abs(Particle[i].Position.y - Target[0].y),2));

           if(distancia_euclideo < 0.37){
               Particle[i].MissionAccomplished = true;
               MissionAccomplishedPop = true;
           }

           if(Particle[i].MissionAccomplished == true){
               countSuccessful = countSuccessful + 1;
           }
           if (FirstOfAll == false){
               if(countSuccessful == nPop){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }else{
               if(MissionAccomplishedPop == true){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }
         }                
        QTest::qWait(timetoSimu);
    }
}

void ParticleSwarmOptimization::resolverProblemaPSOB()
{
    ite = 0;
    MissionAccomplished    = false;
    MissionAccomplishedPop = false;

    Solucionado.W  = 1.0;
    Solucionado.C1 = 0.5;
    Solucionado.C2 = 2.5;

    ParticleSwarmOptimization::reset_state_particle();
    while ( MissionAccomplished != true && ite < MaxIte && bExitSimu){
        ite = ite + 1;
        countSuccessful = 0;
        Solucionado = this->FuncionTriangular(ite, 50, learnCoefficient , 100 , Weight_set);
        for(unsigned int i = 0; i < nPop ; i++){
           //Update Velocity
           Particle[i].Velocity.x = Solucionado.W*Particle[i].Velocity.x
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.x - Particle[i].Position.x)
                    + Solucionado.C2*randu()*(GBest.Position.x             - Particle[i].Position.x);

           Particle[i].Velocity.y = Solucionado.W*Particle[i].Velocity.y
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.y - Particle[i].Position.y)
                    + Solucionado.C2*randu()*(GBest.Position.y             - Particle[i].Position.y);
           //Update Velocity Bounds
           Particle[i].Velocity.x = max(Particle[i].Velocity.x, MinVelocity);
           Particle[i].Velocity.x = min(Particle[i].Velocity.x, MaxVelocity);

           Particle[i].Velocity.y = max(Particle[i].Velocity.y, MinVelocity);
           Particle[i].Velocity.y = min(Particle[i].Velocity.y, MaxVelocity);

           //Update Position

           testPos.x  =  Particle[i].Position.x + Particle[i].Velocity.x;
           actuPos.x  =  Particle[i].Position.x;

           testPos.y  =  Particle[i].Position.y + Particle[i].Velocity.y;
           actuPos.y  =  Particle[i].Position.y;

           MyCost.set_new_Particles(Particle);

           tempCostAct   = MyCost.potential_field_2AB(actuPos, i);
           tempCostSig   = MyCost.potential_field_2AB(testPos, i);



           if(tempCostSig < tempCostAct){
                qDebug("PSO");
                Particle[i].Position.x  = Particle[i].Position.x + Particle[i].Velocity.x;
                Particle[i].Position.y =  Particle[i].Position.y + Particle[i].Velocity.y;
            }else{
               qDebug("PP  x:%f, y:%f",Particle[i].Velocity.x, Particle[i].Velocity.y);
               funcion_min = numeric_limits<double>::infinity();
               for (unsigned int j = 0;  j < Ns; j++){
                    delta_teta  = -PI + (PI -(-PI)) * double(rand() % 100 + 1)/double(100) ;
                    delta_landa = -0.1*landa + (0.1*landa -(-0.1*landa))*double(rand() % 100 + 1)/double(100);

                   pos_siguiente.x = Particle[i].Position.x + landa*cos(theta[j]) + delta_landa*cos(delta_teta);
                   pos_siguiente.y = Particle[i].Position.y + landa*sin(theta[j]) + delta_landa*sin(delta_teta);

                   gg = MyCost.potential_field_2AB(pos_siguiente, i);
                   if(gg < funcion_min){
                       funcion_min = gg;
                       tempvect = pos_siguiente;
                   }
               }
               Particle[i].Position.x = tempvect.x;
               Particle[i].Position.y = tempvect.y;
           }

           //Velocity Mirroring
           OutOfTheRange =(  Particle[i].Position.x  < (XYLimMapa.x[0] + distancia_seguridad) || Particle[i].Position.x > (XYLimMapa.x[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.x= -1*Particle[i].Velocity.x;
                 qDebug("warning! , %f", Particle[i].Velocity.x);
           }

           OutOfTheRange =(  Particle[i].Position.y  < (XYLimMapa.y[0] + distancia_seguridad) || Particle[i].Position.y > (XYLimMapa.y[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.y= -1*Particle[i].Velocity.y;
                 qDebug("warning! , %f", Particle[i].Velocity.y);
           }


            //Update Position Bounds;
            Particle[i].Position.x = max(Particle[i].Position.x, XYLimMapa.x[0] + distancia_seguridad);
            Particle[i].Position.x = min(Particle[i].Position.x, XYLimMapa.x[1] - distancia_seguridad);

            Particle[i].Position.y = max(Particle[i].Position.y, XYLimMapa.y[0] + distancia_seguridad);
            Particle[i].Position.y = min(Particle[i].Position.y, XYLimMapa.y[1] - distancia_seguridad);

           //Evaluation
           Particle[i].Cost = MyCost.potential_field(Particle[i].Position);

           //Update Personal Best
           if(Particle[i].Cost < Particle[i].PBest.Cost){
               Particle[i].PBest.Cost = Particle[i].Cost;
               Particle[i].PBest.Position = Particle[i].Position;
           }

           //Update Global Best
           if(Particle[i].PBest.Cost < GBest.Cost){
               GBest = Particle[i].PBest;
           }

           distancia_euclideo = sqrt( pow(abs(Particle[i].Position.x - Target[0].x),2) + pow(abs(Particle[i].Position.y - Target[0].y),2));

           if(distancia_euclideo < 0.55){
               Particle[i].MissionAccomplished = true;
               MissionAccomplishedPop = true;
           }

           if(Particle[i].MissionAccomplished == true){
               countSuccessful = countSuccessful + 1;
           }
           if (FirstOfAll == false){
               if(countSuccessful == nPop){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }else{
               if(MissionAccomplishedPop == true){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }
         }        
        QTest::qWait(timetoSimu);
    }
}

void ParticleSwarmOptimization::resolverProblemaPSOC()
{
    ite = 0;
    MissionAccomplished    = false;
    MissionAccomplishedPop = false;

    Solucionado.W  = 1.0;
    Solucionado.C1 = 0.5;
    Solucionado.C2 = 2.5;

    ParticleSwarmOptimization::reset_state_particle();
    while ( MissionAccomplished != true && ite < MaxIte && bExitSimu){
        ite = ite + 1;
        countSuccessful = 0;
        Solucionado = this->FuncionTriangular(ite, 50, learnCoefficient ,50 , Weight_set);
        for(unsigned int i = 0; i < Particle.size() ; i++){
           //Update Velocity
           Particle[i].Velocity.x = Solucionado.W*Particle[i].Velocity.x
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.x - Particle[i].Position.x)
                    + Solucionado.C2*randu()*(GBest.Position.x             - Particle[i].Position.x);

           Particle[i].Velocity.y = Solucionado.W*Particle[i].Velocity.y
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.y - Particle[i].Position.y)
                    + Solucionado.C2*randu()*(GBest.Position.y             - Particle[i].Position.y);
           //Update Velocity Bounds
           Particle[i].Velocity.x = max(Particle[i].Velocity.x, MinVelocity);
           Particle[i].Velocity.x = min(Particle[i].Velocity.x, MaxVelocity);

           Particle[i].Velocity.y = max(Particle[i].Velocity.y, MinVelocity);
           Particle[i].Velocity.y = min(Particle[i].Velocity.y, MaxVelocity);

           //Update Position

           testPos.x  =  Particle[i].Position.x + Particle[i].Velocity.x;
           actuPos.x  =  Particle[i].Position.x;

           testPos.y  =  Particle[i].Position.y + Particle[i].Velocity.y;
           actuPos.y  =  Particle[i].Position.y;

           MyCost.set_new_Particles(Particle);

           tempCostAct   = MyCost.potential_field_2AB(actuPos, i);
           tempCostSig   = MyCost.potential_field_2AB(testPos, i);

           if (Particle[i].NoBestIte > 4  && Particle[i].MissionAccomplished == false){
                   Particle[i].NoBestIte = 0;
                   Particle[i].Estancado = true;
            }
           if (tempCostAct < Particle[i].PBest.Cost || Particle[i].NoBestIteHeu > 35){
                   qDebug("out");
                   Particle[i].NoBestIte = 0;
                   Particle[i].NoBestIteHeu = 0;
                   Particle[i].Estancado = false;
           }
           if( Particle[i].Estancado == true){
                      qDebug("HEU [%d]", i);
                      Particle[i].NoBestIteHeu++;

                      funcion_max = -numeric_limits<double>::infinity();
                      for (unsigned int j = 0;  j < Ns; j++){
                           delta_teta  = -PI + (PI -(-PI)) * double(rand() % 100 + 1)/double(100) ;
                           delta_landa = -0.1*landaE + (0.1*landaE -(-0.1*landaE))*double(rand() % 100 + 1)/double(100);

                          pos_siguiente.x = Particle[i].Position.x + landaE*cos(theta[j]) + delta_landa*cos(delta_teta);
                          pos_siguiente.y = Particle[i].Position.y + landaE*sin(theta[j]) + delta_landa*sin(delta_teta);

                          pos_siguiente2.x = Particle[i].Position.x + landaEE*cos(theta[j]) + delta_landa*cos(delta_teta);
                          pos_siguiente2.y = Particle[i].Position.y + landaEE*sin(theta[j]) + delta_landa*sin(delta_teta);

                          gg = MyCost.obstaculos2AB(pos_siguiente, i);
                          if(gg > funcion_max){
                              funcion_max = gg;
                              tempvect = pos_siguiente2;
                              angulo = j;
                          }
                      }

                      if (Particle[i].StateFistTime == false){
                          Particle[i].StateFistTime = true;
                          r  = rand() % 100;
                          if (r > 50)
                              Particle[i].D = -1;
                          else
                              Particle[i].D =  1;
                      }

                      if (funcion_max < 3)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -4);
                      else if (funcion_max < 4)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -3);
                      else if (funcion_max < 5)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -1);
                      else if (funcion_max < 6)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  0);
                      else if (funcion_max < 7)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -1);
                      else if (funcion_max < 8)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  3);
                      else
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  4);

                      pos_siguiente2.x = Particle[i].Position.x + landaEE*cos(theta[Heu]) + delta_landa*cos(delta_teta);
                      pos_siguiente2.y = Particle[i].Position.y + landaEE*sin(theta[Heu]) + delta_landa*sin(delta_teta);
                      Particle[i].Position = pos_siguiente2;
            }
            else if(tempCostSig < tempCostAct){
                qDebug("PSO [%d]" ,i);
                Particle[i].Position.x  = Particle[i].Position.x + Particle[i].Velocity.x;
                Particle[i].Position.y =  Particle[i].Position.y + Particle[i].Velocity.y;
            }else{
               qDebug("PP [%d] x:%f, y:%f", i,Particle[i].Velocity.x, Particle[i].Velocity.y);
               funcion_min = numeric_limits<double>::infinity();
               for (unsigned int j = 0;  j < Ns; j++){
                    delta_teta  = -PI + (PI -(-PI)) * double(rand() % 100 + 1)/double(100) ;
                    delta_landa = -0.1*landa + (0.1*landa -(-0.1*landa))*double(rand() % 100 + 1)/double(100);

                   pos_siguiente.x = Particle[i].Position.x + landa*cos(theta[j]) + delta_landa*cos(delta_teta);
                   pos_siguiente.y = Particle[i].Position.y + landa*sin(theta[j]) + delta_landa*sin(delta_teta);

                   gg = MyCost.potential_field_2AB(pos_siguiente, i);
                   if(gg < funcion_min){
                       funcion_min = gg;
                       tempvect = pos_siguiente;
                   }
               }
               Particle[i].Position.x = tempvect.x;
               Particle[i].Position.y = tempvect.y;
           }

           //Velocity Mirroring
           OutOfTheRange =(  Particle[i].Position.x  < (XYLimMapa.x[0] + distancia_seguridad) || Particle[i].Position.x > (XYLimMapa.x[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.x= -1*Particle[i].Velocity.x;
                 qDebug("warning! , %f", Particle[i].Velocity.x);
           }

           OutOfTheRange =(  Particle[i].Position.y  < (XYLimMapa.y[0] + distancia_seguridad) || Particle[i].Position.y > (XYLimMapa.y[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.y= -1*Particle[i].Velocity.y;
                 qDebug("warning! , %f", Particle[i].Velocity.y);
           }


            //Update Position Bounds;
            Particle[i].Position.x = max(Particle[i].Position.x, XYLimMapa.x[0] + distancia_seguridad);
            Particle[i].Position.x = min(Particle[i].Position.x, XYLimMapa.x[1] - distancia_seguridad);

            Particle[i].Position.y = max(Particle[i].Position.y, XYLimMapa.y[0] + distancia_seguridad);
            Particle[i].Position.y = min(Particle[i].Position.y, XYLimMapa.y[1] - distancia_seguridad);

           //Evaluation
           Particle[i].Cost = MyCost.potential_field(Particle[i].Position);

           //Update Personal Best
           if(Particle[i].Cost < Particle[i].PBest.Cost){
               Particle[i].PBest.Cost = Particle[i].Cost;
               Particle[i].PBest.Position = Particle[i].Position;
           }else{
               Particle[i].NoBestIte++;
           }

           //Update Global Best
           if(Particle[i].PBest.Cost < GBest.Cost){
               GBest = Particle[i].PBest;
           }

           distancia_euclideo = sqrt( pow(abs(Particle[i].Position.x - Target[0].x),2) + pow(abs(Particle[i].Position.y - Target[0].y),2));

           if(distancia_euclideo < 0.55){
               Particle[i].MissionAccomplished = true;
               MissionAccomplishedPop = true;
           }

           if(Particle[i].MissionAccomplished == true){
               countSuccessful = countSuccessful + 1;
           }
           if (FirstOfAll == false){
               if(countSuccessful == nPop){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }else{
               if(MissionAccomplishedPop == true){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }
         }        
        QTest::qWait(timetoSimu);
    }
}

void ParticleSwarmOptimization::resolverProblemaPSOAServer()
{
    ite = 0;
    MissionAccomplished    = false;
    MissionAccomplishedPop = false;
    while ( MissionAccomplished != true && ite < MaxIte && bExitSimu){
        ite = ite + 1;
        countSuccessful = 0;
        Solucionado = this->FuncionTriangular(ite, 50, learnCoefficient ,50 , Weight_set);

        for(unsigned int i = 0; i < nPop ; i++){
           //Update Velocity
           Particle[i].Velocity.x = Solucionado.W*Particle[i].Velocity.x
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.x - Particle[i].Position.x)
                    + Solucionado.C2*randu()*(GBest.Position.x             - Particle[i].Position.x);

           Particle[i].Velocity.y = Solucionado.W*Particle[i].Velocity.y
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.y - Particle[i].Position.y)
                    + Solucionado.C2*randu()*(GBest.Position.y             - Particle[i].Position.y);
           //Update Velocity Bounds
           Particle[i].Velocity.x = max(Particle[i].Velocity.x, MinVelocity);
           Particle[i].Velocity.x = min(Particle[i].Velocity.x, MaxVelocity);

           Particle[i].Velocity.y = max(Particle[i].Velocity.y, MinVelocity);
           Particle[i].Velocity.y = min(Particle[i].Velocity.y, MaxVelocity);

           //Update Real Velocity
           emit send_command_particle(Particle[i].id, Particle[i].Velocity.x*200, Particle[i].Velocity.y*200, 0.25f);

           //Update Position
           set_new_position(Particle[i]);

           //Velocity Mirroring
           OutOfTheRange =(  Particle[i].Position.x  < (XYLimMapa.x[0] + distancia_seguridad) || Particle[i].Position.x > (XYLimMapa.x[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.x= -1*Particle[i].Velocity.x;
                 qDebug("warning! , %f", Particle[i].Velocity.x);
           }

           OutOfTheRange =(  Particle[i].Position.y  < (XYLimMapa.y[0] + distancia_seguridad) || Particle[i].Position.y > (XYLimMapa.y[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.y= -1*Particle[i].Velocity.y;
                 qDebug("warning! , %f", Particle[i].Velocity.y);
           }


           //Evaluation
           MyCost.set_new_Particles(Particle);
           Particle[i].Cost = MyCost.potential_field(Particle[i].Position);

           //Update Personal Best
           if(Particle[i].Cost < Particle[i].PBest.Cost){
               Particle[i].PBest.Cost = Particle[i].Cost;
               Particle[i].PBest.Position = Particle[i].Position;
           }

           //Update Global Best
           if(Particle[i].PBest.Cost < GBest.Cost){
               GBest = Particle[i].PBest;
           }

           distancia_euclideo = sqrt( pow(abs(Particle[i].Position.x - Target[0].x),2) + pow(abs(Particle[i].Position.y - Target[0].y),2));

           if(distancia_euclideo < 2){
               Particle[i].MissionAccomplished = true;
               MissionAccomplishedPop = true;
           }

           if(Particle[i].MissionAccomplished == true){
               countSuccessful = countSuccessful + 1;
           }
           if (FirstOfAll == false){
               if(countSuccessful == nPop){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }else{
               if(MissionAccomplishedPop == true){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }
         }        
        QTest::qWait(timetoSimu);
    }

}

void ParticleSwarmOptimization::resolverProblemaPSOBServer()
{
    ite = 0;
    MissionAccomplished    = false;
    MissionAccomplishedPop = false;   

    Solucionado.W  = 1.0;
    Solucionado.C1 = 0.5;
    Solucionado.C2 = 2.5;

    start_simulacion();

    while ( MissionAccomplished != true && ite < MaxIte && bExitSimu){
        ite = ite + 1;
        countSuccessful = 0;
        Solucionado = this->FuncionTriangular(ite, 50, learnCoefficient ,100 , Weight_set);
        for(unsigned int i = 0; i < nPop  && bExitSimu; i++){
           //Update Velocity
           Particle[i].Velocity.x = Solucionado.W*Particle[i].Velocity.x
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.x - Particle[i].Position.x)
                    + Solucionado.C2*randu()*(GBest.Position.x             - Particle[i].Position.x);

           Particle[i].Velocity.y = Solucionado.W*Particle[i].Velocity.y
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.y - Particle[i].Position.y)
                    + Solucionado.C2*randu()*(GBest.Position.y             - Particle[i].Position.y);
           //Update Velocity Bounds
           Particle[i].Velocity.x = max(Particle[i].Velocity.x, MinVelocity);
           Particle[i].Velocity.x = min(Particle[i].Velocity.x, MaxVelocity);

           Particle[i].Velocity.y = max(Particle[i].Velocity.y, MinVelocity);
           Particle[i].Velocity.y = min(Particle[i].Velocity.y, MaxVelocity);

           //Update Position
           set_new_position(Particle[i]);

           actuPos.y  =  Particle[i].Position.y;
           actuPos.x  =  Particle[i].Position.x;

           testPos.y  =  Particle[i].Position.y + Particle[i].Velocity.y;
           testPos.x  =  Particle[i].Position.x + Particle[i].Velocity.x;

           MyCost.set_new_Particles(Particle);
           tempCostAct   = MyCost.potential_field_2AB(actuPos, i);
           tempCostSig   = MyCost.potential_field_2AB(testPos, i);

           if(tempCostSig < tempCostAct){
                qDebug("PSO");               
                emit send_command_particle(Particle[i].id, Particle[i].Velocity.x*1300, Particle[i].Velocity.y*1300, 0.10f);
            }else{               
               funcion_min = numeric_limits<double>::infinity();
               for (unsigned int j = 0;  j < Ns; j++){
                    delta_teta  = -PI + (PI -(-PI)) * double(rand() % 100 + 1)/double(100) ;
                    delta_landa = -0.1*landa + (0.1*landa -(-0.1*landa))*double(rand() % 100 + 1)/double(100);

                   pos_siguiente.x = Particle[i].Position.x + landa*cos(theta[j]) + delta_landa*cos(delta_teta);
                   pos_siguiente.y = Particle[i].Position.y + landa*sin(theta[j]) + delta_landa*sin(delta_teta);

                   gg = MyCost.potential_field_2AB(pos_siguiente, i);
                   if(gg < funcion_min){
                       funcion_min = gg;
                       tempvect = pos_siguiente;
                   }
               }

               Particle[i].Velocity.x = (tempvect.x - Particle[i].Position.x)*1000;
               Particle[i].Velocity.y = (tempvect.y - Particle[i].Position.y)*1000;

               qDebug("PP [%d] vx:%f, vy:%f", i , Particle[i].Velocity.x, Particle[i].Velocity.y);
               //(Particle[i].id, Particle[i].Velocity.x, Particle[i].Velocity.y, 1);

           }
            QTest::qWait(timetoSimu);            

           //Velocity Mirroring
           OutOfTheRange =(  Particle[i].Position.x  < (XYLimMapa.x[0] + distancia_seguridad) || Particle[i].Position.x > (XYLimMapa.x[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.x= -1*Particle[i].Velocity.x;
                 qDebug("warning! , %f", Particle[i].Velocity.x);
           }

           OutOfTheRange =(  Particle[i].Position.y  < (XYLimMapa.y[0] + distancia_seguridad) || Particle[i].Position.y > (XYLimMapa.y[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.y= -1*Particle[i].Velocity.y;
                 qDebug("warning! , %f", Particle[i].Velocity.y);
           }

           //Evaluation
           Particle[i].Cost = MyCost.potential_field(Particle[i].Position);

           //Update Personal Best
           if(Particle[i].Cost < Particle[i].PBest.Cost){
               Particle[i].PBest.Cost = Particle[i].Cost;
               Particle[i].PBest.Position = Particle[i].Position;
           }

           //Update Global Best
           if(Particle[i].PBest.Cost < GBest.Cost){
               GBest = Particle[i].PBest;
           }

           distancia_euclideo = sqrt( pow( Particle[i].Position.x - Target[0].x,2) + pow( Particle[i].Position.y - Target[0].y,2));
           if(distancia_euclideo < 0.75){
               Particle[i].MissionAccomplished = true;
               MissionAccomplishedPop = true;
           }
           if(Particle[i].MissionAccomplished == true){
               countSuccessful = countSuccessful + 1;
           }

           if (FirstOfAll == false){
               if(countSuccessful == nPop){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }else{
               if(MissionAccomplishedPop == true){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }
         }        
    }
}

void ParticleSwarmOptimization::resolverProblemaPSOCServer()
{
    ite = 0;
    MissionAccomplished    = false;
    MissionAccomplishedPop = false;

    Solucionado.W  = 1.0;
    Solucionado.C1 = 0.5;
    Solucionado.C2 = 2.5;

    ParticleSwarmOptimization::start_simulacion();
    ParticleSwarmOptimization::reset_state_particle();

    while ( MissionAccomplished != true && ite < MaxIte && bExitSimu){
        ite = ite + 1;
        countSuccessful = 0;
        Solucionado = this->FuncionTriangular(ite, 30, learnCoefficient ,30 , Weight_set);
        Solucionado.W  = 1.0;
        for(unsigned int i = 0; i < Particle.size()  && bExitSimu; i++){
           //Update Velocity
           Particle[i].Velocity.x = Solucionado.W*Particle[i].Velocity.x
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.x - Particle[i].Position.x)
                    + Solucionado.C2*randu()*(GBest.Position.x             - Particle[i].Position.x);

           Particle[i].Velocity.y = Solucionado.W*Particle[i].Velocity.y
                    + Solucionado.C1*randu()*(Particle[i].PBest.Position.y - Particle[i].Position.y)
                    + Solucionado.C2*randu()*(GBest.Position.y             - Particle[i].Position.y);
           //Update Velocity Bounds
           Particle[i].Velocity.x = max(Particle[i].Velocity.x, MinVelocity);
           Particle[i].Velocity.x = min(Particle[i].Velocity.x, MaxVelocity);

           Particle[i].Velocity.y = max(Particle[i].Velocity.y, MinVelocity);
           Particle[i].Velocity.y = min(Particle[i].Velocity.y, MaxVelocity);

           //Update Position
           set_new_position(Particle[i]);

           actuPos.y  =  Particle[i].Position.y;
           actuPos.x  =  Particle[i].Position.x;

           testPos.y  =  Particle[i].Position.y + Particle[i].Velocity.y;
           testPos.x  =  Particle[i].Position.x + Particle[i].Velocity.x;

           MyCost.set_new_Particles(Particle);
           tempCostAct   = MyCost.potential_field_2AB(actuPos, i);
           tempCostSig   = MyCost.potential_field_2AB(testPos, i);

           if (Particle[i].NoBestIte > 30  && Particle[i].MissionAccomplished == false){
                   Particle[i].NoBestIte = 0;
                   Particle[i].Estancado = true;
                   Particle[i].repetividad = 0;
           }
           if ( ((tempCostAct < Particle[i].PBest.Cost) || (Particle[i].NoBestIteHeu > 180 )) && (Particle[i].Estancado == true) ){
                   qDebug("------------ [%d]", Particle[i].NoBestIteHeu);
                   Particle[i].NoBestIte = 0;
                   Particle[i].NoBestIteHeu = 0;
                   Particle[i].Estancado = false;
           }

           if( Particle[i].Estancado == true){
                      qDebug("HEU [%d][%d]", i, Particle[i].NoBestIteHeu);
                      Particle[i].NoBestIteHeu++;
                      bool mutex = false;
                      funcion_max = -numeric_limits<double>::infinity();
                      for (unsigned int j = 0;  j < Ns; j++){
                           delta_teta  = -PI + (PI -(-PI)) * double(rand() % 100 + 1)/double(100) ;
                           delta_landa = -0.1*landaE + (0.1*landaE -(-0.1*landaE))*double(rand() % 100 + 1)/double(100);

                          pos_siguiente.x = Particle[i].Position.x + landaE*cos(theta[j]) + delta_landa*cos(delta_teta);
                          pos_siguiente.y = Particle[i].Position.y + landaE*sin(theta[j]) + delta_landa*sin(delta_teta);

                          pos_siguiente2.x = Particle[i].Position.x + landaEE*cos(theta[j]) + delta_landa*cos(delta_teta);
                          pos_siguiente2.y = Particle[i].Position.y + landaEE*sin(theta[j]) + delta_landa*sin(delta_teta);

                          ResultHeu = MyCost.obstaculosHeu(pos_siguiente, i);
                          if(ResultHeu.y > 0 && !mutex){
                              Particle[i].repetividad++;
                              mutex = true;
                          }
                          if(ResultHeu.x > funcion_max){
                              funcion_max = ResultHeu.x;
                              tempvect = pos_siguiente2;
                              angulo = j;
                          }
                      }

                      if(Particle[i].repetividad > 50){
                          Particle[i].NoBestIteHeu = 181;
                      }

                      if (Particle[i].StateFistTime == false){
                          Particle[i].StateFistTime = true;
                          r  = rand() % 100;
                          if (r > 50)
                              Particle[i].D = -1;
                          else
                              Particle[i].D =  1;
                      }


                      if (funcion_max < 3)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -4);
                      else if (funcion_max < 4)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -3);
                      else if (funcion_max < 5)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -2);
                      else if (funcion_max < 6)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  0);
                      else if (funcion_max < 7)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  -2);
                      else if (funcion_max < 8)
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  3);
                      else
                          Heu = MyCost.heuristica( angulo, Particle[i].D,  4);

                      pos_siguiente2.x = Particle[i].Position.x + landaEE*cos(theta[Heu]) + delta_landa*cos(delta_teta);
                      pos_siguiente2.y = Particle[i].Position.y + landaEE*sin(theta[Heu]) + delta_landa*sin(delta_teta);

                      Particle[i].Velocity.x = (pos_siguiente2.x - Particle[i].Position.x)*3300;
                      Particle[i].Velocity.y = (pos_siguiente2.y - Particle[i].Position.y)*3300;

                      emit send_command_particle(Particle[i].id, Particle[i].Velocity.x, Particle[i].Velocity.y, 0.5f);
            }
            else if(tempCostSig < tempCostAct){
                //qDebug("PSO [%d]", i);
                emit send_command_particle(Particle[i].id, Particle[i].Velocity.x*1400, Particle[i].Velocity.y*1400, 0.5f);
            }else{
               funcion_min = numeric_limits<double>::infinity();
               for (unsigned int j = 0;  j < Ns; j++){
                    delta_teta  = -PI + (PI -(-PI)) * double(rand() % 100 + 1)/double(100) ;
                    delta_landa = -0.1*landa + (0.1*landa -(-0.1*landa))*double(rand() % 100 + 1)/double(100);

                   pos_siguiente.x = Particle[i].Position.x + landa*cos(theta[j]) + delta_landa*cos(delta_teta);
                   pos_siguiente.y = Particle[i].Position.y + landa*sin(theta[j]) + delta_landa*sin(delta_teta);

                   gg = MyCost.potential_field_2AB(pos_siguiente, i);
                   if(gg < funcion_min){
                       funcion_min = gg;
                       tempvect = pos_siguiente;
                   }
               }

               Particle[i].Velocity.x = (tempvect.x - Particle[i].Position.x)*2300;
               Particle[i].Velocity.y = (tempvect.y - Particle[i].Position.y)*2300;

               //qDebug("PP [%d] vx:%f, vy:%f", i , Particle[i].Velocity.x, Particle[i].Velocity.y);
               emit send_command_particle(Particle[i].id, Particle[i].Velocity.x, Particle[i].Velocity.y, 0.5f);
           }
            QTest::qWait(timetoSimu);            

           //Velocity Mirroring
           OutOfTheRange =(  Particle[i].Position.x  < (XYLimMapa.x[0] + distancia_seguridad) || Particle[i].Position.x > (XYLimMapa.x[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.x= -1*Particle[i].Velocity.x;
                 qDebug("warning! , %f", Particle[i].Velocity.x);
           }

           OutOfTheRange =(  Particle[i].Position.y  < (XYLimMapa.y[0] + distancia_seguridad) || Particle[i].Position.y > (XYLimMapa.y[1] - distancia_seguridad));
           if (OutOfTheRange){
                 Particle[i].Velocity.y= -1*Particle[i].Velocity.y;
                 qDebug("warning! , %f", Particle[i].Velocity.y);
           }

           //Evaluation
           Particle[i].Cost = MyCost.potential_field(Particle[i].Position);

           //Update Personal Best
           if(Particle[i].Cost < Particle[i].PBest.Cost){
               Particle[i].PBest.Cost = Particle[i].Cost;
               Particle[i].PBest.Position = Particle[i].Position;
           }else{
               Particle[i].NoBestIte++;
           }

           //Update Global Best
           if(Particle[i].PBest.Cost < GBest.Cost){
               GBest = Particle[i].PBest;
           }

           distancia_euclideo = sqrt( pow( Particle[i].Position.x - Target[0].x,2) + pow( Particle[i].Position.y - Target[0].y,2));
           if(distancia_euclideo < 0.55){
               Particle[i].MissionAccomplished = true;
               MissionAccomplishedPop = true;
           }
           if(Particle[i].MissionAccomplished == true){
               countSuccessful = countSuccessful + 1;
           }

           if (FirstOfAll == false){
               if(countSuccessful == nPop){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }else{
               if(MissionAccomplishedPop == true){
                   if(Target.empty()){
                        MissionAccomplished = true;
                   }else{
                       Target.erase(Target.begin());
                       MyCost.set_new_target(Target, 0);
                       ParticleSwarmOptimization::reset_state_particle();
                       ite = 0;
                   }
               }
           }
         }
    }
}
double ParticleSwarmOptimization::randu()
{
    return  ((double)(rand()% 10000+ 1) / 10000);
}

vector<structxy> ParticleSwarmOptimization::getObstaculos(){
    return Obstacles;
}

vector<strucparticle> ParticleSwarmOptimization::getParticle(){
    return Particle;
}

vector<structidxy> ParticleSwarmOptimization::getZoneEnd()
{
    return Target;
}

unsigned int ParticleSwarmOptimization::getCurrentIte()
{
    return ite;
}

Best ParticleSwarmOptimization::getGBest()
{
    return GBest;
}

bool ParticleSwarmOptimization::getThread()
{
    return test_thread;
}

double ParticleSwarmOptimization::randd(double a, double b)
{
    return a + (b - a) * (double(rand() % 100 + 1)/100);
}

solucionTring ParticleSwarmOptimization::FuncionTriangular(unsigned int ite, unsigned int PeriodoIte, unsigned int YMaxFuncion, unsigned int PeriodoIteWWeight, unsigned int YMaxWeight)
{
    PuntoMaxTriangulo = PeriodoIte/2;
    pendiente = (YMaxFuncion - 0)/(PuntoMaxTriangulo);
    M = ite /  PeriodoIte;
    M = int(M) * PeriodoIte;

    PuntoMaxWeight = PeriodoIteWWeight/2;
    pendientew = (YMaxWeight - 0)/(PuntoMaxWeight - 0);
    N = ite /  PeriodoIteWWeight;
    N  = int(N) * PeriodoIteWWeight;

    W1_1 =    pendientew*(ite - (PuntoMaxWeight + N)) + YMaxWeight;
    W1_2 =   -pendientew*(ite - (PuntoMaxWeight + N)) + YMaxWeight;


    W = W1_1*( N <= ite && ite < (PuntoMaxWeight + N) ) + W1_2*( (PuntoMaxWeight + N )<= ite && ite <= (PeriodoIteWWeight + N));


    C1_1 =   pendiente*(ite- (PuntoMaxTriangulo +M)) + YMaxFuncion;
    C1_2 =  -pendiente*(ite- (PuntoMaxTriangulo +M)) + YMaxFuncion ;
    C2_1 =   YMaxFuncion - C1_1;
    C2_2 =   C1_1 - YMaxFuncion;

    C1 = C1_1*( M <= ite && ite < PuntoMaxTriangulo + M) + C1_2*( (PuntoMaxTriangulo +M) <= ite && ite<=  (PeriodoIte + M));
    C2 = C2_1*( M <= ite && ite < PuntoMaxTriangulo + M) + C2_2*( (PuntoMaxTriangulo +M) <= ite && ite<=  (PeriodoIte + M));

    solucionTring solved;
    solved.W = W;
    solved.C1 = C1;
    solved.C2 = C2;

    return solved;
}


