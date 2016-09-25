#!/bin/bash

# small test; memory usage unimportant.
IFS=$'\r\n' rightanswers=(`<soutput`)
youranswers=(`./main <testinput.cpp`)

failcount=0

# now just compare the differences:
for (( i = 0; i < ${#rightanswers[@]}; i++ )); do
	[[ -z "${youranswers[$i]}" ]] && failcount=1 && echo "Insufficient output." && exit 1

	if [[ "${youranswers[$i]}" != "${rightanswers[$i]}" ]]; then
		echo "Your code fails on ${rightanswers[$i-1]}"
		echo -e "You had\t\t ${youranswers[$i]}"
		echo -e "Should have had\t ${rightanswers[$i]}"
		let "failcount = failcount + 1"
	fi
done

if [[ "$failcount" == 0 ]]; then
	echo "Test passed :D"
fi
