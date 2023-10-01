#ifndef PILLAR_H
#define PILLAR_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>


class Pillar : public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX CONSTANT FINAL)
public:
    explicit Pillar();
    ~ Pillar();

    qreal x() const;
    void setX(qreal newX);

signals:
    void Collided();
    void pass();
public slots:

    void deletepillar();

private:
    bool collide();
    QGraphicsPixmapItem* toppillar;
    QGraphicsPixmapItem* botpillar;
    qreal m_x;
    int yPos;
    QPropertyAnimation* xAnimation;
};

#endif // PILLAR_H
