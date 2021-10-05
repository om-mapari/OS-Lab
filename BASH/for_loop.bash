echo "For loop"
echo -e "\n=========================================\n"

for Variable in {1..3}
do
    echo "$Variable"
done
echo -e "\n=========================================\n"

for ((a=1; a <= 3; a++))
do
    echo $a
done
echo -e "\n=========================================\n"

for name in ["in list","hello","bye"]
do
  echo $name
done
echo -e "\n=========================================\n"


for var in my name is khan
do
  echo $var
done
echo -e "\n=========================================\n"


arrayName=(one two three four five six)
for i in "${arrayName[@]}"; do
  echo $i
done
echo -e "\n=========================================\n"
#!/bin/sh

a=0

while [ $a -lt 10 ]
do
   echo $a
   a=`expr $a + 1`
done

echo -e "\n=========================================\n"
b="1"

case "$b" in
   "1") echo "Apple ." 
   ;;
   "2") echo "bread." 
   ;;
   "3") echo "New Zealand" 
   ;;
esac