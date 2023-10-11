#include "snakebody.h"
#include <QDebug>
SnakeBody::SnakeBody()

{
    this->setPixmap(QPixmap(":/image/body.png"));

    this->setTransformOriginPoint(21,21);

    screenScalor = QPointF(0,0);

    move = new QPropertyAnimation(this,"bodypos",this);
}

void SnakeBody::bodymove(QPointF start, QPointF end)
{
    move->stop();
    move->setStartValue(start);
    move->setEndValue(end);
    move->setDuration(100);
    move->setEasingCurve(QEasingCurve::Linear);
    move->start();
}

void SnakeBody::setscreenScalor(QPointF s)
{
    screenScalor = s;
}


QPointF SnakeBody::bodypos() const
{
    return m_bodypos;
}

void SnakeBody::setBodypos(QPointF newBodypos)
{

    this->setPos(m_bodypos);

    m_bodypos = newBodypos;
}
