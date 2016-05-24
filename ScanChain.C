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

bool passMETFilters()
{

  if( phys.isData()                   ){
  if (phys.nVert() == 0               ) return false;

      if (!phys.Flag_HBHENoiseFilter                   ()      ) return false;
      if (!phys.Flag_HBHEIsoNoiseFilter                ()      ) return false;
      if (!phys.Flag_CSCTightHaloFilter            ()      ) return false;
      if (!phys.Flag_EcalDeadCellTriggerPrimitiveFilter()      ) return false;
      if (!phys.Flag_goodVertices                      ()      ) return false;
      if (!phys.Flag_eeBadScFilter                     ()      ) return false;

  }
  return true;
}


int ScanChain( TChain* chain, TString sampleName, TString savePath, bool dovtxreweighting = false, bool do_stdvtx_reweighting = false, bool do_MET_filters = false, bool fast = true, int nEvents = -1) {

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
  

  //=================================
  // PFClass-MET
  //=================================

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

  TH1F *ph_30in_pt = new TH1F(sampleName+"_photonPT30in", "Photonic vector sum of pt for "+sampleName+" with |#eta| > 3", 500,0,500);
  ph_30in_pt->SetDirectory(rootdir);
  ph_30in_pt->Sumw2();

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


  //=================================
  // MET-PHI
  //=================================

  // Overall MET-Phi
  TH1F *net_phi = new TH1F(sampleName+"_netPHI", "Net angle of vector sum of pt for "+sampleName, 200,-3.15,3.15);
  net_phi->SetDirectory(rootdir);
  net_phi->Sumw2();

  TH1F *net_phi_2jets = new TH1F(sampleName+"_netPHI_2jets", "Net angle of vector sum of pt for "+sampleName, 200,-3.15,3.15);
  net_phi_2jets->SetDirectory(rootdir);
  net_phi_2jets->Sumw2();

  TH1F *net_phi_el = new TH1F(sampleName+"_netPHI_el", "Net angle of vector sum of pt for "+sampleName, 200,-3.15,3.15);
  net_phi_el->SetDirectory(rootdir);
  net_phi_el->Sumw2();

  TH1F *net_phi_2jets_el = new TH1F(sampleName+"_netPHI_2jets_el", "Net angle of vector sum of pt for "+sampleName, 200,-3.15,3.15);
  net_phi_2jets_el->SetDirectory(rootdir);
  net_phi_2jets_el->Sumw2();

  TH1F *net_phi_mu = new TH1F(sampleName+"_netPHI_mu", "Net angle of vector sum of pt for "+sampleName, 200,-3.15,3.15);
  net_phi_mu->SetDirectory(rootdir);
  net_phi_mu->Sumw2();

  TH1F *net_phi_2jets_mu = new TH1F(sampleName+"_netPHI_2jets_mu", "Net angle of vector sum of pt for "+sampleName, 200,-3.15,3.15);
  net_phi_2jets_mu->SetDirectory(rootdir);
  net_phi_2jets_mu->Sumw2();

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

  TH1F *ph_30in_phi = new TH1F(sampleName+"_photonPHI30in", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| > 3.0", 200,-3.15,3.15);
  ph_30in_phi->SetDirectory(rootdir);
  ph_30in_phi->Sumw2();

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

  //=================================
  // MET-PHI PT(20)
  //=================================

  // Photonic MET-Phi
  TH1F *ph_0013_phi_pcut20 = new TH1F(sampleName+"_photonPHI0013_PCUT20", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| < 1.3 where |#Sum_{ph} #vec{p}_t| > 20", 200,-3.15,3.15);
  ph_0013_phi_pcut20->SetDirectory(rootdir);
  ph_0013_phi_pcut20->Sumw2();

  TH1F *ph_1624_phi_pcut20 = new TH1F(sampleName+"_photonPHI1624_PCUT20", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4) where |#Sum_{ph} #vec{p}_t| > 20", 200,-3.15,3.15);
  ph_1624_phi_pcut20->SetDirectory(rootdir);
  ph_1624_phi_pcut20->Sumw2();

  TH1F *ph_2430_phi_pcut20 = new TH1F(sampleName+"_photonPHI2430_PCUT20", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0) where |#Sum_{ph} #vec{p}_t| > 20", 200,-3.15,3.15);
  ph_2430_phi_pcut20->SetDirectory(rootdir);
  ph_2430_phi_pcut20->Sumw2();

  TH1F *ph_30in_phi_pcut20 = new TH1F(sampleName+"_photonPHI30in_PCUT20", "Net angle of photonic vector sum of pt for "+sampleName+" with |#eta| > 3.0 where |#Sum_{ph} #vec{p}_t| > 20", 200,-3.15,3.15);
  ph_30in_phi_pcut20->SetDirectory(rootdir);
  ph_30in_phi_pcut20->Sumw2();

  // Charged Hadronic MET-Phi
  TH1F *ch_0013_phi_pcut20 = new TH1F(sampleName+"_chargedPHI0013_PCUT20", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3 where |#Sum_{ch} #vec{p}_t| > 20", 200,-3.15,3.15);
  ch_0013_phi_pcut20->SetDirectory(rootdir);
  ch_0013_phi_pcut20->Sumw2();

  TH1F *ch_1624_phi_pcut20 = new TH1F(sampleName+"_chargedPHI1624_PCUT20", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4) where |#Sum_{ch} #vec{p}_t| > 20", 200,-3.15,3.15);
  ch_1624_phi_pcut20->SetDirectory(rootdir);
  ch_1624_phi_pcut20->Sumw2();

  TH1F *ch_2430_phi_pcut20 = new TH1F(sampleName+"_chargedPHI2430_PCUT20", "Net angle of charged hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0) where |#Sum_{ch} #vec{p}_t| > 20", 200,-3.15,3.15);
  ch_2430_phi_pcut20->SetDirectory(rootdir);
  ch_2430_phi_pcut20->Sumw2();

  // Neutral Hadronic MET-Phi
  TH1F *nu_0013_phi_pcut20 = new TH1F(sampleName+"_neutralPHI0013_PCUT20", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| < 1.3 where |#Sum_{nu} #vec{p}_t| > 20", 200,-3.15,3.15);
  nu_0013_phi_pcut20->SetDirectory(rootdir);
  nu_0013_phi_pcut20->Sumw2();

  TH1F *nu_1624_phi_pcut20 = new TH1F(sampleName+"_neutralPHI1624_PCUT20", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4) where |#Sum_{nu} #vec{p}_t| > 20", 200,-3.15,3.15);
  nu_1624_phi_pcut20->SetDirectory(rootdir);
  nu_1624_phi_pcut20->Sumw2();

  TH1F *nu_2430_phi_pcut20 = new TH1F(sampleName+"_neutralPHI2430_PCUT20", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0) where |#Sum_{nu} #vec{p}_t| > 20", 200,-3.15,3.15);
  nu_2430_phi_pcut20->SetDirectory(rootdir);
  nu_2430_phi_pcut20->Sumw2();

  TH1F *nu_30in_phi_pcut20 = new TH1F(sampleName+"_neutralPHI30in_PCUT20", "Net angle of neutral hadronic vector sum of pt for "+sampleName+" with |#eta| > 3.0 where |#Sum_{nu} #vec{p}_t| > 20", 200,-3.15,3.15);
  nu_30in_phi_pcut20->SetDirectory(rootdir);
  nu_30in_phi_pcut20->Sumw2();

  //=================================
  // SUM ET
  //=================================

  // Photonic SET
  TH1F *ph_0013_set = new TH1F(sampleName+"_photonSET0013", "Photonic scalar sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  ph_0013_set->SetDirectory(rootdir);
  ph_0013_set->Sumw2();

  TH1F *ph_1624_set = new TH1F(sampleName+"_photonSET1624", "Photonic scalar sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  ph_1624_set->SetDirectory(rootdir);
  ph_1624_set->Sumw2();

  TH1F *ph_2430_set = new TH1F(sampleName+"_photonSET2430", "Photonic scalar sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  ph_2430_set->SetDirectory(rootdir);
  ph_2430_set->Sumw2();

  TH1F *ph_30in_set = new TH1F(sampleName+"_photonSET30in", "Photonic scalar sum of pt for "+sampleName+" with |#eta| > 3.0", 500,0,500);
  ph_30in_set->SetDirectory(rootdir);
  ph_30in_set->Sumw2();

  // Charged Hadronic SET
  TH1F *ch_0013_set = new TH1F(sampleName+"_chargedSET0013", "Charged hadronic scalar sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  ch_0013_set->SetDirectory(rootdir);
  ch_0013_set->Sumw2();

  TH1F *ch_1624_set = new TH1F(sampleName+"_chargedSET1624", "Charged hadronic scalar sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  ch_1624_set->SetDirectory(rootdir);
  ch_1624_set->Sumw2();

  TH1F *ch_2430_set = new TH1F(sampleName+"_chargedSET2430", "Charged hadronic scalar sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  ch_2430_set->SetDirectory(rootdir);
  ch_2430_set->Sumw2();

  // Neutral Hadronic SET
  TH1F *nu_0013_set = new TH1F(sampleName+"_neutralSET0013", "Neutral hadronic scalar sum of pt for "+sampleName+" with |#eta| < 1.3", 500,0,500);
  nu_0013_set->SetDirectory(rootdir);
  nu_0013_set->Sumw2();

  TH1F *nu_1624_set = new TH1F(sampleName+"_neutralSET1624", "Neutral hadronic scalar sum of pt for "+sampleName+" with |#eta| #in (1.6,2.4)", 500,0,500);
  nu_1624_set->SetDirectory(rootdir);
  nu_1624_set->Sumw2();

  TH1F *nu_2430_set = new TH1F(sampleName+"_neutralSET2430", "Neutral hadronic scalar sum of pt for "+sampleName+" with |#eta| #in (2.4,3.0)", 500,0,500);
  nu_2430_set->SetDirectory(rootdir);
  nu_2430_set->Sumw2();

  TH1F *nu_30in_set = new TH1F(sampleName+"_neutralSET30in", "Neutral hadronic scalar sum of pt for "+sampleName+" with |#eta| > 3.0", 500,0,500);
  nu_30in_set->SetDirectory(rootdir);
  nu_30in_set->Sumw2();

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

  TH2F *metSumET2D = new TH2F(sampleName+"_METSumET", "MET vs SumET for "+sampleName, 1000, 0, 1000, 10000, 0, 10000);
  metSumET2D->SetDirectory(rootdir);
  metSumET2D->Sumw2();

  //Set up manual vertex reweighting.
  
  TH1F *h_vtxweight;
  TFile *f_vtx;
  
  if( dovtxreweighting ){
    f_vtx = TFile::Open(savePath+"nvtx_ratio.root","READ");
    h_vtxweight = (TH1F*)f_vtx->Get("h_vtx_ratio")->Clone("h_vtxweight");
    h_vtxweight->SetDirectory(rootdir);
    f_vtx->Close();
  }


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
        //weight = phys.evt_scale1fb() * 2.3 * phys.puWeight(); 
        weight = phys.evt_scale1fb() * 2.3; 
      }

      if( (! phys.isData()) && dovtxreweighting ){
        weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(phys.nVert()));   
      }

      if( (! phys.isData()) && do_stdvtx_reweighting){
        weight *= phys.puWeight();   
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

      if (do_MET_filters){
        if (! passMETFilters()) continue;
      }


/*      if (phys.met_T1CHS_miniAOD_CORE_pt() > 400){
        cout<<"run: "<<phys.run()<<endl;
        cout<<"lumi: "<<phys.lumi()<<endl;
        cout<<"event: "<<phys.evt()<<endl;
      }*/


      // Draw samples with 2 jet cut
      if (phys.njets() >= 2){
        if (phys.met_T1CHS_miniAOD_CORE_pt() > 0)
        {
          t1met_2jets->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
          if (phys.met_T1CHS_miniAOD_CORE_pt() > 20)
          {
            net_phi_2jets->Fill(phys.met_T1CHS_miniAOD_CORE_phi(), weight);
          }
          if (phys.hyp_type() == 0)
          {
            t1met_2jets_el->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
            if (phys.met_T1CHS_miniAOD_CORE_pt() > 20)
            {
              net_phi_2jets_el->Fill(phys.met_T1CHS_miniAOD_CORE_phi(), weight);
            }
          }
          else
          {
            t1met_2jets_mu->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
            if (phys.met_T1CHS_miniAOD_CORE_pt() > 20)
            {
              net_phi_2jets_mu->Fill(phys.met_T1CHS_miniAOD_CORE_phi(), weight);
            } 
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
        if (phys.met_T1CHS_miniAOD_CORE_pt() > 20){
          net_phi->Fill(phys.met_T1CHS_miniAOD_CORE_phi(), weight);
        }
        if (phys.hyp_type() == 0){
          t1met_el->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight);
          if (phys.met_T1CHS_miniAOD_CORE_pt() > 20){
            net_phi_el->Fill(phys.met_T1CHS_miniAOD_CORE_phi(), weight);
          }
        }
        else
        {
          t1met_mu->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), weight); 
          if (phys.met_T1CHS_miniAOD_CORE_pt() > 20)
          {
            net_phi_mu->Fill(phys.met_T1CHS_miniAOD_CORE_phi(), weight);
          }
        }
      }

      // Draw photon histos
      if (phys.phpfcands_0013_pt()>0){
        ph_0013_pt->Fill(phys.phpfcands_0013_pt(), weight);
        ph_0013_phi->Fill(phys.phpfcands_0013_phi(), weight);
        ph_0013_set->Fill(phys.phpfcands_0013_sumet(), weight);
        if (phys.phpfcands_0013_pt()>20) {
          ph_0013_phi_pcut20->Fill(phys.phpfcands_0013_phi(), weight);
        }
      }
      if (phys.phpfcands_1624_pt()>0){
        ph_1624_pt->Fill(phys.phpfcands_1624_pt(), weight);
        ph_1624_phi->Fill(phys.phpfcands_1624_phi(), weight);
        ph_1624_set->Fill(phys.phpfcands_1624_sumet(), weight);
        if (phys.phpfcands_1624_pt()>20) {
          ph_1624_phi_pcut20->Fill(phys.phpfcands_1624_phi(), weight);
        }
      }
      if (phys.phpfcands_2430_pt()>0){
        ph_2430_pt->Fill(phys.phpfcands_2430_pt(), weight);
        ph_2430_phi->Fill(phys.phpfcands_2430_phi(), weight);
        ph_2430_set->Fill(phys.phpfcands_2430_sumet(), weight);
        if (phys.phpfcands_2430_pt()>20) {
          ph_2430_phi_pcut20->Fill(phys.phpfcands_2430_phi(), weight);
        }
      }
      if (phys.phpfcands_30in_pt()>0){
        ph_30in_pt->Fill(phys.phpfcands_30in_pt(), weight);
        ph_30in_phi->Fill(phys.phpfcands_30in_phi(), weight);
        ph_30in_set->Fill(phys.phpfcands_30in_sumet(), weight);
        if (phys.phpfcands_30in_pt()>20) {
          ph_30in_phi_pcut20->Fill(phys.phpfcands_30in_phi(), weight);
        }
      }

      // Draw charged hadron histos
      if (phys.chpfcands_0013_pt()>0){
        ch_0013_pt->Fill(phys.chpfcands_0013_pt(), weight);
        ch_0013_phi->Fill(phys.chpfcands_0013_phi(), weight);
        ch_0013_set->Fill(phys.chpfcands_0013_sumet(), weight);
        if (phys.chpfcands_0013_pt()>20) {
          ch_0013_phi_pcut20->Fill(phys.chpfcands_0013_phi(), weight);
        }
      }
      if (phys.chpfcands_1624_pt()>0){
        ch_1624_pt->Fill(phys.chpfcands_1624_pt(), weight);
        ch_1624_phi->Fill(phys.chpfcands_1624_phi(), weight);
        ch_1624_set->Fill(phys.chpfcands_1624_sumet(), weight);
        if (phys.chpfcands_1624_pt()>20) {
          ch_1624_phi_pcut20->Fill(phys.chpfcands_1624_phi(), weight);
        }
      }
      if (phys.chpfcands_2430_pt()>0){
        ch_2430_pt->Fill(phys.chpfcands_2430_pt(), weight);
        ch_2430_phi->Fill(phys.chpfcands_2430_phi(), weight);
        ch_2430_set->Fill(phys.chpfcands_2430_sumet(), weight);
        if (phys.chpfcands_2430_pt()>20) {
          ch_2430_phi_pcut20->Fill(phys.chpfcands_2430_phi(), weight);
        }
      }

      // Draw neutral hadron histos
      if (phys.nupfcands_0013_pt()>0){
        nu_0013_pt->Fill(phys.nupfcands_0013_pt(), weight);
        nu_0013_phi->Fill(phys.nupfcands_0013_phi(), weight);
        nu_0013_set->Fill(phys.nupfcands_0013_sumet(), weight);
        if (phys.nupfcands_0013_pt()>20) {
          nu_0013_phi_pcut20->Fill(phys.nupfcands_0013_phi(), weight);
        }
      }
      if (phys.nupfcands_1624_pt()>0){
        nu_1624_pt->Fill(phys.nupfcands_1624_pt(), weight);
        nu_1624_phi->Fill(phys.nupfcands_1624_phi(), weight);
        nu_1624_set->Fill(phys.nupfcands_1624_sumet(), weight);
        if (phys.nupfcands_1624_pt()>20) {
          nu_1624_phi_pcut20->Fill(phys.nupfcands_1624_phi(), weight);
        }
      }
      if (phys.nupfcands_2430_pt()>0){
        nu_2430_pt->Fill(phys.nupfcands_2430_pt(), weight);
        nu_2430_phi->Fill(phys.nupfcands_2430_phi(), weight);
        nu_2430_set->Fill(phys.nupfcands_2430_sumet(), weight);if (phys.nupfcands_2430_pt()>20) {
          nu_2430_phi_pcut20->Fill(phys.nupfcands_2430_phi(), weight);
        }
      }
      if (phys.nupfcands_30in_pt()>0){
        nu_30in_pt->Fill(phys.nupfcands_30in_pt(), weight);
        nu_30in_phi->Fill(phys.nupfcands_30in_phi(), weight);
        nu_30in_set->Fill(phys.nupfcands_30in_sumet(), weight);
        if (phys.nupfcands_30in_pt()>20) {
          nu_30in_phi_pcut20->Fill(phys.nupfcands_30in_phi(), weight);
        }
      }

      // Draw bump-phi histo
      if (phys.met_T1CHS_miniAOD_CORE_pt() > 50 && phys.met_T1CHS_miniAOD_CORE_pt() < 120){

        bumpPhi->Fill(met_T1CHS_miniAOD_CORE_phi(), weight);
      }

      // Fill num verticies
      nVert->Fill(phys.nVert(), weight);

      // Fill Dilepton Mass
      dilmass->Fill(phys.dilmass(), weight);

      //met vs. sumet plot
      metSumET2D->Fill(phys.met_T1CHS_miniAOD_CORE_pt(), phys.sumet_raw(), weight);


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

  //NET MET-PHI
  net_phi->Write();
  net_phi_2jets->Write();
  net_phi_el->Write();
  net_phi_2jets_el->Write();
  net_phi_mu->Write();
  net_phi_2jets_mu->Write();
  
  //Photon
  ph_0013_pt->Write();
  ph_1624_pt->Write();
  ph_2430_pt->Write();
  ph_30in_pt->Write();
  ph_0013_phi->Write();
  ph_1624_phi->Write();
  ph_2430_phi->Write();
  ph_30in_phi->Write();

  ph_0013_phi_pcut20->Write();
  ph_1624_phi_pcut20->Write();
  ph_2430_phi_pcut20->Write();
  ph_30in_phi_pcut20->Write();
  
  ph_0013_set->Write();
  ph_1624_set->Write();
  ph_2430_set->Write();
  ph_30in_set->Write();
  
  //Charged
  ch_0013_pt->Write();
  ch_1624_pt->Write();
  ch_2430_pt->Write();
  ch_0013_phi->Write();
  ch_1624_phi->Write();
  ch_2430_phi->Write();

  ch_0013_phi_pcut20->Write();
  ch_1624_phi_pcut20->Write();
  ch_2430_phi_pcut20->Write();
  
  ch_0013_set->Write();
  ch_1624_set->Write();
  ch_2430_set->Write();
  
  //Neutral
  nu_0013_pt->Write();
  nu_1624_pt->Write();
  nu_2430_pt->Write();
  nu_30in_pt->Write();
  nu_0013_phi->Write();
  nu_1624_phi->Write();
  nu_2430_phi->Write();
  nu_30in_phi->Write();

  nu_0013_phi_pcut20->Write();
  nu_1624_phi_pcut20->Write();
  nu_2430_phi_pcut20->Write();
  nu_30in_phi_pcut20->Write();

  nu_0013_set->Write();
  nu_1624_set->Write();
  nu_2430_set->Write();
  nu_30in_set->Write();
  
  //Extra
  nVert->Write();
  bumpPhi->Write();
  dilmass->Write();
  numEvents->Write();
  metSumET2D->Write();

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
