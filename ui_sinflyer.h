#ifndef UI_SINFLYER_H
#define UI_SINFLYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QFontDatabase>
#include <QGridLayout>
#include <QTimer>
#include <QDateTime>

#include "sinflyerchart.h"
#include "sinflyergl.h"
#include "sinflyervideo.h"
QT_BEGIN_NAMESPACE

#define BW_speed_max 999
#define BW_speed_min -999
#define RA_angle_max 90
#define RA_angle_min -90
//#define W_speed_max  2047
#define W_speed_max 1000
#define W_speed_min 0

class Ui_sinflyer
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;
	
    //all base
	QWidget *main_widget, *left_widget, *right_widget;
	QGridLayout *main_layout, *left_layout, *right_layout;
    
    //right 
    QTabWidget *rightQtab;
       //Debugs part
         QWidget* debugpart;
         QGridLayout *debug_layout;
         QLineEdit *destination_address_lineedit;
         QLabel *address_label,*basewheel_label, *rollarm_label, *left_wing_label ,*right_wing_label,*both_ctr_label;
         QPushButton *connect_button;
         QSlider *basewheel_speed,*rollarm_angle,*left_wing_speed,*right_wing_speed;
         QSpinBox *basewheel_speed_,*rollarm_angle_,*left_wing_speed_,*right_wing_speed_;
         QCheckBox *both_ctr;
       //Auto part
         QWidget* autopart;
         QGridLayout* auto_layout;
	//left
    QTabWidget *leftQtab;
        //3D part
        QWidget *displaypart;
        QGridLayout *display_layout;
        Sinflyergl *sinflyer3d;
        sinflyerchart *eular_chart;
        sinflyerchart *gyro_chart;
        sinflyerchart *accel_chart;
        //video part
        QWidget *video;
        QGridLayout *video_Layout;
        sinflyervideo *videolabel;
        QPushButton *stop2, *copy2, *Cal2;
       
        
	void setupUi(QMainWindow *NetdemoClass); // setupUi
};

QT_END_NAMESPACE

#endif
