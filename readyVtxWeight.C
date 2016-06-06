#include <iostream>
#include <stdexcept>

#include <TFile.h>
#include <TH1F.h>

#include "ScanChain.C"
#include "DefineDatasets.C"

using namespace std;

void makeReweightVtxHist(TString output_dir, TString primary_loc, TString secondary_loc,  TString primary_name, TString secondary_name)
{

  TFile * f_primary = TFile::Open(primary_loc , "READ"); //typically location to data hist
  TFile * f_secondary = TFile::Open(secondary_loc, "READ"); //typically location to zjets hist

  TH1F * h_primary = (TH1F*)f_primary->Get(primary_name+"_nVert")->Clone("h_"+primary_name);
  TH1F * h_secondary = (TH1F*)f_secondary->Get(secondary_name+"_nVert")->Clone("h_"+secondary_name);

  h_secondary->Scale(1./h_secondary->GetSumOfWeights());
  h_primary->Scale(1./h_primary->GetSumOfWeights());

  TH1F * h_vtx_ratio = (TH1F*) h_primary->Clone("h_vtx_ratio");
  h_vtx_ratio->Divide(h_secondary);

  TFile * file = TFile::Open(output_dir+"nvtx_ratio.root","RECREATE");
  file->cd();
  h_vtx_ratio->Write();
  h_primary->Write();
  h_secondary->Write();
  file->Close();
  
  return;
}

void readyVtxWeight(TString histo_dir, TString data_set, bool do_MET_filters){
    TString primary_loc, secondary_loc, primary_name, secondary_name;
    primary_name="data";
    primary_loc=histo_dir+"METStudy_"+primary_name+".root";   
    secondary_name="DY";
    secondary_loc=histo_dir+"METStudy_"+secondary_name+".root";

    //Make histogram files so that they can be reweighted. 
    ScanChain(getDataChain("80x"), primary_name, histo_dir, false, false, do_MET_filters); 
    ScanChain(getDYChain(data_set), secondary_name, histo_dir, false, false, do_MET_filters);
    makeReweightVtxHist(histo_dir, primary_loc, secondary_loc, primary_name, secondary_name);
}