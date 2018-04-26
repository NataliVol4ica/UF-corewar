./corewar -l 1 $1 > mylog
 ./their/corewar -v 16 $1 > log
 diff log mylog > differ