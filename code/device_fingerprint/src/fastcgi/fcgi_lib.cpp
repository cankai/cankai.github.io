#include "fcgi_lib.h"
#include "common/Utility.h"

char *get_POST(FCGX_Request &request)
{
  int content_length;
  char *buffer = NULL;
  char * lenstr = FCGX_GetParam("CONTENT_LENGTH", request.envp);

  if (lenstr != NULL) {
    content_length = atoi(lenstr);
    buffer = (char*)malloc(sizeof(char) * content_length + 1);
    FCGX_GetStr(buffer, content_length, request.in);
    buffer[content_length] = '\0';
  }
  else { /* null content length */
    exit(1);
  }
  return buffer;
}


char *get_GET(FCGX_Request &request)
{
  char *buffer = FCGX_GetParam("QUERY_STRING", request.envp);

  if (buffer == NULL) {
    exit(1);
  }
  return buffer;
}

char* get_params(FCGX_Request &request) 
{
  char *input;
  char *request_method = FCGX_GetParam("REQUEST_METHOD", request.envp);
  if (!strcmp(request_method,"POST"))
    return get_POST(request);
  else if (!strcmp(request_method,"GET"))
    return get_GET(request);
  else { /* error: invalid request method */
    exit(1);
  }
}

void initUrlParam(std::map<std::string, std::string> &paraMap, std::string &paramStr)
{
    std::vector<std::string> paramList;
    int count = Utility::split(paramStr, " ", paramList);
    for(int i = 0; i != count; ++i)
    {
        paraMap[paramList[i]] = "";
    }
}

bool paramsExpect(const std::string &paraStr, std::map<std::string, std::string> &paraMap)
{
    //split para
    int mapSize = paraMap.size();
    std::vector<std::string> paraList;
    if (Utility::split(paraStr, "&", paraList) != mapSize)
    {
        return false;
    }
    else
    {
        for(std::vector<std::string>::iterator it = paraList.begin();
            it != paraList.end(); ++it)
        {
            std::vector<std::string> sigPara;
            if (Utility::split(*it, "=", sigPara) != 2)
            {
                return false;
            }
            else
            {
                paraMap[sigPara[0]] = sigPara[1];
            }
        }
        if (mapSize != paraMap.size())
        {
            return false;
        }
    }
    return true;
}

bool paramsExpect(llist entries, std::map<std::string, std::string> &paraMapMust, std::string *paraVMust, int size1, std::string *paraVMay, int size2)
{
    //must
    for (int i = 0; i < size1; ++i)
    {
        std::string key = *(paraVMust+i);
        std::string val = cgi_val(entries, (char*)key.c_str());

        paraMapMust[key] = val;

        if(val == "") return false;
        return false;
    }
    for (int i = 0; i < size2; ++i)
    {
        std::string key = *(paraVMay+i);
        std::string val = cgi_val(entries, (char*)key.c_str());
        paraMapMust[key] = val;
    }
    return true;
    //may
    //split para
    /*
    int mustSize = paraMapMust.size();
    int mustCount = 0;
    int maySize = paraMapMay.size();
    int mayCount = 0;
    std::vector<std::string> paraList;
    Utility::split(paraStr, "&", paraList);
    for(std::vector<std::string>::iterator it = paraList.begin();
        it != paraList.end(); ++it)
    {
        std::vector<std::string> sigPara;
        if (Utility::split(*it, "=", sigPara) != 2)
        {
            return false;
        }
        else
        {
            if (paraMapMust.find(sigPara[0]) != paraMapMust.end())
            {
                ++mustCount;
                paraMapMust[sigPara[0]] = sigPara[1];
            }
            else if (paraMapMay.find(sigPara[0]) != paraMapMay.end())
            {
                ++mayCount;
                paraMapMay[sigPara[0]] = sigPara[1];
            }
            else
            {
                return false;
            }
        }
    }
    if (mustCount != mustSize)
    {
        return false;
    }
    if (mayCount > maySize)
    {
        return false;
    }
    return true;
    */
    return true;
}


void list_create(llist *l)
{ 
  l->head = 0;
} 
  
node* list_next(node* w)
{ 
  return w->next;
} 

char x2c(char *what)
{
  register char digit;

  digit = (what[0] >= 'A' ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
  digit *= 16;
  digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));
  return(digit);
}

void unescape_url(char *url)
{
  register int x,y;

  for (x=0,y=0; url[y]; ++x,++y) {
    if((url[x] = url[y]) == '%') {
      url[x] = x2c(&url[y+1]);
      y+=2;
    }
  }
  url[x] = '\0';
}
char *newstr(char *str)
{   
  char *tempstr = (char*)malloc(sizeof(char) * strlen(str) + 1);
    
  if (tempstr != NULL) 
    strcpy(tempstr,str);
  return tempstr;
}

short on_list(llist *l, node* w)
{
  return (w != 0);
}

node* list_insafter(llist* l, node* w, entrytype item)
{
  node* newnode = (node*)malloc(sizeof(node));

  newnode->entry.name = newstr(item.name);
  newnode->entry.value = newstr(item.value);
  if (l->head == 0) {
    newnode->next = 0;
    l->head = newnode;
  }
  else if (!on_list(l,w))
    /* ERROR: can't insert item after w since w is not on l */
    exit(1);
  else {
    /* insert node after */
    if (newnode == 0) /* can assume that w != NULL */
      /* ERROR: nothing too insert after */
      exit(1);
    else {
      newnode->next = w->next;
      w->next = newnode;
    }
  }
  return newnode;
}

char *cgi_val(llist l, char *name)
{
  short FOUND = 0;
  node* window;

  window = l.head;
  while ( (window != 0) && (!FOUND) )
    if (!strcmp(window->entry.name,name))
      FOUND = 1;
    else
      window = window->next;
  if (FOUND)
    return window->entry.value;
  else 
    return NULL;
}

#if 1
int parse_CGI_encoded(llist *entries, char *buffer)
{
  int i, j, num, token;
  int len = strlen(buffer);
  char *lexeme = (char*)malloc(sizeof(char) * len + 1);
  entrytype entry;
  node *window;

  list_create(entries); 
  window = entries->head; 
  i = 0;
  num = 0;
  token = _NAME;
  while (i < len) {
    j = 0;
    while ( (buffer[i] != '=') && (buffer[i] != '&') && (i < len) ) {
      lexeme[j] = (buffer[i] == '+') ? ' ' : buffer[i];
      i++;
      j++;
    }
    lexeme[j] = '\0';
    if (token == _NAME) {
      entry.name = newstr(lexeme);
      unescape_url(entry.name);
      if ( (buffer[i] != '=') || (i == len - 1) ) {
        entry.value = (char*)malloc(sizeof(char));
        strcpy(entry.value,"");
        window = list_insafter(entries, window, entry);
        free(lexeme);
        free(entry.name);
        free(entry.value);
        if (i == len - 1) /* null value at end of expression */
          num++;
        else /* error in expression */
          return -1;
      }
      else
        token = _VALUE;
    }
    else {
      entry.value = newstr(lexeme);
      unescape_url(entry.value);
      window = list_insafter(entries, window, entry);
      free(entry.name);
      free(entry.value);
      token = _NAME;
      num++;
    }
    i++;
    j = 0;
  }
  free(lexeme);
  return num;
}
#endif
