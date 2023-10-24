#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QCursor>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1400,750);

    player = new Playsong;
    l = new Songlist;

    counter = 0;
    loop = once;

    ui->playbutton->setIcon(QIcon(QPixmap(":/pic/playbutton.png")));
    ui->restartbutton->setIcon(QPixmap(":/pic/restartbutton.png"));
    ui->nextbutton->setIcon(QPixmap(":/pic/nextbutton.png"));
    ui->loopbutton->setIcon(QPixmap(":/pic/looponce.png"));
    ui->progressBar->setStyleSheet(" QProgressBar::chunk {background-color: #05B8CC;width: 1px;}");
    ui->label->setText("");
    ui->currentTime->setText("00:00");
    ui->duration->setText("00:00");

    this->Setlist();

    connect(ui->restartbutton,&QPushButton::clicked,player,&Playsong::restart);
    connect(ui->horizontalSlider,&QSlider::valueChanged,player,&Playsong::setVolume);
    connect(player,&Playsong::currentTime,this,&Widget::SetcurrentTime);
    connect(l,&Songlist::Setlistsig,this,&Widget::Setlist);
    connect(player,&Playsong::finishSig,this,&Widget::goNext);
    connect(player,&Playsong::updatelistsig,this,&Widget::upDate);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_playbutton_clicked()
{
    if(ui->comboBox->currentText() != ""){
        if(!player->isplaying()){

            ui->playbutton->setIcon(QIcon(QPixmap(":/pic/pausebutton.png")));
            player->play();

        }else{

            ui->playbutton->setIcon(QIcon(QPixmap(":/pic/playbutton.png")));
            player->pause();
        }
    }
}


void Widget::SetcurrentTime(qint64 time)
{
    int min = (time/1000) / 60;
    int sec = (time/1000) % 60;

    QString t = QString::number(min).rightJustified(2,'0') + ":" + QString::number(sec).rightJustified(2,'0');
    ui->currentTime->setText(t);

    int s = time * 1.0 / player->getSonglengh() * 1000;

    ui->progressBar->setValue(s);
}


void Widget::on_horizontalSlider_actionTriggered(int action)
{

    if(action == 3 ||action == 4){
        int p = QCursor::pos().x() - (this->pos().x() + 80);
        p = p / 200.00 *100.00;

        ui->horizontalSlider->setSliderPosition(p);
    }
}

void Widget::on_addSong_clicked()
{
    player->pause();
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Music (*.mp3 *.wav )"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    l->Setlist(fileNames);
}

void Widget::Setlist()
{
    ui->comboBox->clear();

    for(int i = 0;i < l->getlist().size();i++){
        if(l->getlist().at(i).size() != 0){
            ui->comboBox->addItem(l->getlist().at(i));
        }
    }

}

void Widget::on_comboBox_currentTextChanged(const QString &arg1)
{

    ui->playbutton->setIcon(QIcon(QPixmap(":/pic/playbutton.png")));

    player->SetSong(arg1);

    QString t = QString::number((player->getSonglengh() / 1000) / 60).rightJustified(2,'0') + ":" + QString::number((player->getSonglengh() / 1000) % 60).rightJustified(2,'0');
    ui->duration->setText(t);
    ui->label->setText(player->songName());

    if(counter == 0 ){
        ui->playbutton->setIcon(QIcon(QPixmap(":/pic/playbutton.png")));
        player->pause();
        counter++;
    }
}


void Widget::on_nextbutton_clicked()
{
    this->goNext();
}

void Widget::goNext()
{

    if(loop == once){
        int t = (ui->comboBox->currentIndex() + 1) < ui->comboBox->count() ?  ui->comboBox->currentIndex() + 1 : 0 ;
        ui->comboBox->setCurrentIndex(t);

        player->SetSong(ui->comboBox->currentText());

        ui->playbutton->setIcon(QIcon(QPixmap(":/pic/pausebutton.png")));

        player->play();
    }else if(loop == inf){
        player->changePos(0.0);
        player->play();
    }
}

void Widget::upDate(QString s)
{
    if(ui->comboBox->count() != 0){
        l->updateList(s);
        Setlist();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        QPointF p = QCursor::pos() - (this->pos() + QPointF(100,600));

        if(p.x() >= 0 && p.y() <= 1200 && p.y() >=0 && p.y() <= 62){
            player->changePos(p.x() / 1200);
        }
    }
}

void Widget::on_loopbutton_clicked()
{
    if(loop == once){
        loop = inf;
        ui->loopbutton->setIcon(QPixmap(":/pic/loop.png"));
    }else if(loop == inf){
        loop = once;
        ui->loopbutton->setIcon(QPixmap(":/pic/looponce.png"));
    }
}

