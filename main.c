#include <stdio.h>
#include <stdlib.h>

// strstr
char *strstr(const char *haystack, const char *needle) {
    if (!*needle)
        return (char*)haystack;

    for (; *haystack; haystack++) {
        const char *h = haystack;
        const char *n = needle;
        while (*n && *h && *h == *n) {
            ++h;
            ++n;
        }
        if (!*n)
            return (char*)haystack;
    }
    return 0;
}


#define DEBUG(TEXT) debug(TEXT, __LINE__)
#define DEBUG_ASSERT(TEXT) debug_assert(TEXT, __LINE__)
#define DEBUG_EQ_STR(TEXT1, TEXT2) debug_eq_str(TEXT1, TEXT2, __LINE__)
#define DEBUG_EQ_INT(TEXT1, TEXT2) debug_eq_int(TEXT1, TEXT2, __LINE__)

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#define DEBUG_ARRAY_ENDS_CRLF(TEXT) debug_array_ends_crlf(TEXT, ARRAY_SIZE(TEXT), __LINE__)

#define DEBUG_ARRAY_CONTAINS(TEXT1, TEXT2) debug_array_contains(TEXT1, TEXT2, __LINE__)

// implementation to exit
int stop_execution() {
    //exit(69);
}

// implementation to write message
static inline void debug(const char message[], int line) {
	printf("%s in line %d\n", message, line);
}

static inline void debug_assert(unsigned int a, int line) {
	if(!a) {
		const char message[] = "ASSERTION FAILED";
		debug(message, line);
		stop_execution();
	}	
}

static inline void debug_eq_int(int a, int b, int line) {
	if(a != b) {
		const char info[] = "INT ASSERTION FAILED";
		char message[64];
		sprintf(message, "%s %d != %d", info, a, b);
		debug(message, line);
		stop_execution();
	}
}

static inline void debug_eq_str(const char a[], const char b[], int line) {
	if(a != b) {
		const char info[] = "STRING ASSERTION FAILED";
		char message[64];
		sprintf(message, "%s %s != %s", info, a, b);
		debug(message, line);
		stop_execution();
	}
}

static inline void debug_array_ends_crlf(const char a[], int len, int line) {
	if(! (a[len - 1] == '\n' && a[len - 2] == '\r') ) {
		const char info[] = "ARRAY ASSERTION FAILED";
		char message[64];
		sprintf(message, "%s %s NOT end with CRLF", info, a);
		debug(message, line);
		stop_execution();
	}
}

static inline void debug_array_contains(const char a[], const char b[], int line) {
	if(!(strstr(a, b))) {
		const char info[] = "ARRAY ASSERTION FAILED";
		char message[64];
		sprintf(message, "%s %s NOT contains %s", info, a, b);
		debug(message, line);
		stop_execution();
	}    
}

int main()
{

    DEBUG("Debug Message");
    
    DEBUG_ASSERT(1 == 1);
    
    const char msg[] = "hellol";
    DEBUG_ARRAY_ENDS_CRLF(msg);
    
    const char word[] = "lo";
    
    DEBUG_ARRAY_CONTAINS(msg, word);
    
    DEBUG_EQ_INT(28, 3);
}