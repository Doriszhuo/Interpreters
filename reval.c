#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "strutils.h"
#include "rexp.h"

// this is a testing client provided for you
// see the .in and .expect files for ideas
// there is no need to modify this (unless you attempt the bonus)

int main(void) {
  struct dictionary *constants = dict_create();
  while(1) {
    char *s = readline();
    if (s == NULL) break;
    if (!is_blank(s)) {
      // this is an unsophisticated hack to detect definitions
      if (strstr(s, "define")) {
        add_constant(s, constants);
      } else {
        struct rexp *r = string_to_rexp(s);
        printf("%d\n", rexp_eval(r, constants));
        rexp_destroy(r);
      }
    }
    free(s);
  }
  dict_destroy(constants);
}
