#include <iostream>
#include <stdexcept>

#include <TFile.h>
#include <TH1F.h>

using namespace std;

void getReweightVtxHist(TString output_dir)
{

  TFile * f_data = TFile::Open(output_dir+"METStudy_data.root" , "READ");
  TFile * f_zjet = TFile::Open(output_dir+"METStudy_DY.root", "READ");

  TH1F * h_data = (TH1F*)f_data->Get("data_nVert")->Clone("h_data");
  TH1F * h_zjet = (TH1F*)f_zjet->Get("DY_nVert")->Clone("h_zjet");

  // double bins[23] = {0,5,6,7,8,
  // 					9,10,11,12,13,
  // 					14,15,16,17,18,
  // 					 19,20,21,22,23,24,25,35};

  // int nbins = 22;

  // h_data = (TH1F*) h_data->Rebin(nbins, "h_data_rebinned", bins);
  // h_zjet = (TH1F*) h_zjet->Rebin(nbins, "h_zjet_rebinned", bins);

  // h_data->Rebin(5);
  // h_zjet->Rebin(5);

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