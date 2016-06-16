#include "ScanChain.C"
#include "DefineDatasets.C"

void doAll(TString data_set, TString histo_dir, bool data=true, bool DY=true, bool ttbar=true, bool ST=true, bool zz=true, bool ww=true, bool wz=true, bool vvv=true, bool doVtxFix=false, bool do_STD_vtx_reweight=false, bool do_MET_filters = false, bool force_vtx_reweight = false, bool use_mu_DZ_trig = false){

  cout<<"Using Histogram Directory: "<<histo_dir<<endl;

  if (data){
    ScanChain(getDataChain(data_set), "data", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig); 
  }
  
  if (DY){
    ScanChain(getDYChain(data_set), "DY", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig);  
  }
  
  if (ttbar){
    ScanChain(getTTbarChain(data_set), "TTBar", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig); 
  }
  
  if (zz) {
    ScanChain(getZZChain(data_set), "ZZ", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig); 
  }

  if (ST) {
    ScanChain(getSTChain(data_set), "SingleTop", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig); 
  }

  if (ww){
    ScanChain(getWWChain(data_set), "WW", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig); 
  }

  if (wz) {
    ScanChain(getWZChain(data_set), "WZ", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig); 
  }

  if (vvv) {
    ScanChain(getVVVChain(data_set), "VVV", histo_dir, doVtxFix, do_STD_vtx_reweight, do_MET_filters, force_vtx_reweight, use_mu_DZ_trig); 
}
}
