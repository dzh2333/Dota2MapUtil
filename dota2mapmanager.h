#ifndef DOTA2MAPMANAGER_H
#define DOTA2MAPMANAGER_H

#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QList>



class Dota2MapManager
{

public:
    Dota2MapManager(const Dota2MapManager&)=delete;
    Dota2MapManager& operator=(const Dota2MapManager&)=delete;

    static Dota2MapManager& getInstance(){
        static Dota2MapManager instance;
        return instance;
    }
    void init();
    void setCurrMap(int mapIndex);
    void setReplaceMap(int mapIndex);
    void setMapPatch(QString path);
    bool initFile();

    int saveOldFile();
    bool backToBackFileStatus();

    QString getMapNam(int index);
    int repaceIndex = -1;
    int currIndex = -1;
    QString  mapPath;

private:


    QList<QString> mapNameList;
    Dota2MapManager(){

    }
};

#endif // DOTA2MAPMANAGER_H
