/*************************************************************************
	> File Name: state_machine3.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 11:34:32 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

enum states { before, inside, after  };
void step(enum states *state, int c)
{
    if(c == '\n') {
                putchar('\n');
                *state = before;
            
    } else
    switch(*state) {
                case before:
        if(c != ' ') {
                            putchar(c);
                            *state = inside;
                        
        }
                    break;
                case inside:
        if(c == ' ') {
                            *state = after;
                        
        } else {
                            putchar(c);
                        
        }
                    break;
                case after:
                    break;
            
    }

} 
int main(void)
{
        int c;
        enum states state = before;
    while((c = getchar()) != EOF) {
                step(&state, c);
            
    }
        return 0;

}
