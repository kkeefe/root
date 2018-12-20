#!/bin/bash






#basic introduction to how to define and use sinmple arithmatic operations in bash..
# let examples
a=5
let "a = 5 + 4" #need the ""s if you're going to have spaces;
echo $a		#result is 9

a=5
let a=5+4
echo $a				# result is again 9

# expr examples
a=5
a=`expr 5 + 4`
echo $a				#result is 9 again.. 

# a=5
# a=5+4
# echo $a				# result is "5 + 4 "

a=5;
let "a = 5 % 3"
echo $a				# module which shows the remainder..

