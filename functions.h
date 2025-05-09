#ifndef FUNCTIONS
#define FUNCTIONS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

enum DebugConfig {
    None = 0,
    Type = 1,
    Line = 2,
    Details = 4
};

static enum DebugConfig debug_config = Type | Line; 

void Init_Debug(enum DebugConfig cfg) {
	debug_config = cfg;
}

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

    if(debug_config & Type) {
    switch (err_type)
    {
    case ASSERT:
        snprintf(output, sizeof(output), "ASSERTION FAILED");
        break;
    case EQ_INT:
        snprintf(output, sizeof(output), "INT ASSERTION FAILED");
        break;
    case EQ_STR:
        snprintf(output, sizeof(output), "STRING ASSERTION FAILED");
        break;
    case ENDS_CRLF:
        snprintf(output, sizeof(output), "CRLF ASSERTION FAILED");
        break;
    case CONTAIN:
        snprintf(output, sizeof(output), "CONTAINS ASSERTION FAILED");
        break;
    case ENDS:
        snprintf(output, sizeof(output), "ENDS ASSERTION FAILED");
        break;
    default:
        snprintf(output, sizeof(output), "UNKNOWN ERROR");
    }
    }
    if(debug_config & Line) {
        snprintf(output + strlen(output), sizeof(output) - strlen(output), " in line: %d", line);
    }

    
    if(debug_config & Details) {
        snprintf(output + strlen(output), sizeof(output) - strlen(output), ": %s", details);
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

static inline void debug_char_array_ends(const char a[],
                                    int alen,
                                    const char b[],
                                    int blen,
                                    int line    
                                )
{
    if(alen > blen) {
        int start_a = alen - blen;
        int err = 0;
        for(; start_a < alen; start_a++) {
            if(a[start_a] != b[start_a - (alen - blen)]) {
                char details[128];
                snprintf(details, sizeof(details),
                        "expected %s ends with %s", a, b);
                format(ENDS, line, details);
                return;
            }
        }
    } 
}

static inline void debug_int_array_ends(const int a[],
                                    int alen,
                                    const int b[],
                                    int blen,
                                    int line    
                                )
{
    if(alen > blen) {
        int start_a = alen - blen;
        int err = 0;
        for(; start_a < alen; start_a++) {
            if(a[start_a] != b[start_a - (alen - blen)]) {
                char details[128];
                snprintf(details, sizeof(details),
                        "expected int seq ends with ...");
                format(ENDS, line, details);
                return;
            }
        }
    } 
}

static inline void debug_char_array_contains(const char a[],
                                            int len,
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

static inline void debug_int_array_contains(const int a[],
                                            int len,
											const int b,
											int line)
{
	for(int i = 0; i < len; i++) {
        if(a[i] == b) { return; }
	} 
    char details[128];
    snprintf(details, sizeof(details),
        	 "\"%d\" not found in array", b, a);
    format(CONTAIN, line, details);
}

#endif