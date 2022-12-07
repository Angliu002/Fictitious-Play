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
    if [ $# -eq 2 ];
    then
        ./ficplay $1 $2 < data/$i.txt
    else
        ./ficplay < data/$i.txt
    fi
    echo
done
