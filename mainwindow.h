#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QListWidget>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct BulbAction
            // holds the variables for the pendulum bulb animation
    {
        qreal angle;
        qreal maxAngle;
        qreal step;

        BulbAction (qreal a = 0, qreal ma = 40, qreal s = 1)
            : angle(a), maxAngle(ma), step(s) {}
    }actionVar; // grants access to members of BulbAction to  be use by "this" object


    struct GVar
        // gvar : holds the global variables
        // temporal variables to be used by the functions of "this" object
    {
        long int timeElapse = 0;
        int dotCount = 1;
        qreal gvls = 1; // last graphics view scale set

        bool on = true; // on == true : means show text, false : hide text (for blinking text animation)
    }gvar; // grants access to members of GVar to  be use by "this" object


















public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setup ();
    void intialize ();
    void color ();
    void style ();
    void startAnimation ();
    void boxSetup ();
    void resizeContainers ();
    void resizeAnimation ();

public slots:
    void moveBulb ();
    void blinking ();


    //void moveBulb2 ();
protected:
    void resizeEvent(QResizeEvent *);



    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;

    QGraphicsView* gv;
    QGraphicsScene* scene;
    QGraphicsEllipseItem* holder;
    QGraphicsEllipseItem* nail;
    QGraphicsRectItem* rope;
    QGraphicsEllipseItem* pendBulb;

    QTimer* timer;
    QTimer* textTimer;

    QListWidget* textHolder;

    QWidget* box;
    QHBoxLayout* boxLayout;
};

#endif // MAINWINDOW_H
