#!/bin/sh
ulimit -n 4096
ulimit -c unlimited

FILEPATH=$(cd `dirname $0`; pwd)
cd ${FILEPATH}
killall -9 cgi_device && sleep 3

/usr/local/bin/spawn-fcgi -a 127.0.0.1 -p 8081 -f ./cgi_device



