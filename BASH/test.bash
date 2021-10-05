# rows=9
# for((i=0; i<=rows; i++))
# do
#   for((j=0; j<=i; j++))
#   do
#     echo -n " $(($i - $j))"
#   done
#   echo
# done

# n=1
# while [ $n -le 3 ]
# do
#     echo "$n"
#     (( n++ ))
#     gnome-terminal &
# done    

#not
# a=0
# while [ "$a" -lt 10 ]
# do
#     b="$a"
#     while [ "$b" -ge 0 ]
#     do 
#         echo -n "$(($b ))"
#         b=$(($b - 1))
#     done    
#     echo
#     a=$(($a + 1))
# done   

# p="Hi i am om"
# while read p
# do
#     echo $p
#     if
# done     


# cat file.txt | while read line; do
#   echo $line
# done

# not
# n=1
# until [ $n -ge 10 ] 
# do
#     echo $n
#     n=$(( n+1 ))
# done    

# vehicle=2
# case "$vehicle" in
#     # List patterns for the conditions you want to meet
#     0) echo "Rent of $vehicle is 100.";;
#     1) echo "Rent of $vehicle is 80.";;
#     2) echo "Rent of $vehicle is 60.";;
#     3) echo "Rent of $vehicle is 150.";;
#     *) echo "It is not null.";;  # match everything
# esac

# echo -e "Enter Char : \c "
# read value
# case "$value" in
#     [a-z]) echo "charecter is between a to z";;
#     [A-Z]) echo "charecter is between A to Z";;
#     [0-9]) echo "number is between 0 to 9 ";;
#     ?) echo "Entered value $value is special char";;
#     *) echo "It is not null.";;  
# esac

# #!/bin/bash wrong
# echo "Enter Basic Salary :"
# read bs
# da=$(( (40/100) * $bs ))
# echo $da
# hra=$(( (20/100) * $bs ))
# echo $hra
# gs=$(( $bs+$da+$hra ))
# echo "The gross salary : $gs"

# select name in ram jay pratik om
# do 
#     echo "$name selected"
# done    

# echo -n "Enter number : "
# read n
# x=0
# sum=0
# while [ $n -gt 0 ]
# do
#     x=$(( $n % 10 )) 
#     n=$(( $n / 10 )) 
#     sum=$(( $sum + $x ))
# done
# echo  "SUM is $sum"


echo "Enter basic salary : "
read bs
gs=$((bs+((bs/100)*40)+(bs/100)*20))
echo "gross salary is : $gs"
