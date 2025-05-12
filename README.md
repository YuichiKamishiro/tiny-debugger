# How to use
#### It's just a simple header-only library.
#### All you need is to implement debug() and stop_execution() library.
```c
// implementation to exit
int stop_execution() {
}

// implementation to write message
static inline void debug(const char message[]) {
    printf("%s\n", message);
}

```
## Debug levels
```c
    // Assertion type + line + details of assertion
    Init_Debug(Type | Line | Details); 
    Init_Debug(Type | Line);
    Init_Debug(Type);
```
## Assert
```c
    ASSERT(var == 1);
    ASSERT(foo() == 0);
```
## Eq Macro
```c
    int x, y;
    DEBUG_EQ(x, y)

    DEBUG_EQ("str", "another_one");
```
## Contains Macro
```c
    int data[3] = {1, 2, 3};
    DEBUG_CONTAINS(data, 3);

    DEBUG_CONTAINS("str", 'r');
```
## Ends Macro
```c
    DEBUG_ENDS("message\r\n", "\r\n");
    // Or
    DEBUG_ENDS_CRLF("message\r\n");
```
## All Macro
```c
    int data[3] = {1, 1, 1};
    DEBUG_ALL(data, 1);

    DEBUG_ALL("aaa", 'a');
```
## Other
```c
    if(ARRAY_SIZE(arr) == 2) {
        // ...
    }
```

# About
soon...