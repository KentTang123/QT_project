#ifndef SONGLIST_H
#define SONGLIST_H

#include <QWidget>
#include <QStringList>
#include <fstream>
#include <string>

using namespace std;

class Songlist : public QWidget
{
    Q_OBJECT
public:
    explicit Songlist();
    void Setlist(QStringList l);
    QStringList getlist();
public slots:
    void updateList(QString s);
signals:
    void addSongsig(QStringList l);
    void Setlistsig();
private:
    fstream file;
    QStringList newlist;
    QStringList Wholelist;
    string filename;
};

#endif // SONGLIST_H
