#include "view.h"

View::View(QWidget *parent)
    : QGraphicsView{parent}
{
    defaultSetup();
}

void View::defaultSetup()
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene = new Scene();
    this->setScene(scene);
    this->setFixedSize(1200,scene->sceneRect().height()+2);
}
