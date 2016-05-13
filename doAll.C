{

  gROOT->ProcessLine(".L ScanChain.C+");

  TChain *ch = new TChain("t"); 
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-10to50_amcNLO_v1.root");
  ScanChain(ch); 
}