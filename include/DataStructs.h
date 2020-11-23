/*DataStructs.h
 *Data structures for analysis. To be implemented as a dictionary for ROOT in LinkDef
 *Based on: FocalPlane_SABRE.h
 *Gordon M. Oct. 2019
 */
#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

using namespace std;

struct DPPChannel {
  Double_t Timestamp;
  Int_t Channel, Board, Energy, EnergyShort;
  string Name;
  Int_t Flags;
};

struct DetectorHit {
  Double_t Long=-1, Time=-1, Short=-1;
  Int_t Ch=-1;
};


struct catrina {
  vector<DetectorHit> detector0,detector1,detector2,detector3,detector4,detector5,detector6,detector7;
  vector<DetectorHit> detector8,detector9,detector10,detector11,detector12,detector13,detector14,detector15,RF;
};


struct clovers {
  vector<DetectorHit> crystals;
  vector<DetectorHit> shields;

};

struct CoincEvent {
  catrina neutron;
  clovers CloverArray[6]; //0 = cl3, 1 = cl1, 2 = c3 (noshield on c3)
};




struct ProcessedEvent {



  Double_t CloverCrystalE[6] = {-1,-1,-1,-1,-1,-1}, CloverShieldE[6] = {-1,-1,-1,-1,-1,-1};
  Double_t CloverCrystalChannel[6] = {-1,-1,-1,-1,-1,-1}, CloverShieldChannel[6] = {-1,-1,-1,-1,-1,-1};
  Double_t CloverCrystalTime[6] = {-1,-1,-1,-1,-1,-1}, CloverShieldTime[6] = {-1,-1,-1,-1,-1,-1};

  Double_t neutronTime[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t neutronLong[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t neutronShort[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t RFTime = -1, RFLong = -1; 



  clovers CloverArray[6]; //0 = cl3, 1 = cl1, 2 = cl3, 3 = C3, 4=D4, 5= LEPS
};

struct AnalyzedEvent {

  Double_t TR[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t nLong[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t nLong1[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t nLong2[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t nLong3[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t RF[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t RF1[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t RF2[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t RF3[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  Double_t CloverCrystalE[6] = {-1,-1,-1,-1,-1,-1};


};


#endif
