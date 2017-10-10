// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <GL/glut.h>
#include <QMenu>
#include <QTimer>
#include <vector>
#include <sstream>
#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "mystruct.h"


using namespace Eigen;
using namespace std;
using Eigen::MatrixXd;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent = 0);    
    ~MyGLWidget();
    void contextMenuEvent(QContextMenuEvent *event);
    void set_EnableEnd(bool e);
    void set_Ruta(bool e);
    void set_new_target(vector<structidxy> target);
    void reset_obj();
    void set_thread_values(vector<structxy> obstaculos,vector<strucparticle> particulas, vector<structidxy> fin, unsigned int CurrentIteration);
    void set_current_ite(unsigned int ite);
    void paint_objeto_localizado(structxy vect);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);    
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *e);    

public slots:    
    //void hola_(int a);
    void set_values_problem(vector<structxy> obstaculos,vector<strucparticle> particulas, structxy inicio, vector<structidxy> fin, structMapa XYLimMapa, unsigned int CurrentIteration);
    // slots for graph
    void reinicio_graph();
    // slots for xyz-rotation slider    
    void set_Start(bool);
    void set_End(bool);
    void set_Cam(bool);
    void set_Cam2(bool);    

signals:    
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void start_changed(double x, double y);
    void   end_changed(double x, double y);

private:
    QTimer timer;
    structxy getCursorOpenGL(double x, double y);    
    structxy intersectionInRange(double start, double finish, Vector3f ray);

    Vector3f getPointOnRay(Vector3f ray, float distancia);
    Vector3f binarySearch(int count, double start, double finish, Vector3f ray);




    void utDrawText3D(float x, float y, float z, const char *string);
    void draw();

    double xCursor;
    double yCursor;

    double xRot;
    double yRot;
    double zRot;
    double moveX;
    double moveY;
    double moveZ;

    Vector3f vstart;
    Vector3f vfinish;


    structMapa xyMapLimit;

    vector<structxy> obstacle;
    vector<strucparticle> particle;
    structxy objeto_localizado;
    structxy zoneStart;
    vector<structidxy> zoneEnd;

    structxy tempEnd;
    bool problem_set;
    QPoint lastPos;

    QMenu *menu;
    QAction *setStart;
    QAction *setEnd;
    QAction *setCam;
    QAction *setCam2;
    GLdouble ox=0.0,oy=0.0,oz=0.0;

    int width;
    int height;

    bool bStart, bEnd, bCam, bCam2;
    unsigned int CurrentIte;

    bool bRuta;
};

#endif // MYGLWIDGET_H



