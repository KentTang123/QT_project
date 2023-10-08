#ifndef TANK_H
#define TANK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QtMath>
#include <QDebug>
#include <QElapsedTimer>





class Tank : public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF tankpos READ tankpos WRITE setTankpos CONSTANT FINAL)
    Q_PROPERTY(qreal rot READ rot WRITE setRot CONSTANT FINAL)
    Q_PROPERTY(qreal btime READ btime WRITE setBtime CONSTANT FINAL)
    Q_PROPERTY(qreal bulletrot READ bulletrot WRITE setBulletrot CONSTANT FINAL)

public:
    explicit Tank();

    QPointF tankpos() const;
    void setTankpos(QPointF newTankpos);

    qreal rot() const;
    void setRot(qreal newRot);

    qreal btime() const;
    void setBtime(qreal newBtime);

    void setElapsedTimer(qint64 t);
    QElapsedTimer t;


    qreal bulletrot() const;
    void setBulletrot(qreal newBulletrot);

    QGraphicsPixmapItem* getBullet();
signals:
    void reload();
public slots:
    void moveLeft();
    void moveRight();
    void rotup();
    void rotdown();
    void shoot();
    void deletebullet();
private:
    QPropertyAnimation* move;
    QPropertyAnimation* bRot;
    QPropertyAnimation* bshoot;
    QPropertyAnimation* brotate;
    QPointF m_tankpos;
    QPointF bpos;
    QGraphicsPixmapItem* tankbody;
    QGraphicsPixmapItem* barrel;
    QGraphicsPixmapItem* bullet;
    QGraphicsPixmapItem* smoke;

    qint64 elapsetime;
    qreal barrelrot;
    qreal m_rot;
    qreal m_btime;
    qreal m_bulletrot;
};

#endif // TANK_H
