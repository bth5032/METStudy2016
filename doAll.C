{

  gROOT->ProcessLine(".L ScanChain.C");

  TChain *ch = new TChain("t"); 
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-10to50_amcNLO_v1.root");
  /*ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1.root");
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_1.root");
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_2.root");
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_3.root");
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_4.root");
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_5.root");
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V07-06-09/DYJetsToLL_M-50_amcNLO_v1_6.root");*/
  ScanChain(ch, "DY"); 
}