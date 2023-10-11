#include "snake.h"
#include <QDebug>
#include <QtMath>
Snake::Snake()
{
    screenScalor = QPointF(0,0);

    head = new SnakeBody();
    head->setPixmap(QPixmap(":/image/head.png"));
    head->setTransformOriginPoint(21,21);
    head->setPos(400,300);
    this->addToGroup(head);

    headmove = new QPropertyAnimation(this,"Headpos",this);

    headdir = Right;

    connect(headmove,&QPropertyAnimation::finished,this,&Snake::moving);
    connect(headmove,&QPropertyAnimation::finished,this,&Snake::resetsnakebodyPos);

    SnakeBody* Body1 = new SnakeBody();
    Body1->setTransformOriginPoint(21,21);
    Body1->setPos(380,300);
    snakeBody.push_back(Body1);
    snakebodyPos.push_back(head->pos());


    SnakeBody* Body2 = new SnakeBody();
    Body2->setTransformOriginPoint(21,21);
    Body2->setPos(360,300);
    snakeBody.push_back(Body2);
    snakebodyPos.push_back(Body1->pos());


    this->addToGroup(snakeBody.at(0));
    this->addToGroup(snakeBody.at(1));
    this->moving();


}

QPointF Snake::Headpos() const
{
    return m_Headpos;
}

void Snake::setHeadpos(QPointF newHeadpos)
{
    if (m_Headpos == newHeadpos)
        return;

    head->setRotation(headrot);

    if(m_Headpos.y() < -40){
        headmove->stop();
        emit endgame(snakeBody.size());
    }
       // head->setPos(m_Headpos.x(),600 + screenScalor.y());

    else if(m_Headpos.y() > 600 + screenScalor.y()){
        headmove->stop();
        emit endgame(snakeBody.size());
    }
       //head->setPos(m_Headpos.x(),0);

    else if(m_Headpos.x() < -40){
        headmove->stop();
        emit endgame(snakeBody.size());
    }
       // head->setPos(800 + screenScalor.x(),m_Headpos.y());

    else if(m_Headpos.x() > 800 + screenScalor.x()){
        headmove->stop();
        emit endgame(snakeBody.size());
    }
       // head->setPos(0,m_Headpos.y());
    else
        head->setPos(m_Headpos);

    checkcollide();

    m_Headpos = newHeadpos;

    emit HeadposChanged();
}


QGraphicsPixmapItem *Snake::Gethead()
{
    return head;
}

Headdir Snake::getHeaddir()
{
    return headdir;
}

QList<SnakeBody *> Snake::GetsnakeBody()
{
    return snakeBody;
}

void Snake::checkcollide()
{
    if( (snakeBody.size() > 3)){
        qDebug()<<"13";
        for(int i =3; i < snakeBody.size() ; i++){

            SnakeBody* ref = snakeBody.at(i);
            if(head->collidesWithItem(ref)){
                headmove->stop();
                qDebug()<<"collided";
                emit endgame(snakeBody.size());
            }
        }
    }
}


void Snake::resetsnakebodyPos()
{
    snakebodyPos.clear();

    snakebodyPos.push_back(head->pos());

    for(int i = 1 ; i < snakeBody.size();i++){
        SnakeBody* ref = snakeBody.at(i-1);
        snakebodyPos.push_back(ref->pos());
    }

}

void Snake::moving()
{
    switch (headdir) {
    case Up:
        dir = QPointF(0,-1);
        headrot = -90;
        break;

    case Down:
        dir = QPointF(0,1);
        headrot = 90;
        break;

    case Left:
        dir = QPointF(-1,0);
        headrot = 180;
        break;

    case Right:
        dir = QPointF(1,0);
        headrot = 0;
        break;
    }

    headmove->stop();
    headmove->setDuration(100);
    headmove->setStartValue(head->pos());
    headmove->setEndValue(head->pos()+ 20 * dir );
    headmove->setEasingCurve(QEasingCurve::Linear);

    SnakeBody* r;
    QPointF t ;
    for(int i = 0;i<snakeBody.size();i++){
        r = snakeBody.at(i);
        t = snakebodyPos.at(i);
        r->bodymove(r->pos(),t);
    }

    headmove->start();
}

void Snake::Setheaddir(int index)
{

    switch (index) {
    case 0:
        headdir = Up;
        break;

    case 1:
        headdir = Down;
        break;

    case 2:
        headdir = Left;
        break;

    case 3:
        headdir = Right;
        break;
    }

}

void Snake::setscreenScalor(QPointF s)
{
    screenScalor = s;
    for(int i = 0;i < snakeBody.size();i++){
        SnakeBody* ref = snakeBody.at(i);
        ref->setscreenScalor(s);
    }
}

void Snake::createnewebody()
{
    SnakeBody* ref = snakeBody.at(snakeBody.size()-1);
    SnakeBody* ref2 = snakeBody.at(snakeBody.size()-2);

    SnakeBody* newBody = new SnakeBody();
    newBody->setTransformOriginPoint(21,21);
    newBody->setPos(ref->pos() - (ref2->pos() - ref->pos()));
    snakeBody.push_back(newBody);
    snakebodyPos.push_back(newBody->pos());

    this->addToGroup(snakeBody.at(snakeBody.size()-1));
}
