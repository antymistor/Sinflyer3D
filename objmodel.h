#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>


struct environment
{
    QMatrix4x4 pMatrix;
    QMatrix4x4 vMatrix;
    QMatrix4x4 mMatrix;
    QVector3D  cameraLocation;
    QVector3D  lightCation;
};
class Objmodel
{
public:
    Objmodel(const QString& filename,const QMatrix4x4& trans=QMatrix4x4());
private:
    friend class Objmodelsets;
    void Move_R(const QMatrix4x4& trans=QMatrix4x4());
    void Move_A(const QMatrix4x4& trans=QMatrix4x4());
    void render(QOpenGLExtraFunctions *f,const environment& env);
    void setcolor(const QVector4D& color);
    void settrans(const QMatrix4x4& trans=QMatrix4x4());

    QVector4D color_={0.5,0.5,0.5,1};
    QMatrix4x4 trans_;
    QOpenGLBuffer vbo_;
    QOpenGLShaderProgram program_;
    QVector<float> vertPoints_,normPoints_;
};

#endif // GENERICRENDER_H
