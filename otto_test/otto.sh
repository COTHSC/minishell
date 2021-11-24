#!/bin/bash

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
	if [ $QUIET_SWITCH -eq 0 ]
	then
		cat "${OTTO_WELCOME}"
		echo -e "${BOLDBLUE}\nWELCOME TO OTTO!! AN AUTOMATED TEST SUITE FOR MINISHELL$RESET"
		sleep 2
		echo
	fi
}

print_success()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e " ${BOLDGREEN}✔${RESET} ${GREEN}test $1${RESET}"
	fi
}

print_failure()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e " ${BOLDRED}✖${RESET} ${RED}test $1${RESET}"
	fi
}

print_crash()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e "${BOLDRED}💣${RESET} ${RED}test $1${RESET}"
	fi
}

print_test_name()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e "\n${BOLDBLUE}CURRENT TEST: $1${RESET}"
	fi
}

print_score()
{
	MR_POTATO="./assets/mr_potato"
	SKELETON="./assets/skeleton"
	if [ $1 -eq $2 ]
	then
		if [ $QUIET_SWITCH -eq 0 ]
		then
			cat	"$MR_POTATO"
		fi
		echo -e "${BOLDGREEN}>> SCORE: $1 / $2 ${RESET}"
		echo -e "What are you looking at you hockey puck??"
	else
		if [ $QUIET_SWITCH -eq 0 ]
		then
			cat	"$SKELETON"
		fi
		echo -e "${BOLDRED}>> SCORE: $1 / $2 ${RESET}"
		echo -e "GET BACK TO WORK YOU PUNK!"
	fi
}

execute_basic_tests()
{
	MINISHELL=$MINISHELL_PATH
	TEST_NAME=$1
	TEST_FILE="./inputs/$TEST_NAME"
	TEST_NO=1
	NUMBER_OF_TEST=$(cat "$TEST_FILE" | wc -l)
	print_test_name "BASIC"
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
		if [ -s $ERR_FILE ]
		then
			print_crash "$TEST_NO"
			#echo -n "  ";
			cat $ERR_FILE | grep "ERROR:" | sed 's/.*ERROR://'
		elif [ -s $DIFF_FILE ]
		then 
			print_failure "$TEST_NO"
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

check_diff()
{
	DIFF=$1
	NB_LINES=$(sed -n "s/> //p;s/< //p" $DIFF | wc -l)
	NB_LINES=$((NB_LINES / 2))
	for (( c=1; c <= $NB_LINES; c++ ))
	do
		LEFT=$(sed -n "s/> //p" $DIFF | sed -n "${i}p")
		RIGHT=$(sed -n "s/< //p" $DIFF | sed -n "${i}p")
		if [ LEFT != RIGHT ]
		then
			return 1;
		fi
	done
	return 0;
}

execute_redirections_tests()
{
	MINISHELL="../../$MINISHELL_PATH"
	TEST_NAME=$1
	REDIRECT="/redirection"
	mkdir "$DIFF_DIR$REDIRECT"
	TEST_FILE="./inputs/$TEST_NAME"
	TEST_NO=1
	print_test_name "REDIRECTIONS"
	NUMBER_OF_TEST=$(cat "$TEST_FILE" | wc -l)
	while [ $TEST_NO -le $NUMBER_OF_TEST ]
	do
		CMD_TO_TEST="echo $(sed -n "${TEST_NO}p" $TEST_FILE)"
		ERR_FILE="${ERROR_DIR}/${TEST_NAME}_$TEST_NO"
		DIFF_FILE=$DIFF_DIR${REDIRECT}/${TEST_NAME}_${TEST_NO}
		BASH_OUTPUT=${BASH_OUT_DIR}${REDIRECT}_${TEST_NO}/
		MINISHELL_OUTPUT=${MINISHELL_OUT_DIR}${REDIRECT}_${TEST_NO}/
		mkdir $BASH_OUTPUT $MINISHELL_OUTPUT
		$(cd $BASH_OUTPUT; $CMD_TO_TEST | bash 2> /dev/null)
		$(cd $MINISHELL_OUTPUT; $CMD_TO_TEST | $MINISHELL 2> "../../$ERR_FILE")
		diff -r $BASH_OUTPUT $MINISHELL_OUTPUT >> "$DIFF_FILE"
		DIFF_IS_SCRAMBLED=0
		check_diff "$DIFF_FILE"
		DIFF_IS_SCRAMBLED=$?
		if [ -s $ERR_FILE ]
		then 
			print_crash "$TEST_NO"
		elif [ -s $DIFF_FILE ] && [ $DIFF_IS_SCRAMBLED -eq 0 ]
		then
			print_failure "$TEST_NO"
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

check_error()
{
	BASH_ERR=$(sed -n 's/bash\: line *[0-9]\: //p' $1)
	MINISHELL_ERR=$(sed -n 's/minishell\: //p' $2)
	CHECK_DIFF_ERR=$(diff <(echo "$BASH_ERR") <(echo "$MINISHELL_ERR"))
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

execute_errors_and_exit_status_tests()
{
	MINISHELL="../../$MINISHELL_PATH"
	TEST_NAME=$1
	ERROR_AND_EXIT_DIR="/errors_and_exit_status"
	mkdir "$DIFF_DIR$ERROR_AND_EXIT_DIR"
	TEST_FILE="./inputs/$TEST_NAME"
	TEST_NO=1
	print_test_name "ERRORS AND EXIT STATUS"
	NUMBER_OF_TEST=$(cat "$TEST_FILE" | wc -l)
	while [ $TEST_NO -le $NUMBER_OF_TEST ]
	do
		CMD_TO_TEST="echo $(sed -n "${TEST_NO}p" $TEST_FILE)"
		DIFF_FILE=$DIFF_DIR${ERROR_AND_EXIT_DIR}/${TEST_NAME}_${TEST_NO}
		BASH_OUTPUT=${BASH_OUT_DIR}${ERROR_AND_EXIT_DIR}_${TEST_NO}/
		MINISHELL_OUTPUT=${MINISHELL_OUT_DIR}${ERROR_AND_EXIT_DIR}_${TEST_NO}/
		mkdir $BASH_OUTPUT $MINISHELL_OUTPUT
		$(cd $BASH_OUTPUT; $CMD_TO_TEST | bash > /dev/null 2> err ; echo $? > status)
		$(cd $MINISHELL_OUTPUT; $CMD_TO_TEST | $MINISHELL > /dev/null 2> err ; echo $? > status)
		diff -r $BASH_OUTPUT $MINISHELL_OUTPUT >> "$DIFF_FILE"
		check_error "${BASH_OUTPUT}err" "${MINISHELL_OUTPUT}err" "${BASH_OUTPUT}status" "${MINISHELL_OUTPUT}status"
		CONFIRMED_ERROR=$?
		if [ -s $DIFF_FILE ] && [ $CONFIRMED_ERROR -eq 1 ]
		then
			print_failure "$TEST_NO"
		else
			print_success "$TEST_NO"
			del_empty_file "$DIFF_FILE"
			SUCCESSFUL_TESTS=$((SUCCESSFUL_TESTS + 1))
		fi
		TEST_NO=$((TEST_NO + 1))
	done
	TESTS_TOTAL=$((TESTS_TOTAL + TEST_NO - 1))
}

QUIET_SWITCH=0
CHECK_QUIET=$(diff <(echo "$1") <(echo "-q"))
if [ -z "$CHECK_QUIET" ]
then
	QUIET_SWITCH=1
fi
MINISHELL_PATH="../minishell"
TESTS_TOTAL=0
SUCCESSFUL_TESTS=0
BASH_OUT_DIR="bash_output"
MINISHELL_OUT_DIR="minishell_output"
DIFF_DIR="diff"
ERROR_DIR="errors"
del_files_and_dirs "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR"
mkdir "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR"
print_welcome
chmod 755 ./inputs/*tests*
execute_basic_tests "basic_tests"
execute_redirections_tests "redirections_tests"
execute_errors_and_exit_status_tests "errors_tests"
print_score "$SUCCESSFUL_TESTS" "$TESTS_TOTAL"
#del_files_and_dirs "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR"
del_empty_dirs "$ERROR_DIR" "$DIFF_DIR"
