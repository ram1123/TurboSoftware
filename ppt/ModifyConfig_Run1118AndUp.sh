#####################################################################################################
#
#       EDIT THE CONFIGURATION FILE FOR NEXT RUN
#
#####################################################################################################
awk -v OFS="\t" 'NR==FNR && NR==2 {a=$3} NR==FNR {next} FNR==4 	{$2=0.0} {print}' fit_detail_$1.txt ../EventBuilder/ConfigFiles/OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==2 {a=$3} NR==FNR {next} FNR==5 	{$3=0.0} {print}' fit_detail_$1.txt OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==2 {a=$3} NR==FNR {next} FNR==6 	{$2=$2-a} {print}' fit_detail_$1.txt  OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==3 {a=$3} NR==FNR {next} FNR==7 	{$3=$3-a} {print}' fit_detail_$1.txt OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==4 {a=$3} NR==FNR {next} FNR==8 	{$2=$2-a} {print}' fit_detail_$1.txt OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==5 {a=$3} NR==FNR {next} FNR==9 	{$3=$3-a} {print}' fit_detail_$1.txt OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==6 {a=$3} NR==FNR {next} FNR==10 {$3=$3-a} {print}' fit_detail_$1.txt OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==7 {a=$3} NR==FNR {next} FNR==12 {$3=$3-a} {print}' fit_detail_$1.txt OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==8 {a=$3} NR==FNR {next} FNR==15{$3=$3-a} {print}' fit_detail_$1.txt OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2 > OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf_Run$1_Ite$2
rm OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer1
rm OffsetFlip_EventBuilderVFAT_Oct2014_H2_Run1118AndUp.conf.buffer2
