#ifndef PLAYSONG_H
#define PLAYSONG_H

#include <QObject>
#include <QtMultimedia>

class Playsong :public QObject
{
    Q_OBJECT
public:
    explicit Playsong();

signals:
    void currentTime(qint64 time);
    void finishSig();
    void updatelistsig(QString s);
public slots:
    void play();
    void pause();
    void restart();
    bool isplaying();
    void SetSong(QString s);
    void setVolume(int value);
    void calTime(qint64 x);
    void changePos(float f);
    qint64 getSonglengh();
    QString songName();
private:
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    QUrl url;
};

#endif // PLAYSONG_H
