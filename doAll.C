#include "ScanChain.C"
#include "DefineDatasets.C"
#include "getReweightVtxHist.C"

void doAll(TString histo_dir, TString data_set, bool data=true, bool DY=true, bool ttbar=true, bool ST=true, bool zz=true, bool ww=true, bool wz=true, bool vvv=true, bool makeVTXCorrections=false){

  cout<<"Using Histogram Directory: "<<histo_dir<<endl;

  if (makeVTXCorrections){
    ScanChain(getDataChain(data_set), "data", histo_dir, false); 
    ScanChain(getDYChain(data_set), "DY", histo_dir, false);
    getReweightVtxHist(histo_dir);
    return;
  }
  else{ 
    if (data){
      ScanChain(getDataChain(data_set), "data", histo_dir, true); 
    }

    if (DY){
      ScanChain(getDYChain(data_set), "DY", histo_dir, true);  
    }

    if (ttbar){
      ScanChain(getTTbarChain(data_set), "TTBar", histo_dir, true); 
    }

    if (zz) {
      ScanChain(getZZChain(data_set), "ZZ", histo_dir, true); 
    }

    if (ST) {
      ScanChain(getSTChain(data_set), "SingleTop", histo_dir, true); 
    }

    if (ww){
      ScanChain(getWWChain(data_set), "WW", histo_dir, true); 
    }

    if (wz) {
      ScanChain(getWZChain(data_set), "WZ", histo_dir, true); 
    }
    
    if (vvv) {
      ScanChain(getVVVChain(data_set), "VVV", histo_dir, true); 
    }
  }
}
