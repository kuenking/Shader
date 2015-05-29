#ifndef AI_H_
#define AI_H_
#include "debug_shader.h"
#include "error_code.h"
#include "my_types.h"
#include "my_define.h"
extern Round roundData;
extern ArgsPackage argsMsg;
int point1;
int point2;
int color1;
int color2;

float sameColorP;//凑同花概率
float linkP;//凑顺子概率
int maxPairHand;//公共牌最大的单牌
int maxp;
int ggpType;//公共牌类心
int ggpsameColorNum;
int ggpsamePointNum;
//整体AI
void ai();
void ai_type();//计算玩家类型
//step AI
void stepOneAI();
void stepTwoAI();
void stepThreeAI();
void stepFourAI();
int findTypeIndex(int id);
#endif
