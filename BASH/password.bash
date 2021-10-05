#!/bin/bash

#How to make Silent Value Like Password?

echo "Enter Username"
read user_name
echo "Enter Password"
# Read Password
read -s -p "reading password..." password
echo -e "\n===================================================="
echo -e "Username = $user_name \nPassword = $password"

echo -e "\n===================================================="
# way 2
echo -n Password: 
read -s password
echo
# Run Command
echo $password