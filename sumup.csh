#!/bin/csh
i=1

n=`ls -1 |grep LSFJOB |  wc -l`

#total numbers of info lines within a file
fname=`ls -1  | grep  LSFJOB | head -$i | tail -1`
lines=`grep -i "^total" $fname/STDOUT | wc -l`
#lines=2
ln=1
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
cd /afs/cern.ch/work/p/ppriyank/private/antiTop/CMSSW_7_4_7_patch2/src
hadd electronMuononeTeoneTm.root electronMuononeTeoneTm_*.root
rm -rf electronMuononeTeoneTm_*.root
hadd electronMuononeTeoneTm2e.root electronMuononeTeoneTm2e_*.root
rm -rf electronMuononeTeoneTm2e_*.root
hadd electronMuononeTeoneTm2mu.root electronMuononeTeoneTm2mu_*.root
rm -rf electronMuononeTeoneTm2mu_*.root
hadd electronMuonOppositeCharge.root electronMuonOppositeCharge_*.root
rm -rf electronMuonOppositeCharge_*.root
hadd electronMuonOppositeCharge2e.root electronMuonOppositeCharge2e_*.root
rm -rf electronMuonOppositeCharge2e_*.root
hadd electronMuonOppositeCharge2mu.root electronMuonOppositeCharge2mu_*.root
rm -rf electronMuonOppositeCharge2mu_*.root
hadd electronMuonExtraloose.root electronMuonExtraloose_*.root
rm -rf electronMuonExtraloose_*.root
hadd electronMuonExtraloose2e.root electronMuonExtraloose2e_*.root
rm -rf electronMuonExtraloose2e_*.root
hadd electronMuonExtraloose2mu.root electronMuonExtraloose2mu_*.root
rm -rf electronMuonExtraloose2mu_*.root
hadd met.root met_*.root
rm -rf met_*.root
hadd met2e.root met2e_*.root
rm -rf met2e_*.root
hadd met2mu.root met2mu_*.root
rm -rf met2mu_*.root
rm -rf job*.csh
rm -rf LSFJOB*
