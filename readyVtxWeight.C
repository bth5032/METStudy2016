#include <iostream>
#include <stdexcept>

#include <TFile.h>
#include <TH1F.h>

#include "ScanChain.C"

using namespace std;

void makeReweightVtxHist(TString output_dir)
{

  TFile * f_data = TFile::Open(output_dir+"METStudy_data.root" , "READ");
  TFile * f_zjet = TFile::Open(output_dir+"METStudy_DY.root", "READ");

  TH1F * h_data = (TH1F*)f_data->Get("data_nVert")->Clone("h_data");
  TH1F * h_zjet = (TH1F*)f_zjet->Get("DY_nVert")->Clone("h_zjet");

  h_zjet->Scale(1./h_zjet->GetSumOfWeights());
  h_data->Scale(1./h_data->GetSumOfWeights());

  TH1F * h_vtx_ratio = (TH1F*) h_data->Clone("h_vtx_ratio");
  h_vtx_ratio->Divide(h_zjet);

  TFile * file = TFile::Open(output_dir+"nvtx_ratio.root","RECREATE");
  file->cd();
  h_vtx_ratio->Write();
  h_data->Write();
  h_zjet->Write();
  file->Close();
  
  return;
}

void readyVtxWeight(TString histo_dir){
    ScanChain(getDataChain(data_set), "data", histo_dir, false); 
    ScanChain(getDYChain(data_set), "DY", histo_dir, false);
    makeReweightVtxHist(histo_dir);
}