#include "sinflyer.h"
#include <iostream>
typedef union floatunion_
{
	 char bytes[4];
	 float value;
} floatunion;


Sinflyer::Sinflyer(QWidget *parent): QMainWindow(parent)
{
   
	ui.setupUi(this);
    connect(ui.connect_button, SIGNAL(clicked()), this, SLOT(connect_deal()));
	connect(ui.left_wing_speed_,SIGNAL(valueChanged(int)),this,SLOT(set_leftwingspeed(int)));
	connect(ui.right_wing_speed_,SIGNAL(valueChanged(int)),this,SLOT(set_rightwingspeed(int)));
	connect(ui.basewheel_speed_,SIGNAL(valueChanged(int)),this,SLOT(set_basewheelspeed(int)));
    connect(ui.rollarm_angle_,SIGNAL(valueChanged(int)),this,SLOT(set_rollarmangle(int)));
	connect(ui.both_ctr,SIGNAL(clicked()),this,SLOT(set_bothctr()));
}

void Sinflyer::set_bothctr()
{
     synctr_sta=ui.both_ctr->checkState();
	 if(synctr_sta)
	 {
		 ui.right_wing_speed_->setValue(ui.left_wing_speed_->value());
		 QObject::connect(ui.right_wing_speed_, SIGNAL(valueChanged(int)),ui.left_wing_speed_, SLOT(setValue(int)));
		 QObject::connect(ui.left_wing_speed_, SIGNAL(valueChanged(int)),ui.right_wing_speed_, SLOT(setValue(int)));
		 disconnect(ui.right_wing_speed_,SIGNAL(valueChanged(int)),this,SLOT(set_rightwingspeed(int)));
	 }
	 else
	 {
		 QObject::disconnect(ui.right_wing_speed_, SIGNAL(valueChanged(int)),ui.left_wing_speed_, SLOT(setValue(int)));
		 QObject::disconnect(ui.left_wing_speed_, SIGNAL(valueChanged(int)),ui.right_wing_speed_, SLOT(setValue(int)));
		 connect(ui.right_wing_speed_,SIGNAL(valueChanged(int)),this,SLOT(set_rightwingspeed(int)));
	 }
	 
}

void Sinflyer::connect_deal()
{
    if(connect_sta)
    {
		connect_sta=false;
        //close server;
		if(udp_pointer!=NULL)
		{
			delete(udp_pointer);
			udp_pointer=NULL;
		}
        ui.connect_button->setStyleSheet("QPushButton{background:rgb(223,109,35);\
										border-top-right-radius: 10px;\
										border-bottom-right-radius: 10px;\
										border-top-left-radius: 10px;\
										border-bottom-left-radius: 10px;\
										height:24px;}\
										QPushButton:hover{ background:red; }");
	    //close video
		if(video_pointer!=NULL)
		{
		delete(video_pointer);
		video_pointer=NULL;
		}
    }
    else
    {
         //do udp connect
		 udp_pointer=new udp_m({&(ui.sinflyer3d)->updatestrs,
		                        &(ui.eular_chart)->updatestrs,
								&(ui.gyro_chart)->updatestrs,
								&(ui.accel_chart)->updatestrs
								});
		 if(udp_pointer->connect_())
		 {
		 connect_sta=true;
         ui.connect_button->setStyleSheet("QPushButton{background:rgb(109,223,35);\
										border-top-right-radius: 10px;\
										border-bottom-right-radius: 10px;\
										border-top-left-radius: 10px;\
										border-bottom-left-radius: 10px;\
										height:24px;}\
										QPushButton:hover{ background:green; }");
		 udp_pointer->gocollect();
		 }
		 //do video connect
		 video_pointer=new video_m(&(ui.videolabel->picture2display));
		 video_pointer->gocollect();
	}
}

void Sinflyer::set_leftwingspeed(int power)
{

	static floatunion temp;
	static char sendbuff[8]={0x08,'E','c','l',0,0,0,0};
	if(connect_sta)
	{
	temp.value=static_cast<float>(power);
	if(synctr_sta)
	{
		sendbuff[3]='b';
	}
	else
	{
		sendbuff[3]='l';
	}
    sendbuff[4]=temp.bytes[0];
	sendbuff[5]=temp.bytes[1];
	sendbuff[6]=temp.bytes[2];
	sendbuff[7]=temp.bytes[3];
	udp_pointer->send_(sendbuff,8);
	}
}

void Sinflyer::set_rightwingspeed(int power)
{
	static floatunion temp;
	static char sendbuff[8]={0x08,'E','c','r',0,0,0,0};
	if(connect_sta)
	{
	temp.value=static_cast<float>(power);
    sendbuff[4]=temp.bytes[0];
	sendbuff[5]=temp.bytes[1];
	sendbuff[6]=temp.bytes[2];
	sendbuff[7]=temp.bytes[3];
	udp_pointer->send_(sendbuff,8);
	}
}
void Sinflyer::set_basewheelspeed(int power)
{
    static floatunion temp;
	static char sendbuff[8]={0x08,'E','a','p',0,0,0,0};
	if(connect_sta)
	{
	temp.value=static_cast<float>(power);
    sendbuff[4]=temp.bytes[0];
	sendbuff[5]=temp.bytes[1];
	sendbuff[6]=temp.bytes[2];
	sendbuff[7]=temp.bytes[3];
	udp_pointer->send_(sendbuff,8);
	}
}
void Sinflyer::set_rollarmangle(int power)
{
	static floatunion temp;
	static char sendbuff[8]={0x08,'E','b','p',0,0,0,0};
	if(connect_sta)
	{
	temp.value=static_cast<float>(power);
    sendbuff[4]=temp.bytes[0];
	sendbuff[5]=temp.bytes[1];
	sendbuff[6]=temp.bytes[2];
	sendbuff[7]=temp.bytes[3];
	udp_pointer->send_(sendbuff,8);
	}
}