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
        TString name, title, xlabel, ylabel, type, options, histo_name;
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
        PlotList(TString name, TString histo_name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size, TString options="", TString type=""){
            head = new plotnode();

            //Set vars from user
            head->name = name;
            head->histo_name = histo_name;
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
            null->histo_name = "NULL";
            null->title = "NULL";
            null->xlabel = "NULL";
            null->ylabel = "NULL";
            null->options = "NULL";
            null->type = "NULL";
            null->xmin = 0;
            null->xmax = 0;
            null->bin_size = 0;
        }

        void add(TString name, TString histo_name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size, TString options="", TString type=""){
            plotnode* next = new plotnode();
            next->name = name;
            next->histo_name = histo_name;
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
        bool setPlot(TString name){
            current=head;

            do
            {
                if (current->name == name)
                {
                    return true;
                }
                current=current->next;
            }while (current != tail);

            if (current->name == name){
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
        TString histName(){
            return current->histo_name;
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

  // long range type1 MET
  all_plots->add("type1MET_long", "type1MET", "Type 1 MET for All Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 6000, 5);
  all_plots->add("zoomBump", "type1MET", "Type 1 MET in between 110 and 125 GeV", "E^{miss}_{T} (GeV)", "Count / [1 GeV]", 110, 125, 1);

  //-------
  //TYPE1
  //-------
  all_plots->add("type1MET_2jets", "type1MET_2jets", "Type 1 MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //electron/muon
  all_plots->add("type1MET_el", "type1MET_el", "Type 1 MET for Dielectron Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("type1MET_mu", "type1MET_mu", "Type 1 MET for Dimuon Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //electron/muon with jets
  all_plots->add("type1MET_2jets_el", "type1MET_2jets_el", "Type 1 MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("type1MET_2jets_mu", "type1MET_2jets_mu", "Type 1 MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //-------
  // RAW
  //-------

  all_plots->add("rawMET", "rawMET", "Raw MET for All Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("rawMET_2jets", "rawMET_2jets", "Raw MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //electron/muon
  all_plots->add("rawMET_el", "rawMET_el", "Raw MET for Dielectron Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("rawMET_mu", "rawMET_mu", "Raw MET for Dimuon Events", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //electron/muon with jets
  all_plots->add("rawMET_2jets_el", "rawMET_2jets_el", "Raw MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);
  all_plots->add("rawMET_2jets_mu", "rawMET_2jets_mu", "Raw MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  //-------
  // PHI
  //-------
  all_plots->add("netPHI", "netPHI", "Direction of #vec{E}^{miss}_{T} in Transverse Plane for All Events with E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("netPHI_2jets", "netPHI_2jets", "Direction of #vec{E}^{miss}_{T} in Transverse Plane for All Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  
  //electron/muon
  all_plots->add("netPHI_el", "netPHI_el", "Direction of #vec{E}^{miss}_{T} for Dielectron Events with E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("netPHI_mu", "netPHI_mu", "Direction of #vec{E}^{miss}_{T} for Dimuon Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);

  //electron/muon with jets
  all_plots->add("netPHI_2jets_el", "netPHI_2jets_el", "Direction of #vec{E}^{miss}_{T} for Dielectron Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
  all_plots->add("netPHI_2jets_mu", "netPHI_2jets_mu", "Direction of #vec{E}^{miss}_{T} for Dimuon Events with at Least 2 Jets and E^{miss}_{T} > 20GeV", "#phi for #vec{E}^{miss}_{T}(rads)", "Count / [#frac{2 #pi}{20}]", -3.15, 3.15, 10);
}

void addExtraPlots(PlotList* all_plots){
  //========================
  // EXTRA
  //======================== 

  all_plots->add("nVert", "nVert", "Number of verticies for events in the study", "Number of verticies in event", "Count / [1 vertex]", 0, 50, 1);

  all_plots->add("dilmass", "dilmass", "Dilepton mass for all events in the study.", "Dilepton Mass (GeV)", "Count / [1 GeV]", 75, 105, 1);
  all_plots->add("dilmass_ee", "dilmass_ee", "Dilepton mass for just dielectron events.", "Dilepton Mass (GeV)", "Count / [1 GeV]", 75, 105, 1);
  all_plots->add("dilmass_mm", "dilmass_mm", "Dilepton mass for just dimuon events.", "Dilepton Mass (GeV)", "Count / [1 GeV]", 75, 105, 1);  

  all_plots->add("dilmass_2jets", "dilmass_2jets", "Dilepton mass for events with >=2 jets.", "Dilepton Mass (GeV)", "Count / [1 GeV]", 75, 105, 1);
  all_plots->add("dilmass_2jets_ee", "dilmass_2jets_ee", "Dilepton mass for dielectron events with >=2 jets.", "Dilepton Mass (GeV)", "Count / [1 GeV]", 75, 105, 1);
  all_plots->add("dilmass_2jets_mm", "dilmass_2jets_mm", "Dilepton mass for dimuon events with >=2 jets.", "Dilepton Mass (GeV)", "Count / [1 GeV]", 75, 105, 1);  

}

PlotList* getPlotList(){

  PlotList* all_plots = new PlotList("type1MET", "type1MET", "Type 1 MET for All Events in Study", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 150, 5);

  addMETPlots(all_plots);
  addMllPlots(all_plots);

return all_plots;

}
