{

  gROOT->ProcessLine(".L ScanChain.C");

  //====================================
  // Data
  //====================================

  TChain *ch_data = new TChain("t"); 
  
  //EE
  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_ee.root");
  
  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_ee.root");
  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_ee_1.root");
  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_ee_2.root");
  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_ee_3.root");
  
  //MuMu
  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015C25ns16Dec2015_mm.root");

  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_mm.root");
  ch_data->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/data_2015D25ns16Dec2015_mm_1.root");

  ScanChain(ch_data, "data", true); 

  //====================================
  // DYJets
  //====================================

  TChain *ch_DY = new TChain("t"); 
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-10to50_amcNLO_v1.root");
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1.root");
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_1.root");
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_2.root");
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_3.root");
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_4.root");
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_5.root");
  ch_DY->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_6.root");
  ScanChain(ch_DY, "DY"); 

  //====================================
  // TTbar
  //====================================

  TChain *ch_ttbar = new TChain("t"); 
  ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ttTo2L2Nu_powheg.root");
  ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ttTo2L2Nu_powheg_1.root");
  ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ttTo2L2Nu_powheg_2.root");
  ch_ttbar->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ttTo2L2Nu_powheg_3.root");
  ScanChain(ch_ttbar, "TTBar"); 


  //====================================
  // ZZ
  //====================================

  TChain *ch_ZZ = new TChain("t"); 

  //2L2Nu
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Nu_13TeV_powheg_pythia8.root");
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Nu_13TeV_powheg_pythia8_1.root");
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Nu_13TeV_powheg_pythia8_2.root");
  
  //2L2Q
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8.root");
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_1.root");
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_2.root");
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_3.root");
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_4.root");

  //4L
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo4L_13TeV_powheg_pythia8.root");
  ch_ZZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ZZTo4L_13TeV_powheg_pythia8_1.root");

  ScanChain(ch_ZZ, "ZZ"); 


  //====================================
  // Single Top
  //====================================

  TChain *ch_ST = new TChain("t"); 
  ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ST_tW_antitop_5f_inclusiveDecays_13TeV.root");
  ch_ST->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/ST_tW_top_5f_inclusiveDecays_13TeV.root");
  ScanChain(ch_ST, "SingleTop"); 


  //====================================
  // WW
  //====================================

  TChain *ch_WW = new TChain("t"); 
  
  //2L2Nu
  ch_WW->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WWTo2L2Nu_13TeV-powheg.root");
  
  ScanChain(ch_WW, "WW"); 


  //====================================
  // WZ
  //====================================

  TChain *ch_WZ = new TChain("t"); 
  
  //3LNu
  ch_WZ->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8.root");
  
  ScanChain(ch_WZ, "WZ"); 

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

  
  ScanChain(ch_VVV, "VVV"); 



}