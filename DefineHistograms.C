#include "TString.h"

struct

class ZMEThistogram
{
	public:
		TString title;
		TString 

}

//============================================
  // Define plots
  //============================================
  // Type1 MET
  plot_names.push_back("type1MET");
  plot_vars.push_back("met_T1CHS_miniAOD_CORE_pt");
  plot_titles.push_back("Type 1 MET for All Events in Study");
  cuts.push_back(base_cut+"met_T1CHS_miniAOD_CORE_pt > 0");
  plot_types.push_back("pt");

  // Type1 MET
  plot_names.push_back("type1MET_2Jets");
  plot_vars.push_back("met_T1CHS_miniAOD_CORE_pt");
  plot_titles.push_back("Type 1 MET for All Events with at Least 2 Jets");
  cuts.push_back(base_cut+"met_T1CHS_miniAOD_CORE_pt > 0 && njets >= 2");
  plot_types.push_back("pt");

/*
  //Pileup Weight
  plot_names.push_back("puWeight");
  plot_vars.push_back("puWeight");
  plot_titles.push_back("Pileup Weight");
  cuts.push_back(base_cut+"met_rawPt > 0");
  plot_types.push_back("puWeight");
*/

  //Number of Verticies
  plot_names.push_back("nVert");
  plot_vars.push_back("nVert");
  plot_titles.push_back("Number of Verticies");
  cuts.push_back(base_cut+"met_rawPt > 0");
  plot_types.push_back("nVert");

/*
  // Photon MET-Phi in Barrel
  plot_names.push_back("ph_0013_phi");
  plot_vars.push_back("phpfcands_0013_phi");
  plot_titles.push_back("Photon MET-Phi in Barrel |#eta| < 1.3");
  cuts.push_back(base_cut+"phpfcands_0013_pt > 0");
  plot_types.push_back("phi");

  // Charged Hadron MET-Phi in Barrel
  plot_names.push_back("ch_0013_phi");
  plot_vars.push_back("chpfcands_0013_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Barrel |#eta| < 1.3");
  cuts.push_back(base_cut+"chpfcands_0013_pt > 0");
  plot_types.push_back("phi");

  // Neutral Hadron MET-Phi in Barrel
  plot_names.push_back("nu_0013_phi");
  plot_vars.push_back("nupfcands_0013_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Barrel |#eta| < 1.3");
  cuts.push_back(base_cut+"nupfcands_0013_pt > 0");
  plot_types.push_back("phi");

  // Photon MET-Phi in Endcap
  plot_names.push_back("ph_1624_phi");
  plot_vars.push_back("phpfcands_1624_phi");
  plot_titles.push_back("Photon MET-Phi in Endcap |#eta| #in (1.6,2.4)");
  cuts.push_back(base_cut+"phpfcands_1624_pt > 0");
  plot_types.push_back("phi");

  // Charged Hadron MET-Phi in Endcap
  plot_names.push_back("ch_1624_phi");
  plot_vars.push_back("chpfcands_1624_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Endcap |#eta| #in (1.6,2.4)");
  cuts.push_back(base_cut+"chpfcands_1624_pt > 0");
  plot_types.push_back("phi");

  // Neutral Hadron MET-Phi in Endcap
  plot_names.push_back("nu_1624_phi");
  plot_vars.push_back("nupfcands_1624_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Endcap |#eta| #in (1.6,2.4)");
  cuts.push_back(base_cut+"nupfcands_1624_pt > 0");
  plot_types.push_back("phi");

  // Photon MET-Phi in Forward Endcap (No Tracker)
  plot_names.push_back("ph_2430_phi");
  plot_vars.push_back("phpfcands_2430_phi");
  plot_titles.push_back("Photon MET-Phi in Forward Endcap |#eta| #in (2.4,3.0) (No Tracker)");
  cuts.push_back(base_cut+"phpfcands_2430_pt > 0");
  plot_types.push_back("phi");

  // Charged Hadron MET-Phi in Forward Endcap (No Tracker)
  plot_names.push_back("ch_2430_phi");
  plot_vars.push_back("chpfcands_2430_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Forward Endcap |#eta| #in (2.4,3.0) (No Tracker)");
  cuts.push_back(base_cut+"chpfcands_2430_pt > 0");
  plot_types.push_back("phi");

  // Neutral Hadron MET-Phi in Forward Endcap (No Tracker)
  plot_names.push_back("nu_2430_phi");
  plot_vars.push_back("nupfcands_2430_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Forward Endcap |#eta| #in (2.4,3.0) (No Tracker)");
  cuts.push_back(base_cut+"nupfcands_2430_pt > 0");
  plot_types.push_back("phi");
*/
  // Raw Met
  plot_names.push_back("MET");
  plot_vars.push_back("met_rawPt");
  plot_titles.push_back("Raw MET for all events in study.");
  cuts.push_back(base_cut+"met_rawPt>0");
  plot_types.push_back("pt");

  // Raw Met With at least 2 jets
  plot_names.push_back("MET_2Jets");
  plot_vars.push_back("met_rawPt");
  plot_titles.push_back("Raw MET for all events in study with a minimum 2 jet requirement.");
  cuts.push_back(base_cut+"met_rawPt>0 && njets >= 2");
  plot_types.push_back("pt");

  // Photon Pt in Barrel
  plot_names.push_back("ph_0013_pt");
  plot_vars.push_back("phpfcands_0013_pt");
  plot_titles.push_back("Photon Pt in Barrel |#eta| < 1.3");
  cuts.push_back(base_cut+"phpfcands_0013_pt>0");
  plot_types.push_back("pt");

  // Charged Hadron Pt in Barrel
  plot_names.push_back("ch_0013_pt");
  plot_vars.push_back("chpfcands_0013_pt");
  plot_titles.push_back("Charged Hadron Pt in Barrel |#eta| < 1.3");
  cuts.push_back(base_cut+"chpfcands_0013_pt>0");
  plot_types.push_back("pt");

  // Neutral Hadron Pt in Barrel
  plot_names.push_back("nu_0013_pt");
  plot_vars.push_back("nupfcands_0013_pt");
  plot_titles.push_back("Neutral Hadron Pt in Barrel |#eta| < 1.3");
  cuts.push_back(base_cut+"nupfcands_0013_pt>0");
  plot_types.push_back("pt");

  // Photon Pt in Endcap
  plot_names.push_back("ph_1624_pt");
  plot_vars.push_back("phpfcands_1624_pt");
  plot_titles.push_back("Photon Pt in Endcap |#eta| #in (1.6,2.4)");
  cuts.push_back(base_cut+"phpfcands_1624_pt>0");
  plot_types.push_back("pt");

  // Charged Hadron Pt in Endcap
  plot_names.push_back("ch_1624_pt");
  plot_vars.push_back("chpfcands_1624_pt");
  plot_titles.push_back("Charged Hadron Pt in Endcap |#eta| #in (1.6,2.4)");
  cuts.push_back(base_cut+"chpfcands_1624_pt>0");
  plot_types.push_back("pt");

  // Neutral Hadron Pt in Endcap
  plot_names.push_back("nu_1624_pt");
  plot_vars.push_back("nupfcands_1624_pt");
  plot_titles.push_back("Neutral Hadron Pt in Endcap |#eta| #in (1.6,2.4)");
  cuts.push_back(base_cut+"nupfcands_1624_pt>0");
  plot_types.push_back("pt");

  // Photon Pt in Forward Endcap (No Tracker)
  plot_names.push_back("ph_2430_pt");
  plot_vars.push_back("phpfcands_2430_pt");
  plot_titles.push_back("Photon Pt in Forward Endcap |#eta| #in (2.4,3.0) (No Tracker)");
  cuts.push_back(base_cut+"phpfcands_2430_pt>0");
  plot_types.push_back("pt");
/*
  // Charged Hadron Pt in Forward Endcap (No Tracker)
  plot_names.push_back("ch_2430_pt");
  plot_vars.push_back("chpfcands_2430_pt");
  plot_titles.push_back("Charged Hadron Pt in Forward Endcap |#eta| #in (2.4,3.0) (No Tracker)");
  cuts.push_back(base_cut+"chpfcands_2430_pt>0");
  plot_types.push_back("pt");
*/
  // Neutral Hadron Pt in Forward Endcap (No Tracker)
  plot_names.push_back("nu_2430_pt");
  plot_vars.push_back("nupfcands_2430_pt");
  plot_titles.push_back("Neutral Hadron Pt in Forward Endcap |#eta| #in (2.4,3.0) (No Tracker)");
  cuts.push_back(base_cut+"nupfcands_2430_pt>0");
  plot_types.push_back("pt");

  // Neutral Hadron Pt in Forward Calorimeter (|eta| > 3)
  plot_names.push_back("nu_30in_pt");
  plot_vars.push_back("nupfcands_30in_pt");
  plot_titles.push_back("Neutral Hadron Pt in HF |#eta| > 3 (No Tracker)");
  cuts.push_back(base_cut+"nupfcands_30in_pt>0");
  plot_types.push_back("pt");
