#include <iostream>
#include "tcp_m.h"
#include <QString>
#include <QDebug>
tcp_m::tcp_m(std::string *s,const int& port,const std::string& str):
        str_(s),portnum(port),
        bindreadyif(false),connectreadyif(false),thread_sw(false)
{
  #if Mode
   BaseSocket = socket(AF_INET, SOCK_STREAM, 0);
   ServerAddr.sin_family = AF_INET;
   ServerAddr.sin_port = htons(portnum);

   ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);  //need to change

   if (bind(BaseSocket, (sockaddr *)&ServerAddr, sizeof(sockaddr))<0)
  {
    std::cout<<"bind error"<<std::endl;
  	return ;
  }
  bindreadyif=true;
  #else
  ServerSocket=socket(AF_INET, SOCK_STREAM, 0);
  ServerAddr.sin_family = AF_INET;
  //ServerAddr.sin_port = htons(6572);
  //ServerAddr.sin_addr.s_addr = inet_addr("115.29.109.104");  //need to change
  ServerAddr.sin_port=htons(8080);
  ServerAddr.sin_addr.s_addr = inet_addr(str.c_str());  //need to change
  bindreadyif=true;
  #endif
}
bool tcp_m::connect_()
{
	connectreadyif=false;
	if(!bindreadyif){return false;}
  #if Mode
    if(listen(BaseSocket, 10) < 0)
	{
      std::cout<<"listen error"<<std::endl;
	  return false;
	}
	static socklen_t len=sizeof(sockaddr);
	ServerSocket = accept(BaseSocket, (sockaddr *)&ClientAddr, &len);
	if(ServerSocket<0)
	{
     std::cout<<"accept error"<<std::endl;
		return false;
	}
  #else
  if ( connect( ServerSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) < 0) 
    {
        std::cout << "Error: connect" << std::endl;
        return false;
    }
  #endif
	connectreadyif=true;
  return true;
}

bool tcp_m::gocollecct()
{
   if(!connectreadyif) return false;
   thread_sw=true;  
   int ret=pthread_create(&collectthreadID,NULL,collectthread,this);
   if(ret!=0)
   {
   	thread_sw=false;
    std::cout<<"build new thread error"<<std::endl;
   	return false;
   }
   return true;
}

tcp_m::~tcp_m()
{
    thread_sw=false;
    close(ServerSocket);
}

void *collectthread(void *b)
{
  tcp_m * base=(tcp_m *)b;
	while(base->thread_sw)
	{
	   memset(base->buff, 0, sizeof(base->buff));
	   static socklen_t SenderAddrSize=sizeof(base->ClientAddr);
	   int n=recvfrom(base->ServerSocket,base->buff,
                     sizeof(base->buff), 0, (sockaddr *)&(base->ClientAddr), &SenderAddrSize);
     (base->buff)[n]='\0';
     std::string s=base->buff;
     std::cout<<s<<std::endl;
     QString s1=QString(QLatin1String(base->buff));
     QList<QString> lin=s1.split("\r\n");
     *(base->str_)=(*(lin.end()-2)).toStdString();

	}
} 
