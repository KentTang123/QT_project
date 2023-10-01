#include "pillar.h"
#include "bird.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>

Pillar::Pillar() :
    toppillar(new QGraphicsPixmapItem(QPixmap(":/image/pillar.png"))),
    botpillar(new QGraphicsPixmapItem(QPixmap(":/image/pillar.png")))
{
    toppillar->setScale(0.22);
    botpillar->setScale(0.22);
    toppillar->setRotation(-180);
    toppillar->setOffset(-220,400);
    addToGroup(toppillar);
    addToGroup(botpillar);

    xAnimation = new QPropertyAnimation(this,"x",this);

    yPos = QRandomGenerator::global()->bounded(7);


    xAnimation->setStartValue(510);
    xAnimation->setEndValue(-50);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1300);

    connect(xAnimation,&QPropertyAnimation::finished,this,&Pillar::deletepillar);


    xAnimation->start();
}

Pillar::~Pillar()
{
    qDebug()<<"delete";
}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::setX(qreal newX)
{
    m_x = newX;

    if(newX < 0 ){
        emit pass();
    }

    if(collide()){
        emit Collided();
    }
    setPos(QPointF(newX,yPos*20+180));
}
void Pillar::deletepillar()
{
    scene()->removeItem((this));
    delete this;
}

bool Pillar::collide()
{
    QList<QGraphicsItem*> collideitems = toppillar->collidingItems();
    collideitems.append(botpillar->collidingItems());

    foreach (QGraphicsItem* item, collideitems) {
        Bird* bird = dynamic_cast<Bird* >(item);
        if (bird){
            return true;
        }
    }
    return false;
}
