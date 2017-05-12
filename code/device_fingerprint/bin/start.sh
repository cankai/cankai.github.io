#!/bin/sh
ulimit -n 4096
ulimit -c unlimited

FILEPATH=$(cd `dirname $0`; pwd)
echo $FILEPATH
$FILEPATH/supervise.e $FILEPATH >> /dev/null 2>&1 &
#change to parant dir
supervise $FILEPATH &
exit


