#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QtMath>
#include <QDebug>

class Bullet : public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal btime READ btime WRITE setBtime CONSTANT FINAL)
    Q_PROPERTY(qreal bulletrot READ bulletrot WRITE setBulletrot CONSTANT FINAL)
public:
    explicit Bullet();
    qreal btime() const;
    void setBtime(qreal newBtime);

    void setElapsedTimer(qint64 t);
    QElapsedTimer t;


    qreal bulletrot() const;
    void setBulletrot(qreal newBulletrot);
signals:
private:
    QPropertyAnimation* bshoot;
    QPropertyAnimation* brotate;
};

#endif // BULLET_H
