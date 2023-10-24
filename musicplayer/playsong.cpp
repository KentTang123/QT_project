#include "playsong.h"
#include <QDebug>

Playsong::Playsong()

{

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;

    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(1);

    connect(player,&QMediaPlayer::positionChanged,this,&Playsong::calTime);

}


void Playsong::play()
{
    player->play();
}

void Playsong::pause()
{
    player->pause();
}

void Playsong::restart()
{
    player->stop();
    player->play();
}

bool Playsong::isplaying()
{
    return player->isPlaying();
}

void Playsong::SetSong(QString s)
{
    player->stop();
    url = QUrl::fromLocalFile(s);

    player->setSource(url);
    player->setObjectName(s);

    if(!player->isSeekable()){
        emit updatelistsig(s);
    }

}

void Playsong::setVolume(int value)
{
    float v = value / 100.00;
    audioOutput->setVolume(v);
}

void Playsong::calTime(qint64 pos)
{
    if(pos == player->duration()){
        emit finishSig();
    }
    emit currentTime(pos);
}

void Playsong::changePos(float f)
{
    player->setPosition(player->duration() * f);
}

qint64 Playsong::getSonglengh()
{
    return player->duration();
}

QString Playsong::songName()
{
    QString name ;
    QString temp;

    int h = player->objectName().lastIndexOf("/");
    int t = player->objectName().lastIndexOf(".");

    temp = player->objectName().remove(0,h+1);
    temp = temp.remove(t - h -1, player->objectName().size() - h -1);

    name = temp;
    return name;
}
