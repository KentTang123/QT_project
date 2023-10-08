#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "scene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

signals:
private:
    void defaultSetup();

    Scene * scene;

};

#endif // VIEW_H
