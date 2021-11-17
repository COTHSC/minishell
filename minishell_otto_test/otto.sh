#!/bin/sh

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

del_files()
{
	for file in "$@"
	do
		rm -rf $file
	done
}

execute_tests()
{
	MINISHELL=$MINISHELL_PATH
	FILENAME=$1
	TEST_FILE="$1.txt" 
	del_files "$FILENAME.bash" "$FILENAME.minishell" "$FILENAME.errors"
	TEST_NO=1
	echo "CURRENT TEST: $FILENAME"
	NUMBER_OF_TEST=$(cat "$TEST_FILE" | wc -l)
	echo "$NUMBER_OF_TEST"
	while [ $TEST_NO -le $NUMBER_OF_TEST ]
	do
		CMD_TO_TEST=$(sed -n "${TEST_NO}p" $TEST_FILE)
		echo $CMD_TO_TEST | bash >> "$FILENAME.bash" 2> /dev/null
		echo $CMD_TO_TEST | $MINISHELL >> "$FILENAME.minishell" 2> "$FILENAME.errors"
		TEST_NO=$((TEST_NO + 1))
	done
}

MINISHELL_PATH="../minishell"
chmod 755 "valid_tests.txt"
execute_tests "valid_tests"
