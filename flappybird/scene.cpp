#include "scene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <iostream>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent} ,score(0)
{
    this->setSceneRect(0,60,500,300);
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap(":/image/background.png"));

    SetlpillarTimer();

    background->setScale(0.8);
    this->addItem(background);

    addBird();


    start= new QPushButton();
    this->addWidget(start);
    start->setGeometry(200,250,100,50);
    start->setFlat(true);
    start->setText("Click to Start");
    connect(start,&QPushButton::clicked,this,&Scene::startgame);


    text = new QGraphicsTextItem();
    str = "<p> Score :  " + QString::number(score) + "<p>";
    text->setHtml(str);
    text->setDefaultTextColor(Qt::black);
    this->addItem(text);
    text->setPos(10,70);
}

void Scene::createNewpillar()
{
    pillar=new Pillar();
    connect(pillar,&Pillar::Collided,this,&Scene::endgame);

    connect(pillar,&Pillar::pass,this,&Scene::scoreIncrease);

    this->addItem(pillar);

}

void Scene::addBird()
{
    bird = new Bird;
    this->addItem(bird);
}

void Scene::startgame()
{
    score = 0;
    str = "<p> Score :  " + QString::number(score) + "<p>";
    text->setHtml(str);

    bird->startFly();

    if(!Pillartimer->isActive())
        Pillartimer->start(1500);

    start->setVisible(0);

}

void Scene::endgame()
{
    Pillartimer->stop();

    bird->stop();

    start->setVisible(1);
    start->setText("Try again !!!");
}


void Scene::scoreIncrease()
{
    if(!start->isVisible())
        score++;

    str = "<p> Score :  " + QString::number(score) + "<p>";
    text->setHtml(str);

    disconnect(pillar,&Pillar::pass,this,&Scene::scoreIncrease);
}

void Scene::SetlpillarTimer()
{
    Pillartimer = new QTimer(this);
    connect(Pillartimer,&QTimer::timeout,this,&Scene::createNewpillar);

}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space && !start->isVisible()){
        bird->Up();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !start->isVisible()){
        bird->Up();
    }
    QGraphicsScene::mousePressEvent(event);
}
