/*************************************************************************
	> File Name: state_machine5.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 11:47:23 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
class StateMachine {
        enum states { before = 0, inside = 1, after = 2  } state;
    struct branch {
                enum states new_state:2;
                int should_putchar:1;
            
    };
        static struct branch the_table[3][3];
    public:
        StateMachine() : state(before) {}
    void FeedChar(int c) {
                int idx2 = (c == ' ') ? 0 : (c == '\n') ? 1 : 2;
                struct branch *b = & the_table[state][idx2];
                state = b->new_state;
                if(b->should_putchar) putchar(c);
            
    }

};
struct StateMachine::branch StateMachine::the_table[3][3] = {
                     /* ' '         '\n'        others */
        /* before */ { {before,0}, {before,1}, {inside,1}  },
        /* inside */ { {after, 0}, {before,1}, {inside,1}  },
        /* after  */ { {after, 0}, {before,1}, {after, 0}  }

};
int main(void)
{
        int c;
        StateMachine machine;
        while((c = getchar()) != EOF)
            machine.FeedChar(c);
        return 0;

}
