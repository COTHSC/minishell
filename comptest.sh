rm -f ./output_tests/temp*
make fclean --silent
make debug --silent
make clean --silent
clear
cd otto_test && ./otto.sh && cd ..
rm -f ./output_tests/temp*

