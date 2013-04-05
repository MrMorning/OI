prog=wdstr
for((i=0; i<=2; i++))
do
	echo 10 20 26 $RANDOM | ./"$prog"_datamaker > "$prog".in
	./$prog
	mv $prog.in $prog$i.in
	mv $prog.out $prog$i.out
done
for((i=3; i<=5; i++))
do
	echo 10 200 26 $RANDOM | ./"$prog"_datamaker > "$prog".in
	./$prog
	mv $prog.in $prog$i.in
	mv $prog.out $prog$i.out
done
for((i=6; i<=6; i++))
do
	echo 10 1 1 $RANDOM | ./"$prog"_datamaker > "$prog".in
	./$prog
	mv $prog.in $prog$i.in
	mv $prog.out $prog$i.out
done
for((i=7; i<=9; i++))
do
	echo 10 2000 26 $RANDOM | ./"$prog"_datamaker > "$prog".in
	./$prog
	mv $prog.in $prog$i.in
	mv $prog.out $prog$i.out
done
