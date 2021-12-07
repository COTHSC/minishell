#!/bin/bash

if [ -f "og_keybinds.log" ]
then
	echo "TESTING TERM KEYBINDING ANTE vs POST TEST..."
	sleep 1
	END_TERM_KEYBINDS=$(stty -a | grep intr | tr -d '[:space:]')
	read OG_TERM_KEYBINDS < "og_keybinds.log"
	DIFF_KEYBINDS=$(diff <(echo "$OG_TERM_KEYBINDS") <(echo "$END_TERM_KEYBINDS"))
	if [ -z "$DIFF_KEYBINDS" ]
	then
		echo "TERM KEYBINDINGS WELL RESET"
	else
		echo "/!\\TERM KEYBINDINGS NOT RESET/!\\"
		echo "ANTE TEST: "$OG_TERM_KEYBINDS""
		echo "POST TEST: "$END_TERM_KEYBINDS""
	fi
	rm -rf "og_keybinds.log"
else
	echo "SAVING ORIGINAL TERM KEYBINDINGS..."
	sleep 1
	stty sane
	OG_TERM_KEYBINDS=$(stty -a | grep intr | tr -d '[:space:]')
	echo "$OG_TERM_KEYBINDS" > "og_keybinds.log"
	echo "ORIGINAL TERM KEYBINDINGS SAVED AS FOLLOW:"
	echo -n ">> "
	echo "$OG_TERM_KEYBINDS"
fi
