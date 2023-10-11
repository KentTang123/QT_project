#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QList>
#include "snakebody.h"

enum Headdir{
    Up,
    Down,
    Left,
    Right,
};

class Snake : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF Headpos READ Headpos WRITE setHeadpos NOTIFY HeadposChanged FINAL)
public:
    explicit Snake();

    QPointF Headpos() const;
    void setHeadpos(QPointF newHeadpos);

    QGraphicsPixmapItem* Gethead();
    void moving();

    Headdir getHeaddir();
    QList<SnakeBody*> GetsnakeBody();

    void checkcollide();

signals:
    void HeadposChanged();
    void endgame(qreal score);

public slots:
    void Setheaddir(int index);
    void setscreenScalor(QPointF s);
    void createnewebody();
    void resetsnakebodyPos();

private:
    SnakeBody* head;
    QPropertyAnimation* headmove;
    QTimer* timer;
    Headdir headdir;
    qreal headrot;
    QPointF dir;
    QPointF m_Headpos;
    QPointF screenScalor;
    QList<SnakeBody*> snakeBody;
    QList<QPointF> snakebodyPos; // target
};

#endif // SNAKE_H
