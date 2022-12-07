echo Examples
echo 1. Prisoner\'s Dilemma
./ficplay < data/pd.txt
echo
echo 2. Matching Pennies
./ficplay < data/mp.txt
echo
echo -------------------------------------------------- # 50 * '-'
echo Questions
for i in `seq 1 9`
do
    echo Q$i.
    ./ficplay < data/$i.txt
    echo
done

