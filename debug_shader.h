#ifndef	DEBUG_SHADER_H_
#define DEBUG_SHADER_H_
#ifdef DSHADER
#include "stdio.h"
#undef RU
#undef OT
#ifdef DSHADERPAUSE
#define RU(x) x;printf("file:"__FILE__"\tline:%d""\t--->debug part run\n",__LINE__);getchar()
#define OT(x,format) printf("file:"__FILE__"\tline:%d""\t--->"#x":"#format"\n",__LINE__,x);getchar()
#else
#define RU(x) x;printf("file:"__FILE__"\tline:%d""\t--->debug part run\n",__LINE__)
#define OT(x,format) printf("file:"__FILE__"\tline:%d""\t--->"#x":"#format"\n",__LINE__,x)
#endif
#else
#define RU(x)
#define OT(x,format)
#endif
#endif