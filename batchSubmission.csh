n=$1
s=1
id=1

while [ $s -le $n ]
do
	e=`expr $s + $2 - 1 `

	if [ $e -gt $n ]
	then
		e=$n
	fi

		echo "#!/bin/csh" > job$id.csh
		echo "cd /afs/cern.ch/work/p/ppriyank/private/antiTop/CMSSW_7_4_7_patch2/src" >> job$id.csh 
		echo "eval \`scramv1 runtime -csh\`" >> job$id.csh
		echo "PatMuonEDMAnalyzer $id $s $e" >> job$id.csh

		bsub -q 8nh < job$id.csh
		echo "bsub -q 8nh < job$id.csh"
	s=`expr $e + 1`
	id=`expr $id + 1`
done
