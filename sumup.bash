
i=1

n=`ls -1 |grep LSFJOB |  wc -l`

#total numbers of info lines within a file
fname=`ls -1  | grep  LSFJOB | head -$i | tail -1`
lines=`grep -i "^total" $fname/STDOUT | wc -l`
#lines=2
ln=1
grep -r "^File Name" . | sort
while [ $ln -le $lines ]
do
	i=1
	v=0
	while [ $i -le $n ]
	do

		fname=`ls -1  | grep  LSFJOB | head -$i | tail -1`



		#echo "$i: $fname/STDOUT"

		ldata=`grep -i "^total" $fname/STDOUT | head -$ln | tail -1`
		lv=`echo "$ldata" | cut -d ':' -f2`
		v=`expr $v + $lv`
		#echo "Line:$fname/STDOUT:  `grep -i "^total" $fname/STDOUT | head -$ln | tail -1`"

		if [ $i -eq 1 ]
		then
			ld=`echo "$ldata" | cut -d ':' -f1`
		fi
	
		i=`expr $i + 1`
	done

	echo "$ld:$v"


ln=`expr $ln + 1`
done
