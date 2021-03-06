#!/bin/bash

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
	if [ "$2" ]
	then
		echo "$2" >> "failed_tests"
	fi
}

print_mild_failure()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e " ${BOLDYELLOW}~${RESET} ${YELLOW}test $1${RESET}"
	fi
	if [ "$2" ]
	then
		echo "$2" >> "failed_tests"
	fi
}

print_crash()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e "${BOLDRED}💣${RESET} ${RED}test $1${RESET}"
	fi
	echo "$2" >> "crash_tests"
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
	SCORE=$(expr $1 + $3)
	if [ "$SCORE" -eq $2 ]
	then
		if [ $QUIET_SWITCH -eq 0 ]
		then
			cat	"$MR_POTATO"
			echo -e "What are you looking at you hockey puck??"
		fi
		echo -e "${BOLDGREEN}>> SCORE: $SCORE / $2 ${RESET}"
		if [ $3 -ne 0 ]
		then
			echo -e "${BOLDYELLOW}>> WARNING: $3 POSSIBLE FAILURE DETECTED (Check redirect tests)${RESET}"
		fi
	else
		if [ $QUIET_SWITCH -eq 0 ]
		then
			cat	"$SKELETON"
			echo -e "GET BACK TO WORK YOU PUNK!"
		fi
		echo -e "${BOLDRED}>> SCORE: $1 / $2 ${RESET}"
	fi
}

