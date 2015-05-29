/*相关数据类型*/
#ifndef MY_TYPES_H_
#define MY_TYPES_H_
#include <stdbool.h>
#include "my_define.h"
/*命令行参数包*/
typedef struct {
    //牌桌IP
    char serverIP[16];
    //牌桌端口号
    unsigned short serverPort;
    //牌手IP
    char localIP[16];
    //牌手端口号
    unsigned short localPort;
    //牌手ID
    int ID;
    //各个花色个数
    int colorNum[4];
    //已发的数字个数 从1到14
    int pointNum[15];
} ArgsPackage;

/*牌信息*/
typedef struct {
    //花色
    unsigned char color;
    //点数
    unsigned char point;
} Card;


/*牌手信息*/
typedef struct {
    //ID
    int ID;
    //剩余金钱
    int money;
    //手中筹码
    int jetton;
    //已下赌注
    int bet;
    //是否live true为live
    bool isLive;

    //最佳牌型
    int bestType;
    //本轮下注
    int roundBet;
    //手牌列表
    Card handCard[2];
    //获胜局数
    int winNum;
    //最近行动
    unsigned char action;
    //所有手牌时的行动
    unsigned char actionHand[20];
    int topHand;

} Player;

typedef struct
{

    int ID;
    int type;
    int allin;
    int fold;
    int raise;
    int call;
} TypePlayer;
/**全局信息*/
typedef struct {
    //用户名
    char pname[32];
    //当前进行的局数
    unsigned int roundNums;
    //当前局的人数
    unsigned int playerNum;
    //庄家ID
    int buttonId;
    //庄家下标（下标轮转）
    int buttonIndex;
    //
    int bigBlindID;
    int smallBlindID;
    //公共牌数量取0，3，4，5
    int pubCardNum;
    //公共牌信息
    Card pubCard[5];
    //选手信息（包括自己，便于解析）
    Player player[NUM_PLAYER];
    TypePlayer typePlayer[NUM_PLAYER];
    //玩家自己ID
    //int selfID;
    //玩家自己下标
    int selfIndex;
    //盲注,最小跟注
    int blind;
    int needBet;//最少要跟注
    //当前池底总金额
    int poolSum;
    //当前游戏阶段
    int gameStep;
    int stepNum;//当前阶段经历次数
    int raiseNum;
    int callNum;
    int noFoldNum;//非弃牌玩家数
    int tight;
    int attack;
} Round;

#endif
