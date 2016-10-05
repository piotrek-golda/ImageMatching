#!/bin/bash
CONFIGS_DIR="configs"
RESULTS_DIR="results"
OXFORD_INPUT="OxfordInputFiles.in"
EVD_INPUT="EVDInputFiles.in"

if [[ $# -ne 1 ]]; then
	echo "Argument should be DescriptorDetector_tester executable!"
	exit -1
fi

DET_DSC=(
'HARRIS_PI-ORB'	   'AGAST_PI-BRIEF'  'HARRIS_PI-SIFT'  
'SIFT_PI-BRIEF'    'AGAST_PI-FREAK'  'HARRIS_PI-SURF'  
'SIFT_PI-FREAK'    'AGAST_PI-ORB'    'SIFT_PI-ORB'
'AGAST_PI-SIFT'    'MSER_PI-BRIEF'   'SIFT_PI-SIFT'
'AGAST_PI-SURF'    'MSER_PI-FREAK'   'SIFT_PI-SURF'
'ASIFT_PI-ASIFT'   'MSER_PI-ORB'     'ASIFT_PI-BRIEF'   
'MSER_PI-SIFT'     'SURF_PI-BRIEF'   'ASIFT_PI-FREAK'   
'MSER_PI-SURF'     'SURF_PI-FREAK'   'ASIFT_PI-ORB'     
'SURF_PI-ORB'     'ASIFT_PI-SIFT'    
'ORB_PI-BRIEF'     'SURF_PI-SIFT'    'ASIFT_PI-SURF'    
'ORB_PI-FREAK'     'SURF_PI-SURF'    'ORB_PI-ORB'      
'HARRIS_PI-BRIEF'  'ORB_PI-SIFT'     'HARRIS_PI-FREAK'  
'ORB_PI-SURF' )

OTHER_CONF=( 'default' )
DET_DSC_SIZE=${#DET_DSC[@]}
OTHER_CONF_SIZE=${#OTHER_CONF[@]}

if [ ! -d ${CONFIGS_DIR} ]; then
	echo "Wrong CONFIGS_DIR directory!"
	exit -1
fi

if [ ! -d ${RESULTS_DIR} ]; then
	mkdir ${RESULTS_DIR}
fi

if [ ! -r ${OXFORD_INPUT} ]; then
	echo "Wrong OXFORD_INPUT file!"
	exit -1
fi

if [ ! -r ${EVD_INPUT} ]; then
	echo "Wrong EVD_INPUT file!"
	exit -1
fi

touch ${RESULTS_DIR}/stdout.txt
> ${RESULTS_DIR}/stdout.txt
touch ${RESULTS_DIR}/stderr.txt
> ${RESULTS_DIR}/stderr.txt

if [ ! -d ${RESULTS_DIR}/oxford ]; then
	mkdir ${RESULTS_DIR}/oxford
fi

if [ ! -d ${RESULTS_DIR}/EVD ]; then
	mkdir ${RESULTS_DIR}/EVD
fi

for (( i=0;i<$DET_DSC_SIZE;i++)); do
	for (( j=0;j<$OTHER_CONF_SIZE;j++)); do
			echo "=============================================================="
			echo "Starting maching ${DET_DSC[${i}]} with ${OTHER_CONF[${j}]} dsc-det config."
			echo "=============================================================="
		if [[ ! -r ${RESULTS_DIR}/oxford/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv ]]; then			
			echo "OXFORD dataset"
#			echo "OXFORD" >> ${RESULTS_DIR}/stderr.txt
			./$1 ${CONFIGS_DIR}/main_${DET_DSC[${i}]}.ini ${CONFIGS_DIR}/detdsc_${OTHER_CONF[${j}]}.ini ${CONFIGS_DIR}/matchingConfig.ini ${RESULTS_DIR}/oxford/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_times.csv ${RESULTS_DIR}/oxford/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv < ${OXFORD_INPUT} 1>>${RESULTS_DIR}/stdout.txt 2>>${RESULTS_DIR}/stderr.txt
		else
			echo  "${RESULTS_DIR}/oxford/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv file found. Skipping configuration."
		fi
		
		if [[ ! -r ${RESULTS_DIR}/EVD/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv ]]; then
			echo "EVD dataset"
#			echo "EVD" >> ${RESULTS_DIR}/stderr.txt
			./$1 ${CONFIGS_DIR}/main_${DET_DSC[${i}]}.ini ${CONFIGS_DIR}/detdsc_${OTHER_CONF[${j}]}.ini ${CONFIGS_DIR}/matchingConfig.ini ${RESULTS_DIR}/EVD/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_times.csv ${RESULTS_DIR}/EVD/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv < ${EVD_INPUT} 1>>${RESULTS_DIR}/stdout.txt 2>>${RESULTS_DIR}/stderr.txt
		else
			echo  "${RESULTS_DIR}/EVD/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv file found. Skipping configuration."
		fi
	done
done
