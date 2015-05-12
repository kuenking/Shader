#include "debug_shader.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
	int a=5;
	OT(a,%d);
	RU(printf("hello \n"));
	printf("world\n");
	LOG2F("log1.txt","logmes1");
	LOG2F("log1.txt","logmes2");
	LOG2F("log2.txt","logmes3");
	LOG2F("log2.txt","logmes4");
	return 0;
}