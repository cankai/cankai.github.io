#########################################################################
# File Name: transpose_file.sh
# Brief: )
# Author: Chen Kai(ischenkai@qq.com)
# Home: http://www.chenkai.me
# Created Time: 2017年05月01日 星期一 15时01分23秒
#########################################################################

#########################################################################
#Given a text file file.txt, transpose its content.
#
#You may assume that each row has the same number of columns and each field is separated by the ' ' character.
#
#For example, if file.txt has the following content:
#
#name age
#alice 21
#ryan 30
#Output the following:
#
#name alice ryan
#age 21 30
#########################################################################

#!/bin/bash

awk '
{
    for (i = 1; i <= NF; i++) {
        if (NR == 1){
            s[i]=$i;
        }else{
            s[i] = s[i] " " $i;
        }
    }
}
END {
    for (i = 1; s[i] != ""; i++) {
        print s[i];
    }
}' file.txt
