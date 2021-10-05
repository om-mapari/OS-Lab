# Write a program to implement an address book with options given below: 
# a) Create address book. 
# b) View address book. 
# c) Insert a record. 
# d) Delete a record. 
# e) Modify a record. 
# f) Exit

#!/bin/sh
while :
do
echo -e "\n===============================================\n"
echo "*. SELECT FROM MENU";
echo "0. CREATE NEW LAB RECORD LOGS"
echo "1. INSERT RECORD"
echo "2. VIEW RECORD"
echo "3. VIEW SORTED RECORD  "
echo "4. DELETE RECORD"
echo "5. MODIFY RECORD"
echo "6. EXTI  "
echo -n "ENTER CHOICE [1-4] : "
read choice
case $choice in
  0) 	#creation of lab
        echo "ENTER FILENAME" 
		read fileName
		if [ -e $fileName ] ; then	
			echo "$fileName EXIST..."
		else	
			echo  -e "NAME\t\tROLL NO\t\tBOOK NAME\n==============================================\n" >> $fileName #create file 
            echo "THE FILE WITH [$fileName] CREATED SUCCESSFULLY"
		fi
		;;

  2)    #VIEW RECORD
        cat $fileName 
        ;;

  3)	#VIEW SORTED RECORD
		sort $fileName
		;;

  1)    #INSERT RECORD
        flag=1
		while [ "$flag" -gt 0 ]
		do
			echo -e "\nENTER NAME"
			read name
			echo "ENTER ROLL NO OF [$name]"
			read roll_no
			echo "ENTER BOOK NAME BORROWED BY [$name]"
			read book
			echo -e "$name \t\t$roll_no\t\t$book" | cat >> $fileName
            echo -e "\n===============================================\n"
			echo -e "ENTER 0 TO STOP \nENTER 1 ADD NEXT RECORD"
			read flag
		done
		;;

  4)    #DELETE RECORD
  		echo -e "DELETE RECORD\nENTER NAME/ROLL NO"
		read string_data
		temp="temp"
		grep -v $string_data $fileName | cat >> $temp 
		rm $fileName 
		cat $temp | cat >> $fileName
		rm $temp
		;;

  5)    #Modify a record. 
     	echo "MODIFY RECORD\nENTER NAME/ROLL NO"
		read string_data
		temp="temp"
		grep -v $string_data $fileName | cat >> $temp
		rm $fileName
		cat $temp | cat >> $fileName
		rm $temp
		echo -e "\nENTER NAME"
		read name
		echo "ENTER ROLL NO OF [$name]"
		read roll_no
		echo "ENTER BOOK NAME BORROWED BY [$name]"
		read book
		echo -e "$name \t\t$roll_no\t\t$book" | cat >> $fileName
		;;

  6)    echo "QUITING ..."
        exit;;

  *) echo "INVALID OPTION";;
esac
done