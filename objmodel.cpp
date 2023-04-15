#include "objmodel.h"
#include "objloader_easy.h"
Objmodel::Objmodel(const QString& filename,const QMatrix4x4& trans)
{
    trans_=trans;
    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,"../vsrc_easy.vert");
    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,"../fsrc_easy.frag");
    program_.link();

    //ObjLoader_easy objModelLoader;
    ObjLoader_easy::getinstance().load(filename,vertPoints_,normPoints_);
    QVector<float> points;
    points << vertPoints_ << normPoints_;
    vbo_.create();
    vbo_.bind();
    vbo_.allocate(points.data(),points.count() * sizeof(float));
    color_={0,0,0,0};

}
void Objmodel::Move_R(const QMatrix4x4 &trans)
{
    trans_=trans_*trans;
}
void Objmodel::Move_A(const QMatrix4x4 &trans)
{
    trans_=trans*trans_;
}
void Objmodel::setcolor(const QVector4D& color)
{
    color_=color;
}
void Objmodel::settrans(const QMatrix4x4 &trans)
{
    trans_=trans;
}
void Objmodel::render(QOpenGLExtraFunctions *f, const environment &env)
{

    program_.bind();
    vbo_.bind();

    program_.setUniformValue("uPMatrix",env.pMatrix);
    program_.setUniformValue("uVMatrix",env.vMatrix);
    program_.setUniformValue("uMMatrix",env.mMatrix*trans_);
    program_.setUniformValue("uLightLocation",env.lightCation);
    program_.setUniformValue("uCamera",env.cameraLocation);
    program_.setUniformValue("color",color_);


    program_.enableAttributeArray(0);
    program_.enableAttributeArray(1);
    program_.setAttributeBuffer(0,GL_FLOAT,0,3,3*sizeof(GLfloat));
    program_.setAttributeBuffer(1,GL_FLOAT,vertPoints_.count() * sizeof(GLfloat),3,3*sizeof(GLfloat));

    f->glDrawArrays(GL_TRIANGLES,0,vertPoints_.count()/3);
    //f->glDrawArrays(GL_POINTS,0,vertPoints_.count());
    program_.disableAttributeArray(0);
    program_.disableAttributeArray(1);

    vbo_.release();
    program_.release();

}
