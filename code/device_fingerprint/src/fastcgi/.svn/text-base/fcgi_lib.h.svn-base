#ifndef FCGI_LIB_H
#define FCGI_LIB_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fcgi_stdio.h"
#include <string>
#include <map>
#include <vector>

#define _NAME 0
#define _VALUE 1

typedef struct {
  char *name;
  char *value;
} entrytype;
  
typedef struct _node {
  entrytype entry;
  struct _node* next;
} node;

typedef struct { 
  node* head;
} llist;

char *cgi_val(llist l, char *name);
int parse_CGI_encoded(llist *entries, char *buffer);
node* list_insafter(llist* l, node* w, entrytype item);
short on_list(llist *l, node* w);
char *newstr(char *str);
void unescape_url(char *url);
void list_create(llist *l);
node* list_next(node* w);
char* get_params(FCGX_Request &request);
char *get_POST(FCGX_Request &request);
char *get_GET(FCGX_Request &request);
bool paramsExpect(const std::string &paraStr, std::map<std::string, std::string> &paraMap);
bool paramsExpect(llist, std::map<std::string, std::string>&, std::string*, int, std::string*, int);
void initUrlParam(std::map<std::string, std::string> &paraMap, std::string &paramStr);

#endif
