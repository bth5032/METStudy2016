// Usage:
// > root -b doAll.C

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

using namespace std;
using namespace zmet;

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1, TString sampleName) {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
  
  //=======================================
  // Define Histograms
  //=======================================
  
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  
  //MET Histos
  TH1F *t1met = new TH1F(sample_name+"_type1MET", "Type 1 MET for "+sampleName, 500,0,500);
  tlmet->SetDirectory(rootdir);
  tlmet->Sumw2();

  TH1F *t1met_2jets = new TH1F(sample_name+"_type1MET_2jets", "Type 1 MET for events with at least 2 jets in "+sampleName, 500,0,500);
  tlmet_2jets->SetDirectory(rootdir);
  tlmet_2jets->Sumw2();

  TH1F *t1met_el = new TH1F(sample_name+"_type1MET", "Type 1 MET for "+sampleName+" (just dielectron events)", 500,0,500);
  tlmet_el->SetDirectory(rootdir);
  tlmet_el->Sumw2();

  TH1F *t1met_2jets_el = new TH1F(sample_name+"_type1MET_2jets", "Type 1 MET for events with at least 2 jets in "+sampleName+" (just dielectron events)", 500,0,500);
  tlmet_2jets_el->SetDirectory(rootdir);
  tlmet_2jets_el->Sumw2();

  TH1F *t1met_mu = new TH1F(sample_name+"_type1MET", "Type 1 MET for "+sampleName+" (just dimuon events)", 500,0,500);
  tlmet_mu->SetDirectory(rootdir);
  tlmet_mu->Sumw2();

  TH1F *t1met_2jets_mu = new TH1F(sample_name+"_type1MET_2jets", "Type 1 MET for events with at least 2 jets in "+sampleName+" (just dimuon events)", 500,0,500);
  tlmet_2jets_mu->SetDirectory(rootdir);
  tlmet_2jets_mu->Sumw2();

  TH1F *rawmet = new TH1F(sample_name+"_type1MET", "Raw MET for "+sampleName, 500,0,500);
  rawmet->SetDirectory(rootdir);
  rawmet->Sumw2();

  TH1F *rawmet_2jets = new TH1F(sample_name+"_type1MET_2jets", "Raw MET for events with at least 2 jets in "+sampleName, 500,0,500);
  rawmet_2jets->SetDirectory(rootdir);
  rawmet_2jets->Sumw2();

  TH1F *rawmet_el = new TH1F(sample_name+"_type1MET", "Raw MET for "+sampleName+" (just dielectron events)", 500,0,500);
  rawmet_el->SetDirectory(rootdir);
  rawmet_el->Sumw2();

  TH1F *rawmet_2jets_el = new TH1F(sample_name+"_type1MET_2jets", "Raw MET for events with at least 2 jets in "+sampleName+" (just dielectron events)", 500,0,500);
  rawmet_2jets_el->SetDirectory(rootdir);
  rawmet_2jets_el->Sumw2();

  TH1F *rawmet_mu = new TH1F(sample_name+"_type1MET", "Raw MET for "+sampleName+" (just dimuon events)", 500,0,500);
  rawmet_mu->SetDirectory(rootdir);
  rawmet_mu->Sumw2();

  TH1F *rawmet_2jets_mu = new TH1F(sample_name+"_type1MET_2jets", "Raw MET for events with at least 2 jets in "+sampleName+" (just dimuon events)", 500,0,500);
  rawmet_2jets_mu->SetDirectory(rootdir);
  rawmet_2jets_mu->Sumw2();
  
  // Photonic Pts
  TH1F *ph_0013_pt = new TH1F(sample_name+"_photonPT0013", "Photonic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  ph_0013_pt->SetDirectory(rootdir);
  ph_0013_pt->Sumw2();

  TH1F *ph_1624_pt = new TH1F(sample_name+"_photonPT1624", "Photonic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  ph_1624_pt->SetDirectory(rootdir);
  ph_1624_pt->Sumw2();

  TH1F *ph_2430_pt = new TH1F(sample_name+"_photonPT2430", "Photonic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  ph_2430_pt->SetDirectory(rootdir);
  ph_2430_pt->Sumw2();

  // Charged Hadronic Pts
  TH1F *ch_0013_pt = new TH1F(sample_name+"_chargedPT0013", "Charged hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  ch_0013_pt->SetDirectory(rootdir);
  ch_0013_pt->Sumw2();

  TH1F *ch_1624_pt = new TH1F(sample_name+"_chargedPT1624", "Charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  ch_1624_pt->SetDirectory(rootdir);
  ch_1624_pt->Sumw2();

  TH1F *ch_2430_pt = new TH1F(sample_name+"_chargedPT2430", "Charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  ch_2430_pt->SetDirectory(rootdir);
  ch_2430_pt->Sumw2();
  
  // Neutral Hadronic Pts
  TH1F *nu_0013_pt = new TH1F(sample_name+"_neutralPT0013", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  nu_0013_pt->SetDirectory(rootdir);
  nu_0013_pt->Sumw2();

  TH1F *nu_1624_pt = new TH1F(sample_name+"_neutralPT1624", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  nu_1624_pt->SetDirectory(rootdir);
  nu_1624_pt->Sumw2();

  TH1F *nu_2430_pt = new TH1F(sample_name+"_neutralPT2430", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  nu_2430_pt->SetDirectory(rootdir);
  nu_2430_pt->Sumw2();

  TH1F *nu_30in_pt = new TH1F(sample_name+"_neutralPT2430", "Neutral hadronic vector sum of pt for "+sampleName+" with |#eta| > 3.0", 500,0,500);
  nu_30in_pt->SetDirectory(rootdir);
  nu_30in_pt->Sumw2();


  // Photonic MET-Phi
  TH1F *ph_0013_phi = new TH1F(sample_name+"_photonPHI0013", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 200,-3.15,3.15);
  ph_0013_phi->SetDirectory(rootdir);
  ph_0013_phi->Sumw2();

  TH1F *ph_1624_phi = new TH1F(sample_name+"_photonPHI1624", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 200,-3.15,3.15);
  ph_1624_phi->SetDirectory(rootdir);
  ph_1624_phi->Sumw2();

  TH1F *ph_2430_phi = new TH1F(sample_name+"_photonPHI2430", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 200,-3.15,3.15);
  ph_2430_phi->SetDirectory(rootdir);
  ph_2430_phi->Sumw2();

  // Charged Hadronic MET-Phi
  TH1F *ch_0013_phi = new TH1F(sample_name+"_chargedPHI0013", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 200,-3.15,3.15);
  ch_0013_phi->SetDirectory(rootdir);
  ch_0013_phi->Sumw2();

  TH1F *ch_1624_phi = new TH1F(sample_name+"_chargedPHI1624", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 200,-3.15,3.15);
  ch_1624_phi->SetDirectory(rootdir);
  ch_1624_phi->Sumw2();

  TH1F *ch_2430_phi = new TH1F(sample_name+"_chargedPHI2430", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 200,-3.15,3.15);
  ch_2430_phi->SetDirectory(rootdir);
  ch_2430_phi->Sumw2();

  // Neutral Hadronic MET-Phi
  TH1F *nu_0013_phi = new TH1F(sample_name+"_neutralPHI0013", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3", 200,-3.15,3.15);
  nu_0013_phi->SetDirectory(rootdir);
  nu_0013_phi

  TH1F *nu_1624_phi = new TH1F(sample_name+"_neutralPHI1624", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 200,-3.15,3.15);
  nu_1624_phi->SetDirectory(rootdir);
  nu_1624_phi->Sumw2();

  TH1F *nu_2430_phi = new TH1F(sample_name+"_neutralPHI2430", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 200,-3.15,3.15);
  nu_2430_phi->SetDirectory(rootdir);
  nu_2430_phi->Sumw2();

  TH1F *nu_30in_phi = new TH1F(sample_name+"_neutralPHI2430", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| > 3.0", 200,-3.15,3.15);
  nu_30in_phi->SetDirectory(rootdir);
  nu_30in_phi->Sumw2();

  //Extra Histos
  TH1F *nVert = new TH1F(sample_name+"_nVert", "Number of verticies for "+sampleName, 50,0,50);
  nVert->SetDirectory(rootdir);
  nVert->Sumw2();

  TH1F *bumpPhi = new TH1F(sample_name+"_PHIinBump", "Net angle VSPT of events in 50-120GeV bump for "+sampleName, 140,50,120);
  bumpPhi->SetDirectory(rootdir);
  bumpPhi->Sumw2();

  
  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

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
    
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      phys.GetEntry(event);
      ++nEventsTotal;
    
      // Progress
      ZMET2016::progress( nEventsTotal, nEventsChain );

      // Analysis Code
      phys.dRll() > 0.1
      phys.dilmass() > 81

    }
  
    // Clean Up
    delete tree;
    file.Close();
  }
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  // Example Histograms
  samplehisto->Draw();
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}
