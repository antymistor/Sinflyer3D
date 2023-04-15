#ifndef SINFLYERVIDEO_H
#define SINFLYERVIDEO_H
#include <QtWidgets/QLabel>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <QTimer>

class sinflyervideo:public QLabel
{
  Q_OBJECT
  public:
  sinflyervideo(const unsigned int &width_=500,
                const unsigned int &height_=300,
                const unsigned int &updatefrequency_=30);
  void setsize(const unsigned int &width_,const unsigned int &height_);
  void setFre(const unsigned int updatefrequency_=30);
  void displayset(bool sw_);
  cv::Mat picture2display;
  

  private:
  bool display_sw;
  unsigned int width;
  unsigned int height;
  unsigned int updatefrequency;  //Unit: Hz
  QTimer tm_;
  
  private slots:
    void slotTimeout_();

};

#endif