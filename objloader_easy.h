#ifndef OBJLOADER_EASY_H
#define OBJLOADER_EASY_H

#include <QVector>
#include "modelloaderi.h"
class ObjLoader_easy : public ModelLoaderI
{
public:
    ~ObjLoader_easy()=default;
    ObjLoader_easy(const ObjLoader_easy&)=delete;
    ObjLoader_easy& operator=(const ObjLoader_easy&)=delete;
    bool load(QString fileName, QVector<float> &vPoints,QVector<float> &vnPoints);
    static ObjLoader_easy& getinstance()
    {
        static ObjLoader_easy instance;
        return instance;
    }
private:
     ObjLoader_easy() = default;
};

#endif // OBJLOADER_H
