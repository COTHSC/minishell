#!/bin/bash
source sub_scripts/cleaning.sh
source sub_scripts/colors.sh
source sub_scripts/print_msg.sh
source sub_scripts/smart_diff.sh

execute_basic_tests()
{
	MINISHELL="$MINISHELL_PATH"
	TEST_NAME=$1
	BASIC_TEST_DIR="/""$TEST_NAME"
	DIFF_TEST_DIR="$DIFF_DIR""$BASIC_TEST_DIR"
	mkdir -p "$DIFF_TEST_DIR"
	TEST_FILE="./inputs/$TEST_NAME"
	TEST_NO=1
	NUMBER_OF_TEST=$(cat "$TEST_FILE" | wc -l)
	print_test_name "BASIC"
	while [ $TEST_NO -le $NUMBER_OF_TEST ]
	do
		CMD_TO_TEST="echo $(sed -n "${TEST_NO}p" $TEST_FILE)"
		ERR_FILE="$ERROR_DIR"/"$TEST_NAME"_"$TEST_NO"
		DIFF_FILE=$DIFF_TEST_DIR/${TEST_NAME}_$TEST_NO
		BASH_OUTPUT="$BASH_OUT_DIR""$BASIC_TEST_DIR"_"$TEST_NO"
		MINISHELL_OUTPUT=${MINISHELL_OUT_DIR}${BASIC_TEST_DIR}_$TEST_NO
		mkdir $BASH_OUTPUT $MINISHELL_OUTPUT
		$($CMD_TO_TEST | bash > ${BASH_OUTPUT}/out 2> /dev/null ; echo $? > ${BASH_OUTPUT}/status)
		$($CMD_TO_TEST | $MINISHELL > ${MINISHELL_OUTPUT}/out 2> "$ERR_FILE" ; echo $? > ${MINISHELL_OUTPUT}/status)
		if [ -s "$ERR_FILE" ]
		then
			CHECK_CRASH=$(cat $ERR_FILE | grep "ERROR:")
			if [ ! -z "${CHECK_CRASH}" ]
			then
				print_crash "$TEST_NO" "$CMD_TO_TEST"
			fi
		fi
		del_empty_file $ERR_FILE
		diff -r $BASH_OUTPUT $MINISHELL_OUTPUT >> "$DIFF_FILE"
		if [ -s "$DIFF_FILE" ]
		then
			print_failure "$TEST_NO" "$CMD_TO_TEST"
		else
			print_success "$TEST_NO"
			del_empty_file "$DIFF_FILE"
			SUCCESSFUL_TESTS=$((SUCCESSFUL_TESTS + 1))
		fi
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
		if [ -s "$ERR_FILE" ]
		then
			CHECK_CRASH=$(cat $ERR_FILE | grep "ERROR:" | sed 's/.*ERROR://')
			if [ ! -z "${CHECK_CRASH}" ]
			then
				print_crash "$TEST_NO" "$CMD_TO_TEST"
			fi
		elif [ -s "$DIFF_FILE" ] && [ "$DIFF_IS_SCRAMBLED" -eq 0 ]
		then
			print_mild_failure "$TEST_NO" "$CMD_TO_TEST"
			MILD_FAILURE=$((MILD_FAILURE + 1))
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
		if [ -s "$ERR_FILE" ]
		then
			CHECK_CRASH=$(cat $ERR_FILE | grep "ERROR:" | sed 's/.*ERROR://')
			if [ ! -z "${CHECK_CRASH}" ]
			then
				print_crash "$TEST_NO" "$CMD_TO_TEST"
			fi
		fi
		if [ -s "$DIFF_FILE" ] && [ $CONFIRMED_ERROR -eq 1 ]
		then
			print_failure "$TEST_NO" "$CMD_TO_TEST"
		else
			print_success "$TEST_NO"
			del_empty_file "$DIFF_FILE"
			SUCCESSFUL_TESTS=$((SUCCESSFUL_TESTS + 1))
		fi
		TEST_NO=$((TEST_NO + 1))
	done
	TESTS_TOTAL=$((TESTS_TOTAL + TEST_NO - 1))
}

check_tty_keybinds()
{
	print_test_name "CHECK TERM KEYBINDS"
	END_TERM_KEYBINDS=$(stty -a | grep intr | tr -d '[:space:]')
	#echo "OG: $OG_TERM_KEYBINDS -- ETK: $END_TERM_KEYBINDS"
	DIFF_KEYBINDS=$(diff <(echo "$OG_TERM_KEYBINDS") <(echo "$END_TERM_KEYBINDS"))
	if [ -z "$DIFF_KEYBINDS" ]
	then
		print_success "1"
		SUCCESSFUL_TESTS=$((SUCCESSFUL_TESTS + 1))
	else
		print_failure "1"
		echo "$DIFF_KEYBINDS" > "diff/diff_keybinds"
	fi
	TESTS_TOTAL=$((TESTS_TOTAL + 1))
}

check_quiet()
{
	CHECK_QUIET=$(diff <(echo "$1") <(echo "-q"))
	if [ -z "$CHECK_QUIET" ]
	then
		QUIET_SWITCH=1
	fi
}

compile_minishell()
{
	clear
	make -C ${MINISHELL_ROOT} fclean --silent
	make -C ${MINISHELL_ROOT} debug --silent
	make -C ${MINISHELL_ROOT} clean --silent
	clear
}

MINISHELL_ROOT="../"

QUIET_SWITCH=0
check_quiet $1
MINISHELL_PATH="${MINISHELL_ROOT}minishell"
compile_minishell
stty sane
OG_TERM_KEYBINDS=$(stty -a | grep intr | tr -d '[:space:]')
TESTS_TOTAL=0
MILD_FAILURE=0 #Count failure for redirection + pipe tests, as the output depends on execution speed on piped cmds
SUCCESSFUL_TESTS=0
BASH_OUT_DIR="bash_output"
MINISHELL_OUT_DIR="minishell_output"
DIFF_DIR="diff"
ERROR_DIR="errors"
del_files_and_dirs "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR" "failed_tests" "crash_tests"
mkdir -p "$ERROR_DIR" "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR" "$DIFF_DIR"
print_welcome
chmod 755 ./sub_scripts/*
chmod 755 ./inputs/*tests*
mkdir ./inputs/cannot_access_dir ; chmod 000 ./inputs/cannot_access_dir
touch ./inputs/cannot_access_file ; chmod 000 ./inputs/cannot_access_file
execute_basic_tests "basic_tests"
execute_redirections_tests "redirections_tests"
execute_errors_and_exit_status_tests "errors_tests"
check_tty_keybinds
print_score "$SUCCESSFUL_TESTS" "$TESTS_TOTAL" "$MILD_FAILURE"
del_files_and_dirs "$BASH_OUT_DIR" "$MINISHELL_OUT_DIR"
del_files_and_dirs "./inputs/cannot_access_dir" "./inputs/cannot_access_file"
del_empty_dirs "$ERROR_DIR" "$DIFF_DIR"
