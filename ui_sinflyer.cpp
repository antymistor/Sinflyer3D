#include"ui_sinflyer.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>



void Ui_sinflyer::setupUi(QMainWindow *Qttest2Class) 
{
	int fontId = QFontDatabase::addApplicationFont("fontawesome-webfont.ttf");
	 std::cout<<"uisetupfinish1"<<std::endl;
	//base set
	if (Qttest2Class->objectName().isEmpty())
		Qttest2Class->setObjectName(QStringLiteral("Sinflyer"));

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setStyle("Fusion");
	Qttest2Class->setAttribute(Qt::WA_TranslucentBackground);
	Qttest2Class->setWindowOpacity(0.9);
	//Qttest2Class->setBaseSize(900, 560);
	main_widget = new QWidget(Qttest2Class);
	QPalette pal(main_widget->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    main_widget->setAutoFillBackground(true);
    main_widget->setPalette(pal);

	main_widget->setObjectName(QStringLiteral("main_widget"));
	main_layout = new QGridLayout(main_widget);
	main_layout->setObjectName(QStringLiteral("main_layout"));
	left_widget = new QWidget();
	left_widget->setObjectName(QStringLiteral("left_widget"));
	left_layout = new QGridLayout(left_widget);
	left_layout->setObjectName(QStringLiteral("left_layout"));
	right_widget = new QWidget();
	right_widget->setObjectName(QStringLiteral("right_widget"));
	right_layout = new QGridLayout(right_widget);
	right_layout->setObjectName(QStringLiteral("right_layout"));
	main_layout->addWidget(left_widget, 0, 0, 10, 8);
	main_layout->addWidget(right_widget, 0, 8, 10, 2);
	Qttest2Class->setCentralWidget(main_widget);
	//Qttest2Class->setBaseSize(1800, 1000);
	

	//right
	rightQtab = new QTabWidget();
	right_layout->addWidget(rightQtab);
		//debugpart
		debugpart = new QWidget();
		debug_layout = new QGridLayout(debugpart);
		rightQtab->addTab(debugpart,"Debug");
				                  

	    address_label=new QLabel();
		address_label->setText("Destination IP Address: Port");
		destination_address_lineedit=new QLineEdit();
		destination_address_lineedit->setText("192.168.4.1:8080");
		destination_address_lineedit->setAlignment(Qt::AlignCenter);
		connect_button = new QPushButton();
        connect_button->setObjectName(QStringLiteral("connect_button"));
		connect_button->setStyleSheet("QPushButton{background:rgb(223,109,35);\
										border-top-right-radius: 10px;\
										border-bottom-right-radius: 10px;\
										border-top-left-radius: 10px;\
										border-bottom-left-radius: 10px;\
										height:24px;}\
										QPushButton:hover{ background:red; }");
        basewheel_label=new QLabel();
		basewheel_label->setText("Basewheel Speed");
		rollarm_label=new QLabel();
		rollarm_label->setText("Rollarm Angle");
        left_wing_label=new QLabel();
		left_wing_label->setText("Leftwing Speed");
		right_wing_label=new QLabel();
		right_wing_label->setText("Rightwing Speed");
		both_ctr_label=new QLabel();
		both_ctr_label->setText("Syn-Ctr");


        both_ctr=new QCheckBox();
		
		basewheel_speed_=new QSpinBox();
		basewheel_speed=new QSlider();
		basewheel_speed_->setMinimum(BW_speed_min);
		basewheel_speed_->setMaximum(BW_speed_max);
		basewheel_speed_->setSingleStep(10);
		basewheel_speed->setOrientation(Qt::Horizontal);
		basewheel_speed->setMinimum(BW_speed_min);
		basewheel_speed->setMaximum(BW_speed_max);
		basewheel_speed->setSingleStep(10);
        QObject::connect(basewheel_speed_, SIGNAL(valueChanged(int)),basewheel_speed, SLOT(setValue(int)));
        QObject::connect(basewheel_speed, SIGNAL(valueChanged(int)),basewheel_speed_, SLOT(setValue(int)));
        basewheel_speed->setValue(0);
        
		rollarm_angle_ =new QSpinBox();
		rollarm_angle=new QSlider();
		rollarm_angle_ ->setMinimum(RA_angle_min);
		rollarm_angle_ ->setMaximum(RA_angle_max);
		rollarm_angle_ ->setSingleStep(1);
		rollarm_angle->setOrientation(Qt::Horizontal);
		rollarm_angle->setMinimum(RA_angle_min);
		rollarm_angle->setMaximum(RA_angle_max);
		rollarm_angle->setSingleStep(1);
        QObject::connect(rollarm_angle_, SIGNAL(valueChanged(int)),rollarm_angle, SLOT(setValue(int)));
        QObject::connect(rollarm_angle, SIGNAL(valueChanged(int)),rollarm_angle_, SLOT(setValue(int)));
        rollarm_angle->setValue(0);
        
		left_wing_speed_=new QSpinBox();
		left_wing_speed=new QSlider();
		left_wing_speed_->setMinimum(W_speed_min);
		left_wing_speed_->setMaximum(W_speed_max);
		left_wing_speed_->setSingleStep(10);
		left_wing_speed->setOrientation(Qt::Horizontal);
		left_wing_speed->setMinimum(W_speed_min);
		left_wing_speed->setMaximum(W_speed_max);
		left_wing_speed->setSingleStep(10);
        QObject::connect(left_wing_speed_, SIGNAL(valueChanged(int)),left_wing_speed, SLOT(setValue(int)));
        QObject::connect(left_wing_speed, SIGNAL(valueChanged(int)),left_wing_speed_, SLOT(setValue(int)));
        left_wing_speed->setValue(0);

		right_wing_speed_=new QSpinBox();
		right_wing_speed=new QSlider();
		right_wing_speed_->setMinimum(W_speed_min);
		right_wing_speed_->setMaximum(W_speed_max);
		right_wing_speed_->setSingleStep(10);
		right_wing_speed->setOrientation(Qt::Horizontal);
		right_wing_speed->setMinimum(W_speed_min);
		right_wing_speed->setMaximum(W_speed_max);
		right_wing_speed->setSingleStep(10);
        QObject::connect(right_wing_speed_, SIGNAL(valueChanged(int)),right_wing_speed, SLOT(setValue(int)));
        QObject::connect(right_wing_speed, SIGNAL(valueChanged(int)),right_wing_speed_, SLOT(setValue(int)));
        right_wing_speed->setValue(0);
  
        const int interval=2;
		QLabel *q=new QLabel();
	    debug_layout->addWidget(address_label, 0, 0, 1, 4);
        debug_layout->addWidget(connect_button,0,4,1,1);
		debug_layout->addWidget(destination_address_lineedit,1,0,1,5);
		debug_layout->addWidget(q,2,0,interval,5);
        debug_layout->addWidget(basewheel_label,2+interval,0,1,2);
		debug_layout->addWidget(basewheel_speed_,2+interval,3,1,2);
        debug_layout->addWidget(basewheel_speed,3+interval,0,1,5);
		debug_layout->addWidget(rollarm_label,4+interval,0,1,2);
		debug_layout->addWidget(rollarm_angle_,4+interval,3,1,2);
        debug_layout->addWidget(rollarm_angle,5+interval,0,1,5);

        debug_layout->addWidget(both_ctr_label,6+interval,0,1,2);
		debug_layout->addWidget(both_ctr,6+interval,3,1,2);

        debug_layout->addWidget(left_wing_label,7+interval,0,1,2);
		debug_layout->addWidget(left_wing_speed_,7+interval,3,1,2);
        debug_layout->addWidget(left_wing_speed,8+interval,0,1,5);
        debug_layout->addWidget(right_wing_label,9+interval,0,1,2);
		debug_layout->addWidget(right_wing_speed_,9+interval,3,1,2);
        debug_layout->addWidget(right_wing_speed,10+interval,0,1,5);



        debugpart->setStyleSheet("QLineEdit{color:white;width:160px;font-size:17px;font-family:Arial;border-radius:7px;min-height:25px;background:rgb(51,51,51);}\
		                          QLabel{color:rgb(225,255,255,255);font-size:17px;font-weight:normal;font-family:Arial;}\
								  QSlider::groove:horizontal{background:white;height: 5px;left: 5px;right: 5px;}\
								  QSlider::handle:horizontal{width:15px;background:#333333;}\
								");
   //debugpart
		autopart = new QWidget();
		auto_layout = new QGridLayout(autopart);
		rightQtab->addTab(autopart,"Auto");


	rightQtab->setStyleSheet("QTabWidget{background-color:rgb(0,0,0);font-family:Arial;}\
								QTabBar::tab { border:none;min-width:100px; min-height:30px;font-size:16px;color:white;background-color:[255,255,255,0];}\
								QTabBar::tab:selected{color:#000000;font-weight:bold;background-color:#FFFFFF;}\
								QTabBar::tab:hover{background-color:gray;}\
							");
    

	//left
    leftQtab = new QTabWidget();
	left_layout->addWidget(leftQtab);
		//3Dpart
		displaypart=new QWidget();
		display_layout=new QGridLayout(displaypart);

		sinflyer3d = new Sinflyergl();
		charttype eularcharttype={
                                   "Eular Angles",
								   QColor(45,20,20),
								   "Angle/Deg",
                                   "time/s",
								   0.f,5.f,-180.f,180.f,
                                   {{"Pitch",QColor(20,45,120)},{"Roll",QColor(120,20,45)},{"Yaw",QColor(45,120,20)}}
		                         };
		charttype gyrocharttype={
                                   "Gyro Angles",
								   QColor(20,45,20),
								   "RotSpeed/(Deg/s)",
                                   "time/s",
								   0.f,5.f,-500.f,500.f,
                                   {{"X_gyro",QColor(20,45,120)},{"Y_gyro",QColor(120,20,45)},{"Z_gyro",QColor(45,120,20)}}
		                         };
	    charttype accelcharttype={
                                   "Accel Angles",
								   QColor(20,20,45),
								   "Accelation/g",
                                   "time/s",
								   0.f,5.f,-2.f,2.f,
                                   {{"X_acc",QColor(20,45,120)},{"Y_acc",QColor(120,20,45)},{"Z_acc",QColor(45,120,20)}}
		                         };
		eular_chart=new sinflyerchart(eularcharttype,1);
		gyro_chart=new sinflyerchart(gyrocharttype,9);
		accel_chart=new sinflyerchart(accelcharttype,12);
        
        gyro_chart->setStyleSheet("QWidget{min-width:400px; min-height:200px}");
	    sinflyer3d->setStyleSheet("QWidget{min-width:400px; min-height:200px}");
		display_layout->addWidget(gyro_chart,0,0,1,1);
		display_layout->addWidget(accel_chart,0,1,1,1);
		display_layout->addWidget(eular_chart,1,0,1,1);
		display_layout->addWidget(sinflyer3d,1,1,1,1);


		leftQtab->addTab(displaypart,"Display");
        //videopart
		video=new QWidget();
		video_Layout=new QGridLayout(video);

        videolabel=new sinflyervideo(900,500);
		videolabel->displayset(true);
        video_Layout->addWidget(videolabel,0,0,1,1);

		leftQtab->addTab(video,"Video");
        
        

	leftQtab->setStyleSheet("QTabWidget{background-color:rgb(0,0,0);font-family:Arial;}\
								QTabBar::tab { border:none;min-width:100px; min-height:30px;font-size:16px;color:white;background-color:[255,255,255,0];}\
								QTabBar::tab:selected{color:#000000;font-weight:bold;background-color:#FFFFFF;}\
								QTabBar::tab:hover{background-color:gray;}\
							");

	Qttest2Class->setWindowTitle(QApplication::translate("Qttest2Class", "Sinflyer", Q_NULLPTR));
	QMetaObject::connectSlotsByName(Qttest2Class);
	std::cout<<"uisetupfinish"<<std::endl;
}

