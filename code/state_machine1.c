/*************************************************************************
	> File Name: state_machine1.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 11:31:58 2017
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
        switch(state) {
                        case before:
            if(c == '\n') {
                                    putchar('\n');
                                
            } else
            if(c != ' ') {
                                    putchar(c);
                                    state = inside;
                                
            }
                            break;
                        case inside:
            switch(c) {
                                    case ' ':  state = after; break;
                                    case '\n':
                                        putchar('\n');
                                        state = before;
                                        break;
                                    default:   putchar(c);
                                
            }
                            break;
                        case after:
            if(c == '\n') {
                                    putchar('\n');
                                    state = before;
                                
            }
                    
        }
            
    }
        return 0;
}
