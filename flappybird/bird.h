#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>

class Bird : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal Rotate READ Rotate WRITE setRotate CONSTANT FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY CONSTANT FINAL)

public:
    explicit Bird();

    qreal y() const;
    void setY(qreal newY);

    qreal Rotate() const;
    void setRotate(qreal newRotate);

    void Up();
    void startFly();
    void stop();

public slots:
    void fall();

signals:

private:

    qreal m_y;
    qreal m_Rotate;
    qreal groundPos;
    QPropertyAnimation* yAnimation;
    QPropertyAnimation* rotationAnimation;
};

#endif // BIRD_H
