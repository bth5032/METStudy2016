// Bobak Hashemi
// This is place to store all the info about the plots.
// For now it only holds plot info for drawing.
// 
// It is used by simply calling setting PlotList* var=getPlotList(), 
// then to access data in your program, just call var->setPlot(plot_name).
// 
// If plot_name is found, setPlot returns true and then you can call
// var->name() or title() etc... to get the plot info. 
//
// Otherwise var->name() will return "NULL" (string), and setPlot returns false.
// When looping through plots you can do if (! var->setPlot(name)) continue; which
// lets you skip over any plots that don't exist and sets the plot in one line. 

#include "TString.h"

//TCut base_cut = "dilmass < 101 && dilmass > 81 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 2.4 && abs(lep_p4[1].eta()) < 2.4 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0";

class PlotList {
    
    struct plotnode;
    struct plotnode {
      //name == Name of plot, used internally for bookkeeping
      //title == Title that shows up on drawn plots
      //xlabel == X axis label that shows up on plots
      //ylabel == Y axis lable that shows up on plots
      //bin_size == this is the number to 'rebin' in the plot drawing script
      //xmin == lowest bin floor for the histogram
      //xmax == ceiling of highest bin for the histogram
      //type == for book keeping, used as flags in drawPlots.C
      //options == also for book keeping, also used as flags in drawPlots.C
        TString name, title, xlabel, ylabel, type, options;
        double xmin, xmax, bin_size;
        struct plotnode *next, *prev;
    };    

    private:
        plotnode *head, *current, *tail, *null;

        void _setType(plotnode* node){
          if (node->name.Contains("PT")){
            node->type = "pt";
          }
          else if (node->name.Contains("PHI")){
            node->type = "phi";
          }
          else if (node->name.Contains("SET")){
            node->type = "sumet";
          }
          else if (node->name.Contains("MET")){
            node->type = "met";
          }
          else{
            node->type = "extra";
          }
        }

        void _setOptions(plotnode* node){
          if (node->type == "pt"){
            node->options+="<logy>";
            node->options+="<overflow>";
          }
          else if (node->type == "phi"){
            //node->options+="<maxDigits2>";
          }
          else if (node->type == "met"){
            node->options+="<logy>";
            node->options+="<overflow>";
          }
          else if (node->type == "sumet"){
            //node->options+="<logy>";
            node->options+="<overflow>";
          }
          else if (node->type == "extra"){
            //nothing for now
          }          
        }
    
    public:
        PlotList(TString name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size, TString options="", TString type=""){
            head = new plotnode();
            
            //Set vars from user
            head->name = name;
            head->title = title;
            head->xlabel = xlabel;
            head->ylabel = ylabel;
            head->xmin = xmin;
            head->xmax = xmax;
            head->bin_size = bin_size;
            
            //compute vars if none given
            if (type == ""){
              _setType(head);
            }
            else{
              head->type=type;
            }
            if (options == ""){
              _setOptions(head);
            }
            else{
              head->options=options;
            }

            head->prev=NULL;
            head->next=NULL;


            current=head;
            tail=head;

            null = new plotnode();
            null->name = "NULL";
            null->title = "NULL";
            null->xlabel = "NULL";
            null->ylabel = "NULL";
            null->options = "NULL";
            null->type = "NULL";
            null->xmin = 0;
            null->xmax = 0;
            null->bin_size = 0;
        }

        void add(TString name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size, TString options="", TString type=""){
            plotnode* next = new plotnode();
            next->name = name;
            next->title = title;
            next->xlabel = xlabel;
            next->ylabel = ylabel;
            next->xmin = xmin;
            next->xmax = xmax;
            next->bin_size = bin_size;

            if (type == ""){
              _setType(next);
            }
            else{
              next->type=type;
            }
            if (options == ""){
              _setOptions(next);
            }
            else{
              next->options=options;
            }


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
            
            if (current->name == plotname){
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
        TString type(){
            return current->type;
        }
        bool hasOpt(TString query){
            return current->options.Contains("<"+query+">");
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

void addMETPlots(PlotList* all_plots){
  //========================
  // MET plots
  //========================
  
  //-------
  //TYPE1
  //-------
  all_plots->add("type1MET_2jets", "Type 1 MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  
  //electron/muon
  all_plots->add("type1MET_el", "Type 1 MET for Dielectron Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("type1MET_mu", "Type 1 MET for Dimuon Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //electron/muon with jets
  all_plots->add("type1MET_2jets_el", "Type 1 MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("type1MET_2jets_mu", "Type 1 MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //-------
  // RAW
  //-------

  all_plots->add("rawMET", "Raw MET for All Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("rawMET_2jets", "Raw MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  
  //electron/muon
  all_plots->add("rawMET_el", "Raw MET for Dielectron Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("rawMET_mu", "Raw MET for Dimuon Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //electron/muon with jets
  all_plots->add("rawMET_2jets_el", "Raw MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("rawMET_2jets_mu", "Raw MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //-------
  // PHI
  //-------
  all_plots->add("netPHI", "Direction of #vec{E}^{miss}_{T} in Transverse Plane for All Events with E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("netPHI_2jets", "Direction of #vec{E}^{miss}_{T} in Transverse Plane for All Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  
  //electron/muon
  all_plots->add("netPHI_el", "Direction of #vec{E}^{miss}_{T} for Dielectron Events with E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("netPHI_mu", "Direction of #vec{E}^{miss}_{T} for Dimuon Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);

  //electron/muon with jets
  all_plots->add("netPHI_2jets_el", "Direction of #vec{E}^{miss}_{T} for Dielectron Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("netPHI_2jets_mu", "Direction of #vec{E}^{miss}_{T} for Dimuon Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);


}

void addPTPlots(PlotList* all_plots){
  
  //========================
  // PT plots
  //======================== 
  //-------
  // PHOTON
  //-------

  all_plots->add("photonPT0013", "Photonic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("photonPT1624", "Photonic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("photonPT2430", "Photonic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("photonPT30in", "Photonic vector sum of pt in endcap (no tracker) |#eta| > 3.0", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 80, 5);

  //-------
  // CHARGED HADRONS
  //-------
  all_plots->add("chargedPT0013", "Charged object vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("chargedPT1624", "Charged object vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("chargedPT2430", "Charged object vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);

  //-------
  // NEUTRAL HADRONS
  //-------
  all_plots->add("neutralPT0013", "Neutral hadronic vector sum of pt in barrel |#eta| < 1.3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("neutralPT1624", "Neutral hadronic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("neutralPT2430", "Neutral hadronic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
  all_plots->add("neutralPT30in", "Neutral hadronic vector sum of pt in HF |#eta| > 3", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 200, 5);
}

void addPhiPlots(PlotList* all_plots){
  //========================
  // PHI plots
  //======================== 
  //-------
  // PHOTON
  //-------

  all_plots->add("photonPHI0013", "Net angle of photonic vector sum of pt in barrel |#eta| < 1.3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("photonPHI1624", "Net angle of photonic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("photonPHI2430", "Net angle of photonic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("photonPHI30in", "Net angle of photonic vector sum of pt in endcap (no tracker) |#eta| > 3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);

  //-------
  // CHARGED HADRONS
  //-------
  all_plots->add("chargedPHI0013", "Net angle of charged object vector sum of pt in barrel |#eta| < 1.3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("chargedPHI1624", "Net angle of charged object vector sum of pt in endcap |#eta| #in (1.6,2.4)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("chargedPHI2430", "Net angle of charged object vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);

  //-------
  // NEUTRAL HADRONS
  //-------
  all_plots->add("neutralPHI0013", "Net angle of neutral hadronic vector sum of pt in barrel |#eta| < 1.3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("neutralPHI1624", "Net angle of neutral hadronic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("neutralPHI2430", "Net angle of neutral hadronic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
   all_plots->add("neutralPHI30in", "Net angle of neutral hadronic vector sum of pt in HF |#eta| > 3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
}

void addPhiPTCUTPlots(PlotList* all_plots){
  //========================
  // PHI plots
  //======================== 
  //-------
  // PHOTON
  //-------

  all_plots->add("photonPHI0013_PCUT20", "Net angle of photonic vector sum of pt in barrel |#eta| < 1.3 where | #Sigma_{ph} #vec{p}_{t} | > 20", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("photonPHI1624_PCUT20", "Net angle of photonic vector sum of pt in endcap |#eta| #in (1.6,2.4) where | #Sigma_{ph} #vec{p}_{t} | > 20", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("photonPHI2430_PCUT20", "Net angle of photonic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0) where | #Sigma_{ph} #vec{p}_{t} | > 20", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("photonPHI30in_PCUT20", "Net angle of photonic vector sum of pt in endcap (no tracker) |#eta| > 3 where | #Sigma_{ph} #vec{p}_{t} | > 20", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);

  //-------
  // CHARGED HADRONS
  //-------
  all_plots->add("chargedPHI0013_PCUT20", "Net angle of charged object vector sum of pt in barrel |#eta| < 1.3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("chargedPHI1624_PCUT20", "Net angle of charged object vector sum of pt in endcap |#eta| #in (1.6,2.4)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("chargedPHI2430_PCUT20", "Net angle of charged object vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);

  //-------
  // NEUTRAL HADRONS
  //-------
  all_plots->add("neutralPHI0013_PCUT20", "Net angle of neutral hadronic vector sum of pt in barrel |#eta| < 1.3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("neutralPHI1624_PCUT20", "Net angle of neutral hadronic vector sum of pt in endcap |#eta| #in (1.6,2.4)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("neutralPHI2430_PCUT20", "Net angle of neutral hadronic vector sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
   all_plots->add("neutralPHI30in_PCUT20", "Net angle of neutral hadronic vector sum of pt in HF |#eta| > 3", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
}

void addSumETPlots(PlotList* all_plots){
  //========================
  // SUM ET
  //======================== 
  
  //Net SumET
  all_plots->add("netSET", "Overall SumET for all Events", "#Sigma|E_{T}| (GeV)", "Count / [1 GeV]", 0, 6000, 1);

  //-------
  // PHOTON
  //-------

  all_plots->add("photonSET0013", "Photonic scalar sum of pt in barrel |#eta| < 1.3", "#Sigma|E_{T}| (GeV)", "Count / [1 GeV]", 0, 200, 1);
  all_plots->add("photonSET1624", "Photonic scalar sum of pt in endcap |#eta| #in (1.6,2.4)", "#Sigma|E_{T}| (GeV)", "Count / [1 GeV]", 0, 100, 1);
  all_plots->add("photonSET2430", "Photonic scalar sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#Sigma|E_{T}| (GeV)", "Count / [1 GeV]", 0, 150, 1);
  all_plots->add("photonSET30in", "Photonic scalar sum of pt in HF |#eta| > 3", "#Sigma|E_{T}| (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // CHARGED HADRONS
  //-------
  all_plots->add("chargedSET0013", "Charged object scalar sum of pt in barrel |#eta| < 1.3", "#Sigma|E_{T}| (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedSET1624", "Charged object scalar sum of pt in endcap |#eta| #in (1.6,2.4)", "#Sigma|E_{T}| (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("chargedSET2430", "Charged object scalar sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#Sigma|E_{T}| (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //-------
  // NEUTRAL HADRONS
  //-------
  all_plots->add("neutralSET0013", "Neutral hadronic scalar sum of pt in barrel |#eta| < 1.3", "#Sigma|E_{T}| (GeV)", "Count / [2 GeV]", 0, 150, 2);
  all_plots->add("neutralSET1624", "Neutral hadronic scalar sum of pt in endcap |#eta| #in (1.6,2.4)", "#Sigma|E_{T}| (GeV)", "Count / [2 GeV]", 0, 150, 2);
  all_plots->add("neutralSET2430", "Neutral hadronic scalar sum of pt in endcap (no tracker) |#eta| #in (2.4,3.0)", "#Sigma|E_{T}| (GeV)", "Count / [2 GeV]", 0, 150, 2);
  all_plots->add("neutralSET30in", "Neutral hadronic scalar sum of pt in HF |#eta| > 3", "#Sigma|E_{T}| (GeV)", "Count / [5 GeV]", 0, 500, 5);
}

void addExtraPlots(PlotList* all_plots){
  //========================
  // EXTRA
  //======================== 

  all_plots->add("nVert", "Number of verticies for events in the study", "Number of verticies in event", "Count / [1 vertex]", 0, 50, 1);
  all_plots->add("PHIinBump", "Net angle of vector sum PT for events within the 50-120GeV MET bump", "E^{miss}_{T} (GeV)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("dilmass", "Dilepton mass for all events in the study.", "Dilepton Mass (GeV)", "Count / [1 GeV]", 75, 105, 1);  
}

PlotList* getPlotList(){

  PlotList* all_plots = new PlotList("type1MET", "Type 1 MET for All Events in Study", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  addMETPlots(all_plots);
  addPTPlots(all_plots);
  addPhiPlots(all_plots);
  addPhiPTCUTPlots(all_plots);
  addSumETPlots(all_plots);
  addExtraPlots(all_plots);

return all_plots;

}