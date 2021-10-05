#!/bin/bash
array[0]=valA                # how to define an array
array[1]=valB
array[2]=valC
array=([2]=valC [0]=valA [1]=valB)  # another way
array=(valA valB valC)              # and another

# Declare an array with 6 elements
array0=(one two three four five six)

# Print first element
echo ${array0[0]} # => "one"

# Print all elements
echo ${array0[@]} # => "one two three four five six"

# Print number of elements
echo ${#array0[@]} # => "6"

# Print number of characters in third element
echo ${#array0[2]} # => "5"

# Print 2 elements starting from forth
echo ${array0[@]:3:2} # => "four five"

# Print all elements. Each of them on new line.
for i in "${array0[@]}"; do
    echo "$i"
done