#include "dota2mapmanager.h"

void Dota2MapManager::init(){
    qDebug()<<"Dota2MapManager->init";

    mapNameList = QList<QString>();
    mapNameList<<"dota_spring.vpk";
    mapNameList<<"dota_summer.vpk";
    mapNameList<<"dota_autumn.vpk";
    mapNameList<<"dota_winter.vpk";
    mapNameList<<"dota_ti10.vpk";
    mapNameList<<"dota_journey.vpk";
    mapNameList<<"dota_desert.vpk";
    mapNameList<<"dota_cavern.vpk";
    mapNameList<<"dota_coloseum.vpk";
    mapNameList<<"dota_desert.vpk";
    mapNameList<<"dota_reef.vpk";
}

void Dota2MapManager::setCurrMap(int mapIndex){
    this->currIndex = mapIndex;
}

void Dota2MapManager::setReplaceMap(int mapIndex){
    this->repaceIndex = mapIndex;
}

void Dota2MapManager::setMapPatch(QString path){
    this->mapPath = path;
}


bool Dota2MapManager::initFile(){
    if(this->mapPath.isEmpty()){
        return false;
    }

    return true;
}

QString Dota2MapManager::getMapNam(int index){
    return this->mapNameList.at(index);
}


int Dota2MapManager::saveOldFile(){
    if(this->mapPath.isEmpty()){
        return false;
    }
    QString savePath = QCoreApplication::applicationDirPath();
    qDebug()<<">>" + savePath;
    QString newFile = savePath + "/maps";
    QDir *folder = new QDir;
    bool exist  = folder->exists(newFile);
    if(exist){
        return 2;
    }else{
        bool ok = folder->mkpath(newFile);
    }

    //开始拷贝
    QDir pathFile = QDir(this->mapPath);
    QFileInfoList fileInfoList = pathFile.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
         QString newFilePath = newFile + "/" + fileInfo.fileName();

        if(fileInfo.fileName().endsWith(".vpk") && fileInfo.fileName().startsWith("dota_")){
            //为目标地图文件开始拷贝
            qDebug()<<"fileInfo name is " + fileInfo.fileName();
            QFile::copy(fileInfo.filePath(), newFilePath);
        }
    }
    return 1;
}

bool Dota2MapManager::backToBackFileStatus(){
    QString savePath = QCoreApplication::applicationDirPath();
    QString newFile = savePath + "/maps";
    QDir *folder = new QDir;
    bool exist  = folder->exists(newFile);
    if(!exist){
        return false;
    }

    for(int i = 0; i < mapNameList.size(); i++){
        //开始替换
        QString needBackFileName = Dota2MapManager::getInstance().getMapNam(i);
        //目标地图
        QString oldFilePath = Dota2MapManager::getInstance().mapPath + "/" + needBackFileName;
        QFile oldFile = QFile(oldFilePath);
        if(oldFile.exists()){
            oldFile.remove();
        }
        //保存过的地图
        QString savePath = QCoreApplication::applicationDirPath()+ "/maps/" + needBackFileName;
        bool copy = QFile::copy(savePath, oldFilePath);
        qDebug()<<"copy file " + savePath + "  to " + oldFilePath;
        if(!copy){
            return false;
        }
    }
    return true;
}
