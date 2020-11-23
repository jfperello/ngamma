#!/bin/bash

if [ $# -eq 0 ]
then
echo "Not enough arguments for the run."
echo "./oneshot.sh [Elow] [Ehigh] [Estep]"
else
#for (( i=$1; i<$2; i+=$3))
for i in $(seq $1 $3 $2)
do
j=$(echo "$i + $3" |bc)
sed -e 's/MinRun: 0 MaxRun: 0/MinRun: '"$j"' MaxRun: '"$j"'/' binary2root_input.txt> input1.tmp
./bin/binary2root input1.tmp
sed -e 's/MinRun: 0  MaxRun: 0/MinRun: '"$j"'  MaxRun: '"$j"'/' analyzer_input.txt> input2.tmp
./bin/analyzer -t input2.tmp
done
fi
