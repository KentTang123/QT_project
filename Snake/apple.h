#ifndef APPLE_H
#define APPLE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Apple : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Apple();

signals:
public slots:

};

#endif // APPLE_H
