#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);


signals:
    void Space_clicked();

};

#endif // VIEW_H
