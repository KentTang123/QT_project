#include "bird.h"

Bird::Bird()
{
    this->setPixmap(QPixmap(":/image/bird.png"));
    this->setScale(0.08);

    groundPos = 360;


    yAnimation = new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPos);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);



    rotationAnimation = new QPropertyAnimation(this,"Rotate",this);
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(30);
    rotationAnimation->setEasingCurve(QEasingCurve::InQuad);
    rotationAnimation->setDuration(1000);



}

qreal Bird::y() const
{
    return m_y;
}

void Bird::setY(qreal newY)
{
    moveBy(0,newY- m_y);
    m_y = newY;
}


qreal Bird::Rotate() const
{
    return m_Rotate;
}

void Bird::setRotate(qreal newRotate)
{
    this->setRotation(m_Rotate);

    m_Rotate = newRotate;
}

void Bird::Up()
{
    yAnimation->stop();
    rotationAnimation->stop();

    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(scenePos().y()-50);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(120);
    yAnimation->start();

    connect(yAnimation,&QPropertyAnimation::finished,this,&Bird::fall);

    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(-30);
    rotationAnimation->setEasingCurve(QEasingCurve::OutCubic);
    rotationAnimation->setDuration(100);

    rotationAnimation->start();
}

void Bird::startFly()
{
    yAnimation->start();
    rotationAnimation->start();
}

void Bird::stop()
{
    this->yAnimation->stop();
    this->rotationAnimation->stop();
}

void Bird::fall()
{
    if(this->y()<groundPos){
        rotationAnimation->stop();


        yAnimation->setStartValue(scenePos().y());
        yAnimation->setEndValue(groundPos);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(1000);



        yAnimation->start();


        rotationAnimation->setStartValue(rotation());
        rotationAnimation->setEndValue(30);
        rotationAnimation->setEasingCurve(QEasingCurve::InQuad);
        rotationAnimation->setDuration(1000);

        rotationAnimation->start();
    }
}
