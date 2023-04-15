#include"sinflyervideo.h"
sinflyervideo::sinflyervideo(const unsigned int &width_,
                             const unsigned int &height_,
                             const unsigned int &updatefrequency_)
                             :width(width_),height(height_),updatefrequency(updatefrequency_),display_sw(false)
                             {}

void sinflyervideo::setsize(const unsigned int &width_,const unsigned int &height_)
{
   width= width_;
   height=height_;
}

void sinflyervideo::setFre(const unsigned int updatefrequency_)
{
    updatefrequency=updatefrequency_;
}

void sinflyervideo::displayset(bool sw_)
{
  if(display_sw==sw_)
  {
      return;
  }
  display_sw=sw_;
  if(display_sw)
  {
       connect(&tm_,SIGNAL(timeout()),this,SLOT(slotTimeout_()));
       tm_.start(1000/updatefrequency);
  }
  else
  {
       tm_.stop();
  }
}

void sinflyervideo::slotTimeout_()
{
   if(picture2display.empty())
   {return;}

   if(height==0){height=1;} 

   float WH_ratio=static_cast<float>(width)/height;
   float input_ratio=static_cast<float>(picture2display.cols)/picture2display.rows;
   if(  input_ratio>WH_ratio   )
   {
       cv::resize(picture2display,picture2display,cv::Size(width,width/WH_ratio) );
   }
   else
   {
       cv::resize(picture2display,picture2display,cv::Size(height*WH_ratio,height) );
   }
   cv::Mat displaypic;
   cvtColor(picture2display, displaypic, CV_RGB2BGR);
   QImage Img = QImage((const uchar*)(displaypic.data),
                        displaypic.cols, 
                        displaypic.rows, 
                        displaypic.cols * displaypic.channels(), 
                        QImage::Format_RGB888);
   this->setPixmap(QPixmap::fromImage(Img));
}



