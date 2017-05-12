#!/bin/sh
ulimit -n 4096
ulimit -c unlimited

FILEPATH=$(cd `dirname $0`; pwd)
echo $FILEPATH

trap 'echo Control-c will not terminate $0. ' INT
trap 'echo Control-\ will not terminate $0. ' QUIT
trap 'echo Control-Z will not terminate $0. ' TSTP
echo "Enter any string after the prompt. When you are ready to exit ,type \"stop\"."
while true
do
echo -n "Go ahead ...>"
read
if [[ $reply==[sS]top ]]
then
   echo "break"
   echo $reply
   break
fi
done

