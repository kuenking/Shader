#include "error_code.h"
//����
//#include "args_package.h"
#include "connection.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
//������Ϣ�����α�����Ҫʹ�ã������Ϊȫ�ֱ���
struct    ArgsPackage argsMsg;
//�������������׽���
//������
int    main(   int    args,   char    **argv){
     if   (args!=6){  //����ʱʹ��
       perror   (   "��������"   );
       return    ARGS_NUM_ERROR;
     }
     //��ʼ
     conServer(args);
	 char msg[MAXLENGTH];
     while   (1){
		 getMsg(msg);
       //�ж��Ƿ����
       if   (-1==explMsg(msg))
         break   ;
     }
     //�������ر��׽���
     close(sock);
     return    0;
}