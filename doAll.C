#include "ScanChain.C"
#include "DefineDatasets.C"

void doAll(TString data_set, TString histo_dir, bool data=true, bool DY=true, bool ttbar=true, bool ST=true, bool zz=true, bool ww=true, bool wz=true, bool vvv=true, bool doVtxFix=false){

  cout<<"Using Histogram Directory: "<<histo_dir<<endl;

  if (data){
    ScanChain(getDataChain(data_set), "data", histo_dir, doVtxFix); 
  }

  if (DY){
    ScanChain(getDYChain(data_set), "DY", histo_dir, doVtxFix);  
  }

  if (ttbar){
    ScanChain(getTTbarChain(data_set), "TTBar", histo_dir, doVtxFix); 
  }

  if (zz) {
    ScanChain(getZZChain(data_set), "ZZ", histo_dir, doVtxFix); 
  }

  if (ST) {
    ScanChain(getSTChain(data_set), "SingleTop", histo_dir, doVtxFix); 
  }

  if (ww){
    ScanChain(getWWChain(data_set), "WW", histo_dir, doVtxFix); 
  }

  if (wz) {
    ScanChain(getWZChain(data_set), "WZ", histo_dir, doVtxFix); 
  }
  
  if (vvv) {
    ScanChain(getVVVChain(data_set), "VVV", histo_dir, doVtxFix); 
  }
}
