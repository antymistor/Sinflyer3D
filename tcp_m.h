#ifndef _TCPM_H
#define _TCPM_H

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
#include "sys/time.h"
#include "pthread.h"
#define Mode 0   //1:server 0:client

void *collectthread(void * );

class tcp_m
{
    public:
       tcp_m(std::string *s,const int& port=8080,const std::string& str="192.168.4.1");
       tcp_m()=default;
       ~tcp_m();
       bool connect_();
       bool gocollecct();
       bool thread_sw;
    private:
     friend void *collectthread(void * );
    
    //output address
	 std::string *str_;
    
    //Server management
    bool bindreadyif;
	 bool connectreadyif;
	 int portnum;
	 int  ServerSocket;
	 int BaseSocket;
	 sockaddr_in ServerAddr;
	 sockaddr_in ClientAddr;

     //temp buff
	 char buff[1000];
	 //mult thread related
	 pthread_t collectthreadID;
};

#endif