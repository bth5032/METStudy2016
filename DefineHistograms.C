// Bobak Hashemi
// This file doesn't actually do anything right now.  
// It is just where I am storing some info for which histos to draw.

#include "TString.h"

//TCut base_cut = "dilmass < 101 && dilmass > 81 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 2.4 && abs(lep_p4[1].eta()) < 2.4 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0";

class PlotList {
    
    struct plotnode;
    struct plotnode {
        TString name, title, xlabel, ylabel;
        double xmin, xmax, bin_size;
        struct plotnode *next, *prev;
    };    

    private:
        plotnode *head, *current, *tail, *null;
    
    public:
        PlotList(TString name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size){
            head = new plotnode();
            head->name = name;
            head->title = title;
            head->xlabel = xlabel;
            head->ylabel = ylabel;
            head->xmin = xmin;
            head->xmax = xmax;
            head->bin_size = bin_size;
            head->prev=NULL;
            head->next=NULL;

            current=head;
            tail=head;

            null = new plotnode();
            null->name = "NULL";
            null->title = "NULL";
            null->xlabel = "NULL";
            null->ylabel = "NULL";
            null->xmin = 0;
            null->xmax = 0;
            null->bin_size = 0;
        }

        void add(TString name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size){
            plotnode* next = new plotnode();
            next->name = name;
            next->title = title;
            next->xlabel = xlabel;
            next->ylabel = ylabel;
            next->xmin = xmin;
            next->xmax = xmax;
            next->bin_size = bin_size;

            next->next=NULL;
            next->prev=tail;
            tail->next=next;
            tail=next;
        }

        //set node with plotname, returns 1 if found, 0 otherwise.
        bool setPlot(TString plotname){
            current=head;
            
            do
            {
                if (current->name == plotname)
                {
                    return true;
                }
                current=current->next;
            }while (current != tail);
            
            if (!current->name == plotname){
                return true;
            }
            else{
              current = null; //choose null node.
              return false;
            }
        }

        TString name(){
            return current->name;
        }
        TString title(){
            return current->title;
        }
        TString xlabel(){
            return current->xlabel;
        }
        TString ylabel(){
            return current->ylabel;
        }
        double xmin(){
            return current->xmin;
        }
        double xmax(){
            return current->xmax;
        }
        double binSize(){
            return current->bin_size;
        }

};

PlotList* getPlotList(){
  
  //========================
  // MET plots
  //========================
  
  //-------
  //TYPE1
  //-------
  PlotList* all_plots = new PlotList("type1MET", "Type 1 MET for All Events in Study", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("type1MET_2Jets", "Type 1 MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  
  //electron/muon
  all_plots->add("type1MET_el", "Type 1 MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("type1MET_mu", "Type 1 MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //electron/muon with jets
  all_plots->add("type1MET_2jets_el", "Type 1 MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("type1MET_2jets_mu", "Type 1 MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // RAW
  //-------

  all_plots->add("rawMET", "Raw MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("rawMET_2Jets", "Raw MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  
  //electron/muon
  all_plots->add("rawMET_el", "Raw MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("rawMET_mu", "Raw MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //electron/muon with jets
  all_plots->add("rawMET_2jets_el", "Raw MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("rawMET_2jets_mu", "Raw MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);


  //========================
  // PT plots
  //======================== 
  //-------
  // PHOTON
  //-------

  all_plots->add("photonPT0013", "Photonic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("photonPT1624", "Photonic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("photonPT2430", "Photonic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // CHARGED HADRONS
  //-------
  all_plots->add("chargedPT0013", "Charged hadronic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedPT1624", "Charged hadronic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedPT2430", "Charged hadronic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // NEUTRAL HADRONS
  //-------
  all_plots->add("neutralPT0013", "Neutral hadronic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("neutralPT1624", "Neutral hadronic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("neutralPT2430", "Neutral hadronic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("neutralPT30in", "Neutral hadronic vector sum of pt in HF |#eta| > 3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //========================
  // PHI plots
  //======================== 
  //-------
  // PHOTON
  //-------

  all_plots->add("photonPHI0013", "Net angle of photonic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("photonPHI1624", "Net angle of photonic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("photonPHI2430", "Net angle of photonic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // CHARGED HADRONS
  //-------
  all_plots->add("chargedPHI0013", "Net angle of charged hadronic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedPHI1624", "Net angle of charged hadronic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedPHI2430", "Net angle of charged hadronic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // NEUTRAL HADRONS
  //-------
  all_plots->add("neutralPHI0013", "Net angle of neutral hadronic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("neutralPHI1624", "Net angle of neutral hadronic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("neutralPHI2430", "Net angle of neutral hadronic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
   all_plots->add("neutralPHI30in", "Net angle of neutral hadronic vector sum of pt in HF |#eta| > 3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

   //========================
  // SUM ET
  //======================== 
  //-------
  // PHOTON
  //-------

  all_plots->add("photonPHI0013", "Photonic scalar sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("photonPHI1624", "Photonic scalar sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("photonPHI2430", "Photonic scalar sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // CHARGED HADRONS
  //-------
  all_plots->add("chargedPHI0013", "Charged hadronic scalar sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedPHI1624", "Charged hadronic scalar sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedPHI2430", "Charged hadronic scalar sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // NEUTRAL HADRONS
  //-------
  all_plots->add("neutralPHI0013", "Neutral hadronic scalar sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("neutralPHI1624", "Neutral hadronic scalar sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("neutralPHI2430", "Neutral hadronic scalar sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
   all_plots->add("neutralPHI30in", "Neutral hadronic scalar sum of pt in HF |#eta| > 3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //========================
  // EXTRA
  //======================== 

  all_plots->add("nVert", "Neutral hadronic scalar sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("PHIinBump", "Net angle of vector sum PT for events within the 50-120GeV MET bump", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
   all_plots->add("dilmass", "Neutral hadronic scalar sum of pt in HF |#eta| > 3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);


return all_plots;

}
