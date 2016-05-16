#!/bin/bash
##
## Function for doing 2016 MET study
## Bobak Hashemi

MET_STUDY_HISTO_DIR=/nfs-7/userdata/bobak/METStudy2016/76Histos/
MET_STUDY_PLOTS_OUTPUT_DIR=/home/users/bhashemi/public_html/ZMET2016/looper/

function env {
	
	if [[ -d CMSSW_7_6_4 ]]
	then
		rm -rf CMSSW_7_6_4/src/ 
	fi

	cmsrel CMSSW_8_0_6
	pushd CMSSW_8_0_6/src/
	git clone git@github.com:cmstas/CORE.git
	cmsenv
	popd

	sed -e 's,^//#include "CMSSW_8_0_6/src/CORE/Tools/dorky/dorky\.h"$,#include "CMSSW_8_0_6/src/CORE/Tools/dorky/dorky\.h",' -e 's,^#include "CMSSW_7_6_4/src/CORE/Tools/dorky/dorky\.h"$,//#include "CMSSW_7_6_4/src/CORE/Tools/dorky/dorky\.h",' > scanchain_tmp

	mv scanchain_tmp ScanChain.C
}

function 76env {
	
	if [[ -d CMSSW_8_0_6 ]]
	then
		rm -rf CMSSW_8_0_6/src/ 
	fi

	cmsrel CMSSW_7_6_4
	pushd CMSSW_7_6_4/src/
	git clone git@github.com:cmstas/CORE.git
	cmsenv
	popd

	sed -e 's,^//#include "CMSSW_7_6_4/src/CORE/Tools/dorky/dorky\.h"$,#include "CMSSW_7_6_4/src/CORE/Tools/dorky/dorky\.h",' -e 's,^#include "CMSSW_8_0_6/src/CORE/Tools/dorky/dorky\.h"$,//#include "CMSSW_8_0_6/src/CORE/Tools/dorky/dorky\.h",' > scanchain_tmp

	mv scanchain_tmp ScanChain.C
}

function makePlots {
	git pull
	root -l -b -q "drawPlots.C(true, true, true)"
}

function makeHistos {
	git pull
	rm ${MET_STUDY_HISTO_DIR}MET*.root
	root -l -b -q doAll.C
}

function makeAll {
	git pull
	rm ${MET_STUDY_HISTO_DIR}MET*.root
	root -l -b -q doAll.C
	root -l -b -q "drawPlots.C(true, true, true)"
}

function pc {
	echo root -l -b -q doAll.C
	echo root -l -b -q "drawPlots.C(true, true, true)"
}