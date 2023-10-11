#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "snake.h"
#include "apple.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    Snake *Getsnake();
public slots:
    void Checkcollide();
    void newApple();
    void setScalor(QPointF s);
signals:
    void changedir(int index);
    void collided();
private:
    QPointF applePos;
    QPointF scalor;
    Snake* snake;
    Apple* apple;
    QTimer* timer;
    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
