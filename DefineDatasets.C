//====================================
// Data
//====================================
TChain * getDataChain(TString data_set){
  TChain *ch_data = new TChain("t");

  if (data_set == "76x"){
    //EE
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_ee*");

    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_ee*");
    
    //MuMu
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_mm*");
    
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_mm*");
  }

  else if (data_set == "80x"){
    //EE
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Prompt_ee.root");
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Promptv2_ee.root");
    
    //MuMu
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Prompt_mm.root");
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Promptv2_mm.root");
  }

  else if (data_set == "80x_Bobak"){
    //EE
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/data_2016B_Prompt_ee_v1*");
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/data_2016B_Prompt_ee_v2*");
    
    //MuMu
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/data_2016B_Prompt_mm_v1*");
    ch_data->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/data_2016B_Prompt_mm_v2*");
  }

  return ch_data;
}

//====================================
// DY
//====================================
TChain * getDYChain(TString data_set){
  TChain *ch_DY = new TChain("t");

  if (data_set == "76x"){
    //10-50
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-10to50_amcNLO_v1*");

    //50+
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1*");
  }

  else if (data_set == "80x"){
    //10-50
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/dy_m1050_amcnlo*");

    //50+
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/dy_m50_amcnlo*");
  }
  else if (data_set == "80x_Bobak"){
    //10-50
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/dy_m1050_amcnlo*");
    ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/dy_m50_amcnlo*");
  }

  return ch_DY;
}

//====================================
// TTBar
//====================================
TChain * getTTbarChain(TString data_set){
  TChain *ch_ttbar = new TChain("t");

  if (data_set == "76x"){
    ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ttTo2L2Nu_powheg*");
  }

  else if (data_set == "80x"){
    ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/ttbar_dilep_mgmlm*");
  }
  else if (data_set == "80x_Bobak"){
    ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/ttbar_dilep*");
  }

  return ch_ttbar;
}

//====================================
// ST
//====================================
TChain * getSTChain(TString data_set){
  TChain *ch_ST = new TChain("t");

  if (data_set == "76x"){
    //anti-top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ST_tW_antitop_5f_inclusiveDecays_13TeV.root");
    
    //Top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ST_tW_top_5f_inclusiveDecays_13TeV.root");
  }

  else if (data_set == "80x"){
    //anti-top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/sttw_antitop_powheg*");
    
    //Top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/sttw_top_powheg*");
  }
  else if (data_set == "80x_Bobak"){
    //anti-top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/sttw_antitop_powheg*");
    
    //Top
    ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/sttw_top_powheg*");
  }

  return ch_ST;
}

//====================================
// ZZ
//====================================
TChain * getZZChain(TString data_set){
  TChain *ch_ZZ = new TChain("t");

  if (data_set == "76x"){
    //2L2Nu
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Nu_13TeV_powheg_pythia8*");
    
    //2L2Q
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8*");

    //4L
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo4L_13TeV_powheg_pythia8*");
  }


  else if (data_set == "80x"){
     //2L2Nu
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/zz_2l2nu_powheg*");
    
    //2L2Q
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/zz_2l2q_amcnlo*");
  }
  else if (data_set == "80x_Bobak"){
     //2L2Nu
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/zz_2l2nu_powheg*");
    
    //2L2Q
    ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/zz_2l2q_amcnlo*");
  }

  return ch_ZZ;
}

//====================================
// WW
//====================================
TChain * getWWChain(TString data_set){
  TChain *ch_WW = new TChain("t");

  if (data_set == "76x"){
    //2L2Nu
    ch_WW->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WWTo2L2Nu_13TeV-powheg.root");
  }

  else if (data_set == "80x"){
    //2L2Nu
    ch_WW->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/ww_2l2nu_powheg*");
  }
  else if (data_set == "80x_Bobak"){
    //2L2Nu
    ch_WW->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/ww_2l2nu_powheg*");
  }

  return ch_WW;
}

//====================================
// WZ
//====================================
TChain * getWZChain(TString data_set){
  TChain *ch_WZ = new TChain("t");

  if (data_set == "76x"){
    //3LNu
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8.root");
  }

  else if (data_set == "80x"){
    //2L2Q
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/wz_2l2q_amcnlo*");

    //3LNu
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/wz_3lnu*");
  }
  else if (data_set == "80x_Bobak"){
    //2L2Q
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/wz_2l2q_amcnlo*");

    //3LNu
    ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/wz_3lnu*");
  }

  return ch_WZ;
}

//====================================
// VVV
//====================================
TChain * getVVVChain(TString data_set){
  TChain *ch_VVV = new TChain("t");

  if (data_set == "76x"){
    //WWG
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");

    //WWW
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");

    //WZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");
  }

  else if (data_set == "80x"){
    //WWW
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/www_incl_amcnlo*");

    //WZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/wzz_incl_amcnlo*");

    //ZZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/zzz_incl_mgmlm*");
  }
  else if (data_set == "80x_Bobak"){
    //WWW
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/www_incl_amcnlo*");

    //WZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/wzz_incl_amcnlo*");

    //ZZZ
    ch_VVV->Add("/nfs-7/userdata/ZMEToutput/output/bobakBabies/V7680-hybrid-00-Bobak/zzz_incl_mgmlm*");
  }

  return ch_VVV;
}