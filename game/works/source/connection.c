#include "connection.h"
#include "my_types.h"
#include "error_code.h"
#include "ai.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
char  actions[5][8]= { "check \n" ,  "call \n" ,  "raise" ,  "all_in \n" ,  "fold \n" };

//全局socket
int sock;

//全局变量
Round roundData;

int explMsg(char *msg) {
    RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    //空串
    if (strlen(msg)<2)
    {
        LOG2F(filename,"SUCCESS EXPLMSG!!!");
        return  0;
    }
    char type[10];
    //用于临时信息（通常被丢弃）
    char temp[MAXLENGTH];
    char *p = strtok (msg,"\n");
    sscanf (p,"%s",type);
    p=p + strlen(p) + 1;//移除以处理过的消息
    RU(sprintf(temp,"TYPE:%s",type););
    LOG2F(filename,temp);
    if(strcmp(type,"seat/")==0) { //座次消息
        LOG2F(filename,"SEAT!!!");
        //初始化信息
        roundData.gameStep = STEP_ZERO;
        roundData.buttonId=0;
        roundData.buttonIndex=0;
        roundData.pubCardNum=0;
        //其他玩家信息清空
        memset(roundData.player,0, sizeof(Player)*NUM_PLAYER);
        //公共牌清空
        memset(roundData.pubCard,0, sizeof(Card)*5);
        roundData.selfIndex=0;
        roundData.blind=0;
        roundData.poolSum=0;
        //获取庄家信息，存入位置0
        p = strtok(p, "\n" );//得到一行消息
        sscanf(p,"%s%d%d%d",temp,&roundData.player[0].ID,&roundData.player[0].jetton,&roundData.player[0].money);
        roundData.player[0].isLive = true;
        p = p + strlen(p) + 1;
        //小盲注玩家信息
        p = strtok(p,"\n");
        sscanf(p,"%s%s%d%d%d",temp,temp,&roundData.player[1].ID,&roundData.player[1].jetton,&roundData.player[1].money);
        p = p + strlen(p) + 1;
        roundData.player[1].isLive = true;
        //判断是否有大盲注玩家

        int num = 2;
        sscanf(p,"%s",temp);
        if (strcmp(temp, "big" )==0) {
            p = strtok (p,"\n");
            sscanf (p,"%s%s%d%d%d",temp,temp,&roundData.player[num].ID,&roundData.player[num].jetton,&roundData.player[num].money);
            roundData.player[num].isLive = true;
            ++num;
            p = p + strlen(p)+1;
        }
        //所有玩家信息
        while (1) {
            p = strtok (p,"\n");
            sscanf (p,"%s",temp);
            if ( strcmp(temp, "/seat")==0)
            {
                p = p+strlen(p)+1;
                break ;
            }
            sscanf(p,"%d%d%d",&roundData.player[num].ID,&roundData.player[num].jetton,&roundData.player[num].money);
            roundData.player[num].isLive = true;
            ++num;
            p = p + strlen(p) + 1;
        }
        roundData.selfIndex = findIndex(argsMsg.ID);
        //玩家数量
        roundData.playerNum=num;
        //局数+1
        ++roundData.roundNums;
        //公共牌为0
        roundData.pubCardNum=0;
        LOG2F(filename,"SEAT OVER!!!");
    } else  if ( strcmp (type, "game-over" )==0) { //游戏结束消息
        LOG2F(filename,"GAME_OVER!!!");
        return -1;
    } else  if ( strcmp (type, "blind/" )==0) { //盲注消息
        LOG2F(filename,"BLIND!!!");
        roundData.gameStep = STEP_ZERO;
        while(1)
        {
            p = strtok(p, "\n" );
            sscanf (p,"%s",temp);
            if(strcmp(temp,"/blind")==0)
            {
                p = p + strlen (p)+1;//将信息指向下一行
                break;
            }
            int id,bet;
            sscanf(p,"%d: %d",&id,&bet);
            id = findIndex(id);
            roundData.player[id].bet = bet;
            roundData.player[id].jetton -= bet;//筹码减少
            p = p + strlen (p)+1;
        }
        LOG2F(filename,"BLIND OVER!!!");
    } else  if ( strcmp (type, "hold/" )==0) { //手牌消息
        LOG2F(filename,"HOLD!!!");
        roundData.gameStep = STEP_ONE;
        int selfIndex = roundData.selfIndex;
        for(int i=0; i<2; i++) {
            p = strtok(p, "\n" );
            char color[10],point[5];
            sscanf(p,"%s%s",color,point);
            roundData.player[selfIndex].handCard[i].color = findColor(color);
            roundData.player[selfIndex].handCard[i].point = findPoint(point);
            p = p + strlen (p)+1;
        }
        p = strtok(p, "\n" );//除去最后的结束标志
        p = p + strlen (p)+1;
        LOG2F(filename,"HOLD OVER!!!");
    } else  if ( strcmp (type, "inquire/" )==0) { //询问消息
        LOG2F(filename,"INQUIRE!!!");
        while(1)
        {
            p = strtok(p, "\n" );
            sscanf (p,"%s",temp);
            if(strcmp(temp,"total")==0) break;
            int id,je,mo,bet;
            char action[20];	//本手牌已行动过的所有玩家（包括被询问者和盲注）的id,手中筹码、剩余金币数、本手牌累计投注额、及最近的一次有效action，按逆时针座次由近及远排列，上家排在第一个
            sscanf(p,"%d%d%d%d%s",&id,&je,&mo,&bet,action);
            id = findIndex(id);
            roundData.player[id].jetton = je;
            roundData.player[id].money = mo;
            roundData.player[id].bet = bet;
            roundData.player[id].action = findAction(action);
            if(roundData.player[id].action==FOLD) roundData.player[id].isLive=false;
            p = p + strlen (p)+1;
        }
        p = strtok(p, "\n" );
        sscanf(p,"total pot: %d ",&roundData.poolSum);
        p = p + strlen (p)+1;
        p = strtok(p, "\n" );//除去最后的结束标志
        p = p + strlen (p)+1;

        /*

        此处接入AI算法

        */
        /*random
        if(roundData.player[roundData.selfIndex].isLive==true)
        {
            srand(time(0));
            int t = rand()%5;
            sprintf(temp,"RANDOM:%d!",t);
            LOG2F(filename,temp);
            sendMsg(t,roundData.blind);
            if(t==FOLD) roundData.player[roundData.selfIndex].isLive = false;
        }*/
        /*FOLD
        if(roundData.player[roundData.selfIndex].isLive==true)
        {
            int nums=0;
            for(int i=0;i<8;i++)
            {
                if(roundData.player[i].isLive==true) nums++;
            }
            if(nums==1) sendMsg(ALL_IN,0);
            else {sendMsg(FOLD,0);roundData.player[roundData.selfIndex].isLive=false;}
        }*/
        /*ALL_IN*/
        sendMsg(ALL_IN,0);
        LOG2F(filename,"INQUIRE OVER");

    } else  if ( strcmp (type, "flop/" )==0) { //公牌消息
        LOG2F(filename,"FLOP!!!");
        roundData.gameStep = STEP_TWO;
        roundData.pubCardNum=3;
        for(int i=0; i<3; i++) {
            char color[10],point[5];
            p = strtok(p, "\n" );
            sscanf(p,"%s%s",color,point);
            roundData.pubCard[i].color = findColor(color);
            roundData.pubCard[i].point = findPoint(point);
            p = p + strlen (p)+1;
        }
        p = strtok(p, "\n" );//除去最后的结束标志
        p = p + strlen (p)+1;
        LOG2F(filename,"FLOP OVER!!!");
    } else  if ( strcmp (type, "turn/" )==0) { //转牌消息
        LOG2F(filename,"TURN!!!");
        roundData.gameStep = STEP_THREE;
        roundData.pubCardNum=4;
        char color[10],point[5];
        p = strtok(p, "\n" );
        sscanf(p,"%s%s",color,point);
        roundData.pubCard[3].color = findColor(color);
        roundData.pubCard[3].point = findPoint(point);
        p = p + strlen (p)+1;
        p = strtok(p, "\n" );//除去最后的结束标志
        p = p + strlen (p)+1;
        LOG2F(filename,"TURN OVER!!!");
    } else  if ( strcmp (type, "river/" )==0) { //河牌消息
	LOG2F(filename,"RIVER!!!");
	LOG2F(filename,p);
        roundData.gameStep = STEP_FOUR;
        roundData.pubCardNum=5;
        char color[10],point[5];
        p = strtok(p, "\n" );
        sscanf(p,"%s%s",color,point);
        roundData.pubCard[4].color = findColor(color);
        roundData.pubCard[4].point = findPoint(point);
        p = p + strlen (p)+1;
        p = strtok(p, "\n" );//除去最后的结束标志
        p = p + strlen (p)+1;
	LOG2F(filename,"RIVER OVER!!!");
    } else  if ( strcmp (type, "showdown/" )==0) { //摊牌消息
	LOG2F(filename,"SHOWDOWN!!!");
        roundData.gameStep = STEP_FIVE;
        p = strtok(p,"\n" );
        sscanf(p,"%s",temp);
        p = p + strlen(p)+1;
        if(strcmp(temp,"common/")==0)//处理5张公共牌
        {
            for(int i=0; i<6; i++)
            {
                p = strtok(p, "\n" );
                p = p + strlen(p)+1;
            }
        }
        while(1)
        {
            p = strtok(p, "\n" );
            sscanf (p,"%s",temp);
            if(strcmp(temp,"/showdown")==0)
            {
                p = p+strlen(p)+1;
                break;
            }
            int id;
            char color[2][4],point[2][5],nut[20];
            sscanf(p,"rank: %d%s%c%s%c%s",&id,color[0],point[0],color[1],point[1],nut);
            id = findIndex(id);
            roundData.player[id].handCard[0].color = findColor(color[0]);//剩余玩家的2张手牌
            roundData.player[id].handCard[1].color = findColor(color[1]);
            roundData.player[id].handCard[0].point = findPoint(point[0]);
            roundData.player[id].handCard[1].point = findPoint(point[1]);
            roundData.player[id].bestType = findType(nut);//玩家最佳牌型
            p = p+strlen(p)+1;
        }
	LOG2F(filename,"SHOWDOWN OVER!!!");
    } else  if ( strcmp (type, "pot-win/" )==0) { //彩池分配消息
	LOG2F(filename,"POT_WIN!!!");
        int num;
        roundData.gameStep = STEP_FIVE;
        //所有玩家信息
        while (1)
        {
            p = strtok(p, "\n" );
            sscanf (p, "%s" ,temp);
            if ( strcmp(temp, "/pot-win" )==0)
            {
                p = p+strlen(p)+1;
                break ;
            }
            int id;
            sscanf (p, "%d: %d" ,&id,&num);
            if(id == roundData.selfIndex) roundData.player[id].jetton+=num;
            else
            {
                id = findIndex(id);
                roundData.player[id].jetton+=num;
            }
            p=p + strlen (p)+1;
        }
        //玩家数量
        roundData.playerNum=num;
	LOG2F(filename,"POT_WIN OVER!!!");
    } else
    {
        p = strtok(p, "\n" );
        p=p + strlen (p)+1;
        LOG2F(filename,"OTHER INFO!!!");
        LOG2F(filename,p);
        LOG2F(filename,"OTHER INFO OVER!!!");
    }
    //防止粘包
    LOG2F(filename,"\n\nOTHERRRRRRRRRRRRRRRRRRRRR");
    LOG2F(filename,p);
    LOG2F(filename,"OTHERENDDDDDDDDDDDDDDDDDDD\n\n");
    return  explMsg(p);
}


int conServer(char ** argv)
{
    //处理argv信息
    //字符串赋值
    strcpy(argsMsg.serverIP,argv[1]);
    sscanf(argv[2],"%hd",&argsMsg.serverPort);
    strcpy (argsMsg.localIP,argv[3]);
    sscanf(argv[4],"%hd",&argsMsg.localPort);
    sscanf(argv[5],"%d",&argsMsg.ID);
    RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    if(-1==(sock=socket(AF_INET,SOCK_STREAM,0))) { //定义socket，使用TCP连接
        LOG2F(filename,"FAIL SOCKET!!!");
        return SOCK_ERROR;
    }

    //设置本机的绑定地址
    struct sockaddr_in clentAddr;
    clentAddr.sin_family=AF_INET;
    clentAddr.sin_port=htons(argsMsg.localPort);
     int flag=1,len=sizeof(int);
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,  &flag, len) == -1)
    {
        LOG2F(filename,"FAILE setsockopt!!!");
        return ADDR_ERROR;
    }
    if(inet_pton(AF_INET,argsMsg.localIP,&clentAddr.sin_addr)<=0) { //将“点分十进制” －> “二进制整数”
        LOG2F(filename,"FAILE ADDLOCK!!!");
        return ADDR_ERROR;
    }
    //bind
    bind(sock,(struct sockaddr*)&clentAddr,sizeof(struct sockaddr));
    //设置地址信息
    struct sockaddr_in serverAddr;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(argsMsg.serverPort);
    if(inet_pton(AF_INET,argsMsg.serverIP,&serverAddr.sin_addr)<=0) { //将“点分十进制” －> “二进制整数”
        LOG2F(filename,"FAIL ADD!!!");
        return ADDR_ERROR;
    }
    //连接服务器
    while(connect(sock,(struct sockaddr*)&serverAddr,sizeof(struct sockaddr))<0) {
        RU(static int times=0; char c[100];
           sprintf(c,"FAIL CONNECT!!!:%d",times);
           ++times;);
        LOG2F(filename,c);
    }
    LOG2F(filename,"SUCCESS CONNECT!!!");
    char c[100];
    sprintf(c,"reg: %s %s \n",argv[5],"Shader");
    if(-1 == send(sock,c,strlen(c),0))
        LOG2F(filename,"SEND ERROR!!!");
    LOG2F(filename,"SUCCESS REG!!!");
    return SUCCESS;
}
int getMsg(char*msg )
{
    RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    int rec_len;
    if((rec_len = recv(sock, msg, MAXLENGTH,0)) == -1) {
        LOG2F(filename,"FAIL RECV!!!");
        return RECV_ERROR;
    }
    LOG2F(filename,"RECV SUCCESS!!!");
    RU(char temp[MAXLENGTH];sprintf(temp,"STARTTTTTTTTTTTTTTTTT\n\nRECV MSG IS:%sENDDDDDDDDDDDDDDDDD\n\n",msg););
    LOG2F(filename,temp);
    return SUCCESS;
}

int sendMsg(int actMsg, int addChip)
{
    RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    char raise[MAXLENGTH];
    if (RAISE != actMsg)
    {
        if(-1 == send(sock,actions[actMsg],strlen(actions[actMsg]),0))
            LOG2F(filename,"FAIL ERROR!!!");
    }
    else
    {
        sprintf(raise,"%s %d \n",actions[actMsg],addChip);
        if(-1 == send(sock,raise,strlen(raise),0))
            LOG2F(filename,"FAILE ERROR");
        return SEND_ERROR;
    }

    return SUCCESS;
}

void closeSocket()
{
    close(sock);
}

int findIndex(int id)
{
    for(int i=0; i<NUM_PLAYER; i++)
    {
        if(roundData.player[i].ID==id)
        {
            return i;
        }
    }
    return -1;
}
unsigned char findColor(char *color)
{
    unsigned char c=0;
    if(strcmp(color,"SPADES")==0) c = SPADES;
    else if(strcmp(color,"HEARTS")==0) c=HEARTS;
    else if(strcmp(color,"CLUBS")==0) c=CLUBS;
    else if(strcmp(color,"DIAMONDS")==0) c=DIAMONDS;
    return c;

}
unsigned char findPoint(char* point)
{
    unsigned char p=0;
    if(strcmp(point,"2")==0)p=2;
    else if(strcmp(point,"3")==0)p=3;
    else if(strcmp(point,"4")==0)p=4;
    else if(strcmp(point,"5")==0)p=5;
    else if(strcmp(point,"6")==0)p=6;
    else if(strcmp(point,"7")==0)p=7;
    else if(strcmp(point,"8")==0)p=8;
    else if(strcmp(point,"9")==0)p=9;
    else if(strcmp(point,"10")==0)p=10;
    else if(strcmp(point,"J")==0)p=11;
    else if(strcmp(point,"Q")==0)p=12;
    else if(strcmp(point,"K")==0)p=13;
    else if(strcmp(point,"A")==0)p=14;
    return p;
}
int findType(char *type)
{
    int t=0;
    if(strcmp(type,"HIGH_CARD")==0) t = HIGH_CARD;
    else if(strcmp(type,"ONE_PAIR")==0) t=ONE_PAIR;
    else if(strcmp(type,"TWO_PAIR")==0) t=TWO_PAIR;
    else if(strcmp(type,"THREE_OF_A_KIND")==0) t=THREE_OF_A_KIND;
    else if(strcmp(type,"STRAIGHT")==0) t=STRAIGHT;
    else if(strcmp(type,"FLUSH")==0) t=FLUSH;
    else if(strcmp(type,"FULL_HOUSE")==0) t=FULL_HOUSE;
    else if(strcmp(type,"FOUR_OF_A_KIND")==0) t=FOUR_OF_A_KIND;
    else if(strcmp(type,"STRAIGHT_FLUSH")==0) t=STRAIGHT_FLUSH;
    return t;
}
int findAction(char *action)
{
    int a=0;
    if(strcmp(action,"check")==0) a = CHECK;
    else if(strcmp(action,"call")==0) a=CALL;
    else if(strcmp(action,"raise")==0) a=RAISE;
    else if(strcmp(action,"all_in")==0) a=ALL_IN;
    else if(strcmp(action,"fold")==0) a=FOLD;
    return a;
}
