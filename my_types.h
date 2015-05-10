/**
       相关数据类型
     */
#ifndef MY_TYPES_H_
#define MY_TYPES_H_
#include <stdbool.h>
/**
       命令行参数包
     */
struct     ArgsPackage{
      //牌桌IP
      char     serverIP[16];
      //牌桌端口号
      unsigned     short     serverPort;
      //牌手IP
      char     localIP[16];
      //牌手端口号
      unsigned     short     localPort;
      //牌手ID
      int     ID;
      //各个花色个数
      int    colorNum[4];
      //已发的数字个数 从1到13
      int    pointNum[14];
};
 
/**
       牌信息
     */
struct  Card{
      //花色
      unsigned     char    color;
      //点数
      unsigned     char     point;
};
 
 
/**
       其他牌手信息
     */
struct     OtherPlayer{
      //ID
      int     ID;
      //剩余金钱
      int     money;
      //获胜局数
      //int winNum;
      //筹码
      int     chip;
      //已下赌注
      int     bet;
      //最近行动
      unsigned   char   action;
      //所有行动
      unsigned   char   actionAll[20];
      //是否弃牌
      bool   ifDiscard;
};
 
/**
       自己信息
     */
struct  PersonMsg{
      //牌手ID
      int     ID;
      //用户名
      char     name[32];
      //金币
      int     money;
     //筹码
      int     chip;
      //已下赌注
      int     betAlready;
      //手牌列表
      struct     Card handCard[2];
      //本局下注
      int     Currbet;
      //本轮下注
      int     roundBet;
      //是否弃牌
      bool     ifDiscard;
};
 
 
/**
       全 局信息
     */
struct    Round{
       //当前进行的局数
   // unsigned   int   roundNums;
   //当前局的人数
   unsigned    int    playerNum;
   //庄家ID
   //int buttonId;
   //庄家下标为0
   /*
   //庄家下标
   int   buttonIndex;
   */
   //公共牌数量取3，4，5
   int pubCardNum;
   //公共牌信息
   struct   Card pubCard[5];
   //其他人牌信息（包括自己，便于解析）
   struct  OtherPlayer other[8];
   //自己的信息
   struct  PersonMsg self;
   //小盲注
   int  smallBlind;
};
 
#endif
