#include "ai.h"
#include "connection.h"
#include <stdlib.h>
#include <math.h>
double sub[15][9]= {
    {100,100,100,100,100,100,100,100,100},
    {100,100,100,100,100,100,100,100,100},
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
double Ax[15][9]= {
    {100,100,100,100,100,100,100,100,100},
    {100,100,100,100,100,100,100,100,100},
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


double pp[9][9]= {
    {0.000800333,0.00160066,0.00240098,0.00320129,0.0040016,0.0048019,0.0056022,0.00640248,0.00720277},
    {0.0140859,0.0281697,0.0422516,0.0563315,0.0704095,0.0844854,0.0985594,0.112631,0.126701},
    {0.101482,0.202861,0.304138,0.405311,0.506382,0.607351,0.708216,0.80898,0.909641},
    {0.278596,0.556416,0.833461,1.10974,1.38524,1.65998,1.93395,2.20716,2.4796},
    {0.584883,1.16635,1.74441,2.31909,2.89041,3.45839,4.02304,4.58439,5.14246},
    {1.88767,3.7397,5.55677,7.33954,9.08866,10.8048,12.4885,14.1404,15.7611},
    {5.45843,10.6189,15.4977,20.1102,24.4709,28.5936,32.4913,36.1762,39.66},
    {29.9044,50.8661,65.5593,75.8586,83.078,88.1384,91.6855,94.1719,95.9148},
    {75.9392,94.2108,98.6071,99.6648,99.9194,99.9806,99.9953,99.9989,99.9997}
};



void ai() {
    RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    RU(char c[200]; sprintf(c,"@@@@@@AI...... roundData.gameStep:%d@@@@@@@@",roundData.gameStep););
    // LOG2F(filename,c);
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

int IsVeryStrong(int point1,int point2)
{

    if((point1 == point2 && point1>=12) || (point1+point2>=27))
        return 1;
    return 0;
}
int IsStrong(int point1,int point2,int color1,int color2)
{
    if((point1==point2 && point1>=9)||(point1+point2 >= 26) || (color1==color2 && point1+point2>=25))
    {
        return 1;
    }
    return 0;
}
int IsMid(int point1,int point2)
{
    if(point1+point2>=25 || (point1==14&&point2>=10))//AJo,AT,KQ
    {
        return 1;
    }
    return 0;
}
int IsLikeStrong(int point1,int point2,int color1,int color2)//强投机牌
{   //88-22 / KJs k-10s,QJs,QTs,JTs,T9s
    if(point1==point2 ) return 1;
    if(color1==color2 && point2>=9) return 1;
    return 0;
}
int IsBlend(int point1,int point2,int color1,int color2)
{   //KJo,kTo,QJo,JTo / A9s-A2s,98s,87s
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
    RU(char c[200]; sprintf(c,"@@@@@@point1:%d point2:%d@@@@@@@@",point1,point2););
    // LOG2F(filename,c);
    double p=100.0f;//本手牌概率

    if(point1<point2)//保证point1>point2
    {
        point1 = point1^point2;
        point2 = point1^point2;
        point1 = point1^point2;
    }
    // RU(sprintf(c,"@@@@@@point1:%d point2:%d@@@@@@@@",point1,point2););
    //LOG2F(filename,c);
    if(point1 == point2 ) {
        //不算自身
        p = sub[point1][roundData.playerNum-1];
    } else {
        if(point1 == 14) {
            p = Ax[point2][roundData.playerNum-1];
        } else if(color1==color2 && point1+point2>=24) {
            p=3.02;
        }

    }
    RU(sprintf(c,"@@@@@@p:%f roundData.selfIndex:%d @@@@@@@@",p,roundData.selfIndex););
    LOG2F(filename,c);
    int selfIndex = roundData.selfIndex;
    int raiseMoney=0;
    //条件
    int callNum=0,raiseNum=0,small=0,big=0,tight=0,attack=0,noFoldNum=0;
    //最后一家下注
    int lastMoney=roundData.blind;

    if(selfIndex == roundData.smallBlindID) small=1;
    else if(selfIndex ==  roundData.bigBlindID) big=1;


    {
        callNum = roundData.callNum;
        raiseNum = roundData.raiseNum;
        tight = roundData.tight;
        attack = roundData.attack;
        lastMoney = roundData.needBet;
        noFoldNum = roundData.noFoldNum;
    }
    //判断
        p=1-p/100;
        /*
          (所有-已下注)*胜率>=(已下注+将下注)*败率
          将下注<=((所有-已下注)*胜率)/败率-已下注
         */
        //raiseMoney = (p * roundData.poolSum-roundData.player[selfIndex].bet)/(1-p);//最大下注不会亏
        raiseMoney=(roundData.poolSum-roundData.player[selfIndex].bet)*p/(1-p)-roundData.player[selfIndex].bet;//加注后总额
        //raiseMoney=((roundData.poolSum-roundData.player[selfIndex].bet)*p-roundData.player[selfIndex].bet)/(1+p);//加注后总额
        // raiseMoney = p*roundData.poolSum/(1+p);
        //  raiseMoney =( (int)((float)raiseMoney/roundData.blind+0.5))*roundData.blind;
        // raiseMoney -= roundData.player[selfIndex].bet;
    RU(sprintf(c,"@@@@@@selfIndex:%d raiseMoney:%d@@@@@@@@",selfIndex,raiseMoney););
    LOG2F(filename,c);

    srand(time(0));

    RU(sprintf(c,"@@@@@@blind:%d lastMoney:%d raiseMoney:%d playerNUm:%d raiseNum:%d callNum:%d @@@@@@@@",roundData.blind,lastMoney,raiseMoney,roundData.playerNum,raiseNum,callNum););
    LOG2F(filename,c);
    int mul = 0;
    if(lastMoney!=0) mul = roundData.player[selfIndex].jetton / lastMoney;//手中筹码是下注额的倍数
    int mulBlind = roundData.player[selfIndex].jetton/roundData.blind;//手中筹码是盲注的倍数
    int mid = (roundData.playerNum-2)/2;
    int action = FOLD;
    LOG2F(filename,"判断-------");
    raiseMoney -= lastMoney;
    if(IsVeryStrong(point1,point2)) {
        LOG2F(filename,"VeryStrong");
        //加注是指在之前玩家的基础上
        action = RAISE;
        raiseMoney = (rand()%3+2)*roundData.blind;
        raiseMoney -= roundData.player[selfIndex].bet;
        if(raiseMoney <=0 ) action = CALL;
    } else if(IsStrong(point1,point2,color1,color2)) {
        LOG2F(filename,"Strong");

        if(raiseNum >= 2) action = FOLD;
        else if(raiseNum==1 && callNum >=1) action = CALL;
        else if(big==1 || small==1 || roundData.playerNum<4 ) action = RAISE;
        else if(tight>0) action=FOLD;
        else if(raiseNum == 1 && callNum==0 && selfIndex<=mid)action = FOLD;
        else action = RAISE;
        //raiseMoney -= roundData.player[selfIndex].bet;
        if((action == CALL || action == RAISE) && raiseMoney <0 && mul<=5) action = FOLD;
        if(raiseMoney > roundData.blind*2) raiseMoney = roundData.blind*2; //最多2个大满主
        if(mulBlind < 5) action = ALL_IN;
    } else if(IsMid(point1,point2)) {

        LOG2F(filename,"Mid");

        if(raiseNum==0) {
            if(small == 0 && big==0 && selfIndex<=mid && noFoldNum!=0 ) action = FOLD;
            else action = RAISE;
        }
        else if(raiseNum==1 && callNum==0) {
            if(big==1) action = CALL;
            else if(attack==1) action=CALL;
            else if(roundData.playerNum>5) action=FOLD;
            else action = CALL;
        } else if(raiseNum==1 && callNum>0) {
            if(big==1 || (color1==color2 && point1==13 && point2==12)) action = CALL;
            else if(attack==(raiseNum+callNum)) action=CALL;
            else action = FOLD;
        }
        else action = FOLD;

        if(mul>=10 && action == FOLD ) action = CALL;

        if((action == CALL || action == RAISE) && raiseMoney <0 && mul<5) action = FOLD;

        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*(rand()%2+1); //最多2个大满主

        if(mulBlind <= 5)  action = ALL_IN;
    } else if(IsLikeStrong(point1,point2,color1,color2)) { //强投机牌 //88-22 / KJs k-10s,QJs,QTs,JTs,T9s
        LOG2F(filename,"LikeStrong");
        if(callNum==0 && raiseNum==0) { //全弃牌
            if(big==1 || small==1 || selfIndex>roundData.playerNum/2) action = RAISE;
            else if(noFoldNum==0) action=CALL;
            else action = FOLD;
        } else if(raiseNum==0 && callNum>=1) {
            if(big==1) action = CHECK;
            else if(small==1  || selfIndex>roundData.playerNum/2) action = CALL;
            else action = FOLD;
        } else if(raiseNum==1 && callNum>=0) {
            if(big==1 ) action = CALL;
            else if(attack==(raiseNum+callNum))action = CALL;
            else if(tight>0) action=FOLD;
            else action = FOLD;
        } else action = FOLD;
        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主
        // if(action==FOLD && roundData.playerNum<=4) action = CALL;
        if((action == CALL || action == RAISE) && raiseMoney <0 && mul<5) action = FOLD;

        if(mulBlind < 5) action = ALL_IN;
    } else if(IsBlend(point1,point2,color1,color2)) { //混合牌 //KJo,kTo,QJo,JTo / A9s-A2s,98s,87s
        LOG2F(filename,"Blend");


        if(callNum==0 && raiseNum==0) {//全弃牌
            if(big==1 || small==1 || selfIndex>roundData.playerNum/2) action = RAISE;
            else if(noFoldNum==0) action = CALL;
            else action = FOLD;
        } else if(raiseNum==0 && callNum>=1) { //一个玩家跟注
            if(big==1) action = CHECK;
            else if(small==1) action = CALL;
            else if(selfIndex<=roundData.playerNum/2) action = CHECK;
            else action = CALL;
        }


        if(mulBlind<=10 && lastMoney/roundData.blind<=2) {
            raiseMoney = roundData.blind;
            if(action == FOLD ) action = CALL;
        }

        if((action == CALL || action == RAISE) && raiseMoney <0) action = CHECK;
        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主
        if(mulBlind < 5) action = ALL_IN;
    } else {
        LOG2F(filename,"GAOPAI");
        raiseMoney -= roundData.player[selfIndex].bet;
        if(selfIndex>=roundData.playerNum/2 || roundData.playerNum<=4)
        {
            if(raiseNum==0 && raiseMoney>=0 ) action = CALL;
            else if(raiseMoney>0 && raiseNum+callNum == attack  ) action=CALL;
            else if(raiseNum+callNum<=2 && mul>=10) action = CALL;
            else if(mul>=50) action = CALL;
            else action = FOLD;
        }
        else if(big==1 && raiseNum==0) action = RAISE;
        else if(noFoldNum==0) action = RAISE;
        else if(roundData.player[selfIndex].handCard[0].point>12 || roundData.player[selfIndex].handCard[1].point>12)
        {
            if((float)lastMoney/roundData.poolSum<0.25) action = CALL;
            else action = CHECK;
        }
        else  action = CHECK;

        if(tight>0) action=FOLD;
        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主

    }
    RU(sprintf(c,"@@@@@@action:%d lastMoney:%d@@@@@@@@",action,lastMoney););
    LOG2F(filename,c);
    roundData.stepNum+=1;
    if(action==RAISE && raiseMoney<0) raiseMoney = 0;
    if(roundData.stepNum>2 && action == RAISE) action = CALL;
    if(action==FOLD && noFoldNum==0) action=CALL;
    sendMsg(action,raiseMoney);
    LOG2F(filename,"AI_1 OVER!!!!!");
}

/*判断牌型*/
int cardStyleTwo() {
    //同花
    int sameColor = 0;
    for(int i=0; i<4; i++)
     {
         if(argsMsg.colorNum[i]>=5) sameColor = 1;
         if(argsMsg.colorNum[i]==4) sameColorP = 4/9;
     }

    //判对子 3条 金刚 顺子
    int twoPairNum=0;//2同
    int threePairNum=0;//3同
    int kingKong=0;//4同
    int link=0;//顺子
    maxPairHand=0;
    for(int i=2; i<15; i++)
    {
        if(argsMsg.pointNum[i]==2) {
            ++twoPairNum;
            maxPairHand=i;
        }
        else if(argsMsg.pointNum[i]==3) threePairNum++;
        else if(argsMsg.pointNum[i]==4) kingKong++;
        if(i<11 && argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1 && argsMsg.pointNum[i+3]>=1 && argsMsg.pointNum[i+4]>=1) link=1;
    }
    if(argsMsg.pointNum[5]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1 && argsMsg.pointNum[4]>=1 && argsMsg.pointNum[14]>=1) link=1;
    linkP=0.0f;
    if(link==0)
    {
        for(int i=2; i<11; i++)
        {
            if(argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1 && argsMsg.pointNum[i+3]>=1) linkP=2;
        }
        if(argsMsg.pointNum[1]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1 && argsMsg.pointNum[4]>=1) linkP=1;
        if(argsMsg.pointNum[11]>=1 && argsMsg.pointNum[12]>=1 && argsMsg.pointNum[13]>=1 && argsMsg.pointNum[14]>=1) linkP=1;
    }
    linkP = linkP*4/47;


    maxp=0;
    int pointNum[15];
    for(int i=0;i<15;i++) pointNum[i] = 0;
    for(int i=0;i<3;++i){
        pointNum[roundData.pubCard[i].point]++;
        if(roundData.pubCard[i].point>maxp) maxp = roundData.pubCard[i].point;
    }

    ggpType=-1;
    for(int i=2;i<15;i++)
    {
        if(pointNum[i]==3)
        {
           ggpType = THREE_OF_A_KIND;
           break;
        }
        if(pointNum[i]==2)
        {
           ggpType = TWO_PAIR;
           break;
        }
        if(pointNum[i]==1)
        {
           ggpType = ONE_PAIR;
           break;
        }
    }
    if(ggpType==-1)
    {
        for(int i=2; i<13; i++)
        {
            if(argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1) ggpType = STRAIGHT;
        }
        if(argsMsg.pointNum[14]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1) ggpType=STRAIGHT;
        if(roundData.pubCard[0].color == roundData.pubCard[1].color && roundData.pubCard[0].color == roundData.pubCard[2].color)
        {
                if(ggpType == STRAIGHT) ggpType = STRAIGHT_FLUSH;
                else ggpType = FLUSH;
        }
    }


    if(sameColor && link)   //同花顺
           return STRAIGHT_FLUSH;
    if(kingKong) {
        return FOUR_OF_A_KIND;
    }
    if(threePairNum>0 && twoPairNum>0) {
        return FULL_HOUSE;
    }
    if(sameColor)   return STRAIGHT;

    if(link) {
        //顺子
        return FLUSH;
    }




    if(threePairNum>0) {
        return THREE_OF_A_KIND;
    }
    if(twoPairNum>=2) {
        return TWO_PAIR;
    }
    if(twoPairNum==1)
    {
        return ONE_PAIR;
    }

    return HIGH_CARD;
}



void stepTwoAI() {
    double p=100.0f;//本手牌概率
    int selfIndex = roundData.selfIndex;
    int raiseMoney=0;
    //条件
    int callNum=0,raiseNum=0,small=0,big=0,tight=0,attack=0,noFoldNum=0;
    //最后一家下注
    int lastMoney=roundData.blind;

    if(selfIndex == roundData.smallBlindID) small=1;
    else if(selfIndex ==  roundData.bigBlindID) big=1;
    {
        callNum = roundData.callNum;
        raiseNum = roundData.raiseNum;
        tight = roundData.tight;
        attack = roundData.attack;
        lastMoney = roundData.needBet;
        lastMoney -= roundData.player[selfIndex].bet;
        noFoldNum = roundData.noFoldNum;
    }

    int liveNum=0;
    for(int i=0; i<roundData.playerNum; ++i)
        if(roundData.player[i].isLive)
            ++liveNum;

    int myStyle=cardStyleTwo();
    p=pp[myStyle][liveNum-1];
    if(p!=0) {
        p=1-p/100;
        raiseMoney=(roundData.poolSum-roundData.player[selfIndex].bet)*p/(1-p)-roundData.player[selfIndex].bet;//加注后总额
    } else {
        raiseMoney=roundData.player[selfIndex].jetton;
    }
    srand(time(0));
    int mul = 0;
    if(lastMoney!=0) mul = roundData.player[selfIndex].jetton / lastMoney;//手中筹码是下注额的倍数
    int mulBlind = roundData.player[selfIndex].jetton/roundData.blind;//手中筹码是盲注的倍数
    int action = FOLD;
    raiseMoney -= roundData.player[selfIndex].bet;//减去自己已经下的注
    lastMoney -= roundData.player[selfIndex].bet;
    float poolHand = lastMoney / roundData.poolSum;//底池赔率
    poolHand = poolHand*1.2;
    if(myStyle<=1) {//同花顺和4同 不虚
        action = RAISE;
        raiseMoney = (rand()%3+2)*roundData.blind;
    } else if(myStyle==FULL_HOUSE) {//葫芦
        if(ggpType != THREE_OF_A_KIND)//不虚
        {
             action = RAISE;
             raiseMoney = (rand()%3+2)*roundData.blind;
        }else
        {
            int x = roundData.player[selfIndex].handCard[0].point;
            float xp = (14-x)*4/47 * ((14-x)*4-1)/46;
            xp = 1-xp;//银钱概率
            if(xp<poolHand && noFoldNum!=0) action = FOLD;
            else if(xp/poolHand < 1.2) action = CALL;
            else
            {
                action = RAISE;
                raiseMoney = raiseMoney > roundData.poolSum/2 ? roundData.poolSum/2:raiseMoney;
            }
        }
    } else if(myStyle==FLUSH || myStyle == STRAIGHT) {//同花 huo sunzhi

        if(roundData.player[selfIndex].handCard[0].point>=maxp||roundData.player[selfIndex].handCard[0].point>=maxp)
        {
                action = RAISE;
                raiseMoney = raiseMoney > roundData.poolSum/2 ? roundData.poolSum/2:raiseMoney;
        }
        else
        {
            if(raiseNum >= 2) action = FOLD;
            else action = CALL;
            if(poolHand<0.2 && action ==FOLD) action = CALL;
            if(raiseMoney > roundData.blind*2) raiseMoney = roundData.blind*2; //最多2个大满主
        }


        if(mulBlind <= 5)  action = ALL_IN;
    }else if(myStyle == THREE_OF_A_KIND)//3tiao
    {
        if(ggpType == THREE_OF_A_KIND)
        {
            if(roundData.player[selfIndex].handCard[0].point<12 && roundData.player[selfIndex].handCard[0].point<12)
            {
                if(noFoldNum==0) action=CALL;
                else action = FOLD;
            }
            else action = CALL;
        }
        else
        {
            action = RAISE;
            if(raiseMoney > roundData.blind*3) raiseMoney = roundData.blind*3; //最多2个大满主
        }
    }
    else if(myStyle== TWO_PAIR) {//2对
        if(ggpType==ONE_PAIR)
        {
            if(raiseNum>=2 || poolHand>0.2) action = FOLD;
            else if(raiseNum>0)
            {
                if(poolHand>0.25) action = FOLD;
                else action = CALL;
            }
            else action = RAISE;
            if(raiseMoney > roundData.blind) raiseMoney = roundData.blind; //最多2个大满主

        }else
        {
            action = RAISE;
            if(poolHand<0.25) raiseMoney = 0.5*roundData.poolSum;
        }

        if(mulBlind < 5) action = ALL_IN;
    } else if(myStyle==ONE_PAIR) { //1对
        if(ggpType == ONE_PAIR)
        {
            if(roundData.player[selfIndex].handCard[0].point>=maxp || roundData.player[selfIndex].handCard[0].point>=maxp)
            {
                if(raiseNum >= 3) action=FOLD;
                else
                {
                    if(rand()%2==0) action=CALL;
                    else action=RAISE;
                    if(raiseMoney > roundData.blind) raiseMoney = roundData.blind; //最多2个大满主
                }
            }
            else
            {
                if(poolHand<0.25) action = CALL;
                else action = FOLD;
                if(raiseNum >= 2) action=FOLD;

            }
        }else
        {
            if(maxPairHand >= maxp)
            {
                if(rand()%2==0) action=CALL;
                else action=RAISE;
                if(poolHand>0.2) action = CALL;
            }else
            {
                if(raiseNum>=2) action = FOLD;
                else action = CALL;
            }
        }

        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主
        if(mulBlind < 5) action = ALL_IN;
    } else {//高牌

        if(sameColorP>0 || linkP>0)
        {
            if(sameColorP>poolHand || linkP>poolHand)  action = CALL;
            else action = FOLD;
        }
        else if((roundData.player[selfIndex].handCard[0].point>=maxp || roundData.player[selfIndex].handCard[0].point>=maxp) && maxPairHand>=12)
        {
            if(ggpType == STRAIGHT || ggpType == FLUSH)
            {
                action = FOLD;
            }
            else action = CALL;
        }
        else
        {
            if(raiseNum ==0 || selfIndex==big ) action = CALL;
            else action = FOLD;
        }
        if(tight>0 && maxp>=12) action=FOLD;
        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主

    }
    roundData.stepNum+=1;
    if(action==RAISE && raiseMoney<0) raiseMoney = 0;
    if(roundData.stepNum>3 && action == RAISE) action = CALL;
    if(action==FOLD && noFoldNum==0) action==CALL;
    sendMsg(action,raiseMoney);
}



/*判断牌型*/
int cardStyleThree() {
    //同花
    int sameColor = 0;
    for(int i=0; i<4; i++)
     {
         if(argsMsg.colorNum[i]>=5) sameColor = 1;
         if(argsMsg.colorNum[i]==4) sameColorP = 2/9;
     }

    //判对子 3条 金刚 顺子
    int twoPairNum=0;//2同
    int threePairNum=0;//3同
    int kingKong=0;//4同
    int link=0;//顺子
    maxPairHand=0;
    for(int i=2; i<15; i++)
    {
        if(argsMsg.pointNum[i]==2) {
            ++twoPairNum;
            maxPairHand=i;
        }
        else if(argsMsg.pointNum[i]==3) threePairNum++;
        else if(argsMsg.pointNum[i]==4) kingKong++;
        if(i<11 && argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1 && argsMsg.pointNum[i+3]>=1 && argsMsg.pointNum[i+4]>=1) link=1;
    }
    if(argsMsg.pointNum[14]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1 && argsMsg.pointNum[4]>=1 && argsMsg.pointNum[5]>=1) link=1;
    linkP=0;
    if(link==0)
    {
        for(int i=2; i<11; i++)
        {
            if(argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1 && argsMsg.pointNum[i+3]>=1) linkP=2;
        }
        if(argsMsg.pointNum[14]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1 && argsMsg.pointNum[4]>=1) linkP=1;
        if(argsMsg.pointNum[11]>=1 && argsMsg.pointNum[12]>=1 && argsMsg.pointNum[13]>=1 && argsMsg.pointNum[14]>=1) linkP=1;
    }
    linkP = linkP*2/(50 - 4);


    maxp=0;
    int pointNum[15];
    for(int i=0;i<15;i++) pointNum[i] = 0;
    for(int i=0;i<4;++i){
        pointNum[roundData.pubCard[i].point]++;
        if(roundData.pubCard[i].point>maxp) maxp = roundData.pubCard[i].point;
    }

    ggpType=-1;
    for(int i=2;i<15;i++)
    {
        if(pointNum[i]==3)
        {
           ggpType = THREE_OF_A_KIND;
           break;
        }
        if(pointNum[i]==2)
        {
           ggpType = TWO_PAIR;
           break;
        }
        if(pointNum[i]==1)
        {
           ggpType = ONE_PAIR;
           break;
        }
    }
    if(ggpType==-1)
    {
        for(int i=2; i<12; i++)
        {
            if(argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1 && argsMsg.pointNum[i+3]>=1) ggpType = STRAIGHT;
        }
        if(argsMsg.pointNum[14]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1 && argsMsg.pointNum[4]>=1) ggpType=STRAIGHT;
        if(roundData.pubCard[0].color == roundData.pubCard[1].color && roundData.pubCard[0].color == roundData.pubCard[2].color)
        {
                if(ggpType == STRAIGHT) ggpType = STRAIGHT_FLUSH;
                else ggpType = FLUSH;
        }
    }


    if(sameColor && link)   //同花顺
           return STRAIGHT_FLUSH;
    if(kingKong) {
        return FOUR_OF_A_KIND;
    }
    if(threePairNum>0 && twoPairNum>0) {
        return FULL_HOUSE;
    }
    if(sameColor)   return STRAIGHT;

    if(link) {
        //顺子
        return FLUSH;
    }




    if(threePairNum>0) {
        return THREE_OF_A_KIND;
    }
    if(twoPairNum>=2) {
        return TWO_PAIR;
    }
    if(twoPairNum==1)
    {
        return ONE_PAIR;
    }

    return HIGH_CARD;
}



void stepThreeAI() {
    double p=100.0f;//本手牌概率
    int selfIndex = roundData.selfIndex;
    int raiseMoney=0;
    //条件
    int callNum=0,raiseNum=0,small=0,big=0,tight=0,attack=0,noFoldNum=0;
    //最后一家下注
    int lastMoney=roundData.blind;

    if(selfIndex == roundData.smallBlindID) small=1;
    else if(selfIndex ==  roundData.bigBlindID) big=1;
    {
        callNum = roundData.callNum;
        raiseNum = roundData.raiseNum;
        tight = roundData.tight;
        attack = roundData.attack;
        lastMoney = roundData.needBet;
        lastMoney -= roundData.player[selfIndex].bet;
        noFoldNum = roundData.noFoldNum;
    }

    int liveNum=0;
    for(int i=0; i<roundData.playerNum; ++i)
        if(roundData.player[i].isLive)
            ++liveNum;

    int myStyle=cardStyleThree();
    p=pp[myStyle][liveNum-1];
    if(p!=0) {
        p=1-p/100;
        raiseMoney=(roundData.poolSum-roundData.player[selfIndex].bet)*p/(1-p)-roundData.player[selfIndex].bet;//加注后总额
    } else {
        raiseMoney=roundData.player[selfIndex].jetton;
    }
    srand(time(0));
    int mul = 0;
    if(lastMoney!=0) mul = roundData.player[selfIndex].jetton / lastMoney;//手中筹码是下注额的倍数
    int mulBlind = roundData.player[selfIndex].jetton/roundData.blind;//手中筹码是盲注的倍数
    int action = FOLD;
    raiseMoney -= roundData.player[selfIndex].bet;//减去自己已经下的注
    lastMoney -= roundData.player[selfIndex].bet;
    float poolHand = lastMoney / roundData.poolSum;//底池赔率
    poolHand = poolHand*1.2;
    if(myStyle<=1) {//同花顺和4同 不虚
        action = RAISE;
        raiseMoney = (rand()%3+2)*roundData.blind;
    } else if(myStyle==FULL_HOUSE) {//葫芦
        if(ggpType != THREE_OF_A_KIND)//不虚
        {
             action = RAISE;
             raiseMoney = (rand()%3+2)*roundData.blind;
        }else
        {
            int x = roundData.player[selfIndex].handCard[0].point;
            float xp = (14-x)*4/46 * ((14-x)*4-1)/45;
            xp = 1-xp;//银钱概率
            if(xp<poolHand) action = FOLD;
            else if(xp/poolHand < 1.2) action = CALL;
            else
            {
                action = RAISE;
                raiseMoney = raiseMoney > roundData.poolSum/2 ? roundData.poolSum/2:raiseMoney;
            }
        }
    } else if(myStyle==FLUSH || myStyle == STRAIGHT) {//同花 huo sunzhi
        float xp=0;
        if(roundData.player[selfIndex].handCard[0].point>=maxp||roundData.player[selfIndex].handCard[0].point>=maxp)
        {
                action = RAISE;
                raiseMoney = raiseMoney > roundData.poolSum/2 ? roundData.poolSum/2:raiseMoney;
        }
        else
        {
            if(raiseNum >= 2) action = FOLD;
            else action = CALL;
            if(poolHand<0.2 && action ==FOLD) action = CALL;
            if(raiseMoney > roundData.blind*2) raiseMoney = roundData.blind*2; //最多2个大满主
        }


        if(mulBlind <= 5)  action = ALL_IN;
    }else if(myStyle == THREE_OF_A_KIND)//3tiao
    {
        if(ggpType == THREE_OF_A_KIND)
        {
            if(roundData.player[selfIndex].handCard[0].point<12 && roundData.player[selfIndex].handCard[0].point<12)
            {
                action = FOLD;
            }
            else action = CALL;
        }
        else
        {
            action = RAISE;
            if(raiseMoney > roundData.blind*3) raiseMoney = roundData.blind*3; //最多2个大满主
        }
    }
    else if(myStyle== TWO_PAIR) {//2对
        if(ggpType==ONE_PAIR)
        {
            if(raiseNum>=2 || poolHand>0.2) action = FOLD;
            else if(raiseNum>0)
            {
                if(poolHand>0.25) action = FOLD;
                else action = CALL;
            }
            else action = RAISE;
            if(raiseMoney > roundData.blind) raiseMoney = roundData.blind; //最多2个大满主

        }else
        {
            action = RAISE;
            if(poolHand<0.25) raiseMoney = 0.5*roundData.poolSum;
        }

        if(mulBlind < 5) action = ALL_IN;
    } else if(myStyle==ONE_PAIR) { //1对
        if(ggpType == ONE_PAIR)
        {
            if(roundData.player[selfIndex].handCard[0].point>=maxp || roundData.player[selfIndex].handCard[0].point>=maxp)
            {
                if(raiseNum >= 3) action=FOLD;
                else
                {
                    if(rand()%2==0) action=CALL;
                    else action=RAISE;
                    if(raiseMoney > roundData.blind) raiseMoney = roundData.blind; //最多2个大满主
                }
            }
            else
            {
                if(poolHand<0.25) action = CALL;
                else action = FOLD;
                if(raiseNum >= 2) action=FOLD;
            }
        }else
        {
            if(maxPairHand >= maxp)
            {
                if(rand()%2==0) action=CALL;
                else action=RAISE;
                if(poolHand>0.2) action = CALL;
            }else
            {
                if(raiseNum>=2) action = FOLD;
                else action = CALL;
            }
        }

        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主
        if(mulBlind < 5) action = ALL_IN;
    } else {//高牌

        if(sameColorP>0 || linkP>0)
        {
            if(sameColorP>poolHand || linkP>poolHand)  action = CALL;
            else action = FOLD;
        }
        else if((roundData.player[selfIndex].handCard[0].point>=maxp || roundData.player[selfIndex].handCard[0].point>=maxp) && maxPairHand>=12)
        {
            if(ggpType == STRAIGHT || ggpType == FLUSH)
            {
                action = FOLD;
            }
            else action = CALL;
        }
        else
        {
            if(raiseNum ==0 && selfIndex==big ) action = CALL;
            else action = FOLD;
        }
        if(tight>0 && maxp>=12) action=FOLD;
        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主

    }
    roundData.stepNum+=1;
    if(action==RAISE && raiseMoney<0) raiseMoney = 0;
    if(roundData.stepNum>3 && action == RAISE) action = CALL;
    if(action==FOLD && noFoldNum==0) action==CALL;
    sendMsg(action,raiseMoney);
}


/*判断牌型*/
int cardStyleFour() {
    //同花
    int sameColor = 0;
    for(int i=0; i<4; i++)
     {
         if(argsMsg.colorNum[i]>=5) sameColor = 1;
     }

    //判对子 3条 金刚 顺子
    int twoPairNum=0;//2同
    int threePairNum=0;//3同
    int kingKong=0;//4同
    int link=0;//顺子
    maxPairHand=0;
    for(int i=2; i<15; i++)
    {
        if(argsMsg.pointNum[i]==2) {
            ++twoPairNum;
            maxPairHand=i;
        }
        else if(argsMsg.pointNum[i]==3) threePairNum++;
        else if(argsMsg.pointNum[i]==4) kingKong++;
        if(i<11 && argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1 && argsMsg.pointNum[i+3]>=1 && argsMsg.pointNum[i+4]>=1) link=1;
    }
    if(argsMsg.pointNum[14]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1 && argsMsg.pointNum[4]>=1 && argsMsg.pointNum[5]>=1) link=1;

    maxp=0;
    int pointNum[15];
    for(int i=0;i<15;i++) pointNum[i] = 0;
    for(int i=0;i<5;++i){
        pointNum[roundData.pubCard[i].point]++;
        if(roundData.pubCard[i].point>maxp) maxp = roundData.pubCard[i].point;
    }

    ggpType=-1;
    for(int i=2;i<15;i++)
    {
        if(pointNum[i]==3)
        {
           ggpType = THREE_OF_A_KIND;
           break;
        }
        if(pointNum[i]==2)
        {
           ggpType = TWO_PAIR;
           break;
        }
        if(pointNum[i]==1)
        {
           ggpType = ONE_PAIR;
           break;
        }
    }
    if(ggpType==-1)
    {
        for(int i=2; i<12; i++)
        {
            if(argsMsg.pointNum[i]>=1 && argsMsg.pointNum[i+1]>=1 && argsMsg.pointNum[i+2]>=1 && argsMsg.pointNum[i+3]>=1) ggpType = STRAIGHT;
        }
        if(argsMsg.pointNum[14]>=1 && argsMsg.pointNum[2]>=1 && argsMsg.pointNum[3]>=1 && argsMsg.pointNum[4]>=1) ggpType=STRAIGHT;
        if(roundData.pubCard[0].color == roundData.pubCard[1].color && roundData.pubCard[0].color == roundData.pubCard[2].color)
        {
                if(ggpType == STRAIGHT) ggpType = STRAIGHT_FLUSH;
                else ggpType = FLUSH;
        }
    }


    if(sameColor && link)   //同花顺
           return STRAIGHT_FLUSH;
    if(kingKong) {
        return FOUR_OF_A_KIND;
    }
    if(threePairNum>0 && twoPairNum>0) {
        return FULL_HOUSE;
    }
    if(sameColor)   return STRAIGHT;

    if(link) {
        //顺子
        return FLUSH;
    }




    if(threePairNum>0) {
        return THREE_OF_A_KIND;
    }
    if(twoPairNum>=2) {
        return TWO_PAIR;
    }
    if(twoPairNum==1)
    {
        return ONE_PAIR;
    }

    return HIGH_CARD;
}



void stepFourAI() {
    double p=100.0f;//本手牌概率
    int selfIndex = roundData.selfIndex;
    int raiseMoney=0;
    //条件
    int callNum=0,raiseNum=0,small=0,big=0,tight=0,attack=0,noFoldNum=0;
    //最后一家下注
    int lastMoney=roundData.blind;

    if(selfIndex == roundData.smallBlindID) small=1;
    else if(selfIndex ==  roundData.bigBlindID) big=1;
    {
        callNum = roundData.callNum;
        raiseNum = roundData.raiseNum;
        tight = roundData.tight;
        attack = roundData.attack;
        lastMoney = roundData.needBet;
        lastMoney -= roundData.player[selfIndex].bet;
        noFoldNum = roundData.noFoldNum;
    }

    int liveNum=0;
    for(int i=0; i<roundData.playerNum; ++i)
        if(roundData.player[i].isLive)
            ++liveNum;

    int myStyle=cardStyleFour();
    p=pp[myStyle][liveNum-1];
    if(p!=0) {
        p=1-p/100;
        raiseMoney=(roundData.poolSum-roundData.player[selfIndex].bet)*p/(1-p)-roundData.player[selfIndex].bet;//加注后总额
    } else {
        raiseMoney=roundData.player[selfIndex].jetton;
    }
    srand(time(0));
    int mul = 0;
    if(lastMoney!=0) mul = roundData.player[selfIndex].jetton / lastMoney;//手中筹码是下注额的倍数
    int mulBlind = roundData.player[selfIndex].jetton/roundData.blind;//手中筹码是盲注的倍数
    int action = FOLD;
    raiseMoney -= roundData.player[selfIndex].bet;//减去自己已经下的注
    lastMoney -= roundData.player[selfIndex].bet;
    float poolHand = lastMoney / roundData.poolSum;//底池赔率
    poolHand = poolHand*1.2;
    if(myStyle<=1) {//同花顺和4同 不虚
        action = RAISE;
        raiseMoney = (rand()%3+2)*roundData.blind;
    } else if(myStyle==FULL_HOUSE) {//葫芦
        if(ggpType != THREE_OF_A_KIND)//不虚
        {
             action = RAISE;
             raiseMoney = (rand()%3+2)*roundData.blind;
        }else
        {
            int x = roundData.player[selfIndex].handCard[0].point;
            float xp = (14-x)*4/46 * ((14-x)*4-1)/45;
            xp = 1-xp;//银钱概率
            if(xp<poolHand) action = FOLD;
            else if(xp/poolHand < 1.2) action = CALL;
            else
            {
                action = RAISE;
                raiseMoney = raiseMoney > roundData.poolSum/2 ? roundData.poolSum/2:raiseMoney;
            }
        }
    } else if(myStyle==FLUSH || myStyle == STRAIGHT) {//同花 huo sunzhi
        if(roundData.player[selfIndex].handCard[0].point>=maxp||roundData.player[selfIndex].handCard[0].point>=maxp)
        {
                action = RAISE;
                raiseMoney = raiseMoney > roundData.poolSum/2 ? roundData.poolSum/2:raiseMoney;
        }
        else
        {
            if(raiseNum >= 2) action = FOLD;
            else action = CALL;
            if(poolHand<0.2 && action ==FOLD) action = CALL;
            if(raiseMoney > roundData.blind*2) raiseMoney = roundData.blind*2; //最多2个大满主
        }


        if(mulBlind <= 5)  action = ALL_IN;
    }else if(myStyle == THREE_OF_A_KIND)//3tiao
    {
        if(ggpType == THREE_OF_A_KIND)
        {
            if(roundData.player[selfIndex].handCard[0].point<12 && roundData.player[selfIndex].handCard[0].point<12)
            {
                action = FOLD;
            }
            else action = CALL;
        }
        else
        {
            action = RAISE;
            if(raiseMoney > roundData.blind*3) raiseMoney = roundData.blind*3; //最多2个大满主
        }
    }
    else if(myStyle== TWO_PAIR) {//2对
        if(ggpType==ONE_PAIR)
        {
            if(maxPairHand>maxp )
            {
                action = CALL;
            }
            else if(raiseNum>=2 || poolHand>0.2) action = FOLD;
            else if(raiseNum>0)
            {
                if(poolHand>0.25) action = FOLD;
                else action = CALL;
            }
            else action = RAISE;
            if(raiseMoney > roundData.blind) raiseMoney = roundData.blind; //最多2个大满主

        }else
        {
            action = RAISE;
            if(poolHand<0.25) raiseMoney = 0.5*roundData.poolSum;
            else action = CALL;
            if(raiseNum>=1)
            {
                if(ggpType==STRAIGHT || ggpType == FLUSH) action = FOLD;
            }
        }

        if(mulBlind < 5) action = ALL_IN;
    } else if(myStyle==ONE_PAIR) { //1对
        if(ggpType == ONE_PAIR)
        {
            if(roundData.player[selfIndex].handCard[0].point>=maxp || roundData.player[selfIndex].handCard[0].point>=maxp)
            {
                if(raiseNum+callNum >= 1) action=FOLD;
                else
                {
                    if(big==1 || small==1)
                    {
                        if(rand()%2==0) action=CALL;
                        else action=RAISE;
                        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind; //最多2个大满主

                    }else
                    {
                        action = FOLD;
                   }
                }
            }
            else
            {
                if(poolHand<0.2) action = CALL;
                else action = FOLD;
                if(raiseNum >= 2) action=FOLD;
            }
        }else
        {
            if(maxPairHand >= maxp)
            {
                if(rand()%2==0) action=CALL;
                else action=RAISE;
                if(poolHand>0.25) action = CALL;
                else action = FOLD;
                if(raiseNum>=2) action = FOLD;
            }else
            {
                if(raiseNum+callNum>=2) action = FOLD;
                else action = CALL;
            }
        }

        if(raiseMoney > roundData.blind) raiseMoney = roundData.blind*rand()%2; //最多1个大满主
        if(mulBlind < 5) action = ALL_IN;
    } else {//高牌

        action=FOLD;

    }
    roundData.stepNum+=1;
    if(action==RAISE && raiseMoney<0) raiseMoney = 0;
    if(roundData.stepNum>3 && action == RAISE) action = CALL;
    if(action==FOLD && noFoldNum==0) action==CALL;
    sendMsg(action,raiseMoney);
}
void ai_type()
{

    RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    RU(char c[200];);
    LOG2F(filename,"AI_TYPE");
    for(int i=0; i<NUM_PLAYER; i++)
    {
        if(roundData.player[i].ID == argsMsg.ID) continue;
        int pointa=roundData.player[i].handCard[0].point;
        int pointb=roundData.player[i].handCard[1].point;
        int colora=roundData.player[i].handCard[0].color;
        int colorb=roundData.player[i].handCard[1].color;
        //static bool flag=false;
        int id = roundData.player[i].ID;
        int idIndex = findTypeIndex(id);
        RU(sprintf(c,"TTTTTTTTTTTT i:%d id:%d idIndex:%d pointa:%d pointb%d num:%dTTTTTTTTTTTTT",i,id,idIndex,pointa,pointb,roundData.playerNum););
        LOG2F(filename,c);

        RU(sprintf(c,"TTTTTTTTTTTT topHand:%d id:%d idIndex:%d  TTTTTTTTTTTTT",roundData.player[i].topHand,id,idIndex););
        LOG2F(filename,c);
        int action = roundData.player[i].actionHand[roundData.player[i].topHand-1];
        float type=0;
        if(IsVeryStrong(pointa,pointb))
        {
            if(action==FOLD) type = TYPE_IGNORE;
        }
        else if(IsStrong(pointa,pointb,colora,colorb))
        {
            if(action==ALL_IN) type = TYPE_ATTACK;
        }
        else if(IsMid(pointa,pointb))
        {
            if(action==ALL_IN) type = TYPE_ATTACK;
            if(action==RAISE) type = TYPE_ATTACK;
            if(action==FOLD) type = TYPE_TIGHT;
        }
        else if(IsLikeStrong(pointa,pointb,colora,colorb))
        {

        }
        else if(IsBlend(pointa,pointb,colora,colorb))
        {

        }
        else
        {
            if(action==ALL_IN) type = ALL_IN;
            if(action==RAISE) type = TYPE_ATTACK;
        }
        //if(p==0&&type==0 && (action==RAISE || action==CALL)) type = TYPE_ATTACK;

        if(roundData.roundNums>=50)
        {

            if(roundData.typePlayer[idIndex].allin>roundData.roundNums/4*3) roundData.typePlayer[i].type = TYPE_ALLIN;
            if(roundData.typePlayer[idIndex].fold>roundData.roundNums/4*3) roundData.typePlayer[i].type = TYPE_TIGHT;
            if(roundData.typePlayer[idIndex].raise>roundData.roundNums/2 || roundData.typePlayer[i].call>roundData.roundNums/2)
            {
                if(type==0) roundData.typePlayer[idIndex].type = TYPE_ATTACK;
                else roundData.typePlayer[idIndex].type = type;
            }
            RU(sprintf(c,"TTTTTTTTTTTT idIndex:%d type:%d TTTTTTTTTTTTT",idIndex,roundData.typePlayer[idIndex].type););
            LOG2F(filename,c);

        }

    }
}
int findTypeIndex(int id)
{
    for(int i=0; i<NUM_PLAYER; i++)
    {
        if(id == roundData.typePlayer[i].ID)
        {
            return i;
        }
    }
    return 0;
}
