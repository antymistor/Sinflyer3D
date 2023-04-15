#include "sinflyergl.h"
#include "sinflyer.h"
#include <QApplication>
#include "tcp_m.h"
//#include "udp_m.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Sinflyergl w;
    
    // udp_m se(&(w.updatestr),8080,"192.168.4.1");
    // w.show();
    // se.set_des_addr(8080,"192.168.4.1");
    // // return a.exec();
    // se.connect_();
    // se.gocollecct();
    Sinflyer w;
    w.show();
    return a.exec();
}

