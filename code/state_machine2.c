/*************************************************************************
	> File Name: state_machine2.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 11:34:03 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    enum states {
                before, inside, after
            
    } state;
        int c;
        state = before;
    while((c = getchar()) != EOF) {
        if(c == '\n') {
                        putchar('\n');
                        state = before;
                    
        } else
        switch(state) {
                        case before:
            if(c != ' ') {
                                    putchar(c);
                                    state = inside;
                                
            }
                            break;
                        case inside:
            if(c == ' ') {
                                    state = after;
                                
            } else {
                                    putchar(c);
                                
            }
                            break;
                        case after:
                            break;
                    
        }
            
    }
        return 0;

}
