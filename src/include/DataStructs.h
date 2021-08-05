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
  vector<DetectorHit> detector;
};


struct clovers {
  vector<DetectorHit> crystals;

};

struct BGO {
  vector<DetectorHit> shields;

};

struct CoincEvent {
  catrina neutron[17]; //17th slot is reserved for the RF
  clovers CloverArray[21]; //0-3 cl1, 4-7 cl2, 8-11 cl3, 12-15 c3, 16-19 d4, 20 LEPS
  BGO Shield[3]; //0 = cl3, 1 = cl1, 2 = cl3 (noshield on c3 or d4)
};




struct ProcessedEvent {
  Double_t CrystalE[6] = {-1,-1,-1,-1,-1,-1};
  Double_t CloverChannel[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t Long[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
  Double_t RF[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t nQ[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t nE[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  Double_t TR[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
};

struct FinalEvent {
  //Double_t CrystalE[24] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  //Double_t CrystalE_p3[24] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  //Double_t CrystalE_rp[24] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
};


#endif
