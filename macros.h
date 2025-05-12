#ifndef MACROS
#define MACROS
#define DEBUG(TEXT) debug(TEXT)
#define DEBUG_ASSERT(TEXT) debug_assert(TEXT, __LINE__)

// Generic EQ macro
#define DEBUG_EQ(A, V) \
_Generic((A), \
	char *: f_eq_char_array, \
	const char*: f_eq_char_array, \
	int: f_eq_int \
)( (A), (V), __LINE__ )

// Generic CONTAINS macro
#define DEBUG_CONTAINS(A, V) \
_Generic((A), \
	char *: f_char_array_contains, \
	const char *: f_char_array_contains, \
	int *: f_int_array_contains, \
	const int *: f_int_array_contains \
)( (A), ARRAY_SIZE(A), (V), __LINE__)

// Generic ENDS macro
#define DEBUG_ENDS(A, V) \
_Generic((A), \
	char *: f_char_array_ends, \
	const char *: f_char_array_ends, \
	int *: f_int_array_ends, \
	const int *: f_int_array_ends \
)( (A), ARRAY_SIZE(A), (V), ARRAY_SIZE(V), __LINE__)

// Generic ALL macro
#define DEBUG_ALL(A, V) \
_Generic((A), \
	int *: f_int_array_all, \
	const int *: f_int_array_all, \
	char *: f_char_array_all, \
	const char *: f_char_array_all, \
	double *: f_double_array_all, \
	const double *: f_double_array_all \
)( (A), ARRAY_SIZE(A), (V), __LINE__)


// Other
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#define DEBUG_ARRAY_ENDS_CRLF(TEXT) f_char_array_ends_crlf(TEXT, ARRAY_SIZE(TEXT), __LINE__)

#endif
