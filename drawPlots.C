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

#include "DefineHistograms.C"

using namespace std;

    
TString drawAll(vector<TString> plot_names, TString input_dir, TString save_dir, bool do_extra=false){
  TString errors="";
  PlotList *plot_info = getPlotList();

  TFile* f_DY = new TFile(input_dir+"METStudy_DY.root");
  TFile* f_data = new TFile(input_dir+"METStudy_data.root");
  TFile* f_TTbar = new TFile(input_dir+"METStudy_TTBar.root");;

  TFile* f_ST;
  TFile* f_VVV;
  TFile* f_WW;
  TFile* f_WZ;
  TFile* f_ZZ;


  if (do_extra) {
    f_ST = new TFile(input_dir+"METStudy_SingleTop.root");
    f_VVV = new TFile(input_dir+"METStudy_VVV.root");
    f_WW = new TFile(input_dir+"METStudy_WW.root");
    f_WZ = new TFile(input_dir+"METStudy_WZ.root");
    f_ZZ = new TFile(input_dir+"METStudy_ZZ.root");
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
    
    TH1F* data = (TH1F*) ((TH1F*) f_data->Get("data_"+plot_info->histName()))->Clone("datahist_"+plot_name);
    cout<<plot_info->histName()<<" found in "<<f_data->GetName()<<endl;

    TH1F* zjets = (TH1F*) ( (TH1F*) f_DY->Get("DY_"+plot_info->histName()) )->Clone("zjetshist_"+plot_name);
    cout<<plot_info->histName()<<" found in "<<f_DY->GetName()<<endl;

    TH1F* fsbkg= (TH1F*) ((TH1F*) f_TTbar->Get("TTBar_"+plot_info->histName()))->Clone("ttbarhist_"+plot_name);
    cout<<plot_info->histName()<<" found in "<<f_TTbar->GetName()<<endl;

    // Build Extra Plots
    TH1F* VVV;
    TH1F* WZ;
    TH1F* WW;
    TH1F* ZZ;
    TH1F* extra;

    if (do_extra)
    {
        VVV = (TH1F*) ((TH1F*) f_VVV->Get("VVV_"+plot_info->histName()))->Clone("VVVhist_"+plot_name);
    cout<<plot_name<<" found in "<<f_VVV->GetName()<<endl;

        WW = (TH1F*) ((TH1F*) f_WW->Get("WW_"+plot_info->histName()))->Clone("WWhist_"+plot_name);
    cout<<plot_name<<" found in "<<f_WW->GetName()<<endl;

        WZ = (TH1F*) ((TH1F*) f_WZ->Get("WZ_"+plot_info->histName()))->Clone("WZhist_"+plot_name);
    cout<<plot_name<<" found in "<<f_WZ->GetName()<<endl;

        ZZ = (TH1F*) ((TH1F*) f_ZZ->Get("ZZ_"+plot_info->histName()))->Clone("ZZhist_"+plot_name);
    cout<<plot_name<<" found in "<<f_ZZ->GetName()<<endl;

        extra = (TH1F*) ((TH1F*) f_VVV->Get("VVV_"+plot_info->histName()))->Clone("extrahist_"+plot_name);
    extra->Add(WW);
    extra->Add(WZ);
    extra->Add(ZZ);
    }

    TH1F* mc_sum = (TH1F*) zjets->Clone("mc_sum");
    mc_sum->Add(fsbkg);
    if (do_extra) {mc_sum->Add(extra);}

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

    data->Rebin(plot_info->binSize());
    zjets->Rebin(plot_info->binSize());
    fsbkg->Rebin(plot_info->binSize());
    if (do_extra){extra->Rebin(plot_info->binSize());}
    mc_sum->Rebin(plot_info->binSize());

    //===========================
    // Normalize MC
    //===========================
    double numEventsData = data->Integral(0,-1);
    double numEventsMC = mc_sum->Integral(0,-1);

    TString s1 = "Number of events in Data: ";
    s1+=TString(to_string(numEventsData));
    TString s2 = "Number of events in MC: ";
    s2+=TString(to_string(numEventsMC));

    TLatex tex;
    tex.SetTextAlign(23);
    tex.SetTextSize(0.08);
    tex.DrawLatex(0.8, 0.95, s1);
    tex.DrawLatex(0.8, 0.85, s2);
    /*double scaleFactor = ((double) numEventsData/numEventsMC);

    zjets->Scale(scaleFactor);
    fsbkg->Scale(scaleFactor);
    if (do_extra) extra->Scale(scaleFactor);
    mc_sum->Scale(scaleFactor);*/


    //===========================
    // SET MC COLORS
    //===========================
    
    zjets->SetFillColor(kAzure+5);
    zjets->SetFillStyle(1001);

    fsbkg->SetFillColor(kYellow+1);
    fsbkg->SetFillStyle(1001);

    if (do_extra) {
    extra->SetFillColor(kMagenta);
    extra->SetFillStyle(1001);
    }

    data->SetMarkerStyle(20);

    cout<<"Building Stack"<<endl;
    
    THStack * stack = new THStack("stack_"+plot_name, plot_info->title());
    if (do_extra) {stack->Add(extra);}
    stack->Add(fsbkg);
    stack->Add(zjets);

    //===========================
    // Find Plot Maxima
    //===========================
    
    double ymax = 0;
    TH1F* clonedMC = (TH1F*) mc_sum->Clone("clonedMC_forReweight_"+plot_name);
    TH1F* clonedData = (TH1F*) data->Clone("clonedData_forReweight_"+plot_name);

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

    TH2F* h_axes = new TH2F(Form("%s_axes",plot_name.Data()),plot_info->title(),data->GetNbinsX(),plot_info->xmin(),plot_info->xmax(),1000,0.001,ymax);

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
        double n_bins = data->GetNbinsX();
        double overflow_data = data->GetBinContent(n_bins + 1);
        double overflow_zjets = zjets->GetBinContent(n_bins + 1);
        double overflow_fsbkg = fsbkg->GetBinContent(n_bins + 1);
        double overflow_extra;
        if (do_extra) {overflow_extra= extra->GetBinContent(n_bins + 1);}
        double overflow_mcsum = zjets->GetBinContent(n_bins + 1);

        double max_data = data->Integral(data->FindBin(plot_info->xmax()) - 1, n_bins);
        double max_zjets = zjets->Integral(zjets->FindBin(plot_info->xmax()) - 1, n_bins);
        double max_fsbkg = fsbkg->Integral(fsbkg->FindBin(plot_info->xmax()) - 1, n_bins);
        double max_extra;
        if (do_extra) max_extra = extra->Integral(extra->FindBin(plot_info->xmax()) - 1, n_bins);
        double max_mcsum = mc_sum->Integral(mc_sum->FindBin(plot_info->xmax()) - 1, n_bins);

        data->SetBinContent(data->FindBin(plot_info->xmax()) - 1, max_data+overflow_data);
        zjets->SetBinContent(zjets->FindBin(plot_info->xmax()) - 1, max_zjets+overflow_zjets);
        fsbkg->SetBinContent(fsbkg->FindBin(plot_info->xmax()) - 1, max_fsbkg+overflow_fsbkg);
        if (do_extra) {
            extra->SetBinContent(extra->FindBin(plot_info->xmax()) - 1, max_extra+overflow_extra);
        }
        mc_sum->SetBinContent(mc_sum->FindBin(plot_info->xmax()) - 1 , max_mcsum+overflow_mcsum);
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
    stack->Draw("HIST SAME");
    data->Draw("E1 SAME");

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
    
    l1->SetHeader("Double #mu JSON: 2058.01/pb Double EG JSON: 2058.36/pb");
    l1->AddEntry(data, "data", "p");
    l1->AddEntry(zjets, "Z+jets", "f");
    l1->AddEntry(fsbkg, "t#bar{t}", "f");
    if (do_extra) {l1->AddEntry(extra, "Low #sigma", "f");}

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
    
    TH1F* residual = (TH1F*) data->Clone("residual");
    residual->Divide(mc_sum);

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
    delete mc_sum;
    delete stack;
    delete zjets;
    delete fsbkg;
    //delete extra;
    delete data;
    delete residual;
    delete ratiopad;
    delete plotpad;
    delete fullpad;
    delete c;

    cout<<"next sample...\n"<<endl;
  }

  cout<<"Cleaning up file variables"<<endl;
  f_DY->Close();
  f_TTbar->Close();
  if (do_extra) {
      f_ST->Close();
  f_VVV->Close();
  f_WW->Close();
  f_WZ->Close();
  f_ZZ->Close();
  }
  delete f_DY;
  delete f_TTbar;
  
  if (do_extra) {
    delete f_ST;
  delete f_VVV;
  delete f_WW;
  delete f_WZ;
  delete f_ZZ;
  }

  f_data->Close();
  delete f_data;
  return errors;
  
}

void drawPlots(TString save_dir, TString input_dir, bool pt=false, bool phi=false, bool sumET=false, bool MET=true, bool extra=true, bool do_extra=false)
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

    errors+=drawAll(plot_names, input_dir, save_dir, do_extra);
    plot_names.clear();
  }

  if (extra) { 
    plot_names.push_back("nVert");
    plot_names.push_back("dilmass");
    plot_names.push_back("dilmass_ee");
    plot_names.push_back("dilmass_mm");
    plot_names.push_back("dilmass_2jets");
    plot_names.push_back("dilmass_2jets_ee");
    plot_names.push_back("dilmass_2jets_mm");
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

