#!/bin/bash




echo ""
echo "NFM Program"
echo ""

./calc3p < $1
echo "  --Program--"
./pstack/apd calc_out
echo "  --Program--"
./pstack/api calc_out

echo ""
echo "Our Program"
echo ""

./mycalc3 < $1 > wow.aa
echo "  --Program--"
more wow.aa
echo "  --Program--"
./pstack/apm < wow.aa > wow.apm
./pstack/api wow

echo ""
rm wow.aa
rm wow.apm