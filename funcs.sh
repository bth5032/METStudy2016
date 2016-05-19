#!/bin/bash
##
## Function for doing 2016 MET study
## Bobak Hashemi

#MET_STUDY_HISTO_DIR=/nfs-7/userdata/bobak/METStudy2016/80Histos/
#MET_STUDY_PLOTS_OUTPUT_DIR=/home/users/bhashemi/public_html/ZMET2016/looper/80/

MET_STUDY_HISTO_DIR=/nfs-7/userdata/bobak/METStudy2016/76Histos/
MET_STUDY_PLOTS_OUTPUT_DIR=/home/users/bhashemi/public_html/ZMET2016/looper/76/

function makePlots {
	#
	# Fancy way to call drawPlots script with root. If you run 
	# makePlots met pt phi sumet extra 
	# it will make all the plots, any you leave out of the space
	# seperated string will not be made. If you run without options
	# no warning is given or anything.
	#
	MET_STUDY_PLOTS_FLAG_PT="false"
	MET_STUDY_PLOTS_FLAG_PHI="false"
	MET_STUDY_PLOTS_FLAG_SUMET="false"
	MET_STUDY_PLOTS_FLAG_MET="false"
	MET_STUDY_PLOTS_FLAG_EXTRA="false"

	for i in $@
	do
	  if [[ ${i,,} == "met" ]]
	  then
	    MET_STUDY_PLOTS_FLAG_MET="true"
	  elif [[ ${i,,} == "pt" ]]
	  then
	    MET_STUDY_PLOTS_FLAG_PT="true"
	  elif [[ ${i,,} == "phi" ]]
	  then
	    MET_STUDY_PLOTS_FLAG_PHI="true"
	  elif [[ ${i,,} == "sumet" ]]
	  then
	    MET_STUDY_PLOTS_FLAG_SUMET="true"
	  elif [[ ${i,,} == "extra" ]]
	  then
	    MET_STUDY_PLOTS_FLAG_EXTRA="true"
	  fi
	done


	root -l -b -q "drawPlots.C(\"$MET_STUDY_PLOTS_OUTPUT_DIR\", \"$MET_STUDY_HISTO_DIR\", $MET_STUDY_PLOTS_FLAG_PT, $MET_STUDY_PLOTS_FLAG_PHI, $MET_STUDY_PLOTS_FLAG_SUMET, $MET_STUDY_PLOTS_FLAG_MET, $MET_STUDY_PLOTS_FLAG_EXTRA)"
}

function makeHistos {
	MET_STUDY_HISTOS_FLAG_DATA="false"
	MET_STUDY_HISTOS_FLAG_DY="false"
	MET_STUDY_HISTOS_FLAG_TTBAR="false"
	MET_STUDY_HISTOS_FLAG_ST="false"
	MET_STUDY_HISTOS_FLAG_ZZ="false"
	MET_STUDY_HISTOS_FLAG_WW="false"
	MET_STUDY_HISTOS_FLAG_WZ="false"
	MET_STUDY_HISTOS_FLAG_VVV="false"


	for i in $@
	do
	  if [[ ${i,,} == "data" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_DATA="true"
	  elif [[ ${i,,} == "dy" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_DY="true"
	  elif [[ ${i,,} == "ttbar" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_TTBAR="true"
	  elif [[ ${i,,} == "st" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_ST="true"
	  elif [[ ${i,,} == "zz" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_ZZ="true"
	  elif [[ ${i,,} == "ww" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_WW="true"
	  elif [[ ${i,,} == "wz" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_WZ="true"
	  elif [[ ${i,,} == "vvv" ]]
	  then
	    MET_STUDY_HISTOS_FLAG_ZZ="true"
	  fi
	done

	if [[ -s ${MET_STUDY_HISTO_DIR}METStudy_data.root ]]
	then
		echo "Please clean up the old directory as you see fit before you run."
	else
		root -l -b -q "doAll.C(\"$MET_STUDY_HISTO_DIR\", $MET_STUDY_HISTOS_FLAG_DATA, $MET_STUDY_HISTOS_FLAG_DY, $MET_STUDY_HISTOS_FLAG_TTBAR, $MET_STUDY_HISTOS_FLAG_ST, $MET_STUDY_HISTOS_FLAG_ZZ, $MET_STUDY_HISTOS_FLAG_WW, $MET_STUDY_HISTOS_FLAG_WZ, $MET_STUDY_HISTOS_FLAG_VVV)"
	fi
}	

function moveHistos {
	# This function helps with moving the histograms before we make new ones.
	
	# gets number of last hidden folder.
	MET_STUDY_LASTDIR=`ls -la ${MET_STUDY_HISTO_DIR} | tr -s " " | cut -d ' ' -f 9 | grep "^\.[0-9]" | sed 's/^\.//g' | sort -n | tail -n1`


	NEXTDIR=$((MET_STUDY_LASTDIR+1))

	mkdir ${MET_STUDY_HISTO_DIR}.$NEXTDIR
	echo -n "Enter Comment For Move: "
	read MET_STUDY_comment
	echo $MET_STUDY_comment > ${MET_STUDY_HISTO_DIR}.${NEXTDIR}/README

	mv ${MET_STUDY_HISTO_DIR}*.root ${MET_STUDY_HISTO_DIR}.${NEXTDIR}/
}

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

	sed -e 's,CMSSW_7_6_4/src/CORE/Tools,CMSSW_8_0_6/src/CORE/Tools,' < ScanChain.C > scanchain_tmp

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

	sed -e 's,CMSSW_8_0_6/src/CORE/Tools,CMSSW_7_6_4/src/CORE/Tools,' < ScanChain.C > scanchain_tmp

	mv scanchain_tmp ScanChain.C
}


##
# Make directories
##

if [[ ! -d $MET_STUDY_PLOTS_OUTPUT_DIR ]]
then
	mkdir -p $MET_STUDY_PLOTS_OUTPUT_DIR
	cp ~/public_html/ZMET2016/index.php ${$MET_STUDY_PLOTS_OUTPUT_DIR}/
fi

if [[ ! -d $MET_STUDY_HISTO_DIR ]]
then
	mkdir -p $MET_STUDY_HISTO_DIR
fi

