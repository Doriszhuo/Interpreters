#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "rexp.h"

// global variable being used to trace the current position
int curr = 0;


// string_ro_enode(s, node) returns a pointer to a dynamically allocated enode
//  which stored the string s in the enode.
// effects: allocates memory
static struct enode *string_to_enode(const char *s, struct enode *node) {
 node = malloc(sizeof(struct enode));
 node->left = NULL;
 node->right = NULL;

 while (s[curr] == ')' || s[curr] == ' ') {
  curr += 1;
 }

 char a;
 a = s[curr];

 if ((a >= '0' && a <= '9') || a == '-') {
  node->type = 'n';
  int n;
  sscanf(s + curr, "%d", &n);
  node->number = n;

  while (s[curr] != '\0' && s[curr] != ' ' && s[curr] != ')') {
   curr += 1;
  }

  node->left = NULL;
  node->right = NULL;

 } else if (a == '(' ) {
  curr += 1;
  sscanf(s + curr, "%c", &a);
  node->type = a;
  curr += 2;

  node->left = string_to_enode(s, node->left);
  node->right = string_to_enode(s, node->right);

 } else {
  node->type = 'v';

  int i = 0;
  while (s[curr] !=  ' ' && s[curr] != ')' && s[curr] != '\0') {
   node->id[i] = s[curr];
   curr += 1;
   i += 1;
  }
  node->id[i] = '\0';
  node->left = NULL;
  node->right = NULL;
 }
 return node;
}


// see the interface
struct rexp *string_to_rexp(const char *s) {

 struct rexp *r = malloc(sizeof(struct rexp));

 r->root = string_to_enode(s, r->root);

 //print_rexp(r);
 curr = 0;
 return r;
}


// eval_enode(node, constants) evalueates the enode
static int eval_enode(struct enode *node, const struct dictionary *constants) {
 if (!node) return 0;
 if (node->type == 'n') {
  return node->number;
 } else if (node->type == 'v') {

  return dict_lookup(node->id, constants);
 } else if (node->type == '+') {

  return eval_enode(node->left, constants) +
   eval_enode(node->right, constants);
 } else if (node->type == '-') {
  return eval_enode(node->left, constants) -
   eval_enode(node->right, constants);
 } else if (node->type == '*') {
  return eval_enode(node->left, constants) *
   eval_enode(node->right, constants);
 } else {
  return eval_enode(node->left, constants) /
   eval_enode(node->right, constants);
 }
}


// see the interface
int rexp_eval(const struct rexp *r, const struct dictionary *constants) {
 assert(r);


 return eval_enode(r->root, constants);
}


// destroy_enode(node) deallocates the memory allocated to node
// effects :node is no longer valid
static void destroy_enode(struct enode *node) {
 if (!node) return;

 destroy_enode(node->left);
 destroy_enode(node->right);

 free(node);
}


// see the interface
void rexp_destroy(struct rexp *r) {
 assert(r);

 destroy_enode(r->root);

 free(r);
}


// see the interface
void add_constant(const char *s, struct dictionary *constants) {
 assert(s);
 assert(constants);

 int i = 0;
 while (s[i] != ' ') {
  ++i;
 }
 ++i;

 char *key = malloc(21 * sizeof(char));  // freed below
 int curr = 0;
 while (s[i] != ' ') {
  key[curr] = s[i];
  ++curr;
  ++i;
 }
 key[curr] = '\0';
 i += 1;

 int len = 0;
 int max_len = 32;
 char *temp = malloc(sizeof(char) * max_len);  // freed below
 while (s[i] != '\0') {
  if (len == max_len) {
   max_len *= 2;
   temp = realloc(temp, sizeof(char) * max_len);
  }

  temp[len] =s[i];
  ++len;
  ++i;
 }
 if (len == max_len) {
  max_len *= 2;
  temp = realloc(temp, sizeof(char) * max_len);
 }
 temp[len] = '\0';
 ++len;

 struct rexp *r = string_to_rexp(temp);
 int val = rexp_eval(r, constants);

 dict_add(key, val, constants);

 free(temp);
 free(key);
 rexp_destroy(r);

}


////////////////////////////////////////////////////
// (below may not be useful for your own testing) //            
////////////////////////////////////////////////////

void print_enode(const struct enode *e) {
 //assert(e);
 if (e->type == 'n') {
  printf("%d", e->number);
 } else if (e->type == 'v') {
  printf("%s", e->id);
 } else {
  printf("(%c ", e->type);
  print_enode(e->left);
  printf(" ");
  print_enode(e->right);
  printf(")");
 }
}

void print_rexp(const struct rexp *r) {
 assert(r);
 print_enode(r->root);
 printf("\n");
}

