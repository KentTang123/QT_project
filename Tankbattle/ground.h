#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Ground : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ground();

signals:

};

#endif // GROUND_H
