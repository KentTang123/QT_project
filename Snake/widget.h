#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void resizesig();
    void scalorsig(QPointF s);
public slots:
    void viewresize();
    void restartgame(qreal score);
private:
    Ui::Widget *ui;
    Scene* scene;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_pushButton_clicked();
};
#endif // WIDGET_H
