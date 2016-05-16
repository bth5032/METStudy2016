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

int ScanChain( TChain* chain, TString sampleName, bool isData = 0, bool fast = true, int nEvents = -1, TString savePath="/nfs-7/userdata/bobak/METStudy2016/76Histos/") {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
  
  //=======================================
  // Define Histograms
  //=======================================
  
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  TFile * output = new TFile(savePath+"METStudy_"+sampleName+".root", "create");

  TH1I *numEvents = new TH1I("numEvents_"+sampleName, "Number of events in "+sampleName, 1, 0, 1);
  numEvents->SetDirectory(rootdir);

  //MET Histos
  TH1F *t1met = new TH1F(sampleName+"_type1MET", "Type 1 MET for "+sampleName, 500,0,500);
  t1met->SetDirectory(rootdir);
  t1met->Sumw2();

  TH1F *t1met_2jets = new TH1F(sampleName+"_type1MET_2jets", "Type 1 MET for events with at least 2 jets in "+sampleName, 500,0,500);
  t1met_2jets->SetDirectory(rootdir);
  t1met_2jets->Sumw2();

  TH1F *t1met_el = new TH1F(sampleName+"_type1MET_el", "Type 1 MET for "+sampleName+" (just dielectron events)", 500,0,500);
  t1met_el->SetDirectory(rootdir);
  t1met_el->Sumw2();

  TH1F *t1met_2jets_el = new TH1F(sampleName+"_type1MET_2jets_el", "Type 1 MET for events with at least 2 jets in "+sampleName+" (just dielectron events)", 500,0,500);
  t1met_2jets_el->SetDirectory(rootdir);
  t1met_2jets_el->Sumw2();

  TH1F *t1met_mu = new TH1F(sampleName+"_type1MET_mu", "Type 1 MET for "+sampleName+" (just dimuon events)", 500,0,500);
  t1met_mu->SetDirectory(rootdir);
  t1met_mu->Sumw2();

  TH1F *t1met_2jets_mu = new TH1F(sampleName+"_type1MET_2jets_mu", "Type 1 MET for events with at least 2 jets in "+sampleName+" (just dimuon events)", 500,0,500);
  t1met_2jets_mu->SetDirectory(rootdir);
  t1met_2jets_mu->Sumw2();

  TH1F *rawmet = new TH1F(sampleName+"_rawMET", "Raw MET for "+sampleName, 500,0,500);
  rawmet->SetDirectory(rootdir);
  rawmet->Sumw2();

  TH1F *rawmet_2jets = new TH1F(sampleName+"_rawMET_2jets", "Raw MET for events with at least 2 jets in "+sampleName, 500,0,500);
  rawmet_2jets->SetDirectory(rootdir);
  rawmet_2jets->Sumw2();

  TH1F *rawmet_el = new TH1F(sampleName+"_rawMET_el", "Raw MET for "+sampleName+" (just dielectron events)", 500,0,500);
  rawmet_el->SetDirectory(rootdir);
  rawmet_el->Sumw2();

  TH1F *rawmet_2jets_el = new TH1F(sampleName+"_rawMET_2jets_el", "Raw MET for events with at least 2 jets in "+sampleName+" (just dielectron events)", 500,0,500);
  rawmet_2jets_el->SetDirectory(rootdir);
  rawmet_2jets_el->Sumw2();

  TH1F *rawmet_mu = new TH1F(sampleName+"_rawMET_mu", "Raw MET for "+sampleName+" (just dimuon events)", 500,0,500);
  rawmet_mu->SetDirectory(rootdir);
  rawmet_mu->Sumw2();

  TH1F *rawmet_2jets_mu = new TH1F(sampleName+"_rawMET_2jets_mu", "Raw MET for events with at least 2 jets in "+sampleName+" (just dimuon events)", 500,0,500);
  rawmet_2jets_mu->SetDirectory(rootdir);
  rawmet_2jets_mu->Sumw2();
  
  // Photonic Pts
  TH1F *ph_0013_pt = new TH1F(sampleName+"_photonPT0013", "Photonic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  ph_0013_pt->SetDirectory(rootdir);
  ph_0013_pt->Sumw2();

  TH1F *ph_1624_pt = new TH1F(sampleName+"_photonPT1624", "Photonic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  ph_1624_pt->SetDirectory(rootdir);
  ph_1624_pt->Sumw2();

  TH1F *ph_2430_pt = new TH1F(sampleName+"_photonPT2430", "Photonic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  ph_2430_pt->SetDirectory(rootdir);
  ph_2430_pt->Sumw2();

  // Charged Hadronic Pts
  TH1F *ch_0013_pt = new TH1F(sampleName+"_chargedPT0013", "Charged hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  ch_0013_pt->SetDirectory(rootdir);
  ch_0013_pt->Sumw2();

  TH1F *ch_1624_pt = new TH1F(sampleName+"_chargedPT1624", "Charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  ch_1624_pt->SetDirectory(rootdir);
  ch_1624_pt->Sumw2();

  TH1F *ch_2430_pt = new TH1F(sampleName+"_chargedPT2430", "Charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  ch_2430_pt->SetDirectory(rootdir);
  ch_2430_pt->Sumw2();
  
  // Neutral Hadronic Pts
  TH1F *nu_0013_pt = new TH1F(sampleName+"_neutralPT0013", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  nu_0013_pt->SetDirectory(rootdir);
  nu_0013_pt->Sumw2();

  TH1F *nu_1624_pt = new TH1F(sampleName+"_neutralPT1624", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  nu_1624_pt->SetDirectory(rootdir);
  nu_1624_pt->Sumw2();

  TH1F *nu_2430_pt = new TH1F(sampleName+"_neutralPT2430", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  nu_2430_pt->SetDirectory(rootdir);
  nu_2430_pt->Sumw2();

  TH1F *nu_30in_pt = new TH1F(sampleName+"_neutralPT30in", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| > 3.0", 500,0,500);
  nu_30in_pt->SetDirectory(rootdir);
  nu_30in_pt->Sumw2();


  // Photonic MET-Phi
  TH1F *ph_0013_phi = new TH1F(sampleName+"_photonPHI0013", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 200,-3.15,3.15);
  ph_0013_phi->SetDirectory(rootdir);
  ph_0013_phi->Sumw2();

  TH1F *ph_1624_phi = new TH1F(sampleName+"_photonPHI1624", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 200,-3.15,3.15);
  ph_1624_phi->SetDirectory(rootdir);
  ph_1624_phi->Sumw2();

  TH1F *ph_2430_phi = new TH1F(sampleName+"_photonPHI2430", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 200,-3.15,3.15);
  ph_2430_phi->SetDirectory(rootdir);
  ph_2430_phi->Sumw2();

  // Charged Hadronic MET-Phi
  TH1F *ch_0013_phi = new TH1F(sampleName+"_chargedPHI0013", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 200,-3.15,3.15);
  ch_0013_phi->SetDirectory(rootdir);
  ch_0013_phi->Sumw2();

  TH1F *ch_1624_phi = new TH1F(sampleName+"_chargedPHI1624", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 200,-3.15,3.15);
  ch_1624_phi->SetDirectory(rootdir);
  ch_1624_phi->Sumw2();

  TH1F *ch_2430_phi = new TH1F(sampleName+"_chargedPHI2430", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 200,-3.15,3.15);
  ch_2430_phi->SetDirectory(rootdir);
  ch_2430_phi->Sumw2();

  // Neutral Hadronic MET-Phi
  TH1F *nu_0013_phi = new TH1F(sampleName+"_neutralPHI0013", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 200,-3.15,3.15);
  nu_0013_phi->SetDirectory(rootdir);
  nu_0013_phi->Sumw2();

  TH1F *nu_1624_phi = new TH1F(sampleName+"_neutralPHI1624", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 200,-3.15,3.15);
  nu_1624_phi->SetDirectory(rootdir);
  nu_1624_phi->Sumw2();

  TH1F *nu_2430_phi = new TH1F(sampleName+"_neutralPHI2430", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 200,-3.15,3.15);
  nu_2430_phi->SetDirectory(rootdir);
  nu_2430_phi->Sumw2();

  TH1F *nu_30in_phi = new TH1F(sampleName+"_neutralPHI30in", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| > 3.0", 200,-3.15,3.15);
  nu_30in_phi->SetDirectory(rootdir);
  nu_30in_phi->Sumw2();

  //Extra Histos
  TH1F *nVert = new TH1F(sampleName+"_nVert", "Number of verticies for "+sampleName, 50,0,50);
  nVert->SetDirectory(rootdir);
  nVert->Sumw2();

  TH1F *bumpPhi = new TH1F(sampleName+"_PHIinBump", "Net angle VSPT of events in 50-120GeV bump for "+sampleName, 200,-3.15,3.15);
  bumpPhi->SetDirectory(rootdir);
  bumpPhi->Sumw2();

  TH1F *dilmass = new TH1F(sampleName+"_dilmass", "Dilepton Mass for "+sampleName, 300,0,150);
  dilmass->SetDirectory(rootdir);
  dilmass->Sumw2();

  
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
        weight = phys.evt_scale1fb() * 2.3 * phys.puWeight(); 
      }

      // Base Cut
      if (!(phys.dilmass() < 101 && phys.dilmass() > 81)) continue;

      if (!(phys.nlep() >= 2)) continue;
      if (!(phys.lep_pt().at(0) > 20 && phys.lep_pt().at(1) > 20)) continue;

      if (!(abs(phys.lep_p4().at(0).eta()) < 2.4 && abs(phys.lep_p4().at(1).eta()) < 2.4)) continue;


      if (!(phys.dRll() > 0.1)) continue; 

      if (!(phys.evt_type() == 0)) continue;
      
      if (! ((phys.HLT_DoubleMu() || phys.HLT_DoubleMu_tk() || phys.HLT_DoubleMu_noiso()) && phys.hyp_type() == 1 )){
        if (! ((phys.HLT_DoubleEl_DZ() || phys.HLT_DoubleEl_noiso() ) && phys.hyp_type() == 0) )
        {
          continue; 
        }
      }

      if (! (phys.evt_passgoodrunlist() > 0)) continue;

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

      // Draw other MET hists
      if(phys.met_rawPt() > 0){
        rawmet->Fill(phys.met_rawPt(), weight);
        if (phys.hyp_type() == 0)
        {
          rawmet_el->Fill(phys.met_rawPt(), weight);
        }
        else
        {
          rawmet_mu->Fill(phys.met_rawPt(), weight); 
        }

        t1met->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
        if (phys.hyp_type() == 0)
        {
          t1met_el->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
        }
        else
        {
          t1met_mu->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight); 
        }
      }

      // Draw photon histos
      if (phys.phpfcands_0013_pt()>0){
        ph_0013_pt->Fill(phys.phpfcands_0013_pt(), weight);
        ph_0013_phi->Fill(phys.phpfcands_0013_phi(), weight);
      }
      if (phys.phpfcands_1624_pt()>0){
        ph_1624_pt->Fill(phys.phpfcands_1624_pt(), weight);
        ph_1624_phi->Fill(phys.phpfcands_1624_phi(), weight);
      }
      if (phys.phpfcands_2430_pt()>0){
        ph_2430_pt->Fill(phys.phpfcands_2430_pt(), weight);
        ph_2430_phi->Fill(phys.phpfcands_2430_phi(), weight);
      }

      // Draw charged hadron histos
      if (phys.chpfcands_0013_pt()>0){
        ch_0013_pt->Fill(phys.chpfcands_0013_pt(), weight);
        ch_0013_phi->Fill(phys.chpfcands_0013_phi(), weight);
      }
      if (phys.chpfcands_1624_pt()>0){
        ch_1624_pt->Fill(phys.chpfcands_1624_pt(), weight);
        ch_1624_phi->Fill(phys.chpfcands_1624_phi(), weight);
      }
      if (phys.chpfcands_2430_pt()>0){
        ch_2430_pt->Fill(phys.chpfcands_2430_pt(), weight);
        ch_2430_phi->Fill(phys.chpfcands_2430_phi(), weight);
      }

      // Draw neutral hadron histos
      if (phys.nupfcands_0013_pt()>0){
        nu_0013_pt->Fill(phys.nupfcands_0013_pt(), weight);
        nu_0013_phi->Fill(phys.nupfcands_0013_phi(), weight);
      }
      if (phys.nupfcands_1624_pt()>0){
        nu_1624_pt->Fill(phys.nupfcands_1624_pt(), weight);
        nu_1624_phi->Fill(phys.nupfcands_1624_phi(), weight);
      }
      if (phys.nupfcands_2430_pt()>0){
        nu_2430_pt->Fill(phys.nupfcands_2430_pt(), weight);
        nu_2430_phi->Fill(phys.nupfcands_2430_phi(), weight);
      }
      if (phys.nupfcands_30in_pt()>0){
        nu_30in_pt->Fill(phys.nupfcands_30in_pt(), weight);
        nu_30in_phi->Fill(phys.nupfcands_30in_phi(), weight);
      }

      // Draw bump-phi histo
      if (phys.met_T1CHS_miniAOD_CORE_pt() > 50 && phys.met_T1CHS_miniAOD_CORE_pt() < 120){

        bumpPhi->Fill(met_T1CHS_miniAOD_CORE_phi(), weight);
      }

      // Fill num verticies
      nVert->Fill(phys.nVert(), weight);

      // Fill Dilepton Mass
      dilmass->Fill(phys.dilmass(), weight);


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

  t1met->Write();
  t1met_2jets->Write();
  t1met_el->Write();
  t1met_2jets_el->Write();
  t1met_mu->Write();
  t1met_2jets_mu->Write();
  rawmet->Write();
  rawmet_2jets->Write();
  rawmet_el->Write();
  rawmet_2jets_el->Write();
  rawmet_mu->Write();
  rawmet_2jets_mu->Write();
  ph_0013_pt->Write();
  ph_1624_pt->Write();
  ph_2430_pt->Write();
  ch_0013_pt->Write();
  ch_1624_pt->Write();
  ch_2430_pt->Write();
  nu_0013_pt->Write();
  nu_1624_pt->Write();
  nu_2430_pt->Write();
  nu_30in_pt->Write();
  ph_0013_phi->Write();
  ph_1624_phi->Write();
  ph_2430_phi->Write();
  ch_0013_phi->Write();
  ch_1624_phi->Write();
  ch_2430_phi->Write();
  nu_0013_phi->Write();
  nu_1624_phi->Write();
  nu_2430_phi->Write();
  nu_30in_phi->Write();
  nVert->Write();
  bumpPhi->Write();
  dilmass->Write();
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
