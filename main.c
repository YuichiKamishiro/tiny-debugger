#include "functions.h"
#include "macros.h"

int main()
{
	Init_Debug(Type | Line | Details);

	double data[2] = {1.0, 2.4};
	DEBUG_ALL(data, 1.0);
}