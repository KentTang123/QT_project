#ifndef SCENE_H
#define SCENE_H


#include "ground.h"
#include "tank.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QDebug>
#include <QElapsedTimer>
#include <QPushButton>
#include <QTimer>


class Scene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX CONSTANT FINAL)
public:
    explicit Scene(QObject *parent = nullptr);

    qreal x() const;
    void setX(qreal newX);
    Ground *getGround();
signals:
    void tankmoveLsig();
    void tankmoveRsig();
    void rotupsig();
    void rotdownRsig();
    void shootsig();
    void del();

public slots:
    void changeSceneLeft();
    void changeSceneRight();
    void setfire();
    void setvis();
    void setunvis();
    void checkcollide();
private:
    Ground* ground;
    QGraphicsPixmapItem* sky;
    QPropertyAnimation* changescene;
    Tank* tank;
    qreal scene_x;
    qreal m_x;
    QPushButton* button;
    QTimer* timer;
protected:
    void keyPressEvent(QKeyEvent *event) override;

    // QGraphicsScene interface
protected:
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
