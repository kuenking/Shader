#include "ai.h"
#include "connection.h"
#include <stdlib.h>
#include <math.h>
double sub[15][9]={
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{5.88,11.41,16.54,21.24,25.46,29.14,32.22,34.64,36.33},
	{5.39,10.48,15.26,19.67,23.7,27.29,30.4,33,35.03},
	{4.9,9.56,13.95,18.06,21.86,25.32,28.41,31.09,33.34},
	{4.41,8.62,12.63,16.42,19.96,23.24,26.23,28.92,31.29},
	{3.92,7.69,11.3,14.73,17.99,21.04,23.89,26.51,28.09},
	{3.43,6.74,9.94,13.01,15.95,18.74,21.38,23.87,26.19},
	{2.94,5.8,8.57,11.25,13.84,16.34,18.73,21.01,23.18},
	{2.45,4.84,7.18,9.46,11.68,13.84,15.93,17.95,19.9},
	{1.96,3.89,5.78,7.64,9.46,11.24,12.99,14.7,16.37},
	{1.47,2.92,4.36,5.77,7.17,8.56,9.92,11.27,12.59},
	{0.98,1.95,2.92,3.88,4.84,5.79,6.73,7.66,8.59},
	{0.49,0.98,1.47,1.96,2.44,2.93,3.42,3.91,4.39},
	{0,0,0,0,0,0,0,0,0}
};
double Ax[15][9]={
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{11.02,20.826,29.552,37.315,44.223,50.37,55.84,60.706,65.037},
	{10.041,19.073,27.199,34.509,41.085,47,52.322,57.109,61.416},
	{9.061,17.301,24.795,31.609,37.806,43.442,48.567,53.227,57.465},
	{8.082,15.51,22.338,28.615,34.384,39.687,44.561,49.041,53.16},
	{7.102,13.7,19.829,25.523,30.812,35.726,40.291,44.531,48.471},
	{6.122,11.87,17.266,22.331,27.086,31.55,35.741,39.675,43.369},
	{5.143,10.021,14.649,19.038,23.202,27.152,30.898,34.452,37.823},
	{4.163,8.153,11.977,15.642,19.154,22.52,25.745,28.837,31.799},
	{3.184,6.266,9.25,12.139,14.937,17.645,20.267,22.805,25.263},
	{2.204,4.36,6.468,8.529,10.545,12.517,14.445,16.331,18.175},
	{1.224,2.434,3.629,4.809,5.974,7.126,8.263,9.386,10.496},
	{0.245,0.489,0.733,0.976,1.219,1.46,1.702,1.942,2.183}
};

void ai() {
    switch(roundData.gameStep) {
    case STEP_ONE:
        stepOneAI();
        break;
    case STEP_TWO:
        stepTwoAI();
        break;
    case STEP_THREE:
        stepThreeAI();
        break;
    case STEP_FOUR:
        stepFourAI();
        break;
    default:
        break;
    }
}

int IsVeryStrong()
{

    if((point1 == point2 && point1>=12) || (point1+point2>=27))
    return 1;
    return 0;
}
int IsStrong()
{
    if((point1==point2 && point1>=9)||(point1+point2 >= 26) || (color1==color2 && point1+point2>=25))
    {
        return 1;
    }
    return 0;
}
int IsMid()
{
    if(point1+point2>=25 || (point1==14&&point2>=10))//AJo,AT,KQ
    {
        return 1;
    }
    return 0;
}
int IsLikeStrong()//强投机牌
{//88-22 / KJs k-10s,QJs,QTs,JTs,T9s
    if(point1==point2 ) return 1;
    if(color1==color2 && (point2>=10 || (point1>=10 && point2>=9))) return 1;
    return 0;
}
int IsBlend()
{//KJo,kTo,QJo,JTo / A9s-A2s,98s,87s
    if(point1==13 && (point2==11 || point2==10)) return 1;
    else if(point1==12 && point2==11) return 1;
    else if(point1 == 11 && point2==10) return 1;
    else if(color1==color2)
    {
        if(point1==14 && point2>=2) return 1;
        if(point1==9 && point2==8) return 1;
        if(point1==8 && point2 ==7) return 1;
    }
    return 0;
}
void stepOneAI() {
    point1=roundData.player[roundData.selfIndex].handCard[0].point;
    point2=roundData.player[roundData.selfIndex].handCard[1].point;
    color1=roundData.player[roundData.selfIndex].handCard[0].color;
    color2=roundData.player[roundData.selfIndex].handCard[1].color;
    //static bool flag=false;
    RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    RU(char c[200];sprintf(c,"@@@@@@point1:%d point2:%d@@@@@@@@",point1,point2););
    LOG2F(filename,c);
    double p=0.0f;//本手牌概率

    if(point1<point2)//保证point1>point2
    {
        point1 = point1^point2;
        point2 = point1^point2;
        point1 = point1^point2;
    }
    RU(sprintf(c,"@@@@@@point1:%d point2:%d@@@@@@@@",point1,point2););
    LOG2F(filename,c);
    if(point1 == point2 ){
      //不算自身
      p = sub[point1][roundData.playerNum-1];
    }else{
      if(point1 == 14){
        p = Ax[point2][roundData.playerNum-1];
      }else if(color1==color2 && point1+point2>=24){
        p=3.02;
      }

    }
    RU(sprintf(c,"@@@@@@p:%f@@@@@@@@",p););
    LOG2F(filename,c);
    int selfIndex = roundData.selfIndex;
    int raiseMoney=0;
    if(p!=0)//计算加注
    {
        p=1-p/100;
        /*
          (所有-已下注)*胜率>=(已下注+将下注)*败率
          将下注<=((所有-已下注)*胜率)/败率-已下注
         */
        //raiseMoney = (p * roundData.poolSum-roundData.player[selfIndex].bet)/(1-p);//最大下注不会亏
        //raiseMoney=((roundData.poolSum-roundData.player[selfIndex].bet)*p-roundData.player[selfIndex].bet)/(1+p);//加注后总额
        raiseMoney = p*roundData.poolSum/(1+p);
        raiseMoney =( (int)((float)raiseMoney/roundData.blind+0.5))*roundData.blind;
        raiseMoney -= roundData.player[selfIndex].bet;
    }else raiseMoney = 0;
    RU(sprintf(c,"@@@@@@selfIndex:%d raiseMoney:%d@@@@@@@@",selfIndex,raiseMoney););
    LOG2F(filename,c);
    //条件
    int callNum=0,raiseNum=0,small=0,big=0;
    //最后一家下注
    int lastMoney=roundData.blind;
    if(selfIndex == roundData.smallBlindID) small=1;
    else if(selfIndex ==  roundData.bigBlindID) big=1;
    else{
      for(int i=0;i<selfIndex;i++){
          LOG2F(filename,"----iiii-------");
        if(roundData.player[i].action==CALL){
          ++callNum;
          lastMoney=roundData.player[i].roundBet;
        }
        if(roundData.player[i].action==RAISE || roundData.player[i].action==ALL_IN){
          ++raiseNum;
          lastMoney=roundData.player[i].roundBet;
        }
      }
    }
    srand(time(0));
    //判断
    raiseMoney -= lastMoney;
    int mul = roundData.player[selfIndex].jetton / lastMoney;//手中筹码是下注额的倍数
    int mulBlind = roundData.player[selfIndex].jetton/roundData.blind;//手中筹码是盲注的倍数
    int mid = (roundData.playerNum-2)/2;
    int action = FOLD;
    LOG2F(filename,"判断-------");
    if(IsVeryStrong()){
      LOG2F(filename,"VeryStrong");
      //加注是指在之前玩家的基础上
      action = RAISE;
      raiseMoney = (rand()%3+2)*roundData.blind;
      raiseMoney -= roundData.player[selfIndex].bet;
      if(raiseMoney <=0 ) action = CALL;
    }else if(IsStrong()){
      LOG2F(filename,"Strong");
      if(raiseNum >= 2 && (raiseMoney<=0 || roundData.playerNum>=4)) action = FOLD;
      else if(raiseNum>=2) action = CALL;
      else if(raiseNum==1 && callNum >=1 ) action = CALL;
      else if(big==1 || small==1 || roundData.playerNum<4 || selfIndex<= 2) action = RAISE;
      else if(raiseNum == 1 && callNum==0 && roundData.playerNum>=4) action = FOLD;
      else action = RAISE;
      raiseMoney -= roundData.player[selfIndex].bet;
      if((action == CALL || action == RAISE) && raiseMoney <0 && mul<=5) action = FOLD;
      if(mulBlind < 5) action = ALL_IN;
    }else if(IsMid()){
      LOG2F(filename,"Mid");


      if(raiseNum==0){
        if(small == 0 && big==0 && selfIndex<=mid ) action = FOLD;
        else action = RAISE;
      }
      else if(raiseNum==1 && callNum==0){
        if(big==1) action = CALL;
        else if(roundData.playerNum>5) action=FOLD;
        else action = CALL;
      }else if(raiseNum==1 && callNum>0){
        if(big==1 || (color1==color2 && point1==13 && point2==12)) action = CALL;
        else action = FOLD;
      }
      else action = FOLD;
      if(roundData.playerNum <= 4 && action == FOLD ) action = CALL;
      if((action == CALL || action == RAISE) && raiseMoney <0 && mul<5) action = FOLD;


      if(mulBlind < 5) action = ALL_IN;
    }else if(IsLikeStrong()){//强投机牌 //88-22 / KJs k-10s,QJs,QTs,JTs,T9s
      LOG2F(filename,"LikeStrong");
      if(callNum==0 && raiseNum==0){ //全弃牌
        if(big==1 || small==1 || selfIndex>4) action = RAISE;
        else action = FOLD;
      }else if(raiseNum==0 && callNum>=1){
        if(big==1) action = CHECK;
        else action = CALL;
      }else if(raiseNum==1 && callNum>=0){
        if(big==1 ) action = CALL;
        else action = FOLD;
      }else action = FOLD;

      if(action==FOLD && roundData.playerNum<=4) action = CALL;
      if((action == CALL || action == RAISE) && raiseMoney <0 && mul<5) action = FOLD;

      if(mulBlind < 5) action = ALL_IN;
    }else if(IsBlend()){//混合牌 //KJo,kTo,QJo,JTo / A9s-A2s,98s,87s
      LOG2F(filename,"Blend");
      if(callNum==0 && raiseNum==0) {//全弃牌
        if(big==1 || small==1 || selfIndex>6) action = RAISE;
        else action = FOLD;
      }else if(raiseNum==0 && callNum==1){ //一个玩家跟注
        if(big==1) action = CHECK;
        else if(small==1) sendMsg(CALL,0);
        else action = FOLD;
      }else if(raiseNum==0 && callNum>1) {
        if(big==1) action = CHECK;
        else if(small==1 && selfIndex>6)action = CALL;
        else action = FOLD;
      }
      else action = FOLD;


      if(action==FOLD && roundData.playerNum<=4) action = CALL;
      if((action == CALL || action == RAISE) && raiseMoney <0 && mul<5) action = FOLD;

      if(mulBlind < 5) action = ALL_IN;
    }else{
      LOG2F(filename,"GAOPAI");
      action = FOLD;
    }
    RU(sprintf(c,"@@@@@@action:%d lastMoney:%d@@@@@@@@",action,lastMoney););
    LOG2F(filename,c);
    roundData.stepNum+=1;
    sendMsg(action,raiseMoney);
    LOG2F(filename,"AI_1 OVER!!!!!");
}

/*判断牌型*/
int cardStyle(){
  //同花
  int sameColor = 0;
  for(int i=0;i<4;i++)
  if(argsMsg.colorNum[i]>=5) sameColor = 1;

  //判对子 3条 金刚 顺子
  int twoPairNum=0;//2同
  int threePairNum=0;//3同
  int kingKong=0;//4同
  int maxp=0;//最大的对子
  int link=0;//顺子
  for(int i=2;i<15;i++)
    {
        if(argsMsg.pointNum[i]==2) {++twoPairNum; maxp=i;}
        else if(argsMsg.pointNum[i]==3) threePairNum++;
        else if(argsMsg.pointNum[i]==4) kingKong++;
        if(i<11 && argsMsg.pointNum[i]+argsMsg.pointNum[i+1]+argsMsg.pointNum[i+2]+argsMsg.pointNum[i+3]+argsMsg.pointNum[i+4]==5) link=1;
    }
    if(argsMsg.pointNum[1]+argsMsg.pointNum[2]+argsMsg.pointNum[3]+argsMsg.pointNum[4]+argsMsg.pointNum[14]==5) link=1;

  if(sameColor){
    if(link){
      //同花顺
      return STRAIGHT_FLUSH;
    }else{
      //同花
      return STRAIGHT;
    }
  }
  if(link){
    //顺子
    return FLUSH;
  }
  if(kingKong){
    return FOUR_OF_A_KIND;
  }
  if(threePairNum>0 && twoPairNum>0){
      return FULL_HOUSE;
    }
  if(threePairNum>0){
      return THREE_OF_A_KIND;
    }
  if(twoPairNum>0){
    return TWO_PAIR;
  }

  return HIGH_CARD;
}


void stepTwoAI(){
  int myCardStyle=cardStyle();
  static bool flag=true;
  if(myCardStyle==STRAIGHT_FLUSH){
    sendMsg(ALL_IN,0);
  }else if(myCardStyle==FOUR_OF_A_KIND){
    sendMsg(ALL_IN,0);
  }else if(myCardStyle==FULL_HOUSE){
    if(flag){
      sendMsg(RAISE,roundData.player[roundData.selfIndex].jetton/2);
      flag=false;
    }else{
      sendMsg(CALL,0);
      flag=true;
    }
  }else if(myCardStyle==FLUSH){
    if(flag){
      sendMsg(RAISE,roundData.player[roundData.selfIndex].jetton/3);
      flag=false;
    }else{
      sendMsg(CALL,0);
      flag=true;
    }
  }else if(myCardStyle==STRAIGHT){
    if(flag){
      sendMsg(RAISE,roundData.player[roundData.selfIndex].jetton/4);
      flag=false;
    }else{
      sendMsg(CALL,0);
      flag=true;
    }
  }else if(myCardStyle==THREE_OF_A_KIND){
    if(flag){
      sendMsg(RAISE,roundData.player[roundData.selfIndex].jetton/5);
      flag=false;
    }else{
      sendMsg(CALL,0);
      flag=true;
    }
  }else if(myCardStyle==TWO_PAIR){
    if(flag){
      sendMsg(RAISE,roundData.player[roundData.selfIndex].jetton/10);
      flag=false;
    }else{
      sendMsg(CALL,0);
      flag=true;
    }
  }else if(myCardStyle==ONE_PAIR){
    sendMsg(CALL,0);
  }else{
    int point[2];
    point[0]=roundData.player[roundData.selfIndex].handCard[0].point;
    point[1]=roundData.player[roundData.selfIndex].handCard[1].point;
    if(point[0]+point[1]>=20){
      sendMsg(CALL,0);
    }else{
      sendMsg(FOLD,0);
    }
  }
}

void stepThreeAI(){
  stepTwoAI();
}

void stepFourAI(){
  stepTwoAI();
}
