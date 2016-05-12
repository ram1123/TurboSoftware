#########################################################
#
#	Read the binary file (CRC*.dat), that we get from the Turbo-
#	Online software. 
#
#########################################################

hexdump -v -e '"%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X " "\n" "%08_ad|   " 19/2 "%04X "  "\n"  "\n"' $1 | more
#"%08_ad|   " 19/2 "%04X " "\n"   # This line has to be added for each additional VFAT

#/afs/cern.ch/user/r/rasharma/work/public/GEM_TB_May2016/May2016_TB_Data/Run0010_Pion_5k_MSPL4_HVScan3904_1427uA_T18_Lat12/CRC-Run0010_Pion_5k_MSPL4_HVScan3904_1427uA_T18_Lat12-160510_171928-0.dat   Path of data
