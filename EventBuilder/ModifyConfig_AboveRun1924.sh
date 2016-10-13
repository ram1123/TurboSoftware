#####################################################################################################
#
#       EDIT THE CONFIGURATION FILE FOR NEXT RUN
#
#####################################################################################################
awk -v OFS="\t" 'NR==FNR && NR==8 {a=$4} NR==FNR {next} FNR==6	{$2=$2-a} {print}' OffsetFile.log  ConfigFiles/OffsetFlip_EventBuilderVFAT_NOV2014_H4_AboveRun1924.conf > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==9 {a=$4} NR==FNR {next} FNR==8	{$2=$2-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==10 {a=$4} NR==FNR {next} FNR==10 {$2=$2-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==11 {a=$4} NR==FNR {next} FNR==11 {$2=$2-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==14 {a=$4} NR==FNR {next} FNR==14 {$2=$2-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
awk -v OFS="\t" 'NR==FNR && NR==21 {a=$4} NR==FNR {next} FNR==7 {$3=$3-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
awk -v OFS="\t" 'NR==FNR && NR==22 {a=$4} NR==FNR {next} FNR==9 {$3=$3-a} {print}' OffsetFile.log OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2 > OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1

cp OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1 ConfigFiles/OffsetFlip_EventBuilderVFAT_NOV2014_H4_AboveRun1924.conf
rm OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer1
rm OffsetFlip_EventBuilderVFAT_NOV2014_H4.conf.buffer2
