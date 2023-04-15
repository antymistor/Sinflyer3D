#ifndef _UDPM_H
#define _UDPPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <queue>
#include "sys/time.h"
#include "pthread.h"


void *collectthread_udp(void * );
class udp_m
{
    public:
       udp_m(std::vector<std::queue<std::string> *> s={},const int& port=8080,const std::string& str="192.168.4.1");
       udp_m()=default;
       ~udp_m();
       void set_des_addr(const int& port=8080,const std::string& str="192.168.4.1");
       bool connect_();
       bool gocollect();

       bool send_(char * strhead,unsigned short len);
       bool thread_sw;
    private:
     friend void *collectthread_udp(void * );
    
    //output address
	 ///std::string *str_;
    std::vector<std::queue<std::string> *> str_;

    //Destination IP address
    std::string ipstr;
   

    //Server management
    bool bindreadyif;
	 bool connectreadyif;
	 int portnum;
	 int  ServerSocket; 
	 sockaddr_in ServerAddr;
	

     //temp buff
	 char buff[1000];
	 //mult thread related
	 pthread_t collectthreadID;
};

#endif