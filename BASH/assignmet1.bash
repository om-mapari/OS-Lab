#Assignment 1:Wrtie A program  to implement an address book with options given:
#a) create address book
#b)View address book
#c)Insert a record
#d)Delete a record
#e)Modify a record
#f) Exit


#!/bin/sh
choice = 0
while :
do
	echo -e " 1) create address book\n2)View address book\n3)Insert a record\n4)Delete a record\n5)Modify a record\n6) Exit:"
								    #-e is used to neglect any escape keys	
	read choice
	case $choice in
		1) #creation of address book
			echo "Enter Title of Address Book : "
			read book
			touch $book ;;

		2) #Viewing the address book
			cat $book ;;
		
		3) #Insertion of record
			echo "Enter Student roll no. : "
			read rno
			echo "Enter Student Name : "
			read sname
			echo "Enter Student Branch/Department : "
			read sdep
			echo "Enter Student's Current Residence City : "
			read curcity
			echo -e "$rno $sname $sdep $curcity" >> $book  #pushing the data of one student in book
			sort $book >TempDB                            #pushing whole book in temporary database
			mv TempDB $book;;			      #moving TempDB details back in book

		4) #deletion of the record
			echo "Enter Roll no. you want to delete : "
			read rno
			grep -v "$rno" $book >> TempDB
			sort $book > TempDB
			mv TempDB $book ;;

		5) #modifying the record
			echo "Enter the Roll number You want to modify :"
			read rno
			grep "$rno" $book >> TempDB
						echo "Enter Student roll no. : "
			read rno
			echo "Enter Student New Name : "
			read sname
			echo "Enter Student New Branch/Department : "
			read sdep
			echo "Enter Student's New Current Residence City : "
			read curcity
			echo -e "$rno $sname $sdep $curcity" >> $book  #pushing the data of one student in book
			sort $book >TempDB                            #pushing whole book in temporary database
			mv TempDB $book;;			      #moving TempDB details back in book"
			

		6) #Exiting statement
			exit ;;
	esac
done 

