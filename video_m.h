#ifndef _VIDEOM_H
#define _VIDEOM_H
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "pthread.h"
void *collectthread_video(void *);
class video_m
{
    public:
        video_m(cv::Mat * matout_);
        ~video_m();
        bool gocollect();
    private:
        friend void *collectthread_video(void * );
        cv::VideoCapture capture;
        cv::Mat *matout;
        bool thread_sw;
        pthread_t collectthreadID;

};
#endif