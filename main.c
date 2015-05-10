#include "error_code.h"
//废弃
//#include "args_package.h"
#include "connection.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
//参数信息，本次比赛需要使用，因此作为全局变量
struct    ArgsPackage argsMsg;
//与牌桌建立的套接字
//主函数
int    main(   int    args,   char    **argv){
     if   (args!=6){  //调试时使用
       perror   (   "参数错误"   );
       return    ARGS_NUM_ERROR;
     }
     //开始
     conServer(args);
	 char msg[MAXLENGTH];
     while   (1){
		 getMsg(msg);
       //判断是否结束
       if   (-1==explMsg(msg))
         break   ;
     }
     //结束，关闭套接子
     close(sock);
     return    0;
}