#include "objmodelsets.h"
void Objmodelsets::addobjmodel(const QString& name, const QString& src_path,const QMatrix4x4& trans)
{
  std::shared_ptr<Objmodel> m=std::make_shared<Objmodel>(src_path,trans);
  modelsets[name]=m;
}
void Objmodelsets::addobjmodel(const QString& name,std::shared_ptr<Objmodel> m)
{
  modelsets[name]=m;
}
void Objmodelsets::setenvironment(QMatrix4x4 p, QMatrix4x4 v, QMatrix4x4 m, QVector3D c, QVector3D l)
{
    env.cameraLocation=c;
    env.lightCation=l;
    env.mMatrix=m;
    env.pMatrix=p;
    env.vMatrix=v;
}
bool Objmodelsets::moveobjmode(const QString &name, QMatrix4x4 trans,coodtype c)
{

    auto res=modelsets.find(name);
    if(res==modelsets.end())
    {
        return false;
    }
    if(c==Relative)
    {
     modelsets[name]->Move_R(trans);
    }
    else
    {
     modelsets[name]->Move_A(trans);
    }
    return true;
}

bool Objmodelsets::setobjcolor(const QString &name, const QVector4D &color)
{
    auto res=modelsets.find(name);
    if(res==modelsets.end())
    {
        return false;
    }
    modelsets[name]->setcolor(color);
    return true;
}

bool Objmodelsets::setobjtrans(const QString &name, const QMatrix4x4 &trans)
{
    auto res=modelsets.find(name);
    if(res==modelsets.end())
    {
        return false;
    }
    modelsets[name]->settrans(trans);
    return true;
}
void Objmodelsets::renderall(QOpenGLExtraFunctions *f)
{
      f->glEnable(GL_DEPTH_TEST);
   for(auto iter=modelsets.begin();iter!=modelsets.end();++iter)
   {
       iter->second->render(f,env);
   }
      f->glDisable(GL_DEPTH_TEST);
}
