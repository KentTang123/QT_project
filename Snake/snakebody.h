#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class SnakeBody : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF bodypos READ bodypos WRITE setBodypos CONSTANT FINAL)

public:
    explicit SnakeBody();

    QPointF bodypos() const;
    void setBodypos(QPointF newBodypos);

signals:


public slots:
    void bodymove(QPointF start,QPointF end);
    void setscreenScalor(QPointF s);
private:
    QPropertyAnimation* move;
    QPointF screenScalor;
    QPointF m_bodypos;
};

#endif // SNAKEBODY_H
