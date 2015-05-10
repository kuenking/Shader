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
int    main(   int    args,   char    **argv){
     if   (args!=6){  
       perror   (   "args number error"   );
       return    ARGS_NUM_ERROR;
     }
     conServer(argv);
     char msg[MAXLENGTH];
     while   (1){
		 getMsg(msg);
       if   (-1==explMsg(msg))
         break   ;
     }
     close(sock);
     return    0;
}