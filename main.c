#include <stdio.h>
#include <stdlib.h>

enum DebugConfig {
	EXTRA,
	FULL,
	MINIMUM,
	ONLY_LINE,
};

static enum DebugConfig debug_config = FULL;

void Init_Debug(enum DebugConfig cfg) {
	debug_config = cfg;
}

static char *strstr(const char *haystack, const char *needle) {
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

static int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}

#define DEBUG(TEXT) debug(TEXT)
#define DEBUG_ASSERT(TEXT) debug_assert(TEXT, __LINE__)
#define DEBUG_EQ_STR(TEXT1, TEXT2) debug_eq_str(TEXT1, TEXT2, __LINE__)
#define DEBUG_EQ_INT(TEXT1, TEXT2) debug_eq_int(TEXT1, TEXT2, __LINE__)

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#define DEBUG_ARRAY_ENDS_CRLF(TEXT) debug_array_ends_crlf(TEXT, ARRAY_SIZE(TEXT), __LINE__)

#define DEBUG_ARRAY_CONTAINS(TEXT1, TEXT2) debug_array_contains(TEXT1, TEXT2, __LINE__)

// implementation to exit
int stop_execution() {
}

// implementation to write message
static inline void debug(const char message[]) {
	printf("%s\n", message);
}

enum TypeError {
	ASSERT,
	EQ_INT,
	EQ_STR,
	ENDS,
	ENDS_CRLF,
	CONTAIN,
};

static inline void format(enum TypeError err_type,
						  int line,
						  const char *details)
{
	char label[128];
	char output[256];

	/* Формируем базовую метку без номера строки и деталей */
	switch (err_type)
	{
	case ASSERT:
		snprintf(label, sizeof(label), "ASSERTION FAILED");
		break;
	case EQ_INT:
		snprintf(label, sizeof(label), "INT ASSERTION FAILED");
		break;
	case EQ_STR:
		snprintf(label, sizeof(label), "STRING ASSERTION FAILED");
		break;
	case ENDS_CRLF:
		snprintf(label, sizeof(label), "CRLF ASSERTION FAILED");
		break;
	case CONTAIN:
		snprintf(label, sizeof(label), "CONTAINS ASSERTION FAILED");
		break;
	default:
		snprintf(label, sizeof(label), "UNKNOWN ERROR");
	}

	switch (debug_config)
	{
	case EXTRA:
		/* label + line + details */
		snprintf(output, sizeof(output),
				 "%s at line %d: %s",
				 label, line, details);
		break;
	case FULL:
		/* label + line */
		snprintf(output, sizeof(output),
				 "%s at line %d",
				 label, line);
		break;
	case MINIMUM:
		/* только label */
		snprintf(output, sizeof(output),
				 "%s",
				 label);
		break;
	case ONLY_LINE:
		/* только номер строки */
		snprintf(output, sizeof(output),
				 "Line %d",
				 line);
		break;
	}

	debug(output);
	stop_execution();
}
static inline void debug_assert(unsigned int expr, int line) {
    if (!expr) {
        format(ASSERT, line, "");
    }
}

static inline void debug_eq_int(int a, int b, int line) {
    if (a != b) {
        char details[64];
        snprintf(details, sizeof(details), "%d != %d", a, b);
        format(EQ_INT, line, details);
    }
}

static inline void debug_eq_str(const char a[], const char b[], int line) {
    if (strcmp(a, b) != 0) {
        char details[128];
        snprintf(details, sizeof(details), "\"%s\" != \"%s\"", a, b);
        format(EQ_STR, line, details);
    }
}

static inline void debug_array_ends_crlf(const char a[],
                                         int len,
                                         int line)
{
    if (!(a[len-2] == '\r' && a[len-1] == '\n')) {
        char details[128];
        snprintf(details, sizeof(details),
                 "expected CRLF at end of \"%s\"", a);
        format(ENDS_CRLF, line, details);
    }
}

static inline void debug_array_contains(const char a[],
                                        const char b[],
                                        int line)
{
    if (!strstr(a, b)) {
        char details[128];
        snprintf(details, sizeof(details),
                 "\"%s\" not found in \"%s\"", b, a);
        format(CONTAIN, line, details);
    }
}

int main()
{
	Init_Debug(ONLY_LINE);
    DEBUG("Debug Message\n");
    
    DEBUG_ASSERT(2 == 1);
    
    const char msg[] = "hello";
    DEBUG_ARRAY_ENDS_CRLF(msg);
    
    const char word[] = "hui";
    
    DEBUG_ARRAY_CONTAINS(msg, word);
    
    DEBUG_EQ_INT(28, 3);
}