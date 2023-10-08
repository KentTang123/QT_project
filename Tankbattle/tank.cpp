#include "tank.h"
#include <QDebug>
#include <QKeyEvent>
Tank::Tank()

{

    tankbody = new QGraphicsPixmapItem(QPixmap(":/image/tank1.png"));
    barrel= new QGraphicsPixmapItem(QPixmap(":/image/barrel.png"));

    barrel->setTransformOriginPoint(93,61);
    barrel->setOffset(50,0);

    this->addToGroup(tankbody);
    this->addToGroup(barrel);
    this->setPos(0,242);
    this->setScale(0.9);


    move = new QPropertyAnimation(this,"tankpos",this);
    bRot = new QPropertyAnimation(this,"rot",this);
    bshoot = new QPropertyAnimation(this,"btime",this);
    brotate = new QPropertyAnimation(this,"bulletrot",this);

    qDebug()<<this->sceneBoundingRect();
    qDebug()<<this->transformOriginPoint();

}


QPointF Tank::tankpos() const
{
    return m_tankpos;
}

void Tank::setTankpos(QPointF newTankpos)
{
    if(newTankpos.x() < 0 || newTankpos.x() > 1900){
        move->stop();
    }else{
        this->setPos(m_tankpos);
        m_tankpos = newTankpos;
    }
}

void Tank::moveLeft()
{
    move->stop();
    move->setDuration(50);
    move->setStartValue(this->pos());
    move->setEndValue(this->pos() - QPointF(10,0));
    move->setEasingCurve(QEasingCurve::Linear);
    move->start();
}

void Tank::moveRight()
{
    move->stop();
    move->setDuration(50);
    move->setStartValue(this->pos());
    move->setEndValue(this->pos() + QPointF(10,00));
    move->setEasingCurve(QEasingCurve::Linear);
    move->start();
}

qreal Tank::rot() const
{
    return m_rot;
}

void Tank::setRot(qreal newRot)
{
    if(newRot < -90 ){
        bRot->stop();
    }else if(newRot > 0){
        bRot->stop();
    }else {
        barrel->setRotation(m_rot);
        m_rot = newRot;
    }
}


void Tank::rotup()
{
    bRot->stop();
    bRot->setDuration(70);
    bRot->setStartValue(barrel->rotation());
    bRot->setEndValue(barrel->rotation()-5);
    bRot->setEasingCurve(QEasingCurve::Linear);
    bRot->start();

}

void Tank::rotdown()
{
    bRot->stop();
    bRot->setDuration(70);
    bRot->setStartValue(barrel->rotation());
    bRot->setEndValue(barrel->rotation() + 5);
    bRot->setEasingCurve(QEasingCurve::Linear);
    bRot->start();
}

qreal Tank::btime() const
{
    return m_btime;
}

void Tank::setBtime(qreal newBtime)
{
    qreal v = 100;
    qreal angle = qDegreesToRadians(- (this->rotation()) - barrel->rotation());
    qreal vy = v * qSin(angle);
    qreal vx = v * qCos(angle);
    bullet->setPos(bpos + QPointF(vx * m_btime, - vy * m_btime + 5 * qPow(m_btime,2)));
    m_btime = newBtime;
    if(m_btime == 30){
        delete bullet;
        qDebug()<<"deleted";
        emit reload();
    }
}

void Tank::setElapsedTimer(qint64 t)
{
    elapsetime = t;
}


void Tank::shoot()
{
    setElapsedTimer(this->t.elapsed());

    bullet = new QGraphicsPixmapItem(QPixmap(":/image/bullet.png"));
    bullet->setTransformOriginPoint(95,55);
    bullet->setOffset(85,45);
    bpos = bullet->pos();
    this->addToGroup(bullet);
    bshoot->stop();
    bshoot->setStartValue(0);
    bshoot->setEndValue(30);
    bshoot->setDuration(5000);
    bshoot->setEasingCurve(QEasingCurve::Linear);
    bshoot->start();

    brotate->stop();
    brotate->setStartValue((this->rotation() + barrel->rotation()));
    brotate->setEndValue(-1 * (this->rotation()+barrel->rotation()));
    brotate->setDuration(5000);
    brotate->setEasingCurve(QEasingCurve::OutQuad);
    brotate->start();

    qDebug()<<this->childItems();
}

void Tank::deletebullet()
{

    delete bullet;

    bshoot->stop();
    brotate->stop();

    emit reload();

}


qreal Tank::bulletrot() const
{
    return m_bulletrot;
}

void Tank::setBulletrot(qreal newBulletrot)
{
    bullet->setRotation(m_bulletrot);
    m_bulletrot = newBulletrot;
}

QGraphicsPixmapItem *Tank::getBullet()
{
    return bullet;
}

