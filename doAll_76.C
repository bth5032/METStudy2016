//******************************************
//******************************************
// FOR 76X -- FOR 76X -- FOR 76X -- FOR 76X
//******************************************
//******************************************

#include "ScanChain.C"

void doAll_76(TString histo_dir, bool data=true, bool DY=true, bool ttbar=true, bool ST=true, bool zz=true, bool ww=true, bool wz=true, bool vvv=true){

  cout<<"Using Histogram Directory: "<<histo_dir<<endl;

  if (makeVTXCorrections){
    //====================================
    // Data
    //====================================
    TChain *ch_data = new TChain("t"); 
    
    //EE
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_ee*");

    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_ee*");
    
    //MuMu
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_mm*");
    
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_mm*");
    ScanChain(ch_data, "data", histo_dir); 

    //====================================
    // DYJets
    //====================================

    TChain *ch_DY = new TChain("t"); 
    
    //10-50
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-10to50_amcNLO_v1*");

    //50+
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1*");

    getReweightVtxHist(histo_dir);

    return;

  }


  if (data){
  //====================================
  // Data
  //====================================
    TChain *ch_data = new TChain("t"); 
    
    //EE
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_ee*");

    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_ee*");
    
    //MuMu
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_mm*");
    
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_mm*");
    ScanChain(ch_data, "data", histo_dir, true); 
  }

  if (DY){
    //====================================
    // DYJets
    //====================================

    TChain *ch_DY = new TChain("t"); 
    
    //10-50
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-10to50_amcNLO_v1*");

    //50+
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1*");
    ScanChain(ch_DY, "DY", histo_dir, true);  
  }

  if (ttbar){

    //====================================
    // TTbar
    //====================================

    TChain *ch_ttbar = new TChain("t"); 
    ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ttTo2L2Nu_powheg*");
    ScanChain(ch_ttbar, "TTBar", histo_dir, true); 
  }

  if (zz) {
    //====================================
    // ZZ
    //====================================

    TChain *ch_ZZ = new TChain("t"); 

    //2L2Nu
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Nu_13TeV_powheg_pythia8*");
    
    //2L2Q
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8*");

    //4L
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo4L_13TeV_powheg_pythia8*");

    ScanChain(ch_ZZ, "ZZ", histo_dir, true); 
  }

  if (ST) {
    //====================================
    // Single Top
    //====================================

    TChain *ch_ST = new TChain("t"); 
    
    //anti-top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ST_tW_antitop_5f_inclusiveDecays_13TeV.root");
    
    //Top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ST_tW_top_5f_inclusiveDecays_13TeV.root");

    ScanChain(ch_ST, "SingleTop", histo_dir, true); 
  }

  if (ww){
    //====================================
    // WW
    //====================================

    TChain *ch_WW = new TChain("t"); 
    
    //2L2Nu
    ch_WW->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WWTo2L2Nu_13TeV-powheg.root");
    
    ScanChain(ch_WW, "WW", histo_dir, true); 
  }

  if (wz) {
    //====================================
    // WZ
    //====================================

    TChain *ch_WZ = new TChain("t"); 
    
    //3LNu
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8.root");
    
    ScanChain(ch_WZ, "WZ", histo_dir, true); 
  }
  
  if (vvv) {
    //====================================
    // VVV
    //====================================

    TChain *ch_VVV = new TChain("t"); 
    
    //WWG
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");

    //WWW
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");

    //WZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");
    
    ScanChain(ch_VVV, "VVV", histo_dir, true); 
  }

}