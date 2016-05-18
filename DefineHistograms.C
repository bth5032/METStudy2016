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
        plotnode *head, *current, *tail;
    
    public:
        PlotList(TString name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size){
            head = new plotnode();
            head->name = name;
            head->title = title;
            head->xlabel = xlabel;
            head->ylabel = ylabel;
            head->xmin = xmin;
            head->xmax = xmax;
            head->prev=NULL;
            head->next=NULL;

            current=head;
            tail=head;
        }

        void add(TString name, TString title, TString xlabel, TString ylabel, double xmin, double xmax, double bin_size){
            plotnode* next = new plotnode();
            next->name = name;
            next->title = title;
            next->xlabel = xlabel;
            next->ylabel = ylabel;
            next->xmin = xmin;
            next->xmax = xmax;

            next->next=NULL;
            next->prev=tail;
            tail->next=next;
            tail=next;
        }

        //return node with plotname, always puts last plot name if the plot can't be found!!
        void setPlot(TString plotname){
            current=head;
            do
            {
                if (current->name == plotname)
                {
                    break;
                }
                current=current->next;
            }while (current != tail);
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
  
  PlotList* all_plots = new PlotList("type1MET", "Type 1 MET for All Events in Study", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("type1MET_2Jets", "Type 1 MET for All Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  
  //electron/muon
  all_plots->add("type1MET_el", "Type 1 MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("type1MET_mu", "Type 1 MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

  //electron/muon with jets
  all_plots->add("type1MET_2jets_el", "Type 1 MET for Dielectron Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);
  all_plots->add("type1MET_2jets_mu", "Type 1 MET for Dimuon Events with at Least 2 Jets", "E^{miss}_{T} (GeV)", "Count / [5 GeV]", 0, 500, 5);

return all_plots;

}
