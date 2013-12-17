#!/bin/bash
./calc3p < $1
echo "NFM"
echo "  --Program--"
./pstack/apd calc_out
echo "  --Program--"
./pstack/api calc_out > nm_output
echo ""
echo "Our Program"
echo ""
./mycalc3 < $1 > wow.aa
echo "  --Program--"
more wow.aa
echo "  --Program--"
./pstack/apm < wow.aa > wow.apm
./pstack/api wow > my_output
echo ""
diff_out=$(diff nm_output my_output) # Check the compile error diffs
if [ -z "$diff_out" ]; then
	echo -e "--> \033[1;32mSuccess!\033[0m"
else
	echo -e "--> \033[1;31mError :[\033[0m"
fi
rm wow.aa
rm wow.apm