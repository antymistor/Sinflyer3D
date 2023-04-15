#ifndef __SINFLYER__
#define __SINFLYER__
#include <QtWidgets/QMainWindow>

#include "ui_sinflyer.h"
#include "udp_m.h"
#include "video_m.h"

class Sinflyer : public QMainWindow
{
	Q_OBJECT
public:
	explicit Sinflyer(QWidget *parent = Q_NULLPTR);
	Ui_sinflyer ui;
	udp_m *udp_pointer;
	video_m *video_pointer;
private:
    bool connect_sta=false;
	bool synctr_sta=false;
private slots:
    void connect_deal();
	void set_bothctr();
	void set_basewheelspeed(int power);
	void set_rollarmangle(int power);
	void set_leftwingspeed(int power);
	void set_rightwingspeed(int power);

};
#endif