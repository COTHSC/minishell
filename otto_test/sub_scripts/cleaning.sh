#!/bin/bash

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

