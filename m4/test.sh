#!/usr/bin/env ksh
integer counter=0
until [[ ${counter} -gt 10 ]]
do
    echo ${counter}
    ((counter++))
done
