#include "ai.h"
#include "connection.h"
#include <stdlib.h>
#include <math.h>
void ai(){
  switch(roundData.gameStep){
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


void stepOneAI(){
  int point1=roundData.player[roundData.selfIndex].handCard[0].point;
  int point2=roundData.player[roundData.selfIndex].handCard[1].point;
  int color1=roundData.player[roundData.selfIndex].handCard[0].color;
  int color2=roundData.player[roundData.selfIndex].handCard[1].color;
  static bool flag=false;
  if(point1==point2){
    int t=roundData.player[roundData.selfIndex].jetton/10;
    if(flag==false){
      sendMsg(RAISE,t);
      flag=true;
    }else{
      sendMsg(CALL,0);
      flag=false;
    }
  }else if(point1>10||point2>10){
    sendMsg(CALL,0);
  }else if(color1==color2){
    sendMsg(CALL,0);
  }else if(abs(point1-point2<5)){
    sendMsg(CALL,0);
  }else{
    sendMsg(FOLD,0);
  }
}

void stepTwoAI(){
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
  for(int i=0;i<3;++i){
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
  if(samep1!=0&&samep2!=0){
    if(point1==point2){
      if(samep1==2){
        sendMsg(ALL_IN,0);
        return;
      }else{
        int t=roundData.player[roundData.selfIndex].jetton/5;
        if(flag==false){
          sendMsg(RAISE,t);
          flag=true;
        }else{
          sendMsg(CALL,0);
          flag=false;
        }
        return;
      }
    }else{
      int t=roundData.player[roundData.selfIndex].jetton/10;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
      return;
    }
  }else{
    if(samep1+samep2==3){
      int t=roundData.player[roundData.selfIndex].jetton/7;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
      return;
    }else if(samep1+samep2==2){
       int t=roundData.player[roundData.selfIndex].jetton/10;
       if(flag==false){
         sendMsg(RAISE,t);
         flag=true;
       }else{
         sendMsg(CALL,0);
         return;
       }
       return;
    }else{
      sendMsg(CALL,0);
      return;
    }
  }
  if(point1==point2){
    sendMsg(CALL,0);
    return;
  }
  if(samec1!=0&&samep2!=0){
    if(samec1==samec2){
      if(samec1==3){
        sendMsg(ALL_IN,0);
        return;
      }else{
         int t=roundData.player[roundData.selfIndex].jetton/15;
         if(flag==false){
           sendMsg(RAISE,t);
           flag=true;
         }else{
           sendMsg(CALL,0);
           flag=false;
         }
         return;
      }
    }else{
      sendMsg(CALL,0);
      return;
    }
  }else{
    if(samec1==3){
      sendMsg(CALL,0);
      return;
    }
  }
  if(abs(point1-point2)<5){
    if(link1==3||link2==3){
      int t=roundData.player[roundData.selfIndex].jetton/10;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
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
  for(int i=0;i<4;++i){
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
  if(samep1!=0&&samep2!=0){
    if(point1==point2){
      if(samep1==2){
        sendMsg(ALL_IN,0);
        return;
      }else{
        int t=roundData.player[roundData.selfIndex].jetton/5;
        if(flag==false){
          sendMsg(RAISE,t);
          flag=true;
        }else{
          sendMsg(CALL,0);
          flag=false;
        }
        return;
      }
    }else{
      int t=roundData.player[roundData.selfIndex].jetton/10;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
      return;
    }
  }else{
    if(samep1+samep2==3){
      int t=roundData.player[roundData.selfIndex].jetton/7;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
      return;
    }else if(samep1+samep2==2){
       int t=roundData.player[roundData.selfIndex].jetton/10;
       if(flag==false){
         sendMsg(RAISE,t);
         flag=true;
       }else{
         sendMsg(CALL,0);
         return;
       }
       return;
    }else{
      sendMsg(CALL,0);
      return;
    }
  }
  if(point1==point2){
    sendMsg(CALL,0);
    return;
  }
  if(samec1!=0&&samep2!=0){
    if(samec1==samec2){
      if(samec1>=3){
        sendMsg(ALL_IN,0);
        return;
      }else{
         int t=roundData.player[roundData.selfIndex].jetton/15;
         if(flag==false){
           sendMsg(RAISE,t);
           flag=true;
         }else{
           sendMsg(CALL,0);
           flag=false;
         }
         return;
      }
    }else{
      sendMsg(CALL,0);
      return;
    }
  }else{
    if(samec1==3){
      sendMsg(CALL,0);
      return;
    }
  }
  if(abs(point1-point2)<5){
    if(link1==3||link2==3){
      int t=roundData.player[roundData.selfIndex].jetton/10;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
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
  for(int i=0;i<5;++i){
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
  if(samep1!=0&&samep2!=0){
    if(point1==point2){
      if(samep1==2){
        sendMsg(ALL_IN,0);
        return;
      }else{
        int t=roundData.player[roundData.selfIndex].jetton/5;
        if(flag==false){
          sendMsg(RAISE,t);
          flag=true;
        }else{
          sendMsg(CALL,0);
          flag=false;
        }
        return;
      }
    }else{
      int t=roundData.player[roundData.selfIndex].jetton/10;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
      return;
    }
  }else{
    if(samep1+samep2>=3){
      int t=roundData.player[roundData.selfIndex].jetton/7;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
      return;
    }else if(samep1+samep2==2){
       int t=roundData.player[roundData.selfIndex].jetton/10;
       if(flag==false){
         sendMsg(RAISE,t);
         flag=true;
       }else{
         sendMsg(CALL,0);
         return;
       }
       return;
    }else{
      sendMsg(CALL,0);
      return;
    }
  }
  if(point1==point2){
    sendMsg(CALL,0);
    return;
  }
  if(samec1!=0&&samep2!=0){
    if(samec1==samec2){
      if(samec1==3){
        sendMsg(ALL_IN,0);
        return;
      }else{
         int t=roundData.player[roundData.selfIndex].jetton/15;
         if(flag==false){
           sendMsg(RAISE,t);
           flag=true;
         }else{
           sendMsg(CALL,0);
           flag=false;
         }
         return;
      }
    }else{
      sendMsg(CALL,0);
      return;
    }
  }else{
    if(samec1==3){
      sendMsg(CALL,0);
      return;
    }
  }
  if(abs(point1-point2)<5){
    if(link1==3||link2==3){
      int t=roundData.player[roundData.selfIndex].jetton/10;
      if(flag==false){
        sendMsg(RAISE,t);
        flag=true;
      }else{
        sendMsg(CALL,0);
        flag=false;
      }
    }
  }
  sendMsg(FOLD,0);
}
