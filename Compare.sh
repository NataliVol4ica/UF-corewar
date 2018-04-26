./corewar -l 1 $1 > mylog
 ./their/corewar -v 4 $1 > log
 diff log mylog > differ