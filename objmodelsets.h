#ifndef OBJMODELSETS_H
#define OBJMODELSETS_H

#include <map>
#include <memory>
#include "objmodel.h"

enum coodtype
{
 Relative,
 Absolute
};

class Objmodelsets
{
public:
    Objmodelsets()=default;
    void addobjmodel(const QString& name, const QString& src_path,const QMatrix4x4& trans=QMatrix4x4());
    void addobjmodel(const QString& name,std::shared_ptr<Objmodel> m);
    bool moveobjmode(const QString& name, QMatrix4x4 trans ,coodtype c=Relative);
    bool setobjcolor(const QString& name, const QVector4D& color);
    bool setobjtrans(const QString& name, const QMatrix4x4 &trans);
    void setenvironment(QMatrix4x4 p, QMatrix4x4 v, QMatrix4x4 m, QVector3D c, QVector3D l);
    void renderall(QOpenGLExtraFunctions *f);
private:
   environment env;
   std::map<QString,std::shared_ptr<Objmodel>> modelsets;
};

#endif // GENERICRENDER_H
