/*
    The program creates some animation to ensure the user that
    there is an on going process.

    The naming and the formatting of the code is a working progress.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItemAnimation>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setup()
{
    // make sure everything is ready
    intialize();
    color();
    style();
    startAnimation();

    // add items to window
    setCentralWidget(box);
    boxLayout->addWidget(gv);
    boxLayout->addWidget(textHolder);
    box->setStyleSheet("background: url(\":/wp.jpg\")");

    //
    setWindowTitle("Loading Animation");
}

void MainWindow::intialize()
{
    // creates items at their rigth position and add them to a scene

    const qreal holderRad = 50/4;
    const qreal ropeH = 150/4;
    const qreal ropeW = 2/4;
    const qreal bulbRad = 25;

    timer = new QTimer;
    textTimer = new QTimer;
    textHolder = new QListWidget(this);

    box = new QWidget(this);
    boxLayout = new QHBoxLayout(box);

    gv = new QGraphicsView(this);
    scene = new QGraphicsScene(gv);
    holder = new QGraphicsEllipseItem(-holderRad,0,holderRad*2,holderRad*2);
    nail = new QGraphicsEllipseItem(-holderRad/2,holderRad-holderRad/2,holderRad/2*2,holderRad/2*2,holder);
    rope = new QGraphicsRectItem(-ropeW/2,holderRad*2,ropeW,ropeH);
    pendBulb = new QGraphicsEllipseItem(-bulbRad,holderRad*2+ropeH,bulbRad*2,bulbRad*2);

    gv->setScene(scene);
    scene->addItem(holder);
    scene->addItem(rope);
    scene->addItem(pendBulb);
}

void MainWindow::color()
{
    gv->setRenderHints(QPainter::Antialiasing);

    QColor red (220, 78, 65);
    QColor blackish (7, 9, 16);
    QColor blue (73, 137, 244);
    QColor green (26, 161, 95);
    QColor yellow (255, 205, 66);

    const QPen defPen = QPen(blackish,3);

    holder->setPen(defPen);
    nail->setPen(defPen);
    rope->setPen(defPen);
    pendBulb->setPen(defPen);

    nail->setBrush(blackish);
    pendBulb->setBrush(yellow);
}

void MainWindow::style()
{
    setStyleSheet("border: 0;");
    textHolder->setFont(QFont ("Century Gothic",18,50));
}

void MainWindow::startAnimation()
{
    timer->start(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveBulb()));

    textTimer->start(1000);
    connect(textTimer,SIGNAL(timeout()),this,SLOT(blinking()));
}



QString addDots (QString str = "", int dc = 1)
{
    for(int i = 1; i < dc+1; i++)  {str += '.';}
    return str;
}

QString qstr (int in)
{
    return to_string(in).c_str();
}



void MainWindow::resizeContainers()
{
    gv->setFixedWidth(width()*0.5);
    textHolder->setFixedWidth(width()*0.40);
}

void MainWindow::resizeAnimation()
{
    qreal hops =                                                         // hops : height of pendulum setup
            holder->rect().height() +
            rope->rect().height() +
            pendBulb->rect().height();

    hops *= cos(90-actionVar.maxAngle); // max angular displcement < 90 ,
                                                                                          // 90 from vertical axis

    qreal hws = gv->width()/2;                            // hws : halved width of scene
    qreal ns = hws/hops;                                        // ns : new scale

    gv->scale(1/gvar.gvls,1/gvar.gvls);         // undo the scale we did before
    gv->scale(ns,ns);                                               // do a new scale

    gvar.gvls = ns;                                                     // save new scale
}

void MainWindow::resizeEvent(QResizeEvent* )
{
    resizeContainers();
    resizeAnimation();
}



void MainWindow::moveBulb()
{
    if(-actionVar.maxAngle > actionVar.angle ||
          actionVar.angle > actionVar.maxAngle )
        actionVar.step*=-1;

    actionVar.angle+=actionVar.step;

    pendBulb->setRotation(actionVar.angle);
    rope->setRotation(actionVar.angle);
    holder->setRotation(actionVar.angle);
}

void MainWindow::blinking()
{
    textHolder->clear();

    gvar.timeElapse ++;
    gvar.dotCount ++;
    gvar.on = !gvar.on;
    if(gvar.dotCount>3) gvar.dotCount = 1;

    textHolder->addItems
    ({
            addDots("Loading ", gvar.dotCount),"",
            "Progress: " + QString((gvar.on)? "25%" : ""),"",
            "Time: " + qstr(gvar.timeElapse) + "s","",
            "Please wait" + QString((gvar.on)? "." : "")
     });
}





void MainWindow::mousePressEvent(QMouseEvent */*event*/)
{


}







