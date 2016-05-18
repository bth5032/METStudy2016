#include "ScanChain.C"

void doAll(TString histo_dir, bool data=true, bool DY=true, bool ttbar=true, bool ST=true, bool zz=true, bool ww=true, bool wz=true, bool vvv=true){

  cout<<"Using Histogram Directory: "<<histo_dir<<endl;

  if (data){
  //====================================
  // Data
  //====================================
    TChain *ch_data = new TChain("t"); 
    
    //EE
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Prompt_ee.root");
    
    //MuMu
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Prompt_mm.root");

    ScanChain(ch_data, "data", histo_dir); 
  }

  if (DY){
    //====================================
    // DYJets
    //====================================

    TChain *ch_DY = new TChain("t"); 
    
    //10-50
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/dy_m1050_amcnlo*");

    //50+
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/dy_m50_amcnlo*");
    ScanChain(ch_DY, "DY", histo_dir);  
  }

  if (ttbar){

    //====================================
    // TTbar
    //====================================

    TChain *ch_ttbar = new TChain("t"); 
    ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/ttbar_dilep_mgmlm*");
    ScanChain(ch_ttbar, "TTBar", histo_dir); 
  }

  if (zz) {
    //====================================
    // ZZ
    //====================================

    TChain *ch_ZZ = new TChain("t"); 

    //2L2Nu
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/zz_2l2nu_powheg*");
    
    //2L2Q
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/zz_2l2q_amcnlo*");

    //4L -- Doesn't exist
    //ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/");

    ScanChain(ch_ZZ, "ZZ", histo_dir); 
  }

  if (ST) {
    //====================================
    // Single Top
    //====================================

    TChain *ch_ST = new TChain("t"); 
    
    //anti-top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/sttw_antitop_powheg");
    
    //Top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/sttw_top_powheg*");

    ScanChain(ch_ST, "SingleTop", histo_dir); 
  }

  if (ww){
    //====================================
    // WW
    //====================================

    TChain *ch_WW = new TChain("t"); 
    
    //2L2Nu
    ch_WW->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/ww_2l2nu_powheg*");
    
    ScanChain(ch_WW, "WW", histo_dir); 
  }

  if (wz) {
    //====================================
    // WZ
    //====================================

    TChain *ch_WZ = new TChain("t"); 
    
    //2L2Q
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/wz_2l2q_amcnlo*");

    //3LNu
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/");
    
    ScanChain(ch_WZ, "WZ", histo_dir); 
  }
  
  if (vvv) {
    //====================================
    // VVV
    //====================================

    TChain *ch_VVV = new TChain("t"); 
    
    //WWG -- Doesn't exist
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/");

    //WWW
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/www_incl_amcnlo*");

    //WZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/wzz_incl_amcnlo*");

    //ZZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/zzz_incl_mgmlm*");

    
    ScanChain(ch_VVV, "VVV", histo_dir); 
  }

}