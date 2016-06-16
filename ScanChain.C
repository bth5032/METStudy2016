// Usage:
// > root -b doAll.C

//
// 2016 MET study looper. Written by Bobak Hashemi May 13 2016
//

// C++
#include <iostream>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"

// ZMET2016
#include "ZMET2016.cc"

// CORE
#include "dorky.cc"


using namespace std;
using namespace zmet;
using namespace duplicate_removal;

bool passMETFilters(){

  if( phys.isData()                   ){
  if (phys.nVert() == 0               ) return false;

      if (!phys.Flag_HBHENoiseFilter                   ()      ) return false;
      if (!phys.Flag_HBHEIsoNoiseFilter                ()      ) return false;
      if ( phys.Flag_CSCTightHalo2015Filter_isLoaded ){
        if (!phys.Flag_CSCTightHalo2015Filter            ()      ) return false;  
      }
      else{
        if (!phys.Flag_CSCTightHaloFilter            ()      ) return false;
      }
      if (!phys.Flag_EcalDeadCellTriggerPrimitiveFilter()      ) return false;
      if (!phys.Flag_goodVertices                      ()      ) return false;
      if (!phys.Flag_eeBadScFilter                     ()      ) return false;

  }
  return true;
}

bool passMuonTriggers(){
  if ( phys.isData() ){
    if ( conf->get("use_muon_DZ_triggers") == "true" ){
      cout<<"Using DZ triggers"<<endl;
      return (phys.HLT_DoubleMu() || phys.HLT_DoubleMu_tk() || phys.HLT_DoubleMu_noiso());
    }
    else{
      cout<<"Using Non DZ triggers"<<endl;
      return (phys.HLT_DoubleMu_nonDZ() || phys.HLT_DoubleMu_tk_nonDZ() || phys.HLT_DoubleMu_noiso());
    } 
  }
  
  else{
    return true; //MC always passes
  }
}

bool passElectronTriggers(){
  if (phys.isData()){
    return (phys.HLT_DoubleEl_DZ() || phys.HLT_DoubleEl_noiso() );
  }
  else{
    return true; //MC always passes
  }
}

bool passBaseCut(){
  if (!(phys.dilmass() < 101 && phys.dilmass() > 81)) return false;

  if (!(phys.nlep() >= 2)) return false;
  if (!(phys.lep_pt().at(0) > 20 && phys.lep_pt().at(1) > 20)) return false;

  if (!(abs(phys.lep_p4().at(0).eta()) < 2.4 && abs(phys.lep_p4().at(1).eta()) < 2.4)) return false;


  if (!(phys.dRll() > 0.1)) return false; 

  if (!(phys.evt_type() == 0)) return false;
  
  if (! ( passMuonTriggers() && phys.hyp_type() == 1 )){
    if (! ( passElectronTriggers() && phys.hyp_type() == 0) )
    {
      return false; 
    }
  }

  if (! (phys.evt_passgoodrunlist() > 0)) return false;

  return true;
}

bool vinceRegion(){
  if (! (phys.njets() >= 2)) return false;
  if (! (phys.nBJetMedium() == 0)) return false;

  return true;
}


int ScanChain( TChain* chain, TString sampleName, TString savePath, bool dovtxreweighting = false, bool do_stdvtx_reweighting = false, bool do_MET_filters = false, bool force_vtx_reweight=false, bool fast = true, int nEvents = -1) {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
  
  //=======================================
  // Define Histograms
  //=======================================
  
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  cout<<"Opening file "<<savePath+"METStudy_"+sampleName+".root"<<endl;
  TFile * output = new TFile(savePath+"METStudy_"+sampleName+".root", "recreate");

  TH1I *numEvents = new TH1I("numEvents_"+sampleName, "Number of events in "+sampleName, 1, 0, 1);
  numEvents->SetDirectory(rootdir);

  //MET Histos
  TH1F *t1met = new TH1F(sampleName+"_type1MET", "Type 1 MET for "+sampleName, 6000,0,6000);
  t1met->SetDirectory(rootdir);
  t1met->Sumw2();

  TH1F *t1met_2jets = new TH1F(sampleName+"_type1MET_2jets", "Type 1 MET for events with at least 2 jets in "+sampleName, 6000,0,6000);
  t1met_2jets->SetDirectory(rootdir);
  t1met_2jets->Sumw2();

  TH1F *t1met_el = new TH1F(sampleName+"_type1MET_el", "Type 1 MET for "+sampleName+" (just dielectron events)", 6000,0,6000);
  t1met_el->SetDirectory(rootdir);
  t1met_el->Sumw2();

  TH1F *t1met_2jets_el = new TH1F(sampleName+"_type1MET_2jets_el", "Type 1 MET for events with at least 2 jets in "+sampleName+" (just dielectron events)", 6000,0,6000);
  t1met_2jets_el->SetDirectory(rootdir);
  t1met_2jets_el->Sumw2();

  TH1F *t1met_mu = new TH1F(sampleName+"_type1MET_mu", "Type 1 MET for "+sampleName+" (just dimuon events)", 6000,0,6000);
  t1met_mu->SetDirectory(rootdir);
  t1met_mu->Sumw2();

  TH1F *t1met_2jets_mu = new TH1F(sampleName+"_type1MET_2jets_mu", "Type 1 MET for events with at least 2 jets in "+sampleName+" (just dimuon events)", 6000,0,6000);
  t1met_2jets_mu->SetDirectory(rootdir);
  t1met_2jets_mu->Sumw2();

  TH1F *rawmet = new TH1F(sampleName+"_rawMET", "Raw MET for "+sampleName, 6000,0,6000);
  rawmet->SetDirectory(rootdir);
  rawmet->Sumw2();

  TH1F *rawmet_2jets = new TH1F(sampleName+"_rawMET_2jets", "Raw MET for events with at least 2 jets in "+sampleName, 6000,0,6000);
  rawmet_2jets->SetDirectory(rootdir);
  rawmet_2jets->Sumw2();

  TH1F *rawmet_el = new TH1F(sampleName+"_rawMET_el", "Raw MET for "+sampleName+" (just dielectron events)", 6000,0,6000);
  rawmet_el->SetDirectory(rootdir);
  rawmet_el->Sumw2();

  TH1F *rawmet_2jets_el = new TH1F(sampleName+"_rawMET_2jets_el", "Raw MET for events with at least 2 jets in "+sampleName+" (just dielectron events)", 6000,0,6000);
  rawmet_2jets_el->SetDirectory(rootdir);
  rawmet_2jets_el->Sumw2();

  TH1F *rawmet_mu = new TH1F(sampleName+"_rawMET_mu", "Raw MET for "+sampleName+" (just dimuon events)", 6000,0,6000);
  rawmet_mu->SetDirectory(rootdir);
  rawmet_mu->Sumw2();

  TH1F *rawmet_2jets_mu = new TH1F(sampleName+"_rawMET_2jets_mu", "Raw MET for events with at least 2 jets in "+sampleName+" (just dimuon events)", 6000,0,6000);
  rawmet_2jets_mu->SetDirectory(rootdir);
  rawmet_2jets_mu->Sumw2();
  

  //Extra Histos
  TH1F *nVert = new TH1F(sampleName+"_nVert", "Number of verticies for "+sampleName, 50,0,50);
  nVert->SetDirectory(rootdir);
  nVert->Sumw2();

  TH1F *dilmass = new TH1F(sampleName+"_dilmass", "Dilepton Mass for "+sampleName, 300,0,150);
  dilmass->SetDirectory(rootdir);
  dilmass->Sumw2();

  TH1F *dilmass_ee = new TH1F(sampleName+"_dilmass_ee", "Dilepton Mass (just dielectron events) for "+sampleName, 300,0,150);
  dilmass_ee->SetDirectory(rootdir);
  dilmass_ee->Sumw2();
  
  TH1F *dilmass_mm = new TH1F(sampleName+"_dilmass_mm", "Dilepton Mass (just dimuon events) for "+sampleName, 300,0,150);
  dilmass_mm->SetDirectory(rootdir);
  dilmass_mm->Sumw2();

  TH1F *dilmass_2jets = new TH1F(sampleName+"_dilmass_2jets", "Dilepton Mass with >=2 jets for "+sampleName, 300,0,150);
  dilmass_2jets->SetDirectory(rootdir);
  dilmass_2jets->Sumw2();

  TH1F *dilmass_2jets_ee = new TH1F(sampleName+"_dilmass_2jets_ee", "Dilepton Mass (just dielectron events) with >=2 jets for "+sampleName, 300,0,150);
  dilmass_2jets_ee->SetDirectory(rootdir);
  dilmass_2jets_ee->Sumw2();
  
  TH1F *dilmass_2jets_mm = new TH1F(sampleName+"_dilmass_2jets_mm", "Dilepton Mass (just dimuon events) with >=2 jets for "+sampleName, 300,0,150);
  dilmass_2jets_mm->SetDirectory(rootdir);
  dilmass_2jets_mm->Sumw2();


  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  int nDuplicates = 0;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile file( currentFile->GetTitle() );
    TTree *tree = (TTree*)file.Get("t");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    phys.Init(tree);
    
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {
      numEvents->Fill(0);
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      phys.GetEntry(event);
      ++nEventsTotal;
    
      // Progress
      ZMET2016::progress( nEventsTotal, nEventsChain );

      //=======================================
      // Analysis Code
      //=======================================
      

      //Set up event weight
      double weight; 

      if( phys.isData() ) {
        weight = 1;
        DorkyEventIdentifier id(phys.run(), phys.evt(), phys.lumi());
        if (is_duplicate(id) ){
          ++nDuplicates;
          continue;
        }
      }

      else{
        weight = phys.evt_scale1fb()*2.058; 
      }

      // Base Cut
      if (! passBaseCut()) continue;

      if (do_MET_filters){
        if (! passMETFilters()) continue;
      }

      // Draw samples with 2 jet cut
      if (phys.njets() >= 2){
        if (phys.met_T1CHS_miniAOD_CORE_pt() > 0)
        {
          t1met_2jets->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
          if (phys.hyp_type() == 0)
          {
            t1met_2jets_el->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
          }
          else
          {
            t1met_2jets_mu->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
          }
        }
        if (phys.met_rawPt() > 0)
        {
          rawmet_2jets->Fill(phys.met_rawPt(), weight);
          if (phys.hyp_type() == 0)
          {
            rawmet_2jets_el->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
          }
          else
          {
            rawmet_2jets_mu->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight); 
          }
        }
      }

      // Draw Raw MET hists
      if(phys.met_rawPt() > 0){
        //Raw MET
        rawmet->Fill(phys.met_rawPt(), weight);
        if (phys.hyp_type() == 0)
        {
          rawmet_el->Fill(phys.met_rawPt(), weight);
        }
        else
        {
          rawmet_mu->Fill(phys.met_rawPt(), weight); 
        }
      }
      
      //Type 1 MET
      if(phys.met_T1CHS_miniAOD_CORE_pt() > 0){
        t1met->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
        if (phys.hyp_type() == 0){
          t1met_el->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
        }
        else
        {
          t1met_mu->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight); 
        }
      }

      // Fill num verticies
      nVert->Fill(phys.nVert(), weight);

      // Fill Dilepton Mass
      dilmass->Fill(phys.dilmass(), weight);

      if (phys.hyp_type() == 1){
        dilmass_mm->Fill(phys.dilmass(), weight);        
      }
      else if (phys.hyp_type() == 0){
        dilmass_ee->Fill(phys.dilmass(), weight);        
      }

      // Fill Dilepton Mass
      if (phys.njets() >= 2){
        dilmass_2jets->Fill(phys.dilmass(), weight);

        if (phys.hyp_type() == 1){
          dilmass_2jets_mm->Fill(phys.dilmass(), weight);        
        }
        else if (phys.hyp_type() == 0){
          dilmass_2jets_ee->Fill(phys.dilmass(), weight);        
        }
      }

    }
    // Clean Up
    delete tree;
    file.Close();
  }
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  //=======================================
  // Write Out Histos
  //=======================================

  output->cd();

  //Type 1 MET
  t1met->Write();
  t1met_2jets->Write();
  t1met_el->Write();
  t1met_2jets_el->Write();
  t1met_mu->Write();
  t1met_2jets_mu->Write();
  
  //RAW MET
  rawmet->Write();
  rawmet_2jets->Write();
  rawmet_el->Write();
  rawmet_2jets_el->Write();
  rawmet_mu->Write();
  rawmet_2jets_mu->Write();
  
  //Extra
  nVert->Write();
  dilmass->Write();
  dilmass_ee->Write();
  dilmass_mm->Write();
  dilmass_2jets->Write();
  dilmass_2jets_ee->Write();
  dilmass_2jets_mm->Write();
  numEvents->Write();

  //close output file
  output->Write();
  output->Close();
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << nDuplicates << " Duplicates" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}
