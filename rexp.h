#include "dictionary.h"

// the Racket Expression (rexp) module

// type is one of:
// '+', '-', '*', '/' [BINARY operators]
// 'v' for a variable [name stored in id]
// 'n' for a number   [value stored in number]

// do NOT modify the fields provided
// for the bonus, you may add new fields and types if you wish.

struct enode {
  char type;            // see above
  int number;           // only valid if type is 'n'
  char id[21];          // only valid if type is 'v'
  struct enode *left;   // only valid if type is an operator
  struct enode *right;  // only valid if type is an operator
};

struct rexp {
  struct enode *root;
};


// NOTE: the efficiency (times) are awkward and not provided
//       you are NOT required to meet specific efficiency requirements
//       (although a grossly inefficient implementation may time out)


// string_to_rexp(s) creates a *new* rexp from s
//   for example, s is of the form "(+ 1 1)"
// effects: allocates memory: must call rexp_destroy
struct rexp *string_to_rexp(const char *s);


// add_constant(s, constants) adds to constants
//   the constant defined in s
//   for example, s is of the form "(define n 3)"
// effects: updates constants
void add_constant(const char *s, struct dictionary *constants);


// rexp_eval(r, constants) evaluates the rexp r
// requires: r is a valid rexp
//           constants is a valid dictionary
//           all variables (type 'v') in r appear in constants
int rexp_eval(const struct rexp *r, const struct dictionary *constants);


// rexp_destroy(r) frees all memory allocated to r
// requires: r is a valid rexp
// effects: r is no longer valid
void rexp_destroy(struct rexp *r);


// print_rexp(r) prints the rexp
// requires: r is a valid rexp
// effects: displays a message
void print_rexp(const struct rexp *r);
