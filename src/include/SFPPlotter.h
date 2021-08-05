/*SFPPlotter.h
 *Class for generating histogram files for SPS-SABRE data
 *Intended use case is generating a TChain of multiple analyzed files and making
 *histograms of the larger data set.
 *
 *Created Jan 2020 by GWM
 */

#ifndef SFPCLEANER_H
#define SFPCLEANER_H

#include "DataStructs.h"
#include <TGProgressBar.h>

using namespace std;

class SFPPlotter {
  public:
    SFPPlotter();
    SFPPlotter(bool tf);
    ~SFPPlotter();
    int SetCuts(string cutfilename);
    Double_t TOF(double x, int j, int m);
    Double_t nLong(double x, int j);
    Bool_t cexists(const Char_t* cutname);
    Bool_t checkcutg(const Char_t* cutname, Float_t x, Float_t y);
    inline void AttachProgressBar(TGProgressBar* pb) { m_pb = pb; };
    int ReadCutlist(string& listname);
    void Run(vector<TString> files, string output);

  private:
    void Reset();
    void SetProgressBar(long total);
    void Chain(vector<TString> files); //Form TChain
    void MakeUncutHistograms(ProcessedEvent ev);
    void MakeCutHistograms(ProcessedEvent ev);

    /*Histogram fill wrapper functions*/
    void MyFill(string name, int binsx, double minx, double maxx, double valuex, int binsy, double miny, double maxy, double valuey, int binsz, double minz, double maxz, double valuez);
    void MyFill(string name, int binsx, double minx, double maxx, double valuex, int binsy, double miny, double maxy, double valuey);
    void MyFill(string name, int binsx, double minx, double maxx, double valuex, double valuey, int i);
    void MyFill(string name, int binsx, double minx, double maxx, double valuex);
    void MyFill(string name, double valuex, int i);

    ProcessedEvent *event_address, event, empty;
    FinalEvent fevent,blank;
    /*ROOT Storage*/
    THashTable *rootObj;

    /*Files containing cuts, and actaul cuts... Names should be customized for
     *each individual experiment
     */

    bool cutFlag;
    TFile* nCutFile;
    TCutG* ncut1_0, * ncut2_0, * ncut3_0;
    TCutG* ncut1_1, * ncut2_1, * ncut3_1;
    TCutG* ncut1_2, * ncut2_2, * ncut3_2;
    TCutG* ncut1_3, * ncut2_3, * ncut3_3;
    TCutG* ncut1_4, * ncut2_4, * ncut3_4;
    TCutG* ncut1_5, * ncut2_5, * ncut3_5;
    TCutG* ncut1_6, * ncut2_6, * ncut3_6;
    TCutG* ncut1_7, * ncut2_7, * ncut3_7;
    TCutG* ncut1_8, * ncut2_8, * ncut3_8;
    TCutG* ncut1_9, * ncut2_9, * ncut3_9;
    TCutG* ncut1_10, * ncut2_10, * ncut3_10;
    TCutG* ncut1_11, * ncut2_11, * ncut3_11;
    TCutG* ncut1_12, * ncut2_12, * ncut3_12;
    TCutG* ncut1_13, * ncut2_13, * ncut3_13;
    TCutG* ncut1_14, * ncut2_14, * ncut3_14;
    TCutG* ncut1_15, * ncut2_15, * ncut3_15;
    TCutG* rp, * plus3, * greject, * LongRF;
    TChain* chain;


    TGProgressBar* m_pb; //GUI progress

};

#endif
