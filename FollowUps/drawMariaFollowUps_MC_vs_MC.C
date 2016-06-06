/*
This file draws the plots that Maria wanted after showing the sumET at the JetMET meeting. It's a modified version of plots that plots the MC vs MC or Data vs Data or 80 Data vs. 76 MC.
*/

#include <iostream>
#include <stdexcept>
#include <vector>

#include "TChain.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "THStack.h"
#include "TGaxis.h"
#include "TCut.h"
#include "TH1F.h"

#include "../DefineHistograms.C"

using namespace std;

    
TString drawAll(vector<TString> plot_names, TString input_dir, TString save_dir, bool do_extra=true){
  TString errors="";
  PlotList *plot_info = getPlotList();

  //80MC vs 76MC
  
  TFile* f_80_DY = new TFile(input_dir+"80MC/METStudy_DY.root");
  TFile* f_80_TTbar = new TFile(input_dir+"80MC/METStudy_TTBar.root");;

  TFile* f_80_ST;
  TFile* f_80_VVV;
  TFile* f_80_WW;
  TFile* f_80_WZ;
  TFile* f_80_ZZ;


  if (do_extra) {
    f_80_ST = new TFile(input_dir+"80MC/METStudy_SingleTop.root");
    f_80_VVV = new TFile(input_dir+"80MC/METStudy_VVV.root");
    f_80_WW = new TFile(input_dir+"80MC/METStudy_WW.root");
    f_80_WZ = new TFile(input_dir+"80MC/METStudy_WZ.root");
    f_80_ZZ = new TFile(input_dir+"80MC/METStudy_ZZ.root");
  }


  TFile* f_76_DY = new TFile(input_dir+"76MC/METStudy_DY.root");
  TFile* f_76_TTbar = new TFile(input_dir+"76MC/METStudy_TTBar.root");;

  TFile* f_76_ST;
  TFile* f_76_VVV;
  TFile* f_76_WW;
  TFile* f_76_WZ;
  TFile* f_76_ZZ;


  if (do_extra) {
    f_76_ST = new TFile(input_dir+"76MC/METStudy_SingleTop.root");
    f_76_VVV = new TFile(input_dir+"76MC/METStudy_VVV.root");
    f_76_WW = new TFile(input_dir+"76MC/METStudy_WW.root");
    f_76_WZ = new TFile(input_dir+"76MC/METStudy_WZ.root");
    f_76_ZZ = new TFile(input_dir+"76MC/METStudy_ZZ.root");
  }

  cout << "Found files"<<endl;

  while(!plot_names.empty()){
    TString plot_name = plot_names.back();
    plot_names.pop_back();

    //don't make plots if we can't look up the info.
    if (! plot_info->setPlot(plot_name) )
    {
        errors+="=======================================\n\
ERROR: Could not find plot info for "+plot_name+"\n\
=======================================\n";
        continue;
    }
    cout << "Making Plots for: "<<plot_name<<endl;
    
    // --------------
    // 80
    //---------------

    TH1F* t_80_zjets = (TH1F*) ( (TH1F*) f_80_DY->Get("DY_"+plot_info->histName()) )->Clone("zjetshist_80_"+plot_name);
    cout<<plot_info->histName()<<" found in "<<f_80_DY->GetName()<<endl;

    TH1F* t_80_fsbkg= (TH1F*) ((TH1F*) f_80_TTbar->Get("TTBar_"+plot_info->histName()))->Clone("ttbarhist_80_"+plot_name);
    cout<<plot_info->histName()<<" found in "<<f_80_TTbar->GetName()<<endl;

    // Build Extra Plots
    TH1F* t_80_VVV;
    TH1F* t_80_WZ;
    TH1F* t_80_WW;
    TH1F* t_80_ZZ;
    TH1F* t_80_extra;

    if (do_extra)
    {
        t_80_VVV = (TH1F*) ((TH1F*) f_80_VVV->Get("VVV_"+plot_info->histName()))->Clone("VVVhist_80_"+plot_name);
        cout<<plot_name<<" found in "<<f_80_VVV->GetName()<<endl;

        t_80_WW = (TH1F*) ((TH1F*) f_80_WW->Get("WW_"+plot_info->histName()))->Clone("WWhist_80_"+plot_name);
        cout<<plot_name<<" found in "<<f_80_WW->GetName()<<endl;

        t_80_WZ = (TH1F*) ((TH1F*) f_80_WZ->Get("WZ_"+plot_info->histName()))->Clone("WZhist_80_"+plot_name);
        cout<<plot_name<<" found in "<<f_80_WZ->GetName()<<endl;

        t_80_ZZ = (TH1F*) ((TH1F*) f_80_ZZ->Get("ZZ_"+plot_info->histName()))->Clone("ZZhist_80_"+plot_name);
        cout<<plot_name<<" found in "<<f_80_ZZ->GetName()<<endl;

        t_80_extra = (TH1F*) ((TH1F*) f_80_VVV->Get("VVV_"+plot_info->histName()))->Clone("extrahist_80_"+plot_name);
        t_80_extra->Add(t_80_WW);
        t_80_extra->Add(t_80_WZ);
        t_80_extra->Add(t_80_ZZ);
    }

    TH1F* t_80_mc_sum = (TH1F*) t_80_zjets->Clone("mc_sum");
    t_80_mc_sum->Add(80_fsbkg);
    if (do_extra) {t_80_mc_sum->Add(t_80_extra);}

    // --------------
    // 76
    //---------------

    TH1F* t_76_zjets = (TH1F*) ( (TH1F*) f_76_DY->Get("DY_"+plot_info->histName()) )->Clone("zjetshist_76_"+plot_name);
    cout<<plot_info->histName()<<" found in "<<f_76_DY->GetName()<<endl;

    TH1F* t_76_fsbkg= (TH1F*) ((TH1F*) f_76_TTbar->Get("TTBar_"+plot_info->histName()))->Clone("ttbarhist_76_"+plot_name);
    cout<<plot_info->histName()<<" found in "<<f_76_TTbar->GetName()<<endl;

    // Build Extra Plots
    TH1F* t_76_VVV;
    TH1F* t_76_WZ;
    TH1F* t_76_WW;
    TH1F* t_76_ZZ;
    TH1F* t_76_extra;

    if (do_extra)
    {
        t_76_VVV = (TH1F*) ((TH1F*) f_76_VVV->Get("VVV_"+plot_info->histName()))->Clone("VVVhist_76_"+plot_name);
        cout<<plot_name<<" found in "<<f_76_VVV->GetName()<<endl;

        t_76_WW = (TH1F*) ((TH1F*) f_76_WW->Get("WW_"+plot_info->histName()))->Clone("WWhist_76_"+plot_name);
        cout<<plot_name<<" found in "<<f_76_WW->GetName()<<endl;

        t_76_WZ = (TH1F*) ((TH1F*) f_76_WZ->Get("WZ_"+plot_info->histName()))->Clone("WZhist_76_"+plot_name);
        cout<<plot_name<<" found in "<<f_76_WZ->GetName()<<endl;

        t_76_ZZ = (TH1F*) ((TH1F*) f_76_ZZ->Get("ZZ_"+plot_info->histName()))->Clone("ZZhist_76_"+plot_name);
        cout<<plot_name<<" found in "<<f_76_ZZ->GetName()<<endl;

        t_76_extra = (TH1F*) ((TH1F*) f_76_VVV->Get("VVV_"+plot_info->histName()))->Clone("extrahist_76_"+plot_name);
        t_76_extra->Add(t_76_WW);
        t_76_extra->Add(t_76_WZ);
        t_76_extra->Add(t_76_ZZ);
    }

    TH1F* t_76_mc_sum = (TH1F*) t_76_zjets->Clone("mc_sum");
    t_76_mc_sum->Add(t_76_fsbkg);
    if (do_extra) {t_76_mc_sum->Add(t_76_extra);}

    cout << "Histograms pulled from files, adding draw options"<<endl;

    //============================================
    // Draw Data-MC Plots
    //============================================

    TCanvas * c = new TCanvas("c","",2000,2000);
    c->cd();
    gPad->SetRightMargin(0.05);
    gPad->Modified();
    gStyle->SetOptStat(kFALSE);
    TPad *fullpad = new TPad("fullpad", "fullpad", 0,0,1,1);

    fullpad->Draw();
    fullpad->cd();

    TPad *plotpad = new TPad("plotpad", "plotpad",0,0.2,1.0,0.99);
    
    plotpad->SetRightMargin(0.05);
    if (plot_info->hasOpt("extraRightMargin"))
    {
        plotpad->SetRightMargin(0.08);
    }
    plotpad->SetBottomMargin(0.12);

    plotpad->Draw();
    plotpad->cd();
    
    if (plot_info->hasOpt("logy"))
    {
        cout<<"Plot tagged for log y-axis"<<endl;
        plotpad->SetLogy();
    }

    t_76_mc_sum->Rebin(plot_info->binSize());
    t_80_mc_sum->Rebin(plot_info->binSize());

    //===========================
    // Normalize MC
    //===========================
    double numEventsData = t_80_mc_sum->Integral(0,-1);
    double numEventsMC = t_76_mc_sum->Integral(0,-1);
    double scaleFactor = ((double) numEventsData/numEventsMC);

    t_76_mc_sum->Scale(scaleFactor);


    //===========================
    // SET MC COLORS
    //===========================
    
    t_76_mc_sum->SetFillColor(kAzure+5);
    t_76_mc_sum->SetFillStyle(1001);

    t_80_mc_sum->SetMarkerStyle(20);

    cout<<"Building Stack"<<endl;


    //===========================
    // Find Plot Maxima
    //===========================
    
    double ymax = 0;
    TH1F* clonedMC = (TH1F*) t_76_mc_sum->Clone("clonedMC_forReweight_"+plot_name);
    TH1F* clonedData = (TH1F*) t_80_mc_sum->Clone("clonedData_forReweight_"+plot_name);

    clonedMC->GetXaxis()->SetRangeUser(plot_info->xmin(), plot_info->xmax());
    clonedData->GetXaxis()->SetRangeUser(plot_info->xmin(), plot_info->xmax());

    if (clonedMC->GetMaximum() < clonedData->GetMaximum()){
        ymax = 1.2*clonedData->GetMaximum();
    }
    else {
        ymax = 1.2*clonedMC->GetMaximum();   
    }

    delete clonedMC;
    delete clonedData;

    cout<<"Proper plot maximum set to "<<ymax<<endl;

    TH2F* h_axes = new TH2F(Form("%s_axes",plot_name.Data()),plot_info->title(),t_80_mc_sum->GetNbinsX(),plot_info->xmin(),plot_info->xmax(),1000,0.001,ymax);

    /*if(plot_info->hasOpt("maxDigits2")){
        //TGaxis::SetMaxDigits(2);
    }*/

    //-----------------------
    // AXES FIX
    //-----------------------

    cout<<"Setting axis names"<<endl;
    h_axes->GetXaxis()->SetTitle(plot_info->xlabel());
    h_axes->GetYaxis()->SetTitle(plot_info->ylabel());


    //----------------------
    // ADD OVERFLOW BIN
    //----------------------
    if (plot_info->hasOpt("overflow")){
        cout<<"Plot tagged for overflow bin, building..."<<endl;
        double n_bins = t_80_mc_sum->GetNbinsX();
        
        double overflow_80_mc_sum = t_80_mc_sum->GetBinContent(n_bins + 1);
        double overflow_76_mc_sum = t_76_mc_sum->GetBinContent(n_bins + 1);

        double max_80_mc_sum = 80_mc_sum->Integral(t_80_mc_sum->FindBin(plot_info->xmax()) - 1, n_bins);
        double max_76_mc_sum = 76_mc_sum->Integral(t_76_mc_sum->FindBin(plot_info->xmax()) - 1, n_bins);

        t_80_mc_sum->SetBinContent(t_80_mc_sum->FindBin(plot_info->xmax()) - 1, max_80_mc_sum+overflow_80_mc_sum);
        t_76_mc_sum->SetBinContent(t_76_mc_sum->FindBin(plot_info->xmax()) - 1 , max_76_mc_sum+overflow_76_mc_sum);
    }

        
    /*if (plot_info->type() == "pt" || plot_info->type() == "met"){
        h_axes->GetYaxis()->SetTitleOffset(1.5);
        h_axes->GetYaxis()->SetTitleSize(0.05);
        h_axes->GetYaxis()->SetLabelSize(0.04);
    }
    else if (plot_info->type() == "phi"){
        h_axes->GetYaxis()->SetTitleOffset(1);
        h_axes->GetYaxis()->SetTitleSize(0.04);
        h_axes->GetYaxis()->SetLabelSize(0.03);
    }*/

    plotpad->SetLeftMargin(0.15);
    h_axes->GetYaxis()->SetTitleOffset(1.3);
    h_axes->GetYaxis()->SetTitleSize(0.05);
    h_axes->GetYaxis()->SetLabelSize(0.04);

    cout<<"Drawing histograms"<<endl;
    h_axes->Draw();
    t_80_mc_sum->Draw("E1 SAME");

    plotpad->RedrawAxis();

    TLegend *l1;
    if (plot_info->type()=="phi"){
     l1 = new TLegend(0.73, 0.23, 0.88, 0.38);
    }
    else{
     l1 = new TLegend(0.73, 0.73, 0.88, 0.88);
    }

    l1->SetLineColor(kWhite);  
    l1->SetShadowColor(kWhite);
    l1->SetFillColor(kWhite);
    l1->AddEntry(t_80_mc_sum, "Sum of 80 (2016) MC", "p");
    l1->AddEntry(t_76_mc_sum, "Sum of 76 (2015) MC", "f");

    l1->Draw("same");

    //--------------------------
    // Fill in Residual Plot
    //--------------------------

    cout<<"Getting ready for residual plots"<<endl;
    fullpad->cd();
    TPad *ratiopad = new TPad("ratiopad", "ratiopad" ,0.,0.,1,0.21);
    ratiopad->SetTopMargin(0.05);
    ratiopad->SetLeftMargin(0.15);
    ratiopad->SetBottomMargin(0.1);
    ratiopad->SetRightMargin(0.05);
    ratiopad->SetGridy();  // doesn't actually appear for some reason..
    ratiopad->Draw();
    ratiopad->cd();
    
    TH1F* residual = (TH1F*) t_80_mc_sum->Clone("residual");
    residual->Divide(t_76_mc_sum);

    /*cout<<"Fixing error bars"<<endl;
    for (int count=1; count<=mc_sum->GetNbinsX(); count++){ 
      double relative_error = (mc_sum->GetBinError(count))/ (mc_sum->GetBinContent(count));
      residual->SetBinError(count, residual->GetBinContent(count)*relative_error);
    }*/

    cout<<"Building axes"<<endl;
    TH1F* h_axis_ratio = new TH1F(Form("%s_residual_axes",plot_name.Data()),"",residual->GetNbinsX(),plot_info->xmin(),plot_info->xmax());

    h_axis_ratio->GetYaxis()->SetTitleOffset(0.33);
    h_axis_ratio->GetYaxis()->SetTitleSize(0.18);
    h_axis_ratio->GetYaxis()->SetNdivisions(5);
    h_axis_ratio->GetYaxis()->SetLabelSize(0.15);
    //h_axis_ratio->GetYaxis()->SetRangeUser(0.5,1.5);
    h_axis_ratio->GetYaxis()->SetRangeUser(0.001,2.0);
    h_axis_ratio->GetYaxis()->SetTitle("Data/MC");
    h_axis_ratio->GetXaxis()->SetTickLength(0.07);
    h_axis_ratio->GetXaxis()->SetTitleSize(0.);
    h_axis_ratio->GetXaxis()->SetLabelSize(0.);
    
    TLine* line1 = new TLine(plot_info->xmin(),1,plot_info->xmax(),1);
    line1->SetLineStyle(2);
    
    cout<<"Drawing ratio plot"<<endl;
    h_axis_ratio->Draw("axis");
    line1->Draw("same");
    residual->Draw("same");
    
    c->Update();
    c->cd();

    cout<<"Saving..."<<endl;
    c->SaveAs(save_dir+plot_name+TString(".pdf"));
    c->SaveAs(save_dir+plot_name+TString(".png"));
    //c->SaveAs(save_dir+plot_name+TString(".root"));
    //c->SaveAs(save_dir+plot_name+TString(".C"));

    cout<<"Cleaning up plot variables"<<endl;
    delete l1;
    delete t_76_mc_sum;
    //delete extra;
    delete t_80_mc_sum;
    delete residual;
    delete ratiopad;
    delete plotpad;
    delete fullpad;
    delete c;

    cout<<"next sample...\n"<<endl;
  }

  cout<<"Cleaning up file variables"<<endl;
  f_80_DY->Close();
  f_80_TTbar->Close();
  if (do_extra) {
      f_80_ST->Close();
      f_80_VVV->Close();
      f_80_WW->Close();
      f_80_WZ->Close();
      f_80_ZZ->Close();
  }
  delete f_76_DY;
  delete f_76_TTbar;
  
  if (do_extra) {
    delete f_76_ST;
    delete f_76_VVV;
    delete f_76_WW;
    delete f_76_WZ;
    delete f_76_ZZ;
  }

  return errors;
  
}

void drawMariaFollowUps_MC_vs_MC(TString save_dir="~/public_html/ZMET2016/looper/maria/80MCVs76MC/", TString input_dir="~/maria/", bool pt=true, bool phi=true, bool sumET=true, bool MET=true, bool extra=true, bool do_extra=false)
{
  
  vector<TString> plot_names;
  TString errors="";

  if (pt) {
    //============================================
    // PT plots
    //============================================

    //-----------------define---------------------

    plot_names.push_back("photonPT0013");
    plot_names.push_back("photonPT1624");
    plot_names.push_back("photonPT2430");
    plot_names.push_back("photonPT30in");

    /*plot_names.push_back("photonPT0013_5gcut");
    plot_names.push_back("photonPT1624_5gcut");
    plot_names.push_back("photonPT2430_5gcut");
    plot_names.push_back("photonPT30in_5gcut");*/

    plot_names.push_back("chargedPT0013");
    plot_names.push_back("chargedPT1624");
    plot_names.push_back("neutralPT0013");
    plot_names.push_back("neutralPT1624");
    plot_names.push_back("neutralPT2430");
    plot_names.push_back("neutralPT30in");   

    // Run over PT plots
    errors+=drawAll(plot_names, input_dir, save_dir, do_extra);
    plot_names.clear();
  }

  if (phi) {
  //============================================
  // Phi plots
  //============================================
  //-----------------define---------------------
    plot_names.push_back("photonPHI0013");
    plot_names.push_back("photonPHI1624");
    plot_names.push_back("photonPHI2430");
    plot_names.push_back("photonPHI30in");
    plot_names.push_back("chargedPHI0013");
    plot_names.push_back("chargedPHI1624");
    plot_names.push_back("neutralPHI0013");
    plot_names.push_back("neutralPHI1624");
    plot_names.push_back("neutralPHI2430");
    plot_names.push_back("neutralPHI30in");

    plot_names.push_back("photonPHI0013_PCUT20");
    plot_names.push_back("photonPHI1624_PCUT20");
    plot_names.push_back("photonPHI2430_PCUT20");
    plot_names.push_back("photonPHI30in_PCUT20");
    plot_names.push_back("chargedPHI0013_PCUT20");
    plot_names.push_back("chargedPHI1624_PCUT20");
    plot_names.push_back("neutralPHI0013_PCUT20");
    plot_names.push_back("neutralPHI1624_PCUT20");
    plot_names.push_back("neutralPHI2430_PCUT20");
    plot_names.push_back("neutralPHI30in_PCUT20");   
    
    // Run over Phi plots
    errors+=drawAll(plot_names, input_dir, save_dir, do_extra);
    plot_names.clear();
  }

  if (sumET) {
  //============================================
  // SUMET
  //============================================
  //-----------------define---------------------
    plot_names.push_back("photonSET0013");
    plot_names.push_back("photonSET1624");
    plot_names.push_back("photonSET2430");
    plot_names.push_back("photonSET30in");

    /*plot_names.push_back("photonSET0013_5gcut");
    plot_names.push_back("photonSET1624_5gcut");
    plot_names.push_back("photonSET2430_5gcut");
    plot_names.push_back("photonSET30in_5gcut");*/

    plot_names.push_back("chargedSET0013");
    plot_names.push_back("chargedSET1624");
    plot_names.push_back("neutralSET0013");
    plot_names.push_back("neutralSET1624");
    plot_names.push_back("neutralSET2430");
    plot_names.push_back("neutralSET30in");  

    plot_names.push_back("netSET");
    plot_names.push_back("netSET_log");
    
    // Run over Sum ET plots
    errors+=drawAll(plot_names, input_dir, save_dir, do_extra);
    plot_names.clear();
  }
  
  if (MET){
  //============================================
  // MET
  //============================================
  //-----------------define---------------------
    //Type 1 MET
    plot_names.push_back("type1MET");
    plot_names.push_back("type1MET_2jets");
    plot_names.push_back("type1MET_el");
    plot_names.push_back("type1MET_2jets_el");
    plot_names.push_back("type1MET_mu");
    plot_names.push_back("type1MET_2jets_mu");
    
    //RAW MET
    plot_names.push_back("rawMET");
    plot_names.push_back("rawMET_2jets");
    plot_names.push_back("rawMET_el");
    plot_names.push_back("rawMET_2jets_el");
    plot_names.push_back("rawMET_mu");
    plot_names.push_back("rawMET_2jets_mu");

    //MET-PHI
    plot_names.push_back("netPHI");
    plot_names.push_back("netPHI_2jets");
    plot_names.push_back("netPHI_el");
    plot_names.push_back("netPHI_2jets_el");
    plot_names.push_back("netPHI_mu");
    plot_names.push_back("netPHI_2jets_mu");

    errors+=drawAll(plot_names, input_dir, save_dir, do_extra);
    plot_names.clear();
  }

  if (extra) { 
    plot_names.push_back("nVert");
    plot_names.push_back("dilmass");
    plot_names.push_back("dilmass_ee");
    plot_names.push_back("dilmass_mm");
    plot_names.push_back("PHIinBump");
    plot_names.push_back("type1MET_long");
    plot_names.push_back("zoomBump");
    //plot_names.push_back("numMETFilters");

    /*plot_names.push_back("deltaR");
    plot_names.push_back("deltaR_2jets");
    plot_names.push_back("deltaR_2jets_mt2cut");
    
    plot_names.push_back("mt2_ll");
    plot_names.push_back("ptll_mt2cut");*/

    errors+=drawAll(plot_names, input_dir, save_dir, do_extra);
    plot_names.clear();
  }


  cout<<errors<<endl;
  return;
}

