/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <myglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QPushButton *pushButton_escritura;
    QLineEdit *lineEdit_ip_escritura;
    QLineEdit *lineEdit_port_escritura;
    QLineEdit *lineEdit_ip_escucha;
    QPushButton *pushButton_escucha;
    QLineEdit *lineEdit_port_escucha;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_max_ite;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_num_particle;
    QLabel *label_5;
    QLineEdit *lineEdit_vel_limite;
    QLineEdit *lineEdit_num_obstacle;
    QLabel *label_6;
    QLabel *label_9;
    QLineEdit *lineEdit_source_x;
    QLabel *label_10;
    QLineEdit *lineEdit_source_y;
    QLineEdit *lineEdit_target_x;
    QLineEdit *lineEdit_target_y;
    QLabel *label_11;
    QLineEdit *lineEdit_weight;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_17;
    QLineEdit *lineEdit_learning_coef;
    QGroupBox *groupBox_4;
    QRadioButton *radioButton_SAplicacion;
    QRadioButton *radioButton_SServer;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_3;
    QFrame *frame;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QLabel *label_20;
    QLabel *label_Ruta;
    QLabel *label_24;
    QComboBox *comboBox;
    QLabel *label_28;
    QFrame *frame_2;
    QLabel *label_7;
    QLineEdit *lineEdit_idObj;
    QLabel *label_22;
    QLabel *label_8;
    QLineEdit *lineEdit_2;
    QLabel *label_21;
    QLabel *label_19;
    QLineEdit *lineEdit_3;
    QLabel *label_25;
    QFrame *frame_3;
    QLabel *label_26;
    QLabel *label_16;
    QLineEdit *lineEdit_NEnjambres;
    QPushButton *pushButton_EnjambreOK;
    QFrame *frame_4;
    QLabel *label_27;
    QLabel *label_timer;
    QLabel *label_timer_2;
    QVBoxLayout *verticalLayout_5;
    MyGLWidget *myGLWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QRadioButton *radioButton_PSOA;
    QRadioButton *radioButton_PSOB;
    QRadioButton *radioButton_PSOC;
    QPushButton *pushButton_reset_graph;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_Time_Simu;
    QLabel *label_18;
    QPushButton *pushButton_aceptar_pso;
    QPushButton *pushButton_ejecutar;
    QPushButton *pushButton_salir;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(1100, 600);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Window->sizePolicy().hasHeightForWidth());
        Window->setSizePolicy(sizePolicy);
        Window->setMinimumSize(QSize(1100, 600));
        Window->setMaximumSize(QSize(1100, 587));
        verticalLayout = new QVBoxLayout(Window);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(Window);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(0, 100));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        groupBox->setFont(font);
        pushButton_escritura = new QPushButton(groupBox);
        pushButton_escritura->setObjectName(QStringLiteral("pushButton_escritura"));
        pushButton_escritura->setGeometry(QRect(450, 60, 83, 28));
        QFont font1;
        font1.setFamily(QStringLiteral("Cantarell"));
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        pushButton_escritura->setFont(font1);
        lineEdit_ip_escritura = new QLineEdit(groupBox);
        lineEdit_ip_escritura->setObjectName(QStringLiteral("lineEdit_ip_escritura"));
        lineEdit_ip_escritura->setGeometry(QRect(240, 60, 131, 28));
        lineEdit_ip_escritura->setFont(font1);
        lineEdit_ip_escritura->setMaxLength(15);
        lineEdit_port_escritura = new QLineEdit(groupBox);
        lineEdit_port_escritura->setObjectName(QStringLiteral("lineEdit_port_escritura"));
        lineEdit_port_escritura->setGeometry(QRect(370, 60, 71, 28));
        lineEdit_port_escritura->setFont(font1);
        lineEdit_port_escritura->setMaxLength(6);
        lineEdit_port_escritura->setCursorPosition(5);
        lineEdit_ip_escucha = new QLineEdit(groupBox);
        lineEdit_ip_escucha->setObjectName(QStringLiteral("lineEdit_ip_escucha"));
        lineEdit_ip_escucha->setGeometry(QRect(240, 30, 131, 28));
        lineEdit_ip_escucha->setFont(font1);
        lineEdit_ip_escucha->setMaxLength(15);
        pushButton_escucha = new QPushButton(groupBox);
        pushButton_escucha->setObjectName(QStringLiteral("pushButton_escucha"));
        pushButton_escucha->setGeometry(QRect(450, 30, 83, 28));
        pushButton_escucha->setFont(font1);
        lineEdit_port_escucha = new QLineEdit(groupBox);
        lineEdit_port_escucha->setObjectName(QStringLiteral("lineEdit_port_escucha"));
        lineEdit_port_escucha->setGeometry(QRect(370, 30, 71, 28));
        lineEdit_port_escucha->setFont(font1);
        lineEdit_port_escucha->setMaxLength(6);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 181, 20));
        label->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 231, 20));
        label_2->setFont(font1);

        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Window);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMinimumSize(QSize(0, 270));
        groupBox_2->setMaximumSize(QSize(16777214, 16777215));
        groupBox_2->setFont(font);
        lineEdit_max_ite = new QLineEdit(groupBox_2);
        lineEdit_max_ite->setObjectName(QStringLiteral("lineEdit_max_ite"));
        lineEdit_max_ite->setGeometry(QRect(160, 30, 61, 28));
        lineEdit_max_ite->setFont(font1);
        lineEdit_max_ite->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 40, 141, 20));
        label_3->setFont(font1);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 80, 141, 20));
        label_4->setFont(font1);
        lineEdit_num_particle = new QLineEdit(groupBox_2);
        lineEdit_num_particle->setObjectName(QStringLiteral("lineEdit_num_particle"));
        lineEdit_num_particle->setGeometry(QRect(160, 70, 61, 28));
        lineEdit_num_particle->setFont(font1);
        lineEdit_num_particle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 120, 121, 20));
        label_5->setFont(font1);
        lineEdit_vel_limite = new QLineEdit(groupBox_2);
        lineEdit_vel_limite->setObjectName(QStringLiteral("lineEdit_vel_limite"));
        lineEdit_vel_limite->setGeometry(QRect(160, 110, 61, 28));
        lineEdit_vel_limite->setFont(font1);
        lineEdit_vel_limite->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_num_obstacle = new QLineEdit(groupBox_2);
        lineEdit_num_obstacle->setObjectName(QStringLiteral("lineEdit_num_obstacle"));
        lineEdit_num_obstacle->setGeometry(QRect(160, 230, 61, 28));
        lineEdit_num_obstacle->setFont(font1);
        lineEdit_num_obstacle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 240, 151, 20));
        label_6->setFont(font1);
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(240, 70, 151, 20));
        label_9->setFont(font1);
        lineEdit_source_x = new QLineEdit(groupBox_2);
        lineEdit_source_x->setObjectName(QStringLiteral("lineEdit_source_x"));
        lineEdit_source_x->setGeometry(QRect(380, 60, 41, 28));
        lineEdit_source_x->setFont(font1);
        lineEdit_source_x->setText(QStringLiteral("-3.0"));
        lineEdit_source_x->setMaxLength(4);
        lineEdit_source_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(240, 110, 151, 20));
        label_10->setFont(font1);
        lineEdit_source_y = new QLineEdit(groupBox_2);
        lineEdit_source_y->setObjectName(QStringLiteral("lineEdit_source_y"));
        lineEdit_source_y->setGeometry(QRect(450, 60, 41, 28));
        lineEdit_source_y->setFont(font1);
        lineEdit_source_y->setMaxLength(4);
        lineEdit_source_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_target_x = new QLineEdit(groupBox_2);
        lineEdit_target_x->setObjectName(QStringLiteral("lineEdit_target_x"));
        lineEdit_target_x->setGeometry(QRect(380, 100, 41, 28));
        lineEdit_target_x->setFont(font1);
        lineEdit_target_x->setMaxLength(4);
        lineEdit_target_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_target_y = new QLineEdit(groupBox_2);
        lineEdit_target_y->setObjectName(QStringLiteral("lineEdit_target_y"));
        lineEdit_target_y->setGeometry(QRect(450, 100, 41, 28));
        lineEdit_target_y->setFont(font1);
        lineEdit_target_y->setMaxLength(4);
        lineEdit_target_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 160, 101, 20));
        label_11->setFont(font1);
        lineEdit_weight = new QLineEdit(groupBox_2);
        lineEdit_weight->setObjectName(QStringLiteral("lineEdit_weight"));
        lineEdit_weight->setGeometry(QRect(160, 150, 61, 28));
        lineEdit_weight->setFont(font1);
        lineEdit_weight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(360, 70, 20, 20));
        label_12->setFont(font1);
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(360, 110, 20, 20));
        label_13->setFont(font1);
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(430, 70, 20, 20));
        label_14->setFont(font1);
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(430, 110, 20, 20));
        label_15->setFont(font1);
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(250, 30, 105, 26));
        radioButton->setFont(font1);
        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(420, 30, 101, 26));
        radioButton_2->setFont(font1);
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 200, 151, 20));
        label_17->setFont(font1);
        lineEdit_learning_coef = new QLineEdit(groupBox_2);
        lineEdit_learning_coef->setObjectName(QStringLiteral("lineEdit_learning_coef"));
        lineEdit_learning_coef->setGeometry(QRect(160, 190, 61, 28));
        lineEdit_learning_coef->setFont(font1);
        lineEdit_learning_coef->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(240, 150, 281, 111));
        QFont font2;
        font2.setFamily(QStringLiteral("Cantarell"));
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        groupBox_4->setFont(font2);
        radioButton_SAplicacion = new QRadioButton(groupBox_4);
        radioButton_SAplicacion->setObjectName(QStringLiteral("radioButton_SAplicacion"));
        radioButton_SAplicacion->setGeometry(QRect(30, 40, 201, 26));
        QFont font3;
        font3.setFamily(QStringLiteral("Bitstream Vera Sans"));
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        radioButton_SAplicacion->setFont(font3);
        radioButton_SServer = new QRadioButton(groupBox_4);
        radioButton_SServer->setObjectName(QStringLiteral("radioButton_SServer"));
        radioButton_SServer->setGeometry(QRect(30, 70, 191, 26));
        radioButton_SServer->setFont(font3);

        verticalLayout_2->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        groupBox_3 = new QGroupBox(Window);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 200));
        groupBox_3->setFont(font);
        frame = new QFrame(groupBox_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(260, 30, 271, 91));
        QFont font4;
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        frame->setFont(font4);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 50, 61, 31));
        pushButton->setFont(font4);
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(80, 50, 81, 31));
        pushButton_2->setFont(font4);
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(190, 50, 71, 31));
        pushButton_5->setFont(font4);
        label_20 = new QLabel(frame);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(20, 0, 241, 21));
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(true);
        font5.setItalic(true);
        font5.setWeight(75);
        label_20->setFont(font5);
        label_Ruta = new QLabel(frame);
        label_Ruta->setObjectName(QStringLiteral("label_Ruta"));
        label_Ruta->setGeometry(QRect(240, 20, 16, 20));
        QFont font6;
        font6.setPointSize(11);
        font6.setBold(false);
        font6.setItalic(false);
        font6.setWeight(50);
        label_Ruta->setFont(font6);
        label_24 = new QLabel(frame);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(150, 20, 81, 21));
        label_24->setFont(font6);
        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 20, 61, 21));
        label_28 = new QLabel(frame);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(10, 20, 81, 21));
        label_28->setFont(font6);
        frame_2 = new QFrame(groupBox_3);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 30, 231, 91));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 30, 21, 20));
        label_7->setFont(font4);
        lineEdit_idObj = new QLineEdit(frame_2);
        lineEdit_idObj->setObjectName(QStringLiteral("lineEdit_idObj"));
        lineEdit_idObj->setGeometry(QRect(40, 30, 21, 21));
        lineEdit_idObj->setFont(font4);
        lineEdit_idObj->setMaxLength(1);
        lineEdit_idObj->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_22 = new QLabel(frame_2);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 60, 101, 20));
        label_22->setFont(font4);
        label_22->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(70, 30, 71, 20));
        label_8->setFont(font4);
        lineEdit_2 = new QLineEdit(frame_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(170, 30, 41, 21));
        lineEdit_2->setFont(font4);
        lineEdit_2->setMaxLength(4);
        lineEdit_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_21 = new QLabel(frame_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(140, 30, 16, 20));
        label_21->setFont(font4);
        label_19 = new QLabel(frame_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(140, 60, 21, 20));
        label_19->setFont(font4);
        lineEdit_3 = new QLineEdit(frame_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(170, 60, 41, 21));
        lineEdit_3->setFont(font4);
        lineEdit_3->setMaxLength(4);
        lineEdit_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_25 = new QLabel(frame_2);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 0, 221, 21));
        label_25->setFont(font5);
        frame_3 = new QFrame(groupBox_3);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(10, 130, 321, 65));
        frame_3->setMinimumSize(QSize(0, 65));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_26 = new QLabel(frame_3);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 0, 221, 21));
        label_26->setFont(font5);
        label_16 = new QLabel(frame_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 30, 151, 20));
        label_16->setFont(font4);
        lineEdit_NEnjambres = new QLineEdit(frame_3);
        lineEdit_NEnjambres->setObjectName(QStringLiteral("lineEdit_NEnjambres"));
        lineEdit_NEnjambres->setGeometry(QRect(170, 30, 41, 21));
        lineEdit_NEnjambres->setFont(font4);
        lineEdit_NEnjambres->setMaxLength(4);
        lineEdit_NEnjambres->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_EnjambreOK = new QPushButton(frame_3);
        pushButton_EnjambreOK->setObjectName(QStringLiteral("pushButton_EnjambreOK"));
        pushButton_EnjambreOK->setGeometry(QRect(220, 30, 83, 20));
        pushButton_EnjambreOK->setFont(font4);
        frame_4 = new QFrame(groupBox_3);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(340, 130, 191, 65));
        frame_4->setMinimumSize(QSize(0, 65));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        label_27 = new QLabel(frame_4);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(10, 0, 181, 21));
        label_27->setFont(font5);
        label_timer = new QLabel(frame_4);
        label_timer->setObjectName(QStringLiteral("label_timer"));
        label_timer->setGeometry(QRect(30, 30, 81, 20));
        label_timer->setFont(font4);
        label_timer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_timer_2 = new QLabel(frame_4);
        label_timer_2->setObjectName(QStringLiteral("label_timer_2"));
        label_timer_2->setGeometry(QRect(110, 30, 20, 20));
        label_timer_2->setFont(font4);
        label_timer_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(groupBox_3);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        myGLWidget = new MyGLWidget(Window);
        myGLWidget->setObjectName(QStringLiteral("myGLWidget"));
        myGLWidget->setEnabled(true);
        sizePolicy.setHeightForWidth(myGLWidget->sizePolicy().hasHeightForWidth());
        myGLWidget->setSizePolicy(sizePolicy);
        myGLWidget->setMinimumSize(QSize(500, 400));
        myGLWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        myGLWidget->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_5->addWidget(myGLWidget, 0, Qt::AlignHCenter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(Window);
        widget->setObjectName(QStringLiteral("widget"));
        radioButton_PSOA = new QRadioButton(widget);
        radioButton_PSOA->setObjectName(QStringLiteral("radioButton_PSOA"));
        radioButton_PSOA->setGeometry(QRect(0, 0, 66, 26));
        radioButton_PSOB = new QRadioButton(widget);
        radioButton_PSOB->setObjectName(QStringLiteral("radioButton_PSOB"));
        radioButton_PSOB->setGeometry(QRect(100, 0, 81, 26));
        radioButton_PSOC = new QRadioButton(widget);
        radioButton_PSOC->setObjectName(QStringLiteral("radioButton_PSOC"));
        radioButton_PSOC->setGeometry(QRect(200, 0, 81, 26));

        horizontalLayout->addWidget(widget);

        pushButton_reset_graph = new QPushButton(Window);
        pushButton_reset_graph->setObjectName(QStringLiteral("pushButton_reset_graph"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_reset_graph->sizePolicy().hasHeightForWidth());
        pushButton_reset_graph->setSizePolicy(sizePolicy3);
        pushButton_reset_graph->setMinimumSize(QSize(15, 0));
        pushButton_reset_graph->setMaximumSize(QSize(110, 16777215));

        horizontalLayout->addWidget(pushButton_reset_graph);

        pushButton_3 = new QPushButton(Window);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(130, 0));
        pushButton_3->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_3);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit_Time_Simu = new QLineEdit(Window);
        lineEdit_Time_Simu->setObjectName(QStringLiteral("lineEdit_Time_Simu"));
        lineEdit_Time_Simu->setMaxLength(5);
        lineEdit_Time_Simu->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lineEdit_Time_Simu);

        label_18 = new QLabel(Window);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_3->addWidget(label_18);


        verticalLayout_5->addLayout(horizontalLayout_3);

        pushButton_aceptar_pso = new QPushButton(Window);
        pushButton_aceptar_pso->setObjectName(QStringLiteral("pushButton_aceptar_pso"));

        verticalLayout_5->addWidget(pushButton_aceptar_pso);

        pushButton_ejecutar = new QPushButton(Window);
        pushButton_ejecutar->setObjectName(QStringLiteral("pushButton_ejecutar"));

        verticalLayout_5->addWidget(pushButton_ejecutar);

        pushButton_salir = new QPushButton(Window);
        pushButton_salir->setObjectName(QStringLiteral("pushButton_salir"));

        verticalLayout_5->addWidget(pushButton_salir);


        horizontalLayout_4->addLayout(verticalLayout_5);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(Window);
        QObject::connect(pushButton_salir, SIGNAL(clicked()), Window, SLOT(close()));
        QObject::connect(pushButton_reset_graph, SIGNAL(clicked()), myGLWidget, SLOT(reinicio_graph()));

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "Window", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Window", "Conexi\303\263n UDP", Q_NULLPTR));
        pushButton_escritura->setText(QApplication::translate("Window", "Seleccionar", Q_NULLPTR));
        lineEdit_ip_escritura->setText(QApplication::translate("Window", "192.168.1.13", Q_NULLPTR));
        lineEdit_port_escritura->setText(QApplication::translate("Window", "50010", Q_NULLPTR));
        lineEdit_ip_escucha->setText(QApplication::translate("Window", "192.168.1.12", Q_NULLPTR));
        pushButton_escucha->setText(QApplication::translate("Window", "Escuchar", Q_NULLPTR));
        lineEdit_port_escucha->setText(QApplication::translate("Window", "50020", Q_NULLPTR));
        label->setText(QApplication::translate("Window", "Abrir Conexi\303\263n de Escucha:", Q_NULLPTR));
        label_2->setText(QApplication::translate("Window", "Establecer Direcci\303\263n de Escritura:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Window", "Particle Swarm  Optimization", Q_NULLPTR));
        lineEdit_max_ite->setText(QApplication::translate("Window", "1000", Q_NULLPTR));
        label_3->setText(QApplication::translate("Window", "M\303\241ximas Iteraciones:", Q_NULLPTR));
        label_4->setText(QApplication::translate("Window", "N\303\272mero de Particulas:", Q_NULLPTR));
        lineEdit_num_particle->setText(QApplication::translate("Window", "3", Q_NULLPTR));
        label_5->setText(QApplication::translate("Window", "Velocidad Limite:", Q_NULLPTR));
        lineEdit_vel_limite->setText(QApplication::translate("Window", "0.25", Q_NULLPTR));
        lineEdit_num_obstacle->setText(QApplication::translate("Window", "3", Q_NULLPTR));
        label_6->setText(QApplication::translate("Window", "N\303\272mero Obstaculos:", Q_NULLPTR));
        label_9->setText(QApplication::translate("Window", "Source Particle:", Q_NULLPTR));
        label_10->setText(QApplication::translate("Window", "Target Particle:", Q_NULLPTR));
        lineEdit_source_y->setText(QApplication::translate("Window", "-2.3", Q_NULLPTR));
        lineEdit_target_x->setText(QApplication::translate("Window", "3.0", Q_NULLPTR));
        lineEdit_target_y->setText(QApplication::translate("Window", "2.3", Q_NULLPTR));
        label_11->setText(QApplication::translate("Window", "Inertial Weight:", Q_NULLPTR));
        lineEdit_weight->setText(QApplication::translate("Window", "1", Q_NULLPTR));
        label_12->setText(QApplication::translate("Window", "x:", Q_NULLPTR));
        label_13->setText(QApplication::translate("Window", "x:", Q_NULLPTR));
        label_14->setText(QApplication::translate("Window", "y:", Q_NULLPTR));
        label_15->setText(QApplication::translate("Window", "y:", Q_NULLPTR));
        radioButton->setText(QApplication::translate("Window", "1/2 Cancha", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("Window", "1 Cancha", Q_NULLPTR));
        label_17->setText(QApplication::translate("Window", "Learning Coefficient:", Q_NULLPTR));
        lineEdit_learning_coef->setText(QApplication::translate("Window", "4", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("Window", "Configuraci\303\263n de Simulaci\303\263n", Q_NULLPTR));
        radioButton_SAplicacion->setText(QApplication::translate("Window", "Simular en la Aplicaci\303\263n", Q_NULLPTR));
        radioButton_SServer->setText(QApplication::translate("Window", "Simular en el Servidor", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Window", "Configuraci\303\263n General", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Window", "Activar", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Window", "Desactivar", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Window", "Reset", Q_NULLPTR));
        label_20->setText(QApplication::translate("Window", "Selecci\303\263n de Ruta para Busqueda", Q_NULLPTR));
        label_Ruta->setText(QApplication::translate("Window", "0", Q_NULLPTR));
        label_24->setText(QApplication::translate("Window", "Item de ruta:", Q_NULLPTR));
        label_28->setText(QApplication::translate("Window", "Enjambre:", Q_NULLPTR));
        label_7->setText(QApplication::translate("Window", "ID:", Q_NULLPTR));
        lineEdit_idObj->setText(QApplication::translate("Window", "6", Q_NULLPTR));
        label_22->setText(QApplication::translate("Window", "NOT FOUND", Q_NULLPTR));
        label_8->setText(QApplication::translate("Window", "Posicion", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("Window", "0", Q_NULLPTR));
        label_21->setText(QApplication::translate("Window", "x:", Q_NULLPTR));
        label_19->setText(QApplication::translate("Window", "y:", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("Window", "0", Q_NULLPTR));
        label_25->setText(QApplication::translate("Window", "Selecci\303\263n de Objetivo a Localizar", Q_NULLPTR));
        label_26->setText(QApplication::translate("Window", "Selecci\303\263n de Enjambres ", Q_NULLPTR));
        label_16->setText(QApplication::translate("Window", "Numero de Enjambres:", Q_NULLPTR));
        lineEdit_NEnjambres->setText(QApplication::translate("Window", "1", Q_NULLPTR));
        pushButton_EnjambreOK->setText(QApplication::translate("Window", "OK", Q_NULLPTR));
        label_27->setText(QApplication::translate("Window", "Tiempo de Procesamiento ", Q_NULLPTR));
        label_timer->setText(QApplication::translate("Window", "0", Q_NULLPTR));
        label_timer_2->setText(QApplication::translate("Window", "ms", Q_NULLPTR));
        radioButton_PSOA->setText(QApplication::translate("Window", "PSO A", Q_NULLPTR));
        radioButton_PSOB->setText(QApplication::translate("Window", "PSO BX", Q_NULLPTR));
        radioButton_PSOC->setText(QApplication::translate("Window", "PSO CX", Q_NULLPTR));
        pushButton_reset_graph->setText(QApplication::translate("Window", "Reiniciar C\303\241mara", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Window", "Detener Simulaci\303\263n", Q_NULLPTR));
        lineEdit_Time_Simu->setText(QApplication::translate("Window", "15", Q_NULLPTR));
        label_18->setText(QApplication::translate("Window", "Tiempo de paso para la Simulaci\303\263n (ms)", Q_NULLPTR));
        pushButton_aceptar_pso->setText(QApplication::translate("Window", "Generar/Cargar", Q_NULLPTR));
        pushButton_ejecutar->setText(QApplication::translate("Window", "Ejecutar Codigo Simulacion", Q_NULLPTR));
        pushButton_salir->setText(QApplication::translate("Window", "Salir", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
