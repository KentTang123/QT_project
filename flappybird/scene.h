#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <Qtimer>
#include "pillar.h"
#include "bird.h"
#include <QPushButton>
#include <QGraphicsTextItem>
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

public slots:
    void createNewpillar();
    void addBird();
    void startgame();
    void endgame();
    void scoreIncrease();

signals:
private:
    void SetlpillarTimer();
    QTimer* Pillartimer;
    Bird* bird;
    Pillar* pillar;
    QPushButton* start;
    QGraphicsTextItem* text;
    QString str;
    int score ;
    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCENE_H
