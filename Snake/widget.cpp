#include "widget.h"
#include "./ui_widget.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new Scene();

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setSceneRect(0,0,800,600);

    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

    connect(this,&Widget::resizesig,this,&Widget::viewresize);
    connect(this,&Widget::scalorsig,scene->Getsnake(),&Snake::setscreenScalor);
    connect(this,&Widget::scalorsig,scene,&Scene::setScalor);
    connect(scene->Getsnake(),&Snake::endgame,this,&Widget::restartgame);

    ui->pushButton->setEnabled(false);
    ui->pushButton->setVisible(false);
    ui->textEdit->setTextColor(Qt::white);
    ui->textEdit->setFontItalic(true);
    ui->textEdit->setFont(QFont("Times",22,QFont::Bold));
    ui->textEdit->setVisible(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::viewresize()
{
    ui->graphicsView->resize(this->width(),this->height());

    emit scalorsig(QPointF(this->width()-800,this->height()-600));
}

void Widget::restartgame(qreal score)
{
    ui->pushButton->setEnabled(true);
    ui->pushButton->setVisible(true);

    QString str = "Score : ";
    str.append(QString::number(score));
    ui->textEdit->setText(str);
    ui->textEdit->setAlignment(Qt::AlignHCenter);
    ui->textEdit->setVisible(true);
}

void Widget::resizeEvent(QResizeEvent *event)
{
    ui->pushButton->setGeometry(0.5 * this->width() - 60,450,120,40);
    ui->textEdit->setGeometry(0.5 * this->width() - 100,250,200,120);
    emit resizesig();
}


void Widget::on_pushButton_clicked()
{
    scene = new Scene();

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setSceneRect(0,0,800,600);

    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

    connect(this,&Widget::resizesig,this,&Widget::viewresize);
    connect(this,&Widget::scalorsig,scene->Getsnake(),&Snake::setscreenScalor);
    connect(this,&Widget::scalorsig,scene,&Scene::setScalor);
    connect(scene->Getsnake(),&Snake::endgame,this,&Widget::restartgame);


    ui->pushButton->setEnabled(false);
    ui->pushButton->setVisible(false);
    ui->textEdit->setVisible(false);
}

