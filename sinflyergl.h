#ifndef SINFLYER_H
#define SINFLYER_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include "objmodelsets.h"
#include <string>
#include <queue>

struct inputdata
{   //sp means rotate speed;
    //an means rotate angle;
    float w0_sp; //wheel rotate speed
    float w1_sp; //wing0 rotate speed
    float w2_sp; //wing1 rotate speed

    float J0_an; //balance angle:Pitch
    float J1_an; //rollarm angle
    

    float C0_an; //balance angle: Roll
    float C1_an; //balance angle: Yaw
};
struct camdata
{
    float yaw_an=180;
    float pitch_an=0;
    float distance=300;
};

class Sinflyergl : public QOpenGLWidget
{
    Q_OBJECT

public:
    Sinflyergl(QWidget *parent = 0);
    ~Sinflyergl()=default;
    std::queue<std::string> updatestrs;

protected:
    void initializeGL() override;
    void resizeGL(int w,int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
//curser
    QCursor cursor;                      // 创建光标对象
    QPoint lastoffset;
//timer used to update
    QTimer tm_;
    static const unsigned int updatetime=20;  //Unit:ms
// sinflyer assembling information
    constexpr static const float armheight=50.f;          //Unit:mm
    constexpr static const float armlen=112.5f;
    constexpr static const float wingheight=68.5f;
// moedel sets
    Objmodelsets render_new;
// input information
   inputdata input_;
   float wheel_now_angle=0;
   float wing0_now_angle=0;
   float wing1_now_angle=0;
   QMatrix4x4 wheeltrans_;
   QMatrix4x4 basetrans_;
   QMatrix4x4 rollarmtrans_;
   QMatrix4x4 wing0trans_;
   QMatrix4x4 wing1trans_;
// camera position information
   camdata cam_,camnow;
   QVector3D cameraLocation_,lightLocation_;
   short cam_upflag=1;
   QMatrix4x4 pMatrix_,vMatrix_,mMatrix_;

void cam_position_update(const camdata& camdata);
void mod_position_update(const inputdata& inputdata);

private slots:
    void slotTimeout();
};

#endif 