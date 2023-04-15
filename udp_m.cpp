#include <iostream>
#include "udp_m.h"
#include <QString>
#include <QDebug>
udp_m::udp_m(std::vector<std::queue<std::string> *> s,const int& port,const std::string& str):
        str_(s),portnum(port),ipstr(str),
        bindreadyif(true),connectreadyif(false),thread_sw(false)
{}
bool udp_m::connect_()
{
	connectreadyif=false;
	if(!bindreadyif){return false;}

  ServerSocket=socket(AF_INET, SOCK_DGRAM, 0);
  memset(&ServerAddr,0,sizeof(ServerAddr));

  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_port=htons(portnum);
  ServerAddr.sin_addr.s_addr = inet_addr(ipstr.c_str());  //need to change

  char send_buf[1];
  send_buf[0]='#';
  if(-1==sendto(ServerSocket, send_buf, strlen(send_buf), 0, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)))
  {
   connectreadyif=false;
   return false;
  }
	connectreadyif=true;
  return true;
}
void udp_m::set_des_addr(const int& port,const std::string& str)
{
  portnum=port;
  ipstr=str;
}
udp_m::~udp_m()
{
  char send_buf[1];
  send_buf[0]='$';
  sendto(ServerSocket, send_buf, strlen(send_buf), 0, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
  thread_sw=false;
  close(ServerSocket);
}


bool udp_m::gocollect()
{
   if(!connectreadyif) return false;
   thread_sw=true;  
   int ret=pthread_create(&collectthreadID,NULL,collectthread_udp,this);
   if(ret!=0)
   {
   	thread_sw=false;
    std::cout<<"build new thread error"<<std::endl;
   	return false;
   }
   return true;
}

bool udp_m::send_(char * strhead,unsigned short len)
{
   if(!connectreadyif) return false;
   if(-1==sendto(ServerSocket, strhead, len, 0, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)))
  {
   return false;
  }
  return true;

}

void *collectthread_udp(void *b)
{
    udp_m * base=(udp_m *)b;
    static timeval tpre={0,0};
    static timeval tnow={0,0};
    static socklen_t SenderAddrSize=sizeof(base->ServerAddr);
	while(base->thread_sw)
	{
	   memset(base->buff, 0, sizeof(base->buff));
	   int n=recvfrom(base->ServerSocket,base->buff,
                     sizeof(base->buff), 0, (sockaddr *)&(base->ServerAddr), &SenderAddrSize);
      tpre=tnow;
      gettimeofday(&tnow,NULL);
      (base->buff)[n]='\0';
      std::string s=base->buff;
      std::cout<<1000*(tnow.tv_sec-tpre.tv_sec)+(tnow.tv_usec-tpre.tv_usec)/1000<<" "<<s<<std::endl;

      for(int i=0;i!=(base->str_).size();++i)
      {
         (*(base->str_[i])).push(s);
      }
      //QString s1=QString(QLatin1String(base->buff));
      //QList<QString> lin=s1.split("\r\n");
      //*(base->str_)=(*(lin.end()-2)).toStdString();
	}
} 
