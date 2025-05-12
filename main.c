#include "functions.h"
#include "macros.h"

int main()
{
	Init_Debug(Type | Line | Details);
	DEBUG_ASSERT(ARRAY_SIZE("123") == 3);
}