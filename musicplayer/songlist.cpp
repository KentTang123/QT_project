#include "songlist.h"
#include <QDebug>
Songlist::Songlist()
{
    filename = "songlist.txt";

    file.open(filename,ios::app|ios::out);

    file.close();
}

void Songlist::Setlist(QStringList l)
{
    newlist = l;

    QString text;
    bool existed = false;

    for(int i = 0 ;i < newlist.size() ;i++){
        text = newlist.at(i);
        string temp;

        file.open(filename,ios::in);

        while(getline(file,temp)){
            if(temp == text.toStdString()){
                existed = true;
                break;
            }
        }
        file.close();

        if(!existed){
            file.open(filename,ios::app|ios::out);
            file<<text.toStdString()<<endl;
            file.close();
        }

        existed = false;
    }
    emit Setlistsig();

}

QStringList Songlist::getlist()
{
    file.open(filename,ios::in);

    Wholelist.clear();
    Wholelist.squeeze();

    string temps;
    QString tempQS;

    while(getline(file,temps)){
        tempQS = QString::fromStdString(temps);
        Wholelist.push_back(tempQS);
    }
    file.close();
    return Wholelist;
}

void Songlist::updateList(QString s)
{
    fstream temp;
    string tempstr;

    temp.open("temp.txt",ios::out);

    file.open(filename,ios::in);

    while(getline(file,tempstr)){
        if(tempstr != s.toStdString()){
            temp<<tempstr<<endl;
        }
    }

    temp.close();
    file.close();

    file.open(filename,ios::out);
    temp.open("temp.txt",ios::in);

    while(getline(temp,tempstr)){
        file<<tempstr<<endl;
    }

    temp.close();
    file.close();
}
