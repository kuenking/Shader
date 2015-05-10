#include "connection.h"
#include "my_types.h"
#include "error_code.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
//全局socket
int  sock;
 
//全局变量
struct  Round roundData;
 
int  explMsg( char * msg){
   //空串
   if ( strlen (msg)<8)
     return  0;
   char   type[10];
   char  *p= strtok (msg, "\n" );
   sscanf (p, "%s",type);
   p=p+ strlen (p)+1;
   if  (  strcmp  (type,  "seat/"  )==0){
     //其他玩家信息清空
     memset (roundData.other,0, sizeof ( roundData.other));
     //公共牌清空
     memset (roundData.pubCard,0, sizeof (roundData.pubCard));
     //用于临时信息（通常被丢弃）
     char  temp[32];
     //获取庄家信息，存入位置0
     p= strtok (p, "\n" );
     sscanf (p, "%s%d%d%d" ,temp,&roundData.other[0].ID,&roundData.other[0].chip,&roundData.other[0].money);
     //小盲注玩家信息
     p=p+ strlen (p)+1;
     p= strtok (p, "\n" );
     sscanf (p, "%s%s%d%d%d" ,temp,temp,&roundData.other[1].ID,&roundData.other[1].chip,&roundData.other[1].money);
     p=p+ strlen (p)+1;
     p= strtok (p, "\n" );
     //判断是否有大盲注玩家
     int  num=2;
     sscanf (p, "%s" ,temp);
     if ( strcmp (temp, "big" )==0){
       sscanf (p, "%s%s%d%d%d" ,temp,temp,&roundData.other[num].ID,&roundData.other[num].chip,&roundData.other[num].money);
       ++num;
       p=p+ strlen (p)+1;
       p= strtok (p, "\n" );
     }
     //所有玩家信息
     while (1){
       sscanf (p, "%s" ,temp);
       if ( strcmp (temp, "/seat" )==0)
         break ;
       sscanf (p, "%d%d%d" ,&roundData.other[num].ID,&roundData.other[num].chip,&roundData.other[num].money);
       ++num;
       p=p+ strlen (p)+1;
       p= strtok (p, "\n" );
     }
     //玩家数量
     roundData.playerNum=num;
     //局数+1
     // ++roundData.roundNums;
     //公共牌为0
     roundData.pubCardNum=empty;
     
   } else  if ( strcmp (type, "game-over" )==0){
		printf("游戏结束\n");
		return -1;
   } else  if ( strcmp (type, "blind/" )==0){
		
   } else  if ( strcmp (type, "hold/" )==0){
 
   } else  if ( strcmp (type, "inquire/" )==0){
 
   } else  if ( strcmp (type, "flop/" )==0){//公牌消息
		roundData.pubCardNum=3;
		for(int i=0;i<3;i++){
			p=p+ strlen (p)+1;
			char color[10],point;
			sscanf(p,"%s%c",color,&point);
			if(strcmp(color,"SPADES")==0) roundData.pubCard[i].color = SPADES;
			else if(strcmp(color,"HEARTS")==0) roundData.pubCard[i].color=HEARTS;
			else if(strcmp(color,"CLUBS")==0) roundData.pubCard[i].color=CLUBS;
			else if(strcmp(color,"DIAMONDS")==0) roundData.pubCard[i].color=DIAMONDS;
			if(point<='10')
			roundData.pubCard.point = point-'0';
			else if(point=='J') roundData.pubCard[i].point = 11;
			else if(point=='Q') roundData.pubCard[i].point = 12;
			else if(point=='K') roundData.pubCard[i].point = 13;
			else if(point=='A') roundData.pubCard[i].point = 14;
		}

   } else  if ( strcmp (type, "turn/" )==0){//转牌消息
		roundData.pubCardNum=4;
		p=p+ strlen (p)+1;
		char color[10],point;
		sscanf(p,"%s%c",color,&point);
		if(strcmp(color,"SPADES")==0) roundData.pubCard[3].color = SPADES;
		else if(strcmp(color,"HEARTS")==0) roundData.pubCard[3].color=HEARTS;
		else if(strcmp(color,"CLUBS")==0) roundData.pubCard[3].color=CLUBS;
		else if(strcmp(color,"DIAMONDS")==0) roundData.pubCard[3].color=DIAMONDS;
		if(point<='10')
		roundData.pubCard.point = point-'0';
		else if(point=='J') roundData.pubCard[3].point = 11;
		else if(point=='Q') roundData.pubCard[3].point = 12;
		else if(point=='K') roundData.pubCard[3].point = 13;
		else if(point=='A') roundData.pubCard[3].point = 14;

   } else  if ( strcmp (type, "river/" )==0){//河牌消息
		roundData.pubCardNum=5;
		p=p+ strlen (p)+1;
		char color[10],point;
		sscanf(p,"%s%c",color,&point);
		if(strcmp(color,"SPADES")==0) roundData.pubCard[4].color = SPADES;
		else if(strcmp(color,"HEARTS")==0) roundData.pubCard[4].color=HEARTS;
		else if(strcmp(color,"CLUBS")==0) roundData.pubCard[4].color=CLUBS;
		else if(strcmp(color,"DIAMONDS")==0) roundData.pubCard[4].color=DIAMONDS;
		if(point<='10')
		roundData.pubCard.point = point-'0';
		else if(point=='J') roundData.pubCard[4].point = 11;
		else if(point=='Q') roundData.pubCard[4].point = 12;
		else if(point=='K') roundData.pubCard[4].point = 13;
		else if(point=='A') roundData.pubCard[4].point = 14;
		
   } else  if ( strcmp (type, "showdown/" )==0){//摊牌消息
		p=p+ strlen (p)+1;
		
		
   } else  if ( strcmp (type, "pot-win/" )){//彩池分配消息
		p=p+ strlen (p)+1;
		 //所有玩家信息
		while (1){
		sscanf (p, "%s" ,temp);
		if ( strcmp (temp, "/pot-win" )==0)
			break ;
		int id,num;
		sscanf (p, "%d: %d" ,&id,&num);
		id = findIndex(id);
		if(id == self.ID) roundData.self.jetton+=num;
		else roundData.pubCard[id].jetton+=num;
		
		p=p+ strlen (p)+1;
		p= strtok (p, "\n" );
     }
     //玩家数量
     roundData.playerNum=num;
   }
	//防止粘包
     p=p+ strlen (p)+1;
     return  explMsg(p);
  // return  0;
}
 
 
 
int  conServer(  char  ** argv)
{
   if  (-1==(sock=socket(AF_INET,SOCK_STREAM,0))){  //定义socket，使用TCP连接
     perror   (   "套接字创建失败"   );
     return    SOCK_ERROR;
   }
   //处理argv信息
   //字符串赋值
   //argsMsg.serverIP = argv[1];
   strcpy (argsMsg.serverIP,argv[1]);
   sscanf  (argv[2],  "%u"  ,argsMsg.serverPort);
   //argsMsg.localIP = argv[3];
   strcpy (argsMsg.localIP,argv[3]);
   /*
     sscanf (argv[2], "%u" ,argsMsg.localPort);
     sscanf (argv[2], "%u" ,argsMsg.ID);
   */
   //设置地址信息
   struct    sockaddr_in serverAddr;
   serverAddr.sin_family=AF_INET;
   serverAddr.sin_port=htons(argsMsg.serverPort);
   if   (inet_pton(AF_INET,argsMsg.serverIP,&serverAddr.sin_addr)<=0){  //将“点分十进制” －> “二进制整数”
     perror   (   "地址信息错误"   );
     return    ADDR_ERROR;
   }
   //连接服务器
   if   (connect(sock,(   struct    sockaddr*)&serverAddr,   sizeof   (   struct    sockaddr))<0){
     perror   (   "连接失败"   );
     return    CONN_ERROR;
   }
   return   SUCCESS;
}
int   getMsg(   char   *msg )
{
   int  rec_len;
   if  ((rec_len = recv(sock, msg, MAXLENGTH,0)) == -1) {
     perror  (  "recv error"  );
     return   RECV_ERROR;
   }
}
int   sendMsg(   enum    action actMsg,    int    addChip)
{
   char    raise  [MAXLENGTH];
   if   (RAISE != actMsg)
     {
       if   (-1 == send(sock, actions[actMsg],    strlen   (actions[actMsg]), 0))
         perror   (   "send error\n"   );
     }    else
     {
       sprintf   (  raise  ,    "%s %d \n"   , actions[actMsg],addChip);
       if   (-1 == send(sock,    raise   ,    strlen   (   raise   ), 0))
         perror (   "send error\n"   );
       return   SEND_ERROR;
     }
   return   SUCCESS;
}
void closeSocket()
{
	close(sock);
}