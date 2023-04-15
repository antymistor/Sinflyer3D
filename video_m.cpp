#include "video_m.h"
#include <iostream>
#include <unistd.h>
video_m::video_m(cv::Mat *matout_)
:matout(matout_),thread_sw(false)
{}

video_m::~video_m()
{
    thread_sw=false;
    if(capture.isOpened())
    {
        capture.release();
    }
}
bool video_m::gocollect()
{
    if(!(capture.open(0)))
    {
       std::cout<<"...camera open failed..."<<std::endl;
       return false;
    }
    thread_sw=true;
   int ret=pthread_create(&collectthreadID,NULL,collectthread_video,this);
   if(ret!=0)
   {
   	thread_sw=false;
    std::cout<<"build new thread error"<<std::endl;
   	return false;
   }
   return true;
}

void *collectthread_video(void *b)
{
    video_m* base=static_cast<video_m *> (b);
    while(base->thread_sw)
    {
        if(base->capture.isOpened())
        {
            (base->capture)>> *(base->matout);
        }
         usleep(1000*30);
    }
   
}