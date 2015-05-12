#include "error_code.h"
#include "connection.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
ArgsPackage argsMsg;
int    main(int  args,char **argv) {
    if   (args!=6) {
        perror("args number error");
        return  ARGS_NUM_ERROR;
    }
    RU(char filename[100];
       sprintf(filename,"log_%s.txt",argv[5]););
    conServer(argv);
    LOG2F(filename,"链接完成");
    char msg[MAXLENGTH];
    while(1) {
        LOG2F(filename,"准备接受msg");
	memset(msg,0,MAXLENGTH);
        getMsg(msg);
        if(-1==explMsg(msg))
            break;
    }
    closeSocket();
    return    0;
}
