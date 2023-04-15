#include <QFile>
#include <QDebug>
#include "objloader_easy.h"

bool ObjLoader_easy::load(QString fileName, QVector<float> &vPoints,QVector<float> &vnPoints)
{
    if(fileName.mid(fileName.lastIndexOf('.')) != ".obj"){
        qDebug() << "file is not a obj file";
        return false;
    }

    QFile objFile(fileName);
    if(!objFile.open(QIODevice::ReadOnly)){
        qDebug() << "open" << fileName << "failed";
        return false;
    }
    QVector<float> vertextPoints;
    QVector<float> normalPoints;
    QVector<std::pair<int,int>> facesIndexs;
    while (!objFile.atEnd())
    {
        QByteArray lineData = objFile.readLine();
        lineData = lineData.remove(lineData.count() -1,1);  //to delete "\r\n"
        QList<QByteArray> strValues = lineData.split(' ');
        QString dataType = strValues.takeFirst();
        if(dataType == "v"){
            std::transform(strValues.begin(),strValues.end(),std::back_inserter(vertextPoints),[](QByteArray &str){
                           return str.toFloat();       //input x,y,z values
                           });             
        }else if(dataType == "vn"){
                std::transform(strValues.begin(),strValues.end(),std::back_inserter(normalPoints),[](QByteArray &str){
                               return str.toFloat();       //input x,y,z values
                               });          
        }else if(dataType == "f"){
            std::transform(strValues.begin(),strValues.end(),std::back_inserter(facesIndexs),[](QByteArray &str){
                QList<QByteArray> intStr = str.split('/');
                return std::make_pair(intStr.first().toInt(),intStr.last().toInt());
            });
        }
    }
    for(auto &verFaceinfo:facesIndexs)
    {
        vPoints<<vertextPoints[(verFaceinfo.first-1)*3];
        vPoints<<vertextPoints[(verFaceinfo.first-1)*3+1];
        vPoints<<vertextPoints[(verFaceinfo.first-1)*3+2];

        vnPoints<<normalPoints[(verFaceinfo.second-1)*3];
        vnPoints<<normalPoints[(verFaceinfo.second-1)*3+1];
        vnPoints<<normalPoints[(verFaceinfo.second-1)*3+2];
    }

    vertextPoints.clear();
    facesIndexs.clear();
    normalPoints.clear();
    objFile.close();
    return true;
}
