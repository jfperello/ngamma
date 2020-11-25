/*SFPAnalyzer.cpp
 *Class designed to analyze coincidence events. Currently only implemented for focal plane
 *data. Additional changes for SABRE would include this file and the sructure ProcessedEvent
 *in DataStructs.h. Based on code written by S. Balak, K. Macon, and E. Good.
 *
 *Gordon M. Oct. 2019
 *
 *Refurbished and updated Jan 2020 by GWM. Now uses both focal plane and SABRE data
 */
#include "EventBuilder.h"
#include "SFPAnalyzer.h"

using namespace std;

/*Constructor takes in kinematic parameters for generating focal plane weights*/
SFPAnalyzer::SFPAnalyzer() {

  event_address = new CoincEvent();
  rootObj = new THashTable();
}

SFPAnalyzer::~SFPAnalyzer() {
  rootObj->Clear();
  delete rootObj;
  delete event_address;
}

void SFPAnalyzer::Reset() {
  pevent = blank; //set output back to blank
}

void SFPAnalyzer::AnalyzeEvent(CoincEvent& cevent) {
    Reset();
    /*CATRiNA parts*/
    if(cevent.neutron.detector0.size() > 0) {
      pevent.neutronLong[0] = cevent.neutron.detector0[0].Long;
      pevent.neutronShort[0] = cevent.neutron.detector0[0].Short;
      pevent.neutronTime[0] = cevent.neutron.detector0[0].Time;
    }
    if(cevent.neutron.detector1.size() > 0) {
      pevent.neutronLong[1] = cevent.neutron.detector1[0].Long;
      pevent.neutronShort[1] = cevent.neutron.detector1[0].Short;
      pevent.neutronTime[1] = cevent.neutron.detector1[0].Time;
    }
    if(cevent.neutron.detector2.size() > 0) {
      pevent.neutronLong[2] = cevent.neutron.detector2[0].Long;
      pevent.neutronShort[2] = cevent.neutron.detector2[0].Short;
      pevent.neutronTime[2] = cevent.neutron.detector2[0].Time;
    }
    if(cevent.neutron.detector3.size() > 0) {
      pevent.neutronLong[3] = cevent.neutron.detector3[0].Long;
      pevent.neutronShort[3] = cevent.neutron.detector3[0].Short;
      pevent.neutronTime[3] = cevent.neutron.detector3[0].Time;
    }
    if(cevent.neutron.detector4.size() > 0) {
      pevent.neutronLong[4] = cevent.neutron.detector4[0].Long;
      pevent.neutronShort[4] = cevent.neutron.detector4[0].Short;
      pevent.neutronTime[4] = cevent.neutron.detector4[0].Time;
    }
    if(cevent.neutron.detector5.size() > 0) {
      pevent.neutronLong[5] = cevent.neutron.detector5[0].Long;
      pevent.neutronShort[5] = cevent.neutron.detector5[0].Short;
      pevent.neutronTime[5] = cevent.neutron.detector5[0].Time;
    }
    if(cevent.neutron.detector6.size() > 0) {
      pevent.neutronLong[6] = cevent.neutron.detector6[0].Long;
      pevent.neutronShort[6] = cevent.neutron.detector6[0].Short;
      pevent.neutronTime[6] = cevent.neutron.detector6[0].Time;
    }
    if(cevent.neutron.detector7.size() > 0) {
      pevent.neutronLong[7] = cevent.neutron.detector7[0].Long;
      pevent.neutronShort[7] = cevent.neutron.detector7[0].Short;
      pevent.neutronTime[7] = cevent.neutron.detector7[0].Time;
    }
    if(cevent.neutron.detector8.size() > 0) {
      pevent.neutronLong[8] = cevent.neutron.detector8[0].Long;
      pevent.neutronShort[8] = cevent.neutron.detector8[0].Short;
      pevent.neutronTime[8] = cevent.neutron.detector8[0].Time;
    }
    if(cevent.neutron.detector9.size() > 0) {
      pevent.neutronLong[9] = cevent.neutron.detector9[0].Long;
      pevent.neutronShort[9] = cevent.neutron.detector9[0].Short;
      pevent.neutronTime[9] = cevent.neutron.detector9[0].Time;
    }
    if(cevent.neutron.detector10.size() > 0) {
      pevent.neutronLong[10] = cevent.neutron.detector10[0].Long;
      pevent.neutronShort[10] = cevent.neutron.detector10[0].Short;
      pevent.neutronTime[10] = cevent.neutron.detector10[0].Time;
    }
    if(cevent.neutron.detector11.size() > 0) {
      pevent.neutronLong[11] = cevent.neutron.detector11[0].Long;
      pevent.neutronShort[11] = cevent.neutron.detector11[0].Short;
      pevent.neutronTime[11] = cevent.neutron.detector11[0].Time;
    }
    if(cevent.neutron.detector12.size() > 0) {
      pevent.neutronLong[12] = cevent.neutron.detector12[0].Long;
      pevent.neutronShort[12] = cevent.neutron.detector12[0].Short;
      pevent.neutronTime[12] = cevent.neutron.detector12[0].Time;
    }
    if(cevent.neutron.detector13.size() > 0) {
      pevent.neutronLong[13] = cevent.neutron.detector13[0].Long;
      pevent.neutronShort[13] = cevent.neutron.detector13[0].Short;
      pevent.neutronTime[13] = cevent.neutron.detector13[0].Time;
    }
    if(cevent.neutron.detector14.size() > 0) {
      pevent.neutronLong[14] = cevent.neutron.detector14[0].Long;
      pevent.neutronShort[14] = cevent.neutron.detector14[0].Short;
      pevent.neutronTime[14] = cevent.neutron.detector14[0].Time;
    }
    if(cevent.neutron.detector15.size() > 0) {
      pevent.neutronLong[15] = cevent.neutron.detector15[0].Long;
      pevent.neutronShort[15] = cevent.neutron.detector15[0].Short;
      pevent.neutronTime[15] = cevent.neutron.detector15[0].Time;
    }
    if(cevent.neutron.RF.size() != 0) {
      pevent.RFLong = cevent.neutron.RF[0].Long;
      pevent.RFTime = cevent.neutron.RF[0].Time;
    }
  
    for(int j=0; j<6; j++) {
      if(cevent.CloverArray[j].crystals.size() != 0) {
        pevent.CloverCrystalE[j] = cevent.CloverArray[j].crystals[0].Long;
        pevent.CloverCrystalChannel[j] = cevent.CloverArray[j].crystals[0].Ch;
        pevent.CloverCrystalTime[j] = cevent.CloverArray[j].crystals[0].Time;
	
      }
      if(cevent.CloverArray[j].shields.size() != 0) {
        pevent.CloverShieldE[j] = cevent.CloverArray[j].shields[0].Long;
        pevent.CloverShieldChannel[j] = cevent.CloverArray[j].shields[0].Ch;
        pevent.CloverShieldTime[j] = cevent.CloverArray[j].shields[0].Time;
      }
      /*Aaaand passes on all of the rest. 4/24/20 GWM*/
      pevent.CloverArray[j] = cevent.CloverArray[j];

    }
}

ProcessedEvent SFPAnalyzer::GetProcessedEvent(CoincEvent& event) {
  AnalyzeEvent(event);
  return pevent;
}

/*Bulk of the work done here*/
void SFPAnalyzer::Run(const char *input, const char *output) {
  TFile* inputFile = new TFile(input, "READ");
  TTree* inputTree = (TTree*) inputFile->Get("SortTree");
  inputTree->SetBranchAddress("event", &event_address);

  TFile* outputFile = new TFile(output, "RECREATE");
  TTree* outputTree = new TTree("Tree", "Tree");
  rootObj->SetOwner(false);//Stops THashTable from owning its members; prevents double delete

  outputTree->Branch("event", "ProcessedEvent", &pevent);
  Float_t place;
  Float_t blentries = inputTree->GetEntries();
  cout<<"Number of entries: "<<blentries<<endl;
  cout<<setprecision(2);
  for(long double i=0; i<inputTree->GetEntries(); i++) {
    inputTree->GetEntry(i);
    place = ((long double)i)/blentries*100;
    /*Non-continuous progress update*/
    if(fmod(place, 10.0) == 0) cout<<"\rPercent of file processed: "<<ceil(place)<<"%"<<flush;
    AnalyzeEvent(*event_address);
    outputTree->Fill();
  }
  cout<<endl;
  outputFile->cd();
  rootObj->Write();
  rootObj->Clear();
  outputTree->Write(outputTree->GetName(), TObject::kOverwrite);
  outputFile->Close();
  inputFile->Close();
  delete outputFile;
  delete inputFile;
}
