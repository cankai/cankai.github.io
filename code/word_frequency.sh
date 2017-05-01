#########################################################################
# File Name: word_frequency.sh
# Brief: )
# Author: Chen Kai(ischenkai@qq.com)
# Home: http://www.chenkai.me
# Created Time: 2017年05月01日 星期一 15时04分35秒
#########################################################################

#########################################################################
#Write a bash script to calculate the frequency of each word in a text file words.txt.
#
#For simplicity sake, you may assume:
#
#words.txt contains only lowercase characters and space ' ' characters.
#Each word must consist of lowercase characters only.
#Words are separated by one or more whitespace characters.
#For example, assume that words.txt has the following content:
#
#the day is sunny the the
#the sunny is is
#Your script should output the following, sorted by descending frequency:
#the 4
#is 3
#sunny 2
#day 1
#########################################################################

#!/bin/bash
egrep -o "\b[[:alpha:]]+\b" "words.txt" | awk '{ count[$0]++  } END{ for(ind in count) { printf("%s %d\n",ind,count[ind]);  }  }' | sort -nrk2


