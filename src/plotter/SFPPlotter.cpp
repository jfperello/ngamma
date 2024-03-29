/*SFPPlotter.h
 *Class for generating histogram files for SPS-SABRE data
 *Intended use case is generating a TChain of multiple analyzed files and making
 *histograms of the larger data set.
 *
 *Created Jan 2020 by GWM
 *Refurbished May 2021 by JFP for CATRiNA/Clover experiments
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
  ncut1_0 = NULL, ncut1_4 = NULL, ncut1_12 = NULL, ncut3_2 = NULL;
  ncut2_0 = NULL, ncut2_4 = NULL, ncut2_12 = NULL, ncut2_2 = NULL;
  ncut3_0 = NULL, ncut3_4 = NULL, ncut3_12 = NULL, ncut1_2 = NULL;
  ncut1_1 = NULL, ncut1_5 = NULL, ncut1_9 = NULL, ncut1_13 = NULL;
  ncut2_1 = NULL, ncut2_5 = NULL, ncut2_9 = NULL, ncut2_13 = NULL;
  ncut3_1 = NULL, ncut3_5 = NULL, ncut3_9 = NULL, ncut3_13 = NULL;
  ncut1_0 = NULL, ncut1_6 = NULL, ncut1_10 = NULL, ncut1_14 = NULL;
  ncut2_0 = NULL, ncut2_6 = NULL, ncut2_10 = NULL, ncut2_14 = NULL;
  ncut3_0 = NULL, ncut3_6 = NULL, ncut3_10 = NULL, ncut3_14 = NULL;
  ncut1_3 = NULL, ncut1_7 = NULL, ncut1_11 = NULL, ncut1_15 = NULL;
  ncut2_3 = NULL, ncut2_7 = NULL, ncut2_11 = NULL, ncut2_15 = NULL;
  ncut3_3 = NULL, ncut3_7 = NULL, ncut3_11 = NULL, ncut3_15 = NULL;
  rp = NULL;
  plus3 = NULL;
  LongRF = NULL;
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



Double_t SFPPlotter::nLong(double y, int i){
	double a[16] = {0.6685,1.0062,0.7253,1.1045,1.2789,1.0657,0.7319,0.7928,0,0.65587,0,0.8279,0.9662,0.8617,0,0.81135};
	double b[16] = {63.8665,-131.7577,-61.9522,66.1090,-356.8736,-652.7368,84.6867,63.9396,0,77.5748,0,-33.01022,48.0059,54.7659,0,86.7395};
	double ph;
	ph = a[i]*y+b[i];
	return(ph);

}
Double_t SFPPlotter::TOF(double y, int i, int j){
	double theta[16] = {0.7223,0.47211,0.24094,0.53169,0.39905,0.66434,0.60223,0.36137,0,0.26641,0.53169,0.79721,0.60223,0.36137,0.26641,0.79721}; //angles in radians
	double d[16] = {0.93131,0.91706,0.92973,0.96139,0.9044,0.89491,0.91706,0.92973,0.91706,0.91073,0.89491,0.89648,0.98039,0.97406,0.96614,0.95664}; //detector distance in cm
	double E3 = 10;            //3he beam incident energy in MeV
	double mn = 1.008664*931.4943;      //neutron mass in MeV/c^2
	double m3 = 3.016029*931.4943;	   //3he mass in MeV/c^2	
	double m26 = 25.992333*931.4943;  //26si mass in MeV/c^2	
	double c0 = 5226.77;      //constants pulled out of E, 939.564766*100/(2*2.998^2);
	double En,Q;
/*-------------------CATRiNA---------------------*/
	if(j==1){ //returns only energy	
		En = c0*pow(d[i],2)/pow(y,2);      //neutron energy in MeV
		return(En); 
	}
	if(j==2){ //returns only Q
		En = c0*(d[i]*d[i])/(y*y);      //neutron energy in MeV
		Q = En - E3 + (m3*E3+mn*En-2*sqrt(m3*mn*E3*En)*cos(theta[i]))/m26; //Q function
		return(Q); 
	}
	else{
		return(y); 
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
       	ncut1_0 = (TCutG*)nCutFile->Get("ncut1_0"), ncut2_0 = (TCutG*)nCutFile->Get("ncut2_0"), ncut3_0 = (TCutG*)nCutFile->Get("ncut3_0"), ncut1_1 = (TCutG*)nCutFile->Get("ncut1_1");
        ncut2_1 = (TCutG*)nCutFile->Get("ncut2_1"), ncut3_1 = (TCutG*)nCutFile->Get("ncut3_1"), ncut1_0 = (TCutG*)nCutFile->Get("ncut1_0"), ncut2_0 = (TCutG*)nCutFile->Get("ncut2_0");
        ncut3_0 = (TCutG*)nCutFile->Get("ncut3_0"), ncut1_3 = (TCutG*)nCutFile->Get("ncut1_3"), ncut2_3 = (TCutG*)nCutFile->Get("ncut2_3"), ncut3_3 = (TCutG*)nCutFile->Get("ncut3_3");
        ncut1_4 = (TCutG*)nCutFile->Get("ncut1_4"), ncut2_4 = (TCutG*)nCutFile->Get("ncut2_4"), ncut3_4 = (TCutG*)nCutFile->Get("ncut3_4"), ncut1_5 = (TCutG*)nCutFile->Get("ncut1_5");
        ncut2_5 = (TCutG*)nCutFile->Get("ncut2_5"), ncut3_5 = (TCutG*)nCutFile->Get("ncut3_5"), ncut1_6 = (TCutG*)nCutFile->Get("ncut1_6"), ncut2_6 = (TCutG*)nCutFile->Get("ncut2_6");
        ncut3_6 = (TCutG*)nCutFile->Get("ncut3_6"), ncut1_7 = (TCutG*)nCutFile->Get("ncut1_7"), ncut2_7 = (TCutG*)nCutFile->Get("ncut2_7"), ncut3_7 = (TCutG*)nCutFile->Get("ncut3_7");
        ncut1_2 = (TCutG*)nCutFile->Get("ncut1_2"), ncut2_2 = (TCutG*)nCutFile->Get("ncut2_2"), ncut3_2 = (TCutG*)nCutFile->Get("ncut3_2"), ncut1_9 = (TCutG*)nCutFile->Get("ncut1_9");
        ncut2_9 = (TCutG*)nCutFile->Get("ncut2_9"), ncut3_9 = (TCutG*)nCutFile->Get("ncut3_9"), ncut1_10 = (TCutG*)nCutFile->Get("ncut1_10"), ncut2_10 = (TCutG*)nCutFile->Get("ncut2_10");
        ncut3_10 = (TCutG*)nCutFile->Get("ncut3_10"), ncut1_11 = (TCutG*)nCutFile->Get("ncut1_11"), ncut2_11 = (TCutG*)nCutFile->Get("ncut2_11"), ncut3_11 = (TCutG*)nCutFile->Get("ncut3_11");
        ncut2_12 = (TCutG*)nCutFile->Get("ncut2_12"), ncut3_12 = (TCutG*)nCutFile->Get("ncut3_12"), ncut1_13 = (TCutG*)nCutFile->Get("ncut1_13"), ncut2_13 = (TCutG*)nCutFile->Get("ncut2_13");
        ncut3_13 = (TCutG*)nCutFile->Get("ncut3_13"), ncut1_14 = (TCutG*)nCutFile->Get("ncut1_14"), ncut2_14 = (TCutG*)nCutFile->Get("ncut2_14"), ncut1_12 = (TCutG*)nCutFile->Get("ncut1_12");
        ncut3_14 = (TCutG*)nCutFile->Get("ncut3_14"), ncut1_15 = (TCutG*)nCutFile->Get("ncut1_15"), ncut2_15 = (TCutG*)nCutFile->Get("ncut2_15"), ncut3_15 = (TCutG*)nCutFile->Get("ncut3_15");
        rootObj->Add(ncut1_0), rootObj->Add(ncut2_0), rootObj->Add(ncut3_0), rootObj->Add(ncut1_1), rootObj->Add(ncut2_1), rootObj->Add(ncut3_1), rootObj->Add(ncut1_0), rootObj->Add(ncut2_0), rootObj->Add(ncut3_0), rootObj->Add(ncut1_3);
        rootObj->Add(ncut2_3), rootObj->Add(ncut3_3), rootObj->Add(ncut1_4), rootObj->Add(ncut2_4), rootObj->Add(ncut3_4), rootObj->Add(ncut1_5), rootObj->Add(ncut2_5), rootObj->Add(ncut3_5), rootObj->Add(ncut1_6), rootObj->Add(ncut2_6), rootObj->Add(ncut3_6);
        rootObj->Add(ncut1_7), rootObj->Add(ncut2_7), rootObj->Add(ncut3_7), rootObj->Add(ncut1_9), rootObj->Add(ncut2_9), rootObj->Add(ncut3_9), rootObj->Add(ncut1_10), rootObj->Add(ncut2_10), rootObj->Add(ncut2_2), rootObj->Add(ncut3_2);
        rootObj->Add(ncut3_10), rootObj->Add(ncut1_11), rootObj->Add(ncut2_11), rootObj->Add(ncut3_11), rootObj->Add(ncut1_12), rootObj->Add(ncut2_12), rootObj->Add(ncut3_12), rootObj->Add(ncut1_13), rootObj->Add(ncut2_13), rootObj->Add(ncut3_13);
        rootObj->Add(ncut3_10), rootObj->Add(ncut1_11), rootObj->Add(ncut1_14), rootObj->Add(ncut2_14), rootObj->Add(ncut3_14), rootObj->Add(ncut1_15), rootObj->Add(ncut2_15), rootObj->Add(ncut3_15), rootObj->Add(ncut1_2);
	rp = (TCutG*)nCutFile->Get("rp"), plus3 = (TCutG*)nCutFile->Get("plus3"), greject = (TCutG*)nCutFile->Get("greject"), LongRF = (TCutG*)nCutFile->Get("LongRF");
    	rootObj->Add(rp),rootObj->Add(plus3), rootObj->Add(greject), rootObj->Add(LongRF);
    }
    if(ncut1_0 != NULL && ncut1_4 != NULL &&
        ncut2_0 != NULL && ncut2_4 != NULL &&
        ncut3_0 != NULL && ncut3_4 != NULL &&
        ncut3_2 != NULL && ncut2_2 != NULL && ncut1_2 != NULL &&
        ncut1_1 != NULL && ncut1_5 != NULL && ncut1_9 != NULL &&
        ncut2_1 != NULL && ncut2_5 != NULL && ncut2_9 != NULL &&
        ncut3_1 != NULL && ncut3_5 != NULL && ncut3_9 != NULL &&
        ncut1_0 != NULL && ncut1_6 != NULL && ncut1_10 != NULL &&
        ncut2_0 != NULL && ncut2_6 != NULL && ncut2_10 != NULL &&
        ncut3_0 != NULL && ncut3_6 != NULL && ncut3_10 != NULL &&
        ncut1_3 != NULL && ncut1_7 != NULL && ncut1_11 != NULL &&
        ncut2_3 != NULL && ncut2_7 != NULL && ncut2_11 != NULL &&
        ncut3_3 != NULL && ncut3_7 != NULL && ncut3_11 != NULL &&
        ncut1_12 != NULL && ncut1_13 != NULL && ncut1_14 != NULL &&
        ncut2_12 != NULL && ncut2_13 != NULL && ncut2_14 != NULL &&
        ncut3_12 != NULL && ncut3_13 != NULL && ncut3_14 != NULL &&
        ncut1_15 != NULL && ncut2_15 != NULL && ncut3_15 != NULL &&
	rp!=NULL && plus3!=NULL && greject != NULL && LongRF != NULL){
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
	for (int j = 0; j < 16; j++) {
		double nQ3 =0, Q = 0, En=0, ph = 0;
    	if (j == 8) continue;
		if(ev.Long[j]> 50){
    		for (int k = 0; k < 3; k++) {
				if(ev.CrystalE[k]> 50){
					std::string s = std::to_string(k);
                    int b = 4*k;
                    int b1 = 4*k + 1;
                    int b2 = 4*k + 2;
                    int b3 = 4*k + 3;
					std::string v = std::to_string(b);
					std::string v1 = std::to_string(b1);
					std::string v2 = std::to_string(b2);
					std::string v3 = std::to_string(b3);
					ph = nLong(ev.Long[j],j);
					MyFill(Form("RF_%d", j), 300, 0, 99, ev.RF[j]);   
       	 			MyFill(Form("PSD_%d", j), 8192, 0, 8191, ph, 1024, 0, 1, ev.TR[j]);
       	 			MyFill(Form("Long_%d", j), 8192, 0, 8191, ph);
           			MyFill("g_" + s, 8192, 0, 8191, ev.CrystalE[k]);
            		MyFill("g_all", 8192, 0, 8191, ev.CrystalE[k]);
            		for (int l = 0; l < 3; l++) { //2D g-g coincidence
                		if (b != k) {
                    		MyFill("ggkb", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[l]);
                    		MyFill("ggbk", 8192, 0, 8191, ev.CrystalE[l], 8192, 0, 8191, ev.CrystalE[k]);
                		}//closes l!=k
            		}//closes l3
					if(checkcutg(Form("ncut3_%d",j),ev.Long[j],ev.TR[j])){
						En = TOF(ev.RF[j],j,1);
						nQ3 = TOF(ev.RF[j],j,2);
						Q = -0.032613*(pow(nQ3,2))+0.816376*(pow(nQ3,1))+0.485893;
        				MyFill(Form("RF3_%d", j), 300, 0, 99, ev.RF[j]);   
       	 				MyFill(Form("PSD3_%d", j), 8192, 0, 8191, ph, 1024, 0, 1, ev.TR[j]);
       	 				MyFill(Form("Long3_%d", j), 8192, 0, 8191, ph);
       	 				MyFill(Form("LongRF3_%d", j), 8192, 0, 8191, ph, 300, 0, 99, ev.RF[j]);
        				MyFill(Form("Q_%d", j),600,-8,1, Q);
	        			MyFill(Form("En_%d", j),600,1,9, En);
                        MyFill("g3_" + s, 8192, 0, 8191, ev.CrystalE[k]);
                		MyFill("g3_all", 8192, 0, 8191, ev.CrystalE[k]);
                		for (int l = 0; l < 3; b++) { //2D g-g coincidence
                    		if (l != k) {
                        		MyFill("ggkb3", 8192, 0, 8191, ev.CrystalE[k], 8192, 0, 8191, ev.CrystalE[l]);
                        	    MyFill("ggbk3", 8192, 0, 8191, ev.CrystalE[l], 8192, 0, 8191, ev.CrystalE[k]);
                    		}
                		}//closes b5
                        MyFill("ngamma3_all", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, Q);
                        MyFill("ngamma3_all_Q", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, nQ3);
                        if (ev.CloverChannel[b] == 0 || ev.CloverChannel[b] == 4 || ev.CloverChannel[b] == 8 || ev.CloverChannel[b1] == 12 || ev.CloverChannel[b2] == 2 || ev.CloverChannel[b2] == 6 || ev.CloverChannel[b2] == 10 || ev.CloverChannel[b3] == 3 || ev.CloverChannel[b3] == 7) {
                            MyFill("ngammac3_all", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, Q);
                            MyFill("ngammac3_all_Q", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, nQ3);
                            if (j != 4 && j != 5 && j != 10 && j != 14) {
                                MyFill("ngammac3s_all", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, Q);
                                MyFill("ngammac3s_all_Q", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, nQ3);
                                MyFill(Form("ngammac3s_%d", j), 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, Q);
                            }
                        }
					    if(checkcutg("LongRF",ev.Long[j],ev.RF[j])){
		 					MyFill("ngamma6_all", 8192, 0 , 8191 , ev.CrystalE[k],600,-9,1, Q);
		 					MyFill("ngamma6_all_Q", 8192, 0 , 8191 , ev.CrystalE[k],600,-9,1, nQ3);
                            if(ev.CloverChannel[b] == 0 || ev.CloverChannel[b] == 4 || ev.CloverChannel[b] == 8 || ev.CloverChannel[b1] == 12 || ev.CloverChannel[b2] == 2 || ev.CloverChannel[b2] == 6 || ev.CloverChannel[b2] == 10 || ev.CloverChannel[b3] == 3 || ev.CloverChannel[b3] == 7) {
                                MyFill("ngammac6_all", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, Q);
                                MyFill("ngammac6_all_Q", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, nQ3);
                                if (j != 4 && j != 5 && j != 10 && j != 14) {
                                    MyFill("ngammac6s_all", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, Q);
                                    MyFill("ngammac6s_all_Q", 8192, 0, 8191, ev.CrystalE[k], 600, -9, 1, nQ3);
                                }
						    }
					    }//closes LongRF
					}//closes ncut3
				}//closes CrystalE>50
        	}//closes k3
		}//closes Long>50
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
