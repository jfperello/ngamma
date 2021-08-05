/*SFPPlotter.h
 *Class for generating histogram files for SPS-SABRE data
 *Intended use case is generating a TChain of multiple analyzed files and making
 *histograms of the larger data set.
 *
 *Created Jan 2020 by GWM
 */

#include "EventBuilder.h"
#include "SFPPlotter.h"
#include <TSystem.h>
#include <string>
/*Generates storage and initializes pointers*/
SFPPlotter::SFPPlotter() {
  rootObj = new THashTable();
  rootObj->SetOwner(false);//THashTable doesnt own members; avoid double delete
  event_address = new ProcessedEvent();

  nCutFile = NULL;
  rp = NULL;
  plus3 = NULL;
  greject = NULL;
  chain = new TChain("SPSTree");
  m_pb = NULL;
  cutFlag = false;
}

SFPPlotter::~SFPPlotter() {
    delete event_address;
    if (nCutFile != NULL && nCutFile->IsOpen()) nCutFile->Close();
}
/*2D histogram fill wrapper*/
void SFPPlotter::MyFill(string name, int binsx, double minx, double maxx, double valuex,
    int binsy, double miny, double maxy, double valuey) {
    TH2F* histo = (TH2F*)rootObj->FindObject(name.c_str());
    if (histo != NULL) {
        histo->Fill(valuex, valuey);
    }
    else {
        TH2F* h = new TH2F(name.c_str(), name.c_str(), binsx, minx, maxx, binsy, miny, maxy);
        h->Fill(valuex, valuey);
        rootObj->Add(h);
    }
}

/*2D histogram fill wrapper with variable y binning*/
void SFPPlotter::MyFill(string name, int binsx, double minx, double maxx, double valuex, double valuey, int i) {
    TH2F* histo = (TH2F*)rootObj->FindObject(name.c_str());
    double Bins = 311;
    double tEdges[312] = { 0, 0.9, 0.92, 0.94, 0.96, 0.98, 1, 1.02, 1.04, 1.06, 1.08, 1.1, 1.12, 1.14, 1.16, 1.18, 1.2, 1.22, 1.24, 1.26, 1.28, 1.3, 1.32, 1.34, 1.36, 1.38, 1.4, 1.42, 1.44, 1.46, 1.48, 1.5, 1.52, 1.54, 1.56, 1.58, 1.6, 1.62, 1.64, 1.66, 1.68, 1.7, 1.72, 1.74, 1.76, 1.78, 1.8, 1.82, 1.84, 1.86, 1.88, 1.9, 1.92, 1.94, 1.96, 1.98, 2, 2.025, 2.05, 2.075, 2.1, 2.125, 2.15, 2.175, 2.2, 2.225, 2.25, 2.275, 2.3, 2.325, 2.35, 2.375, 2.4, 2.425, 2.45, 2.475, 2.5, 2.53, 2.56, 2.59, 2.62, 2.65, 2.68, 2.71, 2.74, 2.77, 2.8, 2.83, 2.86, 2.89, 2.92, 2.95, 2.98, 3.01, 3.04, 3.07, 3.1, 3.13, 3.16, 3.19, 3.22, 3.25, 3.28, 3.31, 3.34, 3.37, 3.4, 3.43, 3.46, 3.49, 3.52, 3.55, 3.58, 3.61, 3.64, 3.67, 3.7, 3.735, 3.77, 3.805, 3.84, 3.875, 3.91, 3.945, 3.98, 4.015, 4.05, 4.085, 4.12, 4.155, 4.19, 4.225, 4.26, 4.295, 4.33, 4.365, 4.4, 4.44, 4.48, 4.52, 4.56, 4.6, 4.64, 4.68, 4.72, 4.76, 4.8, 4.84, 4.88, 4.92, 4.96, 5, 5.04, 5.08, 5.12, 5.16, 5.2, 5.24, 5.28, 5.32, 5.36, 5.4, 5.44, 5.48, 5.52, 5.56, 5.6, 5.64, 5.68, 5.72, 5.76, 5.8, 5.84, 5.88, 5.92, 5.96, 6, 6.04, 6.08, 6.12, 6.16, 6.2, 6.24, 6.28, 6.32, 6.36, 6.4, 6.44, 6.48, 6.52, 6.56, 6.6, 6.64, 6.68, 6.72, 6.76, 6.8, 6.84, 6.88, 6.92, 6.96, 7, 7.04, 7.08, 7.12, 7.16, 7.2, 7.24, 7.28, 7.32, 7.36, 7.4, 7.44, 7.48, 7.52, 7.56, 7.6, 7.64, 7.68, 7.72, 7.76, 7.8, 7.84, 7.88, 7.92, 7.96, 8, 8.04, 8.08, 8.12, 8.16, 8.2, 8.24, 8.28, 8.32, 8.36, 8.4, 8.44, 8.48, 8.52, 8.56, 8.6, 8.64, 8.68, 8.72, 8.76, 8.8, 8.84, 8.88, 8.92, 8.96, 9, 9.04, 9.08, 9.12, 9.16, 9.2, 9.24, 9.28, 9.32, 9.36, 9.4, 9.44, 9.48, 9.52, 9.56, 9.6, 9.64, 9.68, 9.72, 9.76, 9.8, 9.84, 9.88, 9.92, 9.96, 10, 10.04, 10.08, 10.12, 10.16, 10.2, 10.24, 10.28, 10.32, 10.36, 10.4, 10.44, 10.48, 10.52, 10.56, 10.6, 10.64, 10.68, 10.72, 10.76, 10.8, 10.84, 10.88, 10.92, 10.96, 11, 11.04, 11.08, 11.12, 11.16, 11.2, 11.24, 11.28, 11.32, 11.36, 11.4 };
    double eEdges[312] = { -8.72,-8.7, -8.68, -8.66, -8.64, -8.62, -8.6, -8.58, -8.56, -8.54, -8.52, -8.5, -8.48, -8.46, -8.44, -8.42, -8.4, -8.38, -8.36, -8.34, -8.32, -8.3, -8.28, -8.26, -8.24, -8.22, -8.2, -8.18, -8.16, -8.14, -8.12, -8.1, -8.08, -8.06, -8.04, -8.02, -8, -7.98, -7.96, -7.94, -7.92, -7.9, -7.88, -7.86, -7.84, -7.82, -7.8, -7.78, -7.76, -7.74, -7.72, -7.7, -7.68, -7.66, -7.64, -7.62, -7.6, -7.575, -7.55, -7.525, -7.5, -7.475, -7.45, -7.425, -7.4, -7.375, -7.35, -7.325, -7.3, -7.275, -7.25, -7.225, -7.2, -7.175, -7.15, -7.125, -7.1, -7.07, -7.04, -7.01, -6.98, -6.95, -6.92, -6.89, -6.86, -6.83, -6.8, -6.77, -6.74, -6.71, -6.68, -6.65, -6.62, -6.59, -6.56, -6.53, -6.5, -6.47, -6.44, -6.41, -6.38, -6.35, -6.32, -6.29, -6.26, -6.23, -6.2, -6.17, -6.14, -6.11, -6.08, -6.05, -6.02, -5.99, -5.96, -5.93, -5.9, -5.865, -5.83, -5.795, -5.76, -5.725, -5.69, -5.655, -5.62, -5.585, -5.55, -5.515, -5.48, -5.445, -5.41, -5.375, -5.34, -5.305, -5.27, -5.235, -5.2, -5.16, -5.12, -5.08, -5.04, -5, -4.96, -4.92, -4.88, -4.84, -4.8, -4.76, -4.72, -4.68, -4.64, -4.6, -4.56, -4.52, -4.48, -4.44, -4.4, -4.36, -4.32, -4.28, -4.24, -4.2, -4.16, -4.12, -4.08, -4.04, -4, -3.96, -3.92, -3.88, -3.84, -3.8, -3.76, -3.72, -3.68, -3.64, -3.6, -3.56, -3.52, -3.48, -3.44, -3.4, -3.36, -3.32, -3.28, -3.24, -3.2, -3.16, -3.12, -3.08, -3.04, -3, -2.96, -2.92, -2.88, -2.84, -2.8, -2.76, -2.72, -2.68, -2.64, -2.6, -2.56, -2.52, -2.48, -2.44, -2.4, -2.36, -2.32, -2.28, -2.24, -2.2, -2.16, -2.12, -2.08, -2.04, -2, -1.96, -1.92, -1.88, -1.84, -1.8, -1.76, -1.72, -1.68, -1.64, -1.6, -1.56, -1.52, -1.48, -1.44, -1.4, -1.36, -1.32, -1.28, -1.24, -1.2, -1.16, -1.12, -1.08, -1.04, -1, -0.96, -0.92, -0.88, -0.84, -0.8, -0.76, -0.72, -0.68, -0.64, -0.6, -0.56, -0.52, -0.48, -0.44, -0.4, -0.36, -0.32, -0.28, -0.24, -0.2, -0.16, -0.12, -0.08, -0.04, -2.45102E-11, 0.04, 0.08, 0.12, 0.16, 0.2, 0.24, 0.28, 0.32, 0.36, 0.4, 0.44, 0.48, 0.52, 0.56, 0.6, 0.64, 0.68, 0.72, 0.76, 0.8, 0.84, 0.88, 0.92, 0.96, 1, 1.04, 1.08, 1.12, 1.16, 1.2, 1.24, 1.28, 1.32, 1.36, 1.4, 1.44, 1.48, 1.52, 1.56, 1.6, 1.64, 1.68, 1.72, 1.76, 1.8 };
    if(i==1){
    	    if (histo != NULL) {
            	histo->Fill(valuex, valuey);
            }
    	    else {
        	TH2F* h = new TH2F(name.c_str(), name.c_str(), binsx, minx, maxx, Bins,tEdges);
        	h->Fill(valuex, valuey);
        	rootObj->Add(h);
    	    }
    }
    if(i==2){
    	    if (histo != NULL) {
            	histo->Fill(valuex, valuey);
            }
    	    else {
        	TH2F* h = new TH2F(name.c_str(), name.c_str(), binsx, minx, maxx, Bins,eEdges);
        	h->Fill(valuex, valuey);
        	rootObj->Add(h);
    	    }
    }
}


/*1D histogram fill wrapper*/
void SFPPlotter::MyFill(string name, int binsx, double minx, double maxx, double valuex) {
    TH1F* histo = (TH1F*)rootObj->FindObject(name.c_str());
    if (histo != NULL) {
        histo->Fill(valuex);
    }
    else {
        TH1F* h = new TH1F(name.c_str(), name.c_str(), binsx, minx, maxx);
        h->Fill(valuex);
        rootObj->Add(h);
    }
}

/*1D histogram fill wrapper with variable x binning*/
void SFPPlotter::MyFill(string name, double valuex,int i) {
    TH1F* histo = (TH1F*)rootObj->FindObject(name.c_str());
    double Bins = 311;
    double tEdges[312] = { 0, 0.9, 0.92, 0.94, 0.96, 0.98, 1, 1.02, 1.04, 1.06, 1.08, 1.1, 1.12, 1.14, 1.16, 1.18, 1.2, 1.22, 1.24, 1.26, 1.28, 1.3, 1.32, 1.34, 1.36, 1.38, 1.4, 1.42, 1.44, 1.46, 1.48, 1.5, 1.52, 1.54, 1.56, 1.58, 1.6, 1.62, 1.64, 1.66, 1.68, 1.7, 1.72, 1.74, 1.76, 1.78, 1.8, 1.82, 1.84, 1.86, 1.88, 1.9, 1.92, 1.94, 1.96, 1.98, 2, 2.025, 2.05, 2.075, 2.1, 2.125, 2.15, 2.175, 2.2, 2.225, 2.25, 2.275, 2.3, 2.325, 2.35, 2.375, 2.4, 2.425, 2.45, 2.475, 2.5, 2.53, 2.56, 2.59, 2.62, 2.65, 2.68, 2.71, 2.74, 2.77, 2.8, 2.83, 2.86, 2.89, 2.92, 2.95, 2.98, 3.01, 3.04, 3.07, 3.1, 3.13, 3.16, 3.19, 3.22, 3.25, 3.28, 3.31, 3.34, 3.37, 3.4, 3.43, 3.46, 3.49, 3.52, 3.55, 3.58, 3.61, 3.64, 3.67, 3.7, 3.735, 3.77, 3.805, 3.84, 3.875, 3.91, 3.945, 3.98, 4.015, 4.05, 4.085, 4.12, 4.155, 4.19, 4.225, 4.26, 4.295, 4.33, 4.365, 4.4, 4.44, 4.48, 4.52, 4.56, 4.6, 4.64, 4.68, 4.72, 4.76, 4.8, 4.84, 4.88, 4.92, 4.96, 5, 5.04, 5.08, 5.12, 5.16, 5.2, 5.24, 5.28, 5.32, 5.36, 5.4, 5.44, 5.48, 5.52, 5.56, 5.6, 5.64, 5.68, 5.72, 5.76, 5.8, 5.84, 5.88, 5.92, 5.96, 6, 6.04, 6.08, 6.12, 6.16, 6.2, 6.24, 6.28, 6.32, 6.36, 6.4, 6.44, 6.48, 6.52, 6.56, 6.6, 6.64, 6.68, 6.72, 6.76, 6.8, 6.84, 6.88, 6.92, 6.96, 7, 7.04, 7.08, 7.12, 7.16, 7.2, 7.24, 7.28, 7.32, 7.36, 7.4, 7.44, 7.48, 7.52, 7.56, 7.6, 7.64, 7.68, 7.72, 7.76, 7.8, 7.84, 7.88, 7.92, 7.96, 8, 8.04, 8.08, 8.12, 8.16, 8.2, 8.24, 8.28, 8.32, 8.36, 8.4, 8.44, 8.48, 8.52, 8.56, 8.6, 8.64, 8.68, 8.72, 8.76, 8.8, 8.84, 8.88, 8.92, 8.96, 9, 9.04, 9.08, 9.12, 9.16, 9.2, 9.24, 9.28, 9.32, 9.36, 9.4, 9.44, 9.48, 9.52, 9.56, 9.6, 9.64, 9.68, 9.72, 9.76, 9.8, 9.84, 9.88, 9.92, 9.96, 10, 10.04, 10.08, 10.12, 10.16, 10.2, 10.24, 10.28, 10.32, 10.36, 10.4, 10.44, 10.48, 10.52, 10.56, 10.6, 10.64, 10.68, 10.72, 10.76, 10.8, 10.84, 10.88, 10.92, 10.96, 11, 11.04, 11.08, 11.12, 11.16, 11.2, 11.24, 11.28, 11.32, 11.36, 11.4 };
    double eEdges[312] = { -8.72,-8.7, -8.68, -8.66, -8.64, -8.62, -8.6, -8.58, -8.56, -8.54, -8.52, -8.5, -8.48, -8.46, -8.44, -8.42, -8.4, -8.38, -8.36, -8.34, -8.32, -8.3, -8.28, -8.26, -8.24, -8.22, -8.2, -8.18, -8.16, -8.14, -8.12, -8.1, -8.08, -8.06, -8.04, -8.02, -8, -7.98, -7.96, -7.94, -7.92, -7.9, -7.88, -7.86, -7.84, -7.82, -7.8, -7.78, -7.76, -7.74, -7.72, -7.7, -7.68, -7.66, -7.64, -7.62, -7.6, -7.575, -7.55, -7.525, -7.5, -7.475, -7.45, -7.425, -7.4, -7.375, -7.35, -7.325, -7.3, -7.275, -7.25, -7.225, -7.2, -7.175, -7.15, -7.125, -7.1, -7.07, -7.04, -7.01, -6.98, -6.95, -6.92, -6.89, -6.86, -6.83, -6.8, -6.77, -6.74, -6.71, -6.68, -6.65, -6.62, -6.59, -6.56, -6.53, -6.5, -6.47, -6.44, -6.41, -6.38, -6.35, -6.32, -6.29, -6.26, -6.23, -6.2, -6.17, -6.14, -6.11, -6.08, -6.05, -6.02, -5.99, -5.96, -5.93, -5.9, -5.865, -5.83, -5.795, -5.76, -5.725, -5.69, -5.655, -5.62, -5.585, -5.55, -5.515, -5.48, -5.445, -5.41, -5.375, -5.34, -5.305, -5.27, -5.235, -5.2, -5.16, -5.12, -5.08, -5.04, -5, -4.96, -4.92, -4.88, -4.84, -4.8, -4.76, -4.72, -4.68, -4.64, -4.6, -4.56, -4.52, -4.48, -4.44, -4.4, -4.36, -4.32, -4.28, -4.24, -4.2, -4.16, -4.12, -4.08, -4.04, -4, -3.96, -3.92, -3.88, -3.84, -3.8, -3.76, -3.72, -3.68, -3.64, -3.6, -3.56, -3.52, -3.48, -3.44, -3.4, -3.36, -3.32, -3.28, -3.24, -3.2, -3.16, -3.12, -3.08, -3.04, -3, -2.96, -2.92, -2.88, -2.84, -2.8, -2.76, -2.72, -2.68, -2.64, -2.6, -2.56, -2.52, -2.48, -2.44, -2.4, -2.36, -2.32, -2.28, -2.24, -2.2, -2.16, -2.12, -2.08, -2.04, -2, -1.96, -1.92, -1.88, -1.84, -1.8, -1.76, -1.72, -1.68, -1.64, -1.6, -1.56, -1.52, -1.48, -1.44, -1.4, -1.36, -1.32, -1.28, -1.24, -1.2, -1.16, -1.12, -1.08, -1.04, -1, -0.96, -0.92, -0.88, -0.84, -0.8, -0.76, -0.72, -0.68, -0.64, -0.6, -0.56, -0.52, -0.48, -0.44, -0.4, -0.36, -0.32, -0.28, -0.24, -0.2, -0.16, -0.12, -0.08, -0.04, -2.45102E-11, 0.04, 0.08, 0.12, 0.16, 0.2, 0.24, 0.28, 0.32, 0.36, 0.4, 0.44, 0.48, 0.52, 0.56, 0.6, 0.64, 0.68, 0.72, 0.76, 0.8, 0.84, 0.88, 0.92, 0.96, 1, 1.04, 1.08, 1.12, 1.16, 1.2, 1.24, 1.28, 1.32, 1.36, 1.4, 1.44, 1.48, 1.52, 1.56, 1.6, 1.64, 1.68, 1.72, 1.76, 1.8 };
    if(i==1){
	    if (histo != NULL) {
       	    	histo->Fill(valuex);
    	    }
    	    else {
          	TH1F* h = new TH1F(name.c_str(), name.c_str(), Bins, tEdges);
        	h->Fill(valuex);
        	rootObj->Add(h);
    	    }
    }
    if(i==2){
	    if (histo != NULL) {
       	    	histo->Fill(valuex);
    	    }
    	    else {
          	TH1F* h = new TH1F(name.c_str(), name.c_str(), Bins, eEdges);
        	h->Fill(valuex);
        	rootObj->Add(h);
    	    }
    }

}

void SFPPlotter::Reset() {
  event = empty;
}

/*Function for user to set the cutfiles; 
 *has to be used in current design!
 *User will probably want to change number of cuts and their names
 */
int SFPPlotter::SetCuts(string cutfilename) {
    nCutFile = new TFile(cutfilename.c_str(), "READ");
    if (nCutFile->IsOpen()) {
    	rp = (TCutG*)nCutFile->Get("rp"), plus3 = (TCutG*)nCutFile->Get("plus3"), greject = (TCutG*)nCutFile->Get("greject");
    	rootObj->Add(rp),rootObj->Add(plus3), rootObj->Add(greject);
    }
    if(rp!=NULL && plus3!=NULL && greject != NULL){
	cutFlag = true;
    	return 1;
    }    

    else {
        return 0;
    }
}
/* This function checks to see if the cut exists. */
Bool_t SFPPlotter::cexists(const Char_t* cutname) {//Existence Begin
    Bool_t returnvalue = kFALSE;
    if (rootObj->FindObject(cutname)) returnvalue = kTRUE;
    else { std::cout << cutname << " " << "cut not found" << std::endl; }
    return returnvalue;
}//Existence End
//* This function checks whether something is in the cut or not. */
Bool_t SFPPlotter::checkcutg(const Char_t* cutname, Float_t x, Float_t y){
    Bool_t returnvalue = kFALSE;
    if (cexists(cutname)) {
        TCutG* gcut = (TCutG*)rootObj->FindObject(cutname);
        if (gcut->IsInside(x, y) == 1) returnvalue = kTRUE;
        return returnvalue;
    }
    else {
        return returnvalue;
    }
}
int SFPPlotter::ReadCutlist(string& listname) {
  ifstream input(listname);
    string junk, cutfilename;
    if (!input.is_open()) return 0;

    input >> junk >> cutfilename;

    input.close();

    return SetCuts(cutfilename);

}

/*Makes histograms where only rejection is unset data*/
void SFPPlotter::MakeUncutHistograms(ProcessedEvent ev) {

}

/*Makes histograms with cuts & gates implemented*/
void SFPPlotter::MakeCutHistograms(ProcessedEvent ev) {
	Reset();
	int ch = 0;
	for (int j = 0; j < 16; j++) {
        if (j == 8 || ev.RF3[j] == -1) continue;
    	for (int k = 0; k < 3; k++) {
		    if(ev.CrystalE[k] == -1) continue;
			std::string s = std::to_string(k);
           	// if (fabs(ev.CloverRelTime[k]) < 100 ) continue;
         	//	cout << "greject check" << endl;
            MyFill("g_" + s, 8192, 0, 8191, ev.CrystalE[k]);
            MyFill("g_all", 8192, 0, 8191, ev.CrystalE[k]);
            for (int b = 0; b < 3; b++) { //2D g-g coincidence
                std::string S = std::to_string(b);
                if (b != k) {
                    MyFill("ggkb", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[b]);
                    MyFill("ggbk", 8192, 0, 8191, ev.CrystalE[b], 8192, 0, 8191, ev.CrystalE[k]);
                    MyFill("ggk_" + s + "_vs_all", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[b]);
                    MyFill("ggb_" + S + "_vs_all", 8192, 0, 8191, ev.CrystalE[b], 8192, 0, 8191, ev.CrystalE[k]);
                }
            }//closes b5
			if(ev.nLong3[j]> 50){
				double nQ3 = 0;
				nQ3 = -0.032613*(pow(ev.nQ3[j],2))+0.816376*(pow(ev.nQ3[j],1))+0.485893;
        		MyFill(Form("RF3_%02d", j), 300, 0, 99, ev.RF3[j]);   
       	 		MyFill(Form("PSD3_%02d", j), 8192, 0, 8191, ev.nLong3[j], 1024, 0, 1, ev.TR3[j]);
        		MyFill(Form("nQ3_%02d", j),600,-8,1, nQ3);
	        	MyFill(Form("nE3_%02d", j),600,1,9, ev.nE3[j]);
                MyFill("g3_" + s, 8192, 0, 8191, ev.CrystalE[k]);
                MyFill("g3_all", 8192, 0, 8191, ev.CrystalE[k]);
                for (int b = 0; b < 3; b++) { //2D g-g coincidence
                    std::string S = std::to_string(b);
                    if (b != k) {
                        MyFill("ggkb3", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[b]);
                        MyFill("ggbk3", 8192, 0, 8191, ev.CrystalE[b], 8192, 0, 8191, ev.CrystalE[k]);
                        MyFill("ggk3_" + s + "_vs_all", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[b]);
                        MyFill("ggb3_" + S + "_vs_all", 8192, 0, 8191, ev.CrystalE[b], 8192, 0, 8191, ev.CrystalE[k]);
                    }
                }//closes b5
	    		MyFill("ngamma3_all", 8192, 0 , 8191 , ev.CrystalE[k],600,-9,1, nQ3);
			if(ev.nLong3[j] > 600){
		 		MyFill("ngamma4_all", 8192, 0 , 8191 , ev.CrystalE[k],600,-9,1, nQ3);
        			MyFill(Form("nQ4_%02d", j),600,-8,1, nQ3);
	        		MyFill(Form("nE4_%02d", j),600,1,9, ev.nE3[j]);
			}
	    		MyFill("ngamma3_all_varBin", 8192, 0 , 8191 , ev.CrystalE[k], nQ3,2);
	    	    if(checkcutg("plus3",ev.CrystalE[k],nQ3)){
                    MyFill("gp3_" + s, 8192, 0, 8191, ev.CrystalE[k]);
                    MyFill("gp3_all", 8192, 0, 8191, ev.CrystalE[k]);
                    for (int b = 0; b < 3; b++) { //2D g-g coincidence
                        std::string S = std::to_string(b);
                        if (b != k) {
                            MyFill("ggkbp3", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[b]);
                            MyFill("ggbkp3", 8192, 0, 8191, ev.CrystalE[b], 8192, 0, 8191, ev.CrystalE[k]);
                            MyFill("ggkp3_" + s + "_vs_all", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[b]);
                            MyFill("ggbp3_" + S + "_vs_all", 8192, 0, 8191, ev.CrystalE[b], 8192, 0, 8191, ev.CrystalE[k]);
                        }
                    }//closes b5
	   	 		}//closes plus3 cut
			}//closes nLong
        }//closes k3
	}//closes j16   
}//closes MakeCutHisto

/*Runs a list of files given from a RunMusher/Collector class*/
void SFPPlotter::Run(vector<TString> files, string output) {
  Chain(files);
  chain->SetBranchAddress("event", &event_address);
  TFile *outfile = new TFile(output.c_str(), "RECREATE");

  long blentries = chain->GetEntries();
  if(m_pb) SetProgressBar(blentries);
  cout<<"Total number of events: "<<blentries<<endl;
  long count=0, flush=blentries*0.1, nflushes=0;
  for(long double i=0; i<chain->GetEntries(); i++) {
    count++;
    if(count == flush) {
      if(m_pb) {
        m_pb->Increment(count);
        gSystem->ProcessEvents();
        count = 0;
      } else {
        nflushes++;
        count=0;
        std::cout<<"\rPercent of data processed: "<<nflushes*10<<"%"<<std::flush;
      }
    }
    chain->GetEntry(i);
    MakeUncutHistograms(*event_address);
    if(cutFlag) MakeCutHistograms(*event_address);
  }
  cout<<endl;
  outfile->cd();
  rootObj->Write();
  delete rootObj;
  outfile->Close();
  delete outfile;
}

/*Link all files*/
void SFPPlotter::Chain(vector<TString> files) {
  for(unsigned int i=0; i<files.size(); i++) {
    chain->Add(files[i]); 
  }
}


void SFPPlotter::SetProgressBar(long total) {
  m_pb->SetMax(total);
  m_pb->SetMin(0);
  m_pb->SetPosition(0);
  gSystem->ProcessEvents();
}
