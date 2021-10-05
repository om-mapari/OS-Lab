#!/bin/sh
a=10
b=20

echo "a is 10"
echo "b is 20"
val= expr $a + $b'
echo "a + b : $val"

val='expr $a - $b
echo "a - b : $val"
val='expr $a \* $b'

echo "a * b : $val"
val= expr $b / $a'

echo "b / a : $val"
val='expr $6 % $a
echo "b % a : $val"

val= expr $b = $a
echo "b = a : $val"
val= expr $b != Sa'
