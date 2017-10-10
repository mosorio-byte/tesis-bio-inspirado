// myglwidget.cpp

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    menu = new QMenu();
    setStart = new QAction("Set Start",this);
    setEnd =   new QAction("Set End",this);
    setCam =   new QAction("Set Cam",this);
    setCam2 =  new QAction("Set Cam2",this);

    menu->addAction(setStart);
    menu->addAction(setEnd);
    menu->addSeparator();
    menu->addAction(setCam);
    menu->addAction(setCam2);


    connect(setStart,SIGNAL(triggered(bool)),this,SLOT(set_Start(bool)));
    connect(setEnd  ,SIGNAL(triggered(bool)),this,SLOT(set_End(bool)));
    connect(setCam  ,SIGNAL(triggered(bool)),this,SLOT(set_Cam(bool)));
    connect(setCam2  ,SIGNAL(triggered(bool)),this,SLOT(set_Cam2(bool)));

    connect(&timer  ,SIGNAL(timeout()), this, SLOT(updateGL()));

    timer.start(16);

    problem_set = false;
    xRot = 0;
    yRot = 0;
    zRot = -7;

    moveX = 0;
    moveY = 0;
    moveZ = 3;

    bStart = false;
    bEnd   = false;
    bCam   = true;
    bCam2  = false;
    CurrentIte = 0;

    reset_obj();
    //qApp->installEventFilter(this);
    setMouseTracking(true);
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void MyGLWidget::set_Start(bool)
{
    //qDebug("start");
    bStart = true;
    bEnd   = false;
    bCam   = false;
    bCam2  = false;
}

void MyGLWidget::set_End(bool)
{
    //qDebug("end");
    bStart = false;
    bEnd   = true;
    bCam   = false;
    bCam2  = false;
}

void MyGLWidget::set_Cam(bool)
{
    bStart = false;
    bEnd   = false;
    bCam   = true;
    bCam2  = false;
}

void MyGLWidget::set_Cam2(bool)
{
    bStart = false;
    bEnd   = false;
    bCam   = false;
    bCam2  = true;
}

void MyGLWidget::paint_objeto_localizado(structxy vect)
{
    objeto_localizado = vect;
}


structxy MyGLWidget::getCursorOpenGL(double mouse_x, double mouse_y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev( GL_PROJECTION_MATRIX, projection);
    glGetIntegerv( GL_VIEWPORT, viewport );

    Matrix4f modelview_;
    Matrix4f projection_;

    for(int i=0;i < 4; i++){
        for(int j=0; j<4;j++){
            modelview_(i,j)    = modelview[i*4+j];
            projection_(i,j)   = projection[i*4+j];
        }
    }
    //---------------------------------------------------
    //cout << "projeciton" << endl << projection_ <<endl;
    float x = (2.0f * mouse_x) / width - 1.0f;
    float y = 1.0f - (2.0f * mouse_y) / height;
    //cout << "(" << x << "," << y << ")" << endl;
    Vector4f clipCordenadas(x, y , -1.0f, 1.0f);
    //------------------------------------------------------------
    Matrix4f invertedProjection = projection_;
    PartialPivLU<Matrix4f> lu(invertedProjection);
    invertedProjection = lu.inverse();
    //cout << "inverse" << endl << invertedProjection << endl;
    //cout << "clipCoo" << endl << clipCordenadas << endl;
    Vector4f eyeCoords = invertedProjection*clipCordenadas;
    eyeCoords(2) = -1.0f;
    eyeCoords(3) =  0.0f;
    //cout << "eyecordenadas" << endl << eyeCoords << endl;
    //------------------------------------------------------------    
    //cout << "model view" << endl << modelview_ << endl;
    Matrix4f invertedModelview = modelview_;
    PartialPivLU<Matrix4f> la(invertedModelview);
    invertedModelview = la.inverse();
    //cout << "inverse" << endl << invertedModelview << endl;
    Vector4f rayWord = invertedModelview*eyeCoords;
    //cout << "rayWord" << endl << rayWord << endl;
    Vector3f mouseray(rayWord(0), rayWord(1), rayWord(2));
    //cout << "mouseray" << endl << mouseray << endl;
    mouseray.normalize();
    //cout << "mouseray normalizado" << endl << mouseray << endl;

    //qDebug("mouse (%f, %f) | (%f, %f, %f)", x,  y, mouseray(0), mouseray(1),mouseray(2));


    return intersectionInRange(0, 20, mouseray);
}

structxy MyGLWidget::intersectionInRange(double start, double finish, Vector3f ray)
{
    vstart  = getPointOnRay(ray, start);
    vfinish = getPointOnRay(ray, finish);

    Vector3f vRay = vfinish - vstart;

    double t = (-7-moveZ)/vRay(2);
    structxy point;
    point.x = moveX + vRay(0)*t;
    point.y = moveY + vRay(1)*t;
    return point;
}

Vector3f MyGLWidget::getPointOnRay(Vector3f ray, float distancia)
{
    Vector3f start( moveX, moveY, moveZ);
    Vector3f scaledRay( ray(0)*distancia , ray(1)*distancia,ray(2)*distancia);
    return Vector3f(start(0) + scaledRay(0), start(1) + scaledRay(1), start(2) + scaledRay(2));
}

void MyGLWidget::utDrawText3D(float x, float y, float z, const char *string)
{
  //char *c;
  // set position to start drawing fonts
  //glRasterPos2f(x, y);
  qglColor(Qt::black);
  glRasterPos3f ( x, y, z);
  // loop all the characters in the string
  for (unsigned int c=0; c < strlen(string); c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[c]);
  }
}
void MyGLWidget::contextMenuEvent(QContextMenuEvent *event)
{            
    xCursor = event->x();
    yCursor = event->y();
    menu->exec(QCursor::pos());
}

void MyGLWidget::set_EnableEnd(bool e)
{
    setStart->setEnabled(e);
}

void MyGLWidget::set_Ruta(bool e)
{
    bRuta = e;
}

void MyGLWidget::set_new_target(vector<structidxy> target)
{
    this->zoneEnd = target;
}

void MyGLWidget::reset_obj()
{
    objeto_localizado.x = -5;
    objeto_localizado.y = -5;
}

void MyGLWidget::set_thread_values(vector<structxy> obstaculos, vector<strucparticle> particulas, vector<structidxy> fin, unsigned int CurrentIteration)
{
    obstacle  = obstaculos;
    particle  = particulas;
    zoneEnd   = fin;
    CurrentIte = CurrentIteration;
}

void MyGLWidget::set_current_ite(unsigned int ite)
{
    CurrentIte = ite;
}

void MyGLWidget::reinicio_graph(){
    zRot = 0;
    xRot = 0;
    yRot = 0;
    moveX = 0;
    moveY = 0;    
    moveZ = 3;
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    static GLfloat lightPosition[4] = { 5, 5, 0, 0.95 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glLoadIdentity();
    glTranslatef( 0, 0, 0);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();gluPerspective(45.0, 1.25 , 1, 100.0);
    glMatrixMode(GL_MODELVIEW);  glLoadIdentity();gluLookAt( moveX, moveY, moveZ, xRot, yRot, zRot,   0 , 1, 0);
    stringstream ss;
    ss << CurrentIte;
    string str = ss.str();

    utDrawText3D(moveX - 4.3, moveY + 3.5, moveZ - 9.1, "Iteracion:");
    utDrawText3D(moveX - 2.8, moveY + 3.5, moveZ - 9.1, str.c_str());

    utDrawText3D(moveX, moveY + 3.5, moveZ - 9.1, "Seleccionado:");
    if(bCam)
        utDrawText3D(moveX + 2.5, moveY + 3.5, moveZ - 9.1, "Camara");
    if(bStart)
        utDrawText3D(moveX + 2.5, moveY + 3.5, moveZ - 9.1, "Start");
    if(bEnd)
        utDrawText3D(moveX + 2.5, moveY + 3.5, moveZ - 9.1, "End");
    if(bCam2)
        utDrawText3D(moveX + 2.5, moveY + 3.5, moveZ - 9.1, "Camara2");
    this->draw();
}

void MyGLWidget::resizeGL(int width, int height)
{    
    //int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport( 0, 0, width, height);        
    this->width = width;
    this->height= height;
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    if (event->buttons() & Qt::LeftButton) {
        if(bStart){
            zoneStart = getCursorOpenGL(event->x(),event->y());
            emit start_changed(zoneStart.x, zoneStart.y);
        }
        if(bEnd){
            structxy zone;
            zone = getCursorOpenGL(event->x(),event->y());

            emit end_changed(zone.x, zone.y);
        }
    }
    if (event->buttons() & Qt::MidButton) {

    }
    lastPos = event->pos();
    event->accept();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{    
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton) {
        if(bCam){            
            moveX +=  -double(dx)/8;
            moveY +=  double(dy)/8;
            xRot  +=  -double(dx)/8;
            yRot  +=  double(dy)/8;            
        }        
        if(bCam2){
            xRot  +=  double(dx)/16.0f;
            yRot  +=  -double(dy)/16.0f;
        }
    }
    if(bEnd){
        tempEnd = getCursorOpenGL(event->x(),event->y());
    }
    lastPos = event->pos();    
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;
    moveZ += -double(numSteps)/10.0f;
    event->accept();
}

void MyGLWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_W){
        moveY += 0.10;
    }
    if (e->key() == Qt::Key_S){
        moveY -= 0.10;
    }
    if (e->key() == Qt::Key_A){
        moveX -= 0.10;
    }
    if (e->key() == Qt::Key_D){
        moveX += 0.10;
    }
}

void MyGLWidget::set_values_problem(vector<structxy> obstaculos, vector<strucparticle> particulas, structxy inicio, vector<structidxy> fin, structMapa XYLimMapa, unsigned int CurrentIteration)
{
    obstacle  = obstaculos;
    particle  = particulas;
    zoneStart = inicio;
    zoneEnd   = fin;    
    problem_set = true;    
    xyMapLimit = XYLimMapa;
    CurrentIte = CurrentIteration;
}

void MyGLWidget::draw()
{    
    if (particle.empty() != 1){      
        qglColor(Qt::gray);
        for(unsigned int i = 0; i < particle.size() ; i++){
            glPushMatrix();
                glTranslatef( particle[i].Position.x, particle[i].Position.y, 0.17 - 7);
                glutSolidSphere(0.17,10,10);
            glPopMatrix();
        }
    }
    if (obstacle.empty() != 1){
        qglColor(Qt::red);
        for(unsigned int i = 0; i < obstacle.size() ; i++){
            glPushMatrix();
                glTranslatef( obstacle[i].x, obstacle[i].y, 0.17 - 7);
                glutSolidSphere(0.17,10,10);
            glPopMatrix();
        }
    }

    if(problem_set)
    {

        glPushMatrix();
        glTranslatef( 0, 0, -7);
        qglColor(Qt::green);
        glBegin(GL_QUADS);
            glNormal3f( 0,  0, 1);
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[0], 0);
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[1], 0);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[1], 0);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[0], 0);
        glEnd();
        glPopMatrix();

        double zone= 0.5;                
        glPushMatrix();
        glTranslatef( zoneStart.x, zoneStart.y, 0.17 -7);
        qglColor(Qt::blue);
        glBegin(GL_LINE_LOOP);
            glNormal3f( 0,  0, 1);
            glVertex2f( - zone , - zone);
            glVertex2f( - zone , + zone);
            glVertex2f( + zone , + zone);
            glVertex2f( + zone , - zone);
        glEnd();
        glPopMatrix();

        for(unsigned int i = 0; i < zoneEnd.size() ; i++ ){
            glPushMatrix();
            glTranslatef( zoneEnd[i].x, zoneEnd[i].y, 0.17 -7);            
                stringstream ss;
                ss << zoneEnd[i].id;
                string str = ss.str();
                utDrawText3D( 0, 0, 0, str.c_str());
            qglColor(Qt::red);
            glBegin(GL_LINE_LOOP);
                glNormal3f( 0,  0, 1);
                glVertex2f( - zone , - zone);
                glVertex2f( - zone , + zone);
                glVertex2f( + zone , + zone);
                glVertex2f( + zone , - zone);
            glEnd();
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef( 0, 0, -7);
        qglColor(Qt::cyan);
        glBegin(GL_QUADS);
            glNormal3f( 0,  1, 0 );
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[0], 0.0);
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[0], 0.2);
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[1], 0.2);
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[1], 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef( 0, 0, -7);
        qglColor(Qt::cyan);
        glBegin(GL_QUADS);
            glNormal3f( 0,  1, 0 );
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[1], 0.0);
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[1], 0.2);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[1], 0.2);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[1], 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef( 0, 0, -7);
        qglColor(Qt::cyan);
        glBegin(GL_QUADS);
            glNormal3f( 0,  1, 0 );
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[1], 0.0);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[1], 0.2);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[0], 0.2);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[0], 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef( 0, 0, -7);
        qglColor(Qt::cyan);
        glBegin(GL_QUADS);
            glNormal3f( 0,  1, 0 );
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[0], 0.0);
            glVertex3f( xyMapLimit.x[0],  xyMapLimit.y[0], 0.2);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[0], 0.2);
            glVertex3f( xyMapLimit.x[1],  xyMapLimit.y[0], 0.0);
        glEnd();
        glPopMatrix();
    }else{
        float cua[4][2] = {{-3.7, -3.0},
                           {-3.7, +3.0},
                           {+3.7, +3.0},
                           {+3.7, -3.0}
                         };
        glPushMatrix();
        glTranslatef( 0, 0, -7);
        qglColor(Qt::green);
        glBegin(GL_QUADS);
            glNormal3f( 0,  0, 1);
            glVertex3f( cua[0][0],  cua[0][1], 0);
            glVertex3f( cua[1][0],  cua[1][1], 0);
            glVertex3f( cua[2][0],  cua[2][1], 0);
            glVertex3f( cua[3][0],  cua[3][1], 0);
        glEnd();
        glPopMatrix();
    }

    if(bEnd){
        double zone= 0.5;
        glPushMatrix();
        glTranslatef( tempEnd.x, tempEnd.y, 0.17 -7);
        qglColor(Qt::gray);
        glBegin(GL_LINE_LOOP);
            glNormal3f( 0,  0, 1);
            glVertex2f( - zone , - zone);
            glVertex2f( - zone , + zone);
            glVertex2f( + zone , + zone);
            glVertex2f( + zone , - zone);
        glEnd();
        glPopMatrix();
    }

    glPushMatrix();
        qglColor(Qt::blue);
        glTranslatef( objeto_localizado.x, objeto_localizado.y, 0.17 - 7);
        glutSolidSphere(0.17,10,10);
    glPopMatrix();

    /*glTranslatef( 0, 0, 0);
    qglColor(Qt::black);
    glBegin(GL_LINE_LOOP);
       glVertex3f( vstart(0),  vstart(1),  vstart(2));
       glVertex3f( vfinish(0), vfinish(1), vfinish(2));
    glEnd();
    glPopMatrix();*/
}



