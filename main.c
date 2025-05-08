#include "functions.h"
#include "macros.h"


int main()
{
	Init_Debug(EXTRA);

	int val[5]={1,2,3,4,5};
	DEBUG_CONTAINS(val, 22);
	
	DEBUG_CONTAINS("1234", "567");

	DEBUG_EQ(1, 2);
	DEBUG_ASSERT(1 == 2);

	DEBUG_EQ("123", "456");

	DEBUG_ARRAY_ENDS_CRLF("123");
}