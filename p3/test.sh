#!/bin/bash

IFS=$'\r\n' rightanswers=(`<rightanswers`)

failcount=0

# now just compare the differences:
i=0
for f in ./testdata/t* ; do
	yours=$(./wordcount <$f | awk 'BEGIN{OFS = "\t"} {print $1, $2, $3, $4, $5}')
	if [[ $yours != ${rightanswers[$i]} ]]; then
		echo "Your code fails on input $f"
		echo "should have had:"
		echo "${rightanswers[$i]}"
		echo "but you had:"
		echo $yours
		(( failcount++ ))
	fi
	(( i++ ))
done

if [[ "$failcount" == 0 ]]; then
	echo "Test passed :D"
fi
