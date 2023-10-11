#include "scene.h"
#include "snakebody.h"
#include <QKeyEvent>
#include <QRandomGenerator>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{
    scalor = QPointF(0,0);

    QPen background_p(Qt::black);
    QBrush background_b(Qt::black,Qt::SolidPattern);
    this->addRect(0,0,1536,793,background_p,background_b);

    snake = new Snake();
    this->addItem(snake);

    apple = new Apple();
    this->addItem(apple);

    timer = new QTimer();
    timer->start(100);

    connect(this,&Scene::changedir,snake,&Snake::Setheaddir);
    connect(timer,&QTimer::timeout,this,&Scene::Checkcollide);
    connect(this,&Scene::collided,this,&Scene::newApple);
    connect(this,&Scene::collided,snake,&Snake::createnewebody);
    connect(this,&Scene::changedir,snake,&Snake::resetsnakebodyPos);


}

Snake *Scene::Getsnake()
{
    return snake;
}

void Scene::Checkcollide()
{
    if(snake->Gethead()->collidesWithItem(apple)){
        emit collided();
    }
}

void Scene::newApple()
{
    delete apple;

    apple = new Apple();
    this->addItem(apple);
    bool isoccupied = true;
    int x;
    int y;
    do{
        x = QRandomGenerator::global()->bounded(750 + scalor.x());
        y = QRandomGenerator::global()->bounded(550 + scalor.y());

        for(int i =0;i < snake->GetsnakeBody().size();i++){
            SnakeBody*ref = snake->GetsnakeBody().at(i);
            if(QPointF(x , y) != ref->pos() && QPointF(x , y) != snake->Gethead()->pos()){
                isoccupied = false;
                break;
            }
        }
    }while(isoccupied);
    apple->setPos(x,y);
}

void Scene::setScalor(QPointF s)
{
    scalor = s;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W && snake->getHeaddir() != Down){

        emit changedir(0);

    }else if(event->key() == Qt::Key_A && snake->getHeaddir() != Right){

        emit changedir(2);
    }else if(event->key() == Qt::Key_S && snake->getHeaddir() != Up){

        emit changedir(1);
    }
    else if(event->key() == Qt::Key_D && snake->getHeaddir() != Left){

        emit changedir(3);
    }
}

