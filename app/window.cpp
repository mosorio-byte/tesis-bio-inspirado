// window.cpp

#include <QtWidgets>
#include "window.h"
#include "ui_window.h"
#include "myglwidget.h"
#include "particleswarmoptimization.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);    
    ui->radioButton_2->setChecked(true);
    ui->radioButton_SAplicacion->setChecked(true);
    ui->radioButton_PSOC->setChecked(true);
    ui->pushButton_2->setEnabled(false);
    ui->comboBox->addItem("1", QVariant(0));    

    connect( ui->myGLWidget, SIGNAL(start_changed(double, double)), this, SLOT(start_changed(double, double)));
    connect( ui->myGLWidget, SIGNAL(  end_changed(double, double)), this, SLOT(  end_changed(double, double)));

    bRuta = false;       
    ui->myGLWidget->set_Ruta(false);
    NEnjambres = 1;

    ui->label_22->setText("NOT FOUND");
    ui->label_22->setStyleSheet("QLabel { background-color : red; color : black; }");

    VEnjambres.reserve(5);
    target.reserve(5);

    udpSocketSend = new QUdpSocket(this);
    udpSocketReceive = new QUdpSocket(this);
    udpSocketSend_Command = new QUdpSocket(this);

    m_thread = new QThread(this);
    QTimer* timer_ = new QTimer(0);
    timer_->setInterval(5);
    timer_->moveToThread(m_thread);

    this->connect(timer_, SIGNAL(timeout()), SLOT(doIt()), Qt::DirectConnection);
    timer_->connect(m_thread, SIGNAL(started()), SLOT(start()));
}

Window::~Window()
{        
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();    
    else
        QWidget::keyPressEvent(e);
}

void Window::on_pushButton_aceptar_pso_clicked()
{    
    ui->myGLWidget->reset_obj();
    ui->label_22->setText("NOT FOUND");
    ui->label_22->setStyleSheet("QLabel { background-color : red; color : black; }");
    structxy source;
    structidxy target_;

    VEnjambres.clear();
    for(unsigned int i = 0; i < NEnjambres ; i++){
        VEnjambres.push_back(new ParticleSwarmOptimization());
        VEnjambres[i]->set_enjambre(i);
        connect( VEnjambres[i], SIGNAL(problema_generado(vector<structxy> ,vector<strucparticle> , structxy , vector<structidxy>, structMapa, unsigned int)), ui->myGLWidget , SLOT(set_values_problem(vector<structxy>,vector<strucparticle>, structxy, vector<structidxy> , structMapa, unsigned int)));
        connect( VEnjambres[i], SIGNAL(  finished()),this,SLOT( thread_finished()));
        connect( VEnjambres[i], SIGNAL(send_request_particle(uint,uint)), this, SLOT(request_particle( uint, uint)));
        connect( VEnjambres[i], SIGNAL(send_command_particle(uint,double,double,double)),this,SLOT(command_particle(uint,double,double,double)));
    }

    if(!bRuta){
        if(target.empty()){
            target.resize(VEnjambres.size());
        }

        for(unsigned int i  = 0; i < target.size() ; i++){
            if(target[i].empty()){
                target[i].clear();
                target_.id   = 1;
                target_.x    = ui->lineEdit_target_x->text().toFloat();
                target_.y    = ui->lineEdit_target_y->text().toFloat();
                target[i].push_back(target_);
            }
        }

        ui->label_Ruta->setText(QString::number(target[ui->comboBox->currentIndex()].size()));
    }

    unsigned int maxite      = ui->lineEdit_max_ite->text().toInt();
    float vellimite = ui->lineEdit_vel_limite->text().toFloat();    

    source.x    = ui->lineEdit_source_x->text().toFloat();
    source.y    = ui->lineEdit_source_y->text().toFloat();
    unsigned weight = ui->lineEdit_weight->text().toInt();
    double learnCoefficient = ui->lineEdit_learning_coef->text().toDouble();
    unsigned int timeSimu = ui->lineEdit_Time_Simu->text().toInt();
    unsigned int numparticle = ui->lineEdit_num_particle->text().toInt();
    unsigned int numObstacle = ui->lineEdit_num_obstacle->text().toInt();


    for( int i = 0; i < VEnjambres.size(); i++){       

        if(ui->radioButton->isChecked()){
            VEnjambres[i]->set_limiteMapa(false);
        }else{
            VEnjambres[i]->set_limiteMapa(true);
        }

        if(ui->radioButton_SAplicacion->isChecked()){
            VEnjambres[i]->set_problem( (numparticle / NEnjambres) * i , maxite, numparticle / NEnjambres, vellimite, numObstacle, weight, learnCoefficient, source, target[i], timeSimu);
            VEnjambres[i]->generarProblema();
        }
        if(ui->radioButton_SServer->isChecked()){
            if(!ui->pushButton_escucha->isEnabled()&&!ui->pushButton_escritura->isEnabled()){
                source.x = -5;
                source.y = -5;
                idobs = ui->lineEdit_idObj->text().toInt();
                VEnjambres[i]->set_objeto_localizar(idobs);
                VEnjambres[i]->set_problem( (numparticle / NEnjambres) * i , maxite, numparticle / NEnjambres, vellimite, numObstacle, weight, learnCoefficient, source, target[i], timeSimu);
                VEnjambres[i]->generarProblemaServidor();
            }else{
                QMessageBox::warning(this, tr("Error!"),
                                               tr("No hay conexión establecida."),
                                               QMessageBox::Ok);
            }
        }
    }
    Window::refresh();
    m_thread->start();
}

void Window::on_pushButton_ejecutar_clicked()
{            
    elaptimer.start();    
    for(int i = 0; i < VEnjambres.size() ; i++){

        if(ui->radioButton_SAplicacion->isChecked()){
            if(ui->radioButton_PSOA->isChecked()){
                VEnjambres[i]->set_mode_of_simulation(0);
                //VEnjambres[i]->resolverProblemaPSOA();
            }
            if(ui->radioButton_PSOB->isChecked()){
                VEnjambres[i]->set_mode_of_simulation(1);
                //VEnjambres[i]->resolverProblemaPSOB();
            }
            if(ui->radioButton_PSOC->isChecked()){
                VEnjambres[i]->set_mode_of_simulation(2);
                //VEnjambres[i]->resolverProblemaPSOC();
            }
        }

        if(ui->radioButton_SServer->isChecked()){
            if(ui->radioButton_PSOA->isChecked()){
                VEnjambres[i]->set_mode_of_simulation(3);
                //VEnjambres[i]->resolverProblemaPSOAServer();
            }
            if(ui->radioButton_PSOB->isChecked()){
                VEnjambres[i]->set_mode_of_simulation(4);
                //VEnjambres[i]->resolverProblemaPSOBServer();
            }
            if(ui->radioButton_PSOC->isChecked()){
                VEnjambres[i]->set_mode_of_simulation(5);
                //VEnjambres[i]->resolverProblemaPSOCServer();
            }
        }

        VEnjambres[i]->start();
    }    
    for(unsigned int i = 0; i < NEnjambres ; i++){
        VEnjambres[i]->start_simulacion();
    }    
}

void Window::start_changed(double x, double y)
{ 
    ui->lineEdit_source_x->setText(QString::number(x));
    ui->lineEdit_source_y->setText(QString::number(y));
}

void Window::end_changed(double x, double y)
{
    structidxy target_;
    ui->lineEdit_target_x->setText(QString::number(x));
    ui->lineEdit_target_y->setText(QString::number(y));

    target_.x    = x;
    target_.y    = y;

    if(bRuta)    {        
        if(target[ui->comboBox->currentIndex()].size() > 6){
            target[ui->comboBox->currentIndex()].clear();
        }
         target_.id = target[ui->comboBox->currentIndex()].size() + 1;
         target[ui->comboBox->currentIndex()].push_back(target_);
    }else{
        target[ui->comboBox->currentIndex()].clear();
        target_.id = 1;
        target[ui->comboBox->currentIndex()].push_back(target_);
    }
    ui->label_Ruta->setText(QString::number(target[ui->comboBox->currentIndex()].size()));

    Window::update_problem();
}

void Window::obj_found(structxy vect)
{
  ui->lineEdit_2->setText(QString::number(vect.x));
  ui->lineEdit_3->setText(QString::number(vect.y));  
  ui->label_22->setText("FOUND!");
  ui->label_22->setStyleSheet("QLabel { background-color : green; color : white; }");
}

void Window::on_pushButton_escucha_clicked()
{    
    ip_server   = QHostAddress(ui->lineEdit_ip_escucha->text().toStdString().c_str());
    port_server = ui->lineEdit_port_escucha->text().toInt();
    udpSocketReceive->bind( ip_server, port_server);

    ui->pushButton_escucha->setEnabled(false);
    ui->lineEdit_ip_escucha->setEnabled(false);
    ui->lineEdit_port_escucha->setEnabled(false);        
}

void Window::on_pushButton_escritura_clicked()
{
    ip   = QHostAddress(ui->lineEdit_ip_escritura->text().toStdString().c_str());
    port = ui->lineEdit_port_escritura->text().toInt();

    ui->pushButton_escritura->setEnabled(false);
    ui->lineEdit_ip_escritura->setEnabled(false);
    ui->lineEdit_port_escritura->setEnabled(false);
}

void Window::on_radioButton_SAplicacion_clicked()
{
    ui->myGLWidget->set_EnableEnd(true);
}

void Window::on_radioButton_SServer_clicked()
{
    ui->myGLWidget->set_EnableEnd(false);
}

void Window::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->myGLWidget->set_Ruta(true);
    bRuta = true;
}

void Window::on_pushButton_2_clicked()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->myGLWidget->set_Ruta(false);
    bRuta = false;
}

void Window::update_problem()
{   
   VEnjambres[ui->comboBox->currentIndex()]->set_new_target(target[ui->comboBox->currentIndex()]);
   Window::refresh();
}

void Window::refresh()
{
    vector<structidxy> targetCompleto;
    vector<structidxy>::iterator it;
    it = targetCompleto.begin();

    for(unsigned int i = 0; i < target.size(); i++){
        for(unsigned int j = 0; j < target[i].size(); j++)
         it = targetCompleto.insert(it, target[i][j]);
    }
    ui->myGLWidget->set_new_target(targetCompleto);
}

void Window::on_pushButton_3_clicked()
{
    for(unsigned int i = 0; i < NEnjambres; i++) {
        VEnjambres[i]->exit_simulacion();
    }
}

void Window::on_pushButton_5_clicked()
{    
    target[ui->comboBox->currentIndex()].clear();
    ui->label_Ruta->setText(QString::number(target[ui->comboBox->currentIndex()].size()));
    Window::update_problem();
}

void Window::on_pushButton_EnjambreOK_clicked()
{    
    NEnjambres = ui->lineEdit_NEnjambres->text().toInt();
    ui->comboBox->clear();
    for(unsigned int i = 0 ; i < NEnjambres ; i++){
        ui->comboBox->addItem(QString::number(i+1) ,QVariant(i));
    }
    double test = (double)ui->lineEdit_num_particle->text().toInt() / (double) ui->lineEdit_NEnjambres->text().toInt();
    test = test - (int)test  ;
    if(test > 0){
        QMessageBox::warning(this, tr("Error!"),
                                       tr("No sé pueden crear las colonias."),
                                       QMessageBox::Ok);
        NEnjambres = 1;
        ui->lineEdit_NEnjambres->setText(QString::number(1));
    }else{
        target.resize(NEnjambres);
        VEnjambres.resize(NEnjambres);
    }
    Window::on_pushButton_aceptar_pso_clicked();
}

void Window::doIt()
{
    obsThread.clear();
    partThread.clear();
    endThread.clear();
    CurrentIterationThread = 0;

    for(int i = 0; i < VEnjambres.size(); i++){
           CobsThread  = VEnjambres[i]->getObstaculos();
           CpartThread = VEnjambres[i]->getParticle();
           CendThread  = VEnjambres[i]->getZoneEnd();

           obsThread.insert (  obsThread.begin() , CobsThread.begin() , CobsThread.end());
           partThread.insert(  partThread.begin(), CpartThread.begin(), CpartThread.end());
           endThread.insert (  endThread.begin() , CendThread.begin() , CendThread.end());
           CurrentIterationThread += VEnjambres[i]->getCurrentIte();
    }

    for(int i = 0; i < VEnjambres.size(); i++){           
           VEnjambres[i]->set_new_obstacles(obsThread);                      
           VEnjambres[i]->set_new_Particles_Thread(partThread);
    }
    ui->myGLWidget->set_thread_values(obsThread, partThread, endThread , CurrentIterationThread/VEnjambres.size());
}

void Window::on_pushButton_reset_graph_clicked()
{
    for(unsigned int i = 0; i < partThread.size(); i++){
        qDebug(" %d (%f, %f)", partThread[i].id, partThread[i].Position.x, partThread[i].Position.y);
    }
    for(int i = 0; i < VEnjambres.size(); i++){
           qDebug("%i", VEnjambres[i]->getThread());
    }
}

void Window::thread_finished()
{
    ui->label_timer->setText(QString::number(elaptimer.elapsed()));
    QApplication::beep();
    /*QMessageBox::information(this, tr("Successful!"),
                                   tr("Simulación terminada."),
                                   QMessageBox::Ok);*/
}

void Window::request_particle(unsigned int id, unsigned int enjambre)
{
    //qDebug("id: %d enjambre: %d", id, enjambre);
    result_request = -1;

    //Paquete
    packet.Clear();
    request = packet.mutable_request();
    request->set_robotid(id);
    datagram.clear();
    datagram.resize(packet.ByteSize());
    packet.SerializeToArray(datagram.data(), datagram.size());

    //Envio Request
    udpSocketSend->writeDatagram(datagram, ip, port);
    if(nBytesSend <= 0) {
        qDebug("Error: Can't send data");
        VEnjambres[enjambre]->exit_simulacion();
        result_request = -1;
    }else{
        receiveDatagram.clear();
        udpSocketReceive->waitForReadyRead(500);
        receiveDatagram.resize(udpSocketReceive->pendingDatagramSize());
        nBytesRecieve = udpSocketReceive->readDatagram(receiveDatagram.data(), receiveDatagram.size());
        if(nBytesRecieve > 0){
            result_request = 0;
            robotStatus.Clear();
            robotStatus.ParseFromArray(receiveDatagram.data(), receiveDatagram.size());

            responce_particle.id =  robotStatus.robotid();
            responce_particle.Position.x = robotStatus.pos().x()/1000;
            responce_particle.Position.y = robotStatus.pos().y()/1000;

            VEnjambres[enjambre]->set_responce_particle(responce_particle);
            for(int i=0; i< robotStatus.obstacles_size(); i++)
            {
                    responce_obstacle.x = robotStatus.obstacles(i).pos().x() / double(1000);
                    responce_obstacle.y = robotStatus.obstacles(i).pos().y() / double(1000);

                    if(idobs == robotStatus.obstacles(i).obstacleid())
                    {
                        VEnjambres[enjambre]->exit_simulacion();
                        Window::obj_found(responce_obstacle);
                        ui->myGLWidget->paint_objeto_localizado(responce_obstacle);                                                
                    }else{                        
                        VEnjambres[enjambre]->set_new_obstacles(responce_obstacle);                        
                    }
            }
        }
        else{
            qDebug("Read timeout !!");
            VEnjambres[enjambre]->exit_simulacion();
            result_request = -1;
        }
    }

    VEnjambres[enjambre]->set_result_request(result_request);
    VEnjambres[enjambre]->set_unlockmutex_a();
}

void Window::command_particle(unsigned int id, double vx, double vy, double t)
{        
    command = packet_send.mutable_command();
    command->set_robotid(id);
    command->set_vx(vx);
    command->set_vy(vy);
    command->set_t(t);

    datagram_send.resize(packet_send.ByteSize());
    packet_send.SerializeToArray(datagram_send.data(), datagram_send.size());

    if(udpSocketSend_Command->writeDatagram( datagram_send, ip, port) <= 0){
        qDebug("Error: Can't send data");
    }
}
