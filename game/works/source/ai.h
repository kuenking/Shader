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

//整体AI
void ai();

//step AI
void stepOneAI();
void stepTwoAI();
void stepThreeAI();
void stepFourAI();
#endif
