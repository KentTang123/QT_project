#include "view.h"
#include "bird.h"
#include "scene.h"
#include "pillar.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


View::View(QWidget *parent)
    : QGraphicsView{parent}
{

    Scene* scene = new Scene(this);



    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSceneRect(0,60,500,300);
    this->setFixedSize(500,300);
    this->setScene(scene);

}

