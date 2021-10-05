echo "enter a : "
read a
echo "enter b : "
read b
if [ $a -eq $b ]
then
    echo "$a is not equel to $b"
elif [ $a -lt $b ]
then
    echo "$a is less than $b"
else
    echo "$a is greater than $b"    
fi  