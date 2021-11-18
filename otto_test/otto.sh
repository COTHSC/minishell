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

del_empty_file()
{
	if ! [ -s  $1 ]
	then
		rm -rf $1
	fi
}

print_success()
{
	echo " ${BOLDGREEN}✔${RESET} ${GREEN}test $1${RESET}"
}

print_failure()
{
	echo " ${BOLDRED}✖${RESET} ${RED}test $1${RESET}"
}

print_error()
{
	echo "${BOLDRED}💣${RESET} ${RED}test $1${RESET}"
}

print_score()
{
	if [ $1 -eq $2 ]
	then
		echo "${BOLDGREEN}>> SCORE: $1 / $2 ${RESET}"
		echo "What are you looking at you hockey puck??"
		cat	"$MR_POTATO"
	else
		echo "${BOLDRED}>> SCORE: $1 / $2 ${RESET}"
		echo "GET BACK TO WORK YOU PUNK!"
		cat	"$SKELETON"
	fi
}

execute_tests()
{
	MINISHELL=$MINISHELL_PATH
	FILENAME=$1
	INPUT_FILE="./inputs/$1.txt" 
	BASH_OUT_DIR="bash_output"
	MINISHELL_OUT_DIR="minishell_output"
	DIFF_DIR="diff"
	ERROR_DIR="errors"
	del_files "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR"
	mkdir "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR"
	TEST_NO=1
	echo "CURRENT TEST: $FILENAME"
	NUMBER_OF_TEST=$(cat "$INPUT_FILE" | wc -l)
	while [ $TEST_NO -le $NUMBER_OF_TEST ]
	do
		CMD_TO_TEST="echo $(sed -n "${TEST_NO}p" $INPUT_FILE)"
		ERR_FILE=${ERROR_DIR}/${FILENAME}_$TEST_NO
		DIFF_FILE=$DIFF_DIR/diff_${TEST_NO}
		BASH_OUTPUT=${BASH_OUT_DIR}/${FILENAME}_$TEST_NO
		MINISHELL_OUTPUT=${MINISHELL_OUT_DIR}/${FILENAME}_$TEST_NO
		echo $CMD_TO_TEST | bash 2> /dev/null | bash >> "$BASH_OUTPUT" 2> /dev/null
		echo $CMD_TO_TEST | $MINISHELL  2> "$ERR_FILE" | bash >> "$MINISHELL_OUTPUT" 2> /dev/null
		del_empty_file $ERR_FILE
		diff $BASH_OUTPUT $MINISHELL_OUTPUT >> "$DIFF_FILE"
		if [ -s $DIFF_FILE ] || [ -s $ERR_FILE ] 
		then 
			if [ -s $ERR_FILE ]
			then
				print_error "$TEST_NO"
				echo -n "  ";
				cat $ERR_FILE | grep "ERROR:" | sed 's/.*ERROR://'
			else
				print_failure "$TEST_NO"
			fi
		else
			print_success "$TEST_NO"
			del_empty_file "$DIFF_FILE"
			SUCCESSFUL_TESTS=$((SUCCESSFUL_TESTS + 1))
		fi
		TEST_NO=$((TEST_NO + 1))
	done
	TESTS_TOTAL=$((TESTS_TOTAL + TEST_NO - 1))
	del_files "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR"
}

MINISHELL_PATH="../minishell"
TESTS_TOTAL=0
SUCCESSFUL_TESTS=0
MR_POTATO="./assets/mr_potato"
SKELETON="./assets/skeleton"
chmod 755 "./inputs/valid_tests.txt"
execute_tests "valid_tests"
print_score "$SUCCESSFUL_TESTS" "$TESTS_TOTAL"
