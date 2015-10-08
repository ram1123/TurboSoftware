#####################################################################################################
#
#       EDIT THE CONFIGURATION FILE FOR NEXT RUN
#
#####################################################################################################
awk -v OFS="\t" 'NR==FNR && NR==8 {a=$4} NR==FNR {next} FNR==6	{$2=$2-a} {print}' OffsetFile.log ConfigFiles/OffsetFlip_EventBuilderVFAT_Oct2014_H2.conf > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==9 {a=$4} NR==FNR {next} FNR==8	{$2=$2-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==16 {a=$4} NR==FNR {next} FNR==7 {$3=$3-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==17 {a=$4} NR==FNR {next} FNR==9 {$3=$3-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==18 {a=$4} NR==FNR {next} FNR==10 {$3=$3-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==19 {a=$4} NR==FNR {next} FNR==11 {$3=$3-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==20 {a=$4} NR==FNR {next} FNR==14 {$3=$3-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1

cp OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 ConfigFiles/OffsetFlip_EventBuilderVFAT_Oct2014_H2.conf
#cat OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 
rm OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
rm OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
