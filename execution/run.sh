#!/bin/bash
cd scripts 
./runOxEVD.sh DescriptorDetector_tester 0
cd ..
echo Running matcher with other PI configs
cd scripts_otherPIcfgs 
./runOxEVD.sh DescriptorDetector_tester 1
cd ..

