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
#define BLIND   5
extern char  actions[5][8];
//阶段
#define STEP_ZERO	 0	 //开始阶段 连接服务器 接收座次消息
#define STEP_ONE	 1	 //2张手牌阶段就是0张公共牌阶段
#define STEP_TWO	 2	 //三张公共牌阶段 接收前三张并处理
#define STEP_THREE	 3	 //四张公共牌阶段 接收第四张并处理
#define STEP_FOUR	 4   //五张公共牌阶段 接收第五张并处理
#define STEP_FIVE	 5	 //接收摊牌和彩池分配消息

#define MAXTYPE 500
//牌型
#define HIGH_CARD      	8
#define ONE_PAIR       	7
#define TWO_PAIR       	6
#define THREE_OF_A_KIND	5
#define FLUSH		3       //tonghua
#define STRAIGHT	4      //sunzi
#define FULL_HOUSE     	2
#define FOUR_OF_A_KIND	1
#define STRAIGHT_FLUSH	0

//玩家类型
#define TYPE_IGNORE         1//可忽略
#define TYPE_ALLIN          2//allin型
#define TYPE_TIGHT          3//紧
#define TYPE_ATTACK         4//大胆型

#endif
