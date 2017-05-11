/*************************************************************************
	> File Name: state_machine4.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 11:35:31 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

enum states { before = 0, inside = 1, after = 2  };
struct branch {
        unsigned char new_state:2;
        unsigned char should_putchar:1;

};
struct branch the_table[3][3] = {
                     /* ' '         '\n'        others */
        /* before */ { {before,0}, {before,1}, {inside,1}  },
        /* inside */ { {after, 0}, {before,1}, {inside,1}  },
        /* after  */ { {after, 0}, {before,1}, {after, 0}  }

};
void step(enum states *state, int c)
{
        int idx2 = (c == ' ') ? 0 : (c == '\n') ? 1 : 2;
        struct branch *b = & the_table[*state][idx2];
        //set state
        *state = (enum states)(b->new_state);
        //do action
        if(b->should_putchar) putchar(c);

}
int main(void)
{
        int c;
        enum states state = before;
        while((c = getchar()) != EOF)
            step(&state, c);
        return 0;

}
