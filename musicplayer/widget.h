#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "playsong.h"
#include "songlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


enum LoopStatus{
    once,
    inf
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_playbutton_clicked();
    void SetcurrentTime(qint64 time);
    void on_horizontalSlider_actionTriggered(int action);
    void on_addSong_clicked();
    void Setlist();
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_nextbutton_clicked();

    void goNext();

    void upDate(QString s);

    void on_loopbutton_clicked();

private:
    Ui::Widget *ui;
    Playsong* player;
    Songlist* l;
    int counter;
    LoopStatus loop;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // WIDGET_H
