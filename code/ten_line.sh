#########################################################################
# File Name: ten_line.sh
# Brief: print the ten line of a file
# Author: Chen Kai(ischenkai@qq.com)
# Home: http://www.chenkai.me
# Created Time: 2017年05月01日 星期一 14时54分31秒
#########################################################################

#########################################################################
#For example, assume that file.txt has the following content:
#
#Line 1
#Line 2
#Line 3
#Line 4
#Line 5
#Line 6
#Line 7
#Line 8
#Line 9
#Line 10
#Your script should output the tenth line, which is:
#Line 10
#########################################################################

#!/bin/bash
#solution one use sed
sed -n '10p' file,txt
#solution two use sed
awk 'NR==10 {print $0}' file.txt
