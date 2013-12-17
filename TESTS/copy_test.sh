#!/bin/bash



count = 0
right_count = 0
wrong_count = 0
for f in tests/*.calc
do
	count=`expr $count + 1`
	echo "-------------------"
	echo " $count:   $f  "
	echo "-------------------"
	# echo ""
	# echo "NFM Program"
	# echo ""
	./calc3p < $f
	# echo "  --Program--"
	# ./pstack/apd calc_out
	# echo "  --Program--"
	./pstack/api calc_out > nm_output
	# echo ""
	# echo "Our Program"
	#echo ""
	./mycalc3 < $f > wow.aa
	# echo "  --Program--"
	# more wow.aa
	# echo "  --Program--"
	./pstack/apm < wow.aa > wow.apm
	./pstack/api wow > my_output
	#echo ""
	diff_out=$(diff nm_output my_output) # Check the compile error diffs
	if [ -z "$diff_out" ]; then
		echo -e "--> \033[1;32mSuccess!\033[0m"
		right_count=`expr $right_count + 1`
	else
		echo -e "--> \033[1;31mError :[\033[0m"
		echo ""
		echo "NFM Program"
		echo ""
		echo "  --Program--"
		./pstack/apd calc_out
		echo "  --Program--"
		echo ""
		echo "Our Program"
		echo ""
		echo "  --Program--"
		cat wow.aa
		echo "  --program--"
		wrong_count=`expr $wrong_count + 1`
	fi
	rm wow.aa
	rm wow.apm
done
echo "right:$right_count"
echo "wrong:$wrong_count"