#include "functions.h"
#include "macros.h"


int main()
{
	Init_Debug(Line | Details);

	int val[5]={1,2,3,1,0};
	int msg[2]={1,0};

	DEBUG_ENDS(val, msg);
}