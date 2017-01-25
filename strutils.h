#include <stdbool.h>

// a module that provides some string helpers

// my_strdup(s) makes a duplicate of s
// effects: allocates memory (caller must free)
char *my_strdup(const char *s);

// readline() reads in a new line from I/O
//   or returns NULL if EOF
// effects: allocates memory (caller must free)
char *readline(void);


// is_blank(s) determines if s contains only spaces
//   or is an empty string
bool is_blank(const char *s);
