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

del_files_and_dirs()
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

del_empty_dirs()
{
	for dir in "$@"
	do
		if [ -z "$(ls -A $dir)" ]
		then
			rm -rf $dir
		fi
	done
}

print_welcome()
{
	OTTO_WELCOME="./assets/otto_welcome"
	cat "${OTTO_WELCOME}"	
	echo "${BOLDBLUE}WELCOME TO OTTO!! AN AUTOMATED TEST SUITE FOR MINISHELL$RESET"
	sleep 2
	echo
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
	MR_POTATO="./assets/mr_potato"
	SKELETON="./assets/skeleton"
	if [ $1 -eq $2 ]
	then
		cat	"$MR_POTATO"
		echo "${BOLDGREEN}>> SCORE: $1 / $2 ${RESET}"
		echo "What are you looking at you hockey puck??"
	else
		cat	"$SKELETON"
		echo "${BOLDRED}>> SCORE: $1 / $2 ${RESET}"
		echo "GET BACK TO WORK YOU PUNK!"
	fi
}

execute_basic_tests()
{
	MINISHELL=$MINISHELL_PATH
	TEST_NAME=$1
	TEST_FILE="./inputs/$TEST_NAME"
	del_files_and_dirs "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR"
	mkdir "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR"
	TEST_NO=1
	echo "\n${BOLDBLUE}CURRENT TEST: BASIC TESTS${RESET}"
	NUMBER_OF_TEST=$(cat "$TEST_FILE" | wc -l)
	while [ $TEST_NO -le $NUMBER_OF_TEST ]
	do
		CMD_TO_TEST="echo $(sed -n "${TEST_NO}p" $TEST_FILE)"
		ERR_FILE=${ERROR_DIR}/${TEST_NAME}_$TEST_NO
		DIFF_FILE=$DIFF_DIR/diff_${TEST_NO}
		BASH_OUTPUT=${BASH_OUT_DIR}/${TEST_NAME}_$TEST_NO
		MINISHELL_OUTPUT=${MINISHELL_OUT_DIR}/${TEST_NAME}_$TEST_NO
		echo $CMD_TO_TEST | bash 2> /dev/null | bash >> "$BASH_OUTPUT" 2> /dev/null
		echo $CMD_TO_TEST | $MINISHELL  2> "$ERR_FILE" | bash >> "$MINISHELL_OUTPUT" 2> /dev/null
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
		del_empty_file $ERR_FILE
		TEST_NO=$((TEST_NO + 1))
	done
	TESTS_TOTAL=$((TESTS_TOTAL + TEST_NO - 1))
}

execute_redirections_tests()
{
	MINISHELL="../../$MINISHELL_PATH"
	TEST_NAME=$1
	REDIRECT="/redirection"
	mkdir "$DIFF_DIR$REDIRECT"
	TEST_FILE="./inputs/$TEST_NAME"
	TEST_NO=1
	echo "\n${BOLDBLUE}CURRENT TEST: REDIRECTION TESTS${RESET}"
	NUMBER_OF_TEST=$(cat "$TEST_FILE" | wc -l)
	while [ $TEST_NO -le $NUMBER_OF_TEST ]
	do
		CMD_TO_TEST="echo $(sed -n "${TEST_NO}p" $TEST_FILE)"
		ERR_FILE="../../${ERROR_DIR}/${TEST_NAME}_$TEST_NO"
		DIFF_FILE=$DIFF_DIR${REDIRECT}/${TEST_NAME}_${TEST_NO}
		BASH_OUTPUT=${BASH_OUT_DIR}${REDIRECT}_${TEST_NO}/
		MINISHELL_OUTPUT=${MINISHELL_OUT_DIR}${REDIRECT}_${TEST_NO}/
		mkdir $BASH_OUTPUT $MINISHELL_OUTPUT
		$(cd $BASH_OUTPUT; $CMD_TO_TEST | bash 2> /dev/null)
		$(cd $MINISHELL_OUTPUT; $CMD_TO_TEST | $MINISHELL 2> "$ERR_FILE")
		diff -r $BASH_OUTPUT $MINISHELL_OUTPUT >> "$DIFF_FILE"
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
		del_empty_file $ERR_FILE
		TEST_NO=$((TEST_NO + 1))
	done
	TESTS_TOTAL=$((TESTS_TOTAL + TEST_NO - 1))
}

MINISHELL_PATH="../minishell"
TESTS_TOTAL=0
SUCCESSFUL_TESTS=0
BASH_OUT_DIR="bash_output"
MINISHELL_OUT_DIR="minishell_output"
DIFF_DIR="diff"
ERROR_DIR="errors"
#BASH_ERROR_DIR="bash_errors"
#MINISHELL_ERROR_DIR="minishell_errors"
print_welcome
chmod 755 ./inputs/*
execute_basic_tests "basic_tests"
execute_redirections_tests "redirections_tests"
print_score "$SUCCESSFUL_TESTS" "$TESTS_TOTAL"
#del_files_and_dirs "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR"
del_empty_dirs "$ERROR_DIR" "$DIFF_DIR"	
