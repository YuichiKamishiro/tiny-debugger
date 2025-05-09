#ifndef MACROS
#define MACROS
#define DEBUG(TEXT) debug(TEXT)
#define DEBUG_ASSERT(TEXT) debug_assert(TEXT, __LINE__)

// Generic EQ macro
#define DEBUG_EQ(A, V) \
_Generic((A), \
	char *: debug_eq_str, \
	const char*: debug_eq_str, \
	int: debug_eq_int \
)( (A), (V), __LINE__ )

// Non Generic EQ macro
#define DEBUG_EQ_STR(TEXT1, TEXT2) debug_eq_str(TEXT1, TEXT2, __LINE__)
#define DEBUG_EQ_INT(TEXT1, TEXT2) debug_eq_int(TEXT1, TEXT2, __LINE__)

// Generic CONTAINS macro
#define DEBUG_CONTAINS(A, V) \
_Generic((A), \
	char *: debug_char_array_contains, \
	const char *: debug_char_array_contains, \
	int *: debug_int_array_contains, \
	const int *: debug_int_array_contains \
)( (A), ARRAY_SIZE(A), (V), __LINE__)

// Non Generic CONTAINS macro
#define DEBUG_CHAR_ARRAY_CONTAINS(TEXT1, TEXT2) debug_array_contains(TEXT1, TEXT2, __LINE__)
#define DEBUG_INT_ARRAY_CONTAINS(TEXT1, TEXT2) debug_int_array_contains(TEXT1, TEXT2, __LINE__)

#define DEBUG_ENDS(A, V) \
_Generic((A), \
	char *: debug_char_array_ends, \
	const char *: debug_char_array_ends, \
	int *: debug_int_array_ends, \
	const int *: debug_int_array_ends \
)( (A), ARRAY_SIZE(A), (V), ARRAY_SIZE(V), __LINE__)


// Other
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#define DEBUG_ARRAY_ENDS_CRLF(TEXT) debug_array_ends_crlf(TEXT, ARRAY_SIZE(TEXT), __LINE__)
#define DEBUG_ARRAY_ALL(ARRAY, VAL) debug_array_all(ARRAY, VAL, __LINE__)

#endif
