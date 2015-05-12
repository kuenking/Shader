#ifndef MY_DEFINE_H_
#define MY_DEFINE_H_
/*存放各种宏定义*/
#define NUM_PLAYER 8   //其他玩家数量
#define MAXLENGTH 1024 //最大字符长度
//花色
#define SPADES     0   //黑桃
#define HEARTS     1   //红桃
#define CLUBS      2   //梅花
#define DIAMONDS   3   //方片
//行动 唯一需要小写的宏
#define CHECK		0
#define CALL		1
#define RAISE		2
#define ALL_IN		3
#define FOLD		4
extern char  actions[5][8];
//阶段
#define STEP_ZERO	 0	 //开始阶段 连接服务器 接收座次消息
#define STEP_ONE	 1	 //2张手牌阶段就是0张公共牌阶段
#define STEP_TWO	 2	 //三张公共牌阶段 接收前三张并处理
#define STEP_THREE	 3	 //四张公共牌阶段 接收第四张并处理
#define STEP_FOUR	 4   //五张公共牌阶段 接收第五张并处理
#define STEP_FIVE	 5	 //接收摊牌和彩池分配消息

//牌型
#define HIGH_CARD		1
#define ONE_PAIR		2
#define TWO_PAIR		3
#define THREE_OF_A_KIND	4
#define STRAIGHT		5
#define FLUSH			6
#define FULL_HOUSE		7
#define FOUR_OF_A_KIND	8
#define STRAIGHT_FLUSH	9


#endif