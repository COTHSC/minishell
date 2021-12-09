#!/bin/bash

check_error()
{
	BASH_ERR=$(sed -n 's/bash\: line *[0-9]\: //p' $1)
	MINISHELL_ERR=$(sed -n 's/minishell\: //p' $2)
    BASH_ERR=$(echo "$BASH_ERR" | head -1)
    #BASH_ERR=$(sed -n 1p $BASH_ERR)
	CHECK_DIFF_ERR=$(diff <(echo "$BASH_ERR") <(echo "$MINISHELL_ERR"))
    #echo "DIFF: $CHECK_DIFF_ERR"
	BASH_STATUS=$(cat $3)
	MINISHELL_STATUS=$(cat $4)
	CHECK_DIFF_STATUS=$(diff <(echo "$BASH_STATUS") <(echo "$MINISHELL_STATUS"))
	#echo "CHECK_DIFF_ERR: $CHECK_DIFF_ERR"
	#echo "CHECK_DIFF_STATUS: $CHECK_DIFF_STATUS"
	if [ -z "$CHECK_DIFF_ERR" ] && [ -z "$CHECK_DIFF_STATUS" ]
	then
		return 0
	else
		return 1
	fi
}

check_diff()
{
	DIFF=$1
	NB_LINES=$(sed -n "s/> //p;s/< //p" $DIFF | wc -l)
	NB_LINES=$((NB_LINES / 2))
	for (( c=1; c <= $NB_LINES; c++ ))
	do
		LEFT=$(sed -n "s/> //p" $DIFF | sed -n "${i}p")
		RIGHT=$(sed -n "s/< //p" $DIFF | sed -n "${i}p")
		#echo "R: "$RIGHT" -- L: "$LEFT""
		if [ "$LEFT" != "$RIGHT" ]
		then
			return 1;
		fi
	done
	return 0;
}

