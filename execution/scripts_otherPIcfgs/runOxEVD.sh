#!/bin/bash
CONFIGS_DIR="configs"
RESULTS_DIR="results"
OXFORD_INPUT="OxfordInputFiles.in"
EVD_INPUT="EVDInputFiles.in"

if [[ $# -ne 2 ]]; then
	echo "Argument should be DescriptorDetector_tester executable and PI_DIFF_CONFIG_FLAG!"
	exit -1
fi

if [[ $2 -ne 1 ]]; then
	DET_DSC=( 'ORB_BRIEF' 'ORB_ORB' 'MSER_SIFT' 'SIFT_SIFT' 'HARRAFF_SIFT' 'SURF_SURF' 'SURF_FREAK' 'AGAST_FREAK' 'ASIFT_ASIFT' 'ORB_PI' 'MSER_PI' 'SIFT_PI' 'HARRAFF_PI' 'SURF_PI' 'AGAST_PI' 'ASIFT_PI' )
	OTHER_CONF=( 'default' )
	DET_DSC_SIZE=${#DET_DSC[@]}
	OTHER_CONF_SIZE=${#OTHER_CONF[@]}
else
		DET_DSC=( 'ORB_PI' 'MSER_PI' 'SIFT_PI' 'HARRAFF_PI' 'SURF_PI' 'AGAST_PI' 'ASIFT_PI' )
	OTHER_CONF=( 'default_31' 'default_63' 'default_127' )
	DET_DSC_SIZE=${#DET_DSC[@]}
	OTHER_CONF_SIZE=${#OTHER_CONF[@]}
fi

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

if [ -d ${RESULTS_DIR}/oxford ]; then
	rm -r ${RESULTS_DIR}/oxford
fi
mkdir ${RESULTS_DIR}/oxford

if [ -d ${RESULTS_DIR}/EVD ]; then
	rm -r ${RESULTS_DIR}/EVD
fi
mkdir ${RESULTS_DIR}/EVD

for (( i=0;i<$DET_DSC_SIZE;i++)); do
	for (( j=0;j<$OTHER_CONF_SIZE;j++)); do
		echo "=============================================================="
		echo "Starting maching ${DET_DSC[${i}]} with ${OTHER_CONF[${j}]} dsc-det config."
		echo "=============================================================="
		echo "OXFORD dataset"
#		echo "OXFORD" >> ${RESULTS_DIR}/stderr.txt
		./$1 ${CONFIGS_DIR}/main_${DET_DSC[${i}]}.ini ${CONFIGS_DIR}/detdsc_${OTHER_CONF[${j}]}.ini ${CONFIGS_DIR}/matchingConfig.ini ${RESULTS_DIR}/oxford/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_times.csv ${RESULTS_DIR}/oxford/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv < ${OXFORD_INPUT} 1>>${RESULTS_DIR}/stdout.txt 2>>${RESULTS_DIR}/stderr.txt
		
		echo "EVD dataset"
#		echo "EVD" >> ${RESULTS_DIR}/stderr.txt
		./$1 ${CONFIGS_DIR}/main_${DET_DSC[${i}]}.ini ${CONFIGS_DIR}/detdsc_${OTHER_CONF[${j}]}.ini ${CONFIGS_DIR}/matchingConfig.ini ${RESULTS_DIR}/EVD/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_times.csv ${RESULTS_DIR}/EVD/${DET_DSC[${i}]}_${OTHER_CONF[${j}]}_matches.csv < ${EVD_INPUT} 1>>${RESULTS_DIR}/stdout.txt 2>>${RESULTS_DIR}/stderr.txt

	done
done

