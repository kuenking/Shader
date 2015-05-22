#ifndef	DEBUG_SHADER_H_
#define DEBUG_SHADER_H_
#ifdef DSHADER
#include "stdio.h"
#undef RU
#undef OT
#define LOG2F(filename,str) {\
FILE *__p=fopen(filename,"a");\
if(__p==NULL)printf("open log file error\n");\
else{\
fprintf(__p, str );\
fprintf( __p,"\n" );\
fclose(__p);\
}\
}
#ifdef DSHADERPAUSE
#define RU(x) x;printf("file:"__FILE__"\tline:%d""\t--->debug part run\n",__LINE__);getchar()
#define OT(x,format) printf("file:"__FILE__"\tline:%d""\t--->"#x":"#format"\n",__LINE__,x);getchar()
#else
#define RU(x) x;printf("file:"__FILE__"\tline:%d""\t--->debug part run\n",__LINE__)
#define OT(x,format) printf("file:"__FILE__"\tline:%d""\t--->"#x":"#format"\n",__LINE__,x)
#endif
#else
#define LOG2F(fileName,str)
#define RU(x)
#define OT(x,format)
#endif
#endif
