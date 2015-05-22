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
    if((point1==point2 && point1>=9)||(point1+point2 == 26) || (color1==color2 && point1+point2==25))
    {
        return 1;
    }
    return 0;
}
int IsMid()
{
    if(point1+point2==25 || (point1==14&&point2==10))//AJo,AT,KQ
    {
        return 1;
    }
    return 0;
}
int IsLikeStrong()//强投机牌
{//88-22 / KJs k-10s,QJs,QTs,JTs,T9s
    if(point1==point2 ) return 1;
    if(color1==color2 && (point2>=10 || (point1==10 && point2==9))) return 1;
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
    static bool flag=false;
    double p=0.0f;//本手牌概率
    if(point1<point2)//保证point1>point2
    {
        point1 = point1^point2;
        point2 = point1^point2;
        point1 = point1^point2;
    }
     RU(char filename[100];
       sprintf(filename,"log_%d.txt",argsMsg.ID););
    RU(char c[200];sprintf(c,"@@@@@@point1:%d point2:%d@@@@@@@@",point1,point2););
    LOG2F(filename,c);
    if(point1 == point2 )
    {
        p = sub[point1][roundData.playerNum];
    }
    else
    {
        if(point1 == 14)
        {
            p = Ax[point2][roundData.playerNum];
        }
        if(color1==color2 && point1+point2>=24)
        {
            p=3.02;//跟牌
        }

    }
    RU(sprintf(c,"@@@@@@p:%f@@@@@@@@",p););
    LOG2F(filename,c);
    int selfIndex = roundData.selfIndex,raiseMoney=0;
    if(p!=0)//计算加注
    {
        p=1-p/100;
        raiseMoney = (p * roundData.poolSum-roundData.player[selfIndex].bet)/(1-p);//最大下注不会亏
    }else raiseMoney = 0;
    RU(sprintf(c,"@@@@@@selfIndex:%d raiseMoney:%d@@@@@@@@",selfIndex,raiseMoney););
    LOG2F(filename,c);
    //条件
    int callNum=0,raiseNum=0,small=0,big=0;
    if(selfIndex == 0) small=1;
    else if(selfIndex == 1) big=1;
    else
    {
        for(int i=2;i<selfIndex;i++)
        {
            if(roundData.player[i].action==CALL) ++callNum;
            if(roundData.player[i].action==RAISE || roundData.player[i].action==ALL_IN) ++raiseNum;
        }
    }

    //判断
    if(IsVeryStrong())
    {
        LOG2F(filename,"VeryStrong");
        sendMsg(RAISE,raiseMoney);
    }
    else if(IsStrong())
    {
        LOG2F(filename,"Strong");
        if(raiseNum >= 2) sendMsg(FOLD,0);
        else if(raiseNum==1 && callNum >=1) sendMsg(CALL,0);
        else if(big==1 || small==1) sendMsg(RAISE,raiseMoney);
        else if(raiseNum == 1 && callNum==0 && selfIndex<=3) sendMsg(FOLD,0);
        else sendMsg(RAISE,raiseMoney);
    }
    else if(IsMid())
    {
        LOG2F(filename,"Mid");
        if(raiseNum==0)
        {
            if(selfIndex==2 || selfIndex==3) sendMsg(FOLD,0);
            else sendMsg(RAISE,raiseMoney);
        }
        else if(raiseNum==1 && callNum==0)
        {
            if(big==1) sendMsg(CALL,0);
            else sendMsg(FOLD,0);
        }
        else if(raiseNum==1 && callNum>0)
        {
            if(big==1 || (color1==color2 && point1==13 && point2==12)) sendMsg(CALL,0);
            else sendMsg(FOLD,0);
        }
    }
    else if(IsLikeStrong())//强投机牌
    {
        LOG2F(filename,"LikeStrong");
        if(callNum==0 && raiseNum==0) //全弃牌
        {
            if(big==1 || small==1 || selfIndex>6) sendMsg(RAISE,raiseMoney);
            else sendMsg(FOLD,0);
        }
        else if(raiseNum==0 && callNum==1) //一个玩家跟注
        {
            if(big==1) sendMsg(CHECK,0);
            else if(small==1 || selfIndex>6) sendMsg(CALL,0);
            else sendMsg(FOLD,0);
        }
        else if(raiseNum==0 && callNum>1)
        {
            if(big==1) sendMsg(CHECK,0);
            else sendMsg(CALL,0);
        }
        else if(raiseNum==1 && callNum==0)
        {
            if(big==1 ) sendMsg(CALL,0);
            else sendMsg(FOLD,0);
        }
        else if(raiseNum==1 && callNum>0)
        {
            sendMsg(CALL,0);
        }
        else sendMsg(FOLD,0);
    }
    else if(IsBlend())//混合牌
    {
        LOG2F(filename,"Blend");
          if(callNum==0 && raiseNum==0) //全弃牌
        {
            if(big==1 || small==1 || selfIndex>6) sendMsg(RAISE,raiseMoney);
            else sendMsg(FOLD,0);
        }
        else if(raiseNum==0 && callNum==1) //一个玩家跟注
        {
            if(big==1) sendMsg(CHECK,0);
            else if(small==1) sendMsg(CALL,0);
            else sendMsg(FOLD,0);
        }
        else if(raiseNum==0 && callNum>1)
        {
            if(big==1) sendMsg(CHECK,0);
            else if(small==1 && selfIndex>6)sendMsg(CALL,0);
            else sendMsg(FOLD,0);
        }
        else sendMsg(FOLD,0);
    }else
    {
        LOG2F(filename,"GAOPAI");
        sendMsg(FOLD,0);
    }
    LOG2F(filename,"AI_1 OVER!!!!!");
    /*if(point1==point2) {
        int t=roundData.player[roundData.selfIndex].jetton/10;
        if(flag==false) {
            sendMsg(RAISE,t);
            flag=true;
        } else {
            sendMsg(CALL,0);
            flag=false;
        }
    } else if(point1>10||point2>10) {
        sendMsg(CALL,0);
    } else if(color1==color2) {
        sendMsg(CALL,0);
    } else if(abs(point1-point2<5)) {
        sendMsg(CALL,0);
    } else {
        sendMsg(FOLD,0);
    }*/
}

void stepTwoAI() {
    int point1=roundData.player[roundData.selfIndex].handCard[0].point;
    int point2=roundData.player[roundData.selfIndex].handCard[1].point;
    int pubPoint[3];
    pubPoint[0]=roundData.pubCard[0].point;
    pubPoint[1]=roundData.pubCard[1].point;
    pubPoint[2]=roundData.pubCard[2].point;
    int color1=roundData.player[roundData.selfIndex].handCard[0].color;
    int color2=roundData.player[roundData.selfIndex].handCard[1].color;
    int pubColor[3];
    pubColor[0]=roundData.pubCard[0].color;
    pubColor[1]=roundData.pubCard[1].color;
    pubColor[2]=roundData.pubCard[2].color;
    bool flag=false;
    int samep1=0;
    int samep2=0;
    int samec1=0;
    int samec2=0;
    int link1=0;
    int link2=0;
    for(int i=0; i<3; ++i) {
        if(pubPoint[i]==point1)
            ++samep1;
        if(pubPoint[i]==point2)
            ++samep2;
        if(pubColor[i]==color1)
            ++samec1;
        if(pubColor[i]==color2)
            ++samec2;
        if(abs(pubPoint[i]-point1)<5)
            ++link1;
        if(abs(pubPoint[i]-point2)<5)
            ++link2;
    }
    if(samep1!=0&&samep2!=0) {
        if(point1==point2) {
            if(samep1==2) {
                sendMsg(ALL_IN,0);
                return;
            } else {
                int t=roundData.player[roundData.selfIndex].jetton/5;
                if(flag==false) {
                    sendMsg(RAISE,t);
                    flag=true;
                } else {
                    sendMsg(CALL,0);
                    flag=false;
                }
                return;
            }
        } else {
            int t=roundData.player[roundData.selfIndex].jetton/10;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                flag=false;
            }
            return;
        }
    } else {
        if(samep1+samep2==3) {
            int t=roundData.player[roundData.selfIndex].jetton/7;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                flag=false;
            }
            return;
        } else if(samep1+samep2==2) {
            int t=roundData.player[roundData.selfIndex].jetton/10;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                return;
            }
            return;
        } else {
            sendMsg(CALL,0);
            return;
        }
    }
    if(point1==point2) {
        sendMsg(CALL,0);
        return;
    }
    if(samec1!=0&&samep2!=0) {
        if(samec1==samec2) {
            if(samec1==3) {
                sendMsg(ALL_IN,0);
                return;
            } else {
                int t=roundData.player[roundData.selfIndex].jetton/15;
                if(flag==false) {
                    sendMsg(RAISE,t);
                    flag=true;
                } else {
                    sendMsg(CALL,0);
                    flag=false;
                }
                return;
            }
        } else {
            sendMsg(CALL,0);
            return;
        }
    } else {
        if(samec1==3) {
            sendMsg(CALL,0);
            return;
        }
    }
    if(abs(point1-point2)<5) {
        if(link1==3||link2==3) {
            sendMsg(CALL,0);
            flag=true;
        }
    }
    sendMsg(FOLD,0);
}


void stepThreeAI() {
    int point1=roundData.player[roundData.selfIndex].handCard[0].point;
    int point2=roundData.player[roundData.selfIndex].handCard[1].point;
    int pubPoint[4];
    pubPoint[0]=roundData.pubCard[0].point;
    pubPoint[1]=roundData.pubCard[1].point;
    pubPoint[2]=roundData.pubCard[2].point;
    pubPoint[3]=roundData.pubCard[3].point;
    int color1=roundData.player[roundData.selfIndex].handCard[0].color;
    int color2=roundData.player[roundData.selfIndex].handCard[1].color;
    int pubColor[4];
    pubColor[0]=roundData.pubCard[0].color;
    pubColor[1]=roundData.pubCard[1].color;
    pubColor[2]=roundData.pubCard[2].color;
    pubColor[3]=roundData.pubCard[3].color;
    bool flag=false;
    int samep1=0;
    int samep2=0;
    int samec1=0;
    int samec2=0;
    int link1=0;
    int link2=0;
    for(int i=0; i<4; ++i) {
        if(pubPoint[i]==point1)
            ++samep1;
        if(pubPoint[i]==point2)
            ++samep2;
        if(pubColor[i]==color1)
            ++samec1;
        if(pubColor[i]==color2)
            ++samec2;
        if(abs(pubPoint[i]-point1)<5)
            ++link1;
        if(abs(pubPoint[i]-point2)<5)
            ++link2;
    }
    if(samep1!=0&&samep2!=0) {
        if(point1==point2) {
            if(samep1==2) {
                sendMsg(ALL_IN,0);
                return;
            } else {
                int t=roundData.player[roundData.selfIndex].jetton/5;
                if(flag==false) {
                    sendMsg(RAISE,t);
                    flag=true;
                } else {
                    sendMsg(CALL,0);
                    flag=false;
                }
                return;
            }
        } else {
            int t=roundData.player[roundData.selfIndex].jetton/10;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                flag=false;
            }
            return;
        }
    } else {
        if(samep1+samep2==3) {
            int t=roundData.player[roundData.selfIndex].jetton/7;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                flag=false;
            }
            return;
        } else if(samep1+samep2==2) {
            int t=roundData.player[roundData.selfIndex].jetton/10;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                return;
            }
            return;
        } else {
            sendMsg(CALL,0);
            return;
        }
    }
    if(point1==point2) {
        sendMsg(CALL,0);
        return;
    }
    if(samec1!=0&&samep2!=0) {
        if(samec1==samec2) {
            if(samec1>=3) {
                sendMsg(ALL_IN,0);
                return;
            } else {
                int t=roundData.player[roundData.selfIndex].jetton/15;
                if(flag==false) {
                    sendMsg(RAISE,t);
                    flag=true;
                } else {
                    sendMsg(CALL,0);
                    flag=false;
                }
                return;
            }
        } else {
            sendMsg(CALL,0);
            return;
        }
    } else {
        if(samec1==3) {
            sendMsg(CALL,0);
            return;
        }
    }
    if(abs(point1-point2)<5) {
        if(link1==3||link2==3) {
            sendMsg(CALL,0);
            flag=true;
        }
    }
    sendMsg(FOLD,0);
}



void stepFourAI() {
    int point1=roundData.player[roundData.selfIndex].handCard[0].point;
    int point2=roundData.player[roundData.selfIndex].handCard[1].point;
    int pubPoint[5];
    pubPoint[0]=roundData.pubCard[0].point;
    pubPoint[1]=roundData.pubCard[1].point;
    pubPoint[2]=roundData.pubCard[2].point;
    pubPoint[3]=roundData.pubCard[3].point;
    pubPoint[4]=roundData.pubCard[4].point;
    int color1=roundData.player[roundData.selfIndex].handCard[0].color;
    int color2=roundData.player[roundData.selfIndex].handCard[1].color;
    int pubColor[5];
    pubColor[0]=roundData.pubCard[0].color;
    pubColor[1]=roundData.pubCard[1].color;
    pubColor[2]=roundData.pubCard[2].color;
    pubColor[3]=roundData.pubCard[3].color;
    pubColor[4]=roundData.pubCard[4].color;
    bool flag=false;
    int samep1=0;
    int samep2=0;
    int samec1=0;
    int samec2=0;
    int link1=0;
    int link2=0;
    for(int i=0; i<5; ++i) {
        if(pubPoint[i]==point1)
            ++samep1;
        if(pubPoint[i]==point2)
            ++samep2;
        if(pubColor[i]==color1)
            ++samec1;
        if(pubColor[i]==color2)
            ++samec2;
        if(abs(pubPoint[i]-point1)<5)
            ++link1;
        if(abs(pubPoint[i]-point2)<5)
            ++link2;
    }
    if(samep1!=0&&samep2!=0) {
        if(point1==point2) {
            if(samep1==2) {
                sendMsg(ALL_IN,0);
                return;
            } else {
                int t=roundData.player[roundData.selfIndex].jetton/5;
                if(flag==false) {
                    sendMsg(RAISE,t);
                    flag=true;
                } else {
                    sendMsg(CALL,0);
                    flag=false;
                }
                return;
            }
        } else {
            int t=roundData.player[roundData.selfIndex].jetton/10;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                flag=false;
            }
            return;
        }
    } else {
        if(samep1+samep2>=3) {
            int t=roundData.player[roundData.selfIndex].jetton/7;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                flag=false;
            }
            return;
        } else if(samep1+samep2==2) {
            int t=roundData.player[roundData.selfIndex].jetton/10;
            if(flag==false) {
                sendMsg(RAISE,t);
                flag=true;
            } else {
                sendMsg(CALL,0);
                return;
            }
            return;
        } else {
            sendMsg(CALL,0);
            return;
        }
    }
    if(point1==point2) {
        sendMsg(CALL,0);
        return;
    }
    if(samec1!=0&&samep2!=0) {
        if(samec1==samec2) {
            if(samec1==3) {
                sendMsg(ALL_IN,0);
                return;
            } else {
                int t=roundData.player[roundData.selfIndex].jetton/15;
                if(flag==false) {
                    sendMsg(RAISE,t);
                    flag=true;
                } else {
                    sendMsg(CALL,0);
                    flag=false;
                }
                return;
            }
        } else {
            sendMsg(CALL,0);
            return;
        }
    } else {
        if(samec1==3) {
            sendMsg(CALL,0);
            return;
        }
    }
    if(abs(point1-point2)<5) {
        if(link1==3||link2==3) {
            sendMsg(CALL,0);
            flag=true;
        }
    }
    sendMsg(FOLD,0);
}
