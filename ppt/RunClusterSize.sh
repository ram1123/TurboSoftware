rm Cluster_Size.txt
for f in /afs/cern.ch/user/r/rasharma/public/TurboSoftware/EventBuilder/OutPutData/Run*/; do
	if [ ! -f $f/CRC*.root ]; then
		echo "No root file is present in $f"
	else
		for R in $f/CRC*.root; do
			echo "root -l -b -q ClusterSize.C\(\"$R\",\"$(basename $f)\"\)"
			root -l -b -q ClusterSize.C\(\"$R\",\"$(basename $f)\"\)
			#echo "$(basename $f)"
		done
	fi
done
#rm Run*.pdf Run*.root Run*.png Run*.C
