#include "scene.h"
#include <QKeyEvent>


Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{
    sky = new QGraphicsPixmapItem(QPixmap(":/image/sky.png"));
    sky->setPos(0,0);
    this->addItem(sky);

    scene_x = 0;
    this->setSceneRect(scene_x,0,1200,600);

    ground = new Ground();
    this->addItem(ground);

    tank = new Tank();
    this->addItem(tank);

    button = new QPushButton();
    this->addWidget(button);

    button->setGeometry(this->sceneRect().x()+this->sceneRect().width()/2-50,this->sceneRect().y()+this->sceneRect().height()/2+150,100,50);
    button->setFlat(true);
    button->setText("Reload");
    button->setStyleSheet("background-color: rgba(140,167,66,100)");

    timer = new QTimer();
    changescene = new QPropertyAnimation(this,"x",this);

    connect(this,&Scene::tankmoveLsig,tank,&Tank::moveLeft);
    connect(this,&Scene::tankmoveRsig,tank,&Tank::moveRight);
    connect(this,&Scene::rotupsig,tank,&Tank::rotup);
    connect(this,&Scene::rotdownRsig,tank,&Tank::rotdown);
    connect(button,&QPushButton::clicked,this,&Scene::setfire);
    connect(tank,&Tank::reload,this,&Scene::setvis);
    connect(button,&QPushButton::released,this,&Scene::setunvis);
    connect(this,&Scene::del,tank,&Tank::deletebullet);
    connect(timer,&QTimer::timeout,this,&Scene::checkcollide);

}

qreal Scene::x() const
{
    return m_x;
}

void Scene::setX(qreal newX)
{

    if(newX < 0 ){
        changescene->stop();
    }
    else if(newX > 800){
        changescene->stop();
    }
    else{
        this->setSceneRect(scene_x,0,1200,600);
         button->setGeometry(this->sceneRect().x()+this->sceneRect().width()/2-50,this->sceneRect().y()+this->sceneRect().height()/2+150,100,50);
        m_x= newX;
    }
}

Ground *Scene::getGround()
{
    return ground;
}

void Scene::changeSceneLeft()
{
    changescene->stop();
    changescene->setDuration(10);
    changescene->setStartValue(scene_x);
    changescene->setEndValue(scene_x-25);
    changescene->setEasingCurve(QEasingCurve::Linear);
    changescene->start();
    scene_x = scene_x - 25;
    if(scene_x < 0){
        scene_x = 0;
    }
}

void Scene::changeSceneRight()
{
    changescene->stop();
    changescene->setDuration(10);
    changescene->setStartValue(scene_x);
    changescene->setEndValue(scene_x + 25);
    changescene->setEasingCurve(QEasingCurve::Linear);
    changescene->start();
    scene_x = scene_x + 25;
    if(scene_x > 800){
        scene_x = 800;
    }
}

void Scene::setfire()
{
    connect(this,&Scene::shootsig,tank,&Tank::shoot);
}

void Scene::setvis()
{
    timer->stop();
    button->setVisible(true);
}

void Scene::setunvis()
{
    button->setVisible(false);
}

void Scene::checkcollide()
{
    if(ground->collidesWithItem(tank->getBullet())){
        emit del();
    }
}



void Scene::keyPressEvent(QKeyEvent *event)
{
    changescene->stop();
    if(event->key() == Qt::Key_Left){
        //scene go left
        changeSceneLeft();

    }else if(event->key() == Qt::Key_Right){
        //scene go right
        changeSceneRight();
    }else if(event->key() == Qt::Key_A){
        //tank move left
        emit tankmoveLsig();
    }else if(event->key() == Qt::Key_D){
        //tank move right
        emit tankmoveRsig();
    }else if(event->key() == Qt::Key_W){
        //barrel rot up
        emit rotupsig();
    }else if(event->key() == Qt::Key_S){
        //barrel rot down
        emit rotdownRsig();
    }
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    tank->t.start();
    if(event->key() == Qt::Key_Space){
        timer->start(40);
        emit shootsig();
        disconnect(this,&Scene::shootsig,tank,&Tank::shoot);

    }
}

