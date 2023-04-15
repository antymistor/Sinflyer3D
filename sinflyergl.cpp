#include "sinflyergl.h"
#include "math.h"
#include "sys/time.h"
#include <iostream>
Sinflyergl::Sinflyergl(QWidget *parent): QOpenGLWidget(parent)
{
    connect(&tm_,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    tm_.start(updatetime);
    cursor.setShape(Qt::OpenHandCursor); // 设置光标形状
    setCursor(cursor);
}


void Sinflyergl::initializeGL()
{
    QMatrix4x4 temp;
    temp.translate(0,-36,0);
    render_new.addobjmodel("ground","../objsrc/ground.obj",temp);
    render_new.addobjmodel("base","../objsrc/base.obj");
    render_new.addobjmodel("wheel","../objsrc/wheel.obj");
    render_new.addobjmodel("rollarm","../objsrc/rollarm.obj");
    render_new.addobjmodel("wing0","../objsrc/wing.obj");
    render_new.addobjmodel("wing1","../objsrc/wing.obj");
    render_new.setobjcolor("ground",{0.3,0.3,0.3,1});
    render_new.setobjcolor("rollarm",{0.7,0.7,0.8,1});
    render_new.setobjcolor("base",{0.7,0.2,0.3,1});
    cameraLocation_={0,50,200};
    lightLocation_={200,0,0};
    cam_position_update(camdata());
    mod_position_update(inputdata());
    mMatrix_=QMatrix4x4();
}


void Sinflyergl::resizeGL(int w, int h)
{
    pMatrix_.setToIdentity();
    pMatrix_.perspective(60,float(w)/h,0.01f,1000.0f);
}

void Sinflyergl::paintGL()
{
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    f->glClearColor(0.1f,0.1f,0.1f,1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_new.setenvironment(pMatrix_, vMatrix_, mMatrix_, cameraLocation_, lightLocation_);
    render_new.renderall(f);
}

void Sinflyergl::cam_position_update(const camdata &camdata)
{
   if(cos(camdata.pitch_an*3.1415926f/180)*cos(cam_.pitch_an*3.1415926f/180)<=0)
   {
       cam_upflag*=-1;
   }
   cam_=camdata;
   vMatrix_=QMatrix4x4();
   cameraLocation_={cam_.distance*cos(cam_.pitch_an*3.1415926f/180)*sin(cam_.yaw_an*3.1415926f/180),
                    cam_.distance*sin(cam_.pitch_an*3.1415926f/180),
                    cam_.distance*cos(cam_.pitch_an*3.1415926f/180)*cos(cam_.yaw_an*3.1415926f/180)};
   vMatrix_.lookAt(cameraLocation_,QVector3D(0,50,0),QVector3D(0,cam_upflag,0));
}

void Sinflyergl::mod_position_update(const inputdata &inputdata)
{
  input_=inputdata;
  wheel_now_angle+=input_.w0_sp*updatetime/1000;
  wing0_now_angle+=input_.w1_sp*updatetime/1000;
  wing1_now_angle+=input_.w2_sp*updatetime/1000;
  //wheel set
  
  wheeltrans_.setToIdentity();
  wheeltrans_.rotate(input_.C1_an,0,1,0);   //yaw
  wheeltrans_.rotate(input_.C0_an,0,0,1);   //roll
  wheeltrans_.rotate(input_.J0_an,1,0,0);   //pitch
  wheeltrans_.rotate(wheel_now_angle,1,0,0);
  //base set
  basetrans_.setToIdentity();
  basetrans_.rotate(input_.C1_an,0,1,0);
  basetrans_.rotate(input_.C0_an,0,0,1);
  basetrans_.rotate(input_.J0_an,1,0,0);
  
  //rollarm set
  rollarmtrans_.setToIdentity();
  rollarmtrans_.rotate(input_.C1_an,0,1,0);
  rollarmtrans_.rotate(input_.C0_an,0,0,1);
  rollarmtrans_.rotate(input_.J0_an,1,0,0);
  rollarmtrans_.translate(0,armheight,0);
  rollarmtrans_.rotate(input_.J1_an,1,0,0);
  //wing0 set
  wing0trans_.setToIdentity();
  wing0trans_.rotate(input_.C1_an,0,1,0);
  wing0trans_.rotate(input_.C0_an,0,0,1);
  wing0trans_.rotate(input_.J0_an,1,0,0);
  wing0trans_.translate(0,armheight,0);
  wing0trans_.rotate(input_.J1_an,1,0,0);
  wing0trans_.translate(armlen,wingheight-armheight,1);
  wing0trans_.rotate(wing0_now_angle,0,1,0);
  //wing1 set
  wing1trans_.setToIdentity();
  wing1trans_.rotate(input_.C1_an,0,1,0);
  wing1trans_.rotate(input_.C0_an,0,0,1);
  wing1trans_.rotate(input_.J0_an,1,0,0);
  wing1trans_.translate(0,armheight,0);
  wing1trans_.rotate(input_.J1_an,1,0,0);
  wing1trans_.translate(-armlen,wingheight-armheight,1);
  wing1trans_.rotate(-wing1_now_angle,0,1,0);
  //set all trans
  render_new.setobjtrans("wheel",wheeltrans_);
  render_new.setobjtrans("base",basetrans_);
  render_new.setobjtrans("rollarm",rollarmtrans_);
  render_new.setobjtrans("wing0",wing0trans_);
  render_new.setobjtrans("wing1",wing1trans_);
}

void Sinflyergl::wheelEvent(QWheelEvent *event)    // 滚轮事件
{
    if(event->delta() > 0){                    // 当滚轮远离使用者时
       camnow.distance+=8;
       if(camnow.distance>900)
       {
           camnow.distance=900;
       }
    }else{                                     // 当滚轮向使用者方向旋转时
       camnow.distance-=8;
       if(camnow.distance<5)
       {
           camnow.distance=5;
       }
    }
}
void Sinflyergl::mousePressEvent(QMouseEvent *event) // 鼠标按下事件
{
    if(event->button() == Qt::LeftButton)
    {       // 如果是鼠标左键按下
        //QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        setCursor(cursor);
        lastoffset=event->pos();
    }
}
void Sinflyergl::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint movedis;
    if(event->buttons()&Qt::LeftButton)
    {
        movedis=event->pos()-lastoffset;
        lastoffset=event->pos();
        camnow.yaw_an-=movedis.x();
        camnow.pitch_an+=movedis.y();
    }
}
void Sinflyergl::mouseReleaseEvent(QMouseEvent *event) // 鼠标释放事件
{
    cursor.setShape(Qt::OpenHandCursor); 
    setCursor(cursor);
}

void Sinflyergl::slotTimeout()
{
    static inputdata in={0,0,0,0,0,0,0};
    //std::cout<<updatestr<<std::endl;
    static std::string updatestr;
    if(!updatestrs.empty())
    {
        updatestr=updatestrs.back();
        while(!updatestrs.empty())
        {
         updatestrs.pop();
        }
    }
    QList<QString> lin=(QString::fromStdString(updatestr)).split("\r\n");
    if(lin.length()>1)
    {
        QList<QString> temp= (*(lin.end()-2)).split(" ");
        if(temp.length()>8){ 
        in={temp[5].toFloat(),    //basewheel speed
            temp[7].toFloat(),    //left wing drive power
            temp[8].toFloat(),    //right wing drive power
            -temp[1].toFloat(),    //pitch 
            temp[4].toFloat(),    //rollarm angle
            -temp[2].toFloat(),   //roll
            temp[3].toFloat()};  //yaw
        }
    }
    mod_position_update(in);
    cam_position_update(camnow);
    update();
}
