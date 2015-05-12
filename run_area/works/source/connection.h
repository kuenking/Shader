/**
    通信相关函数
  */
#ifndef CONNECTION_H_
#define CONNECTION_H_
#include "my_types.h"
#include "my_define.h"
#include "debug_shader.h"
//声明参数包
extern   ArgsPackage argsMsg;
//声明套接字
extern int  sock;
/**
    初始化连接,连接服务器
    param conmsg 连接信息结构体
    @return 成功返回0,否则返回-1
  */
int  conServer(char **argv);

/**
    接收消息并转发
   @return -1 表示传递结束
  */
int  getMsg( /*char  *msg*/);

/**
      发送行动消息
      @param msg [in]待发送消息(见my_define.h定义)
      @param addChip需要增加的筹码(只有RAISE情况下生效);
   */
int sendMsg(int actMsg, int  addChip);

/**
    处理消息并转发
   @param msg [out]接收的消息
  */
int  explMsg( char * msg);

/*关闭套接字*/
void closeSocket();


//查找转换函数
int findIndex(int id);//下标
unsigned char findColor(char *color);//花色
unsigned char findPoint(char* point);//点数
int findType(char *type);//牌型
int findAction(char *action);//行动
#endif