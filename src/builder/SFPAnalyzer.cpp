/*SFPAnalyzer.cpp
 *Class designed to analyze coincidence events. Currently only implemented for focal plane
 *data. Additional changes for SABRE would include this file and the sructure ProcessedEvent
 *in DataStructs.h. Based on code written by S. Balak, K. Macon, and E. Good.
 *
 *Gordon M. Oct. 2019
 *
 *Refurbished May 2021 by JFP for CATRiNA/Clover experiments
 */
#include "EventBuilder.h"
#include "SFPAnalyzer.h"
#include <TRandom.h>

using namespace std;

/*Constructor takes in kinematic parameters for generating focal plane weights*/
SFPAnalyzer::SFPAnalyzer() {
  rootObj = new THashTable();
  rootObj->SetOwner(false);//THashTable doesnt own members; avoid double delete
  event_address = new CoincEvent();
}

SFPAnalyzer::~SFPAnalyzer() {
  rootObj->Clear();
  delete rootObj;
  delete event_address;
}

void SFPAnalyzer::Reset() {
  pevent = blank; //set output back to blank
}

/*1D histogram fill wrapper*/
void SFPAnalyzer::MyFill(string name, int binsx, double minx, double maxx, double valuex) {
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

/*1D histogram fill wrapper with variable x binning NOTE: see ToF_calibration.h*/
void SFPAnalyzer::MyFill(string name, double valuex, int i) {
    TH1F* histo = (TH1F*)rootObj->FindObject(name.c_str());
    if (i == 1) {
        if (histo != NULL) {
            histo->Fill(valuex);
        }
        else {
            TH1F* h = new TH1F(name.c_str(), name.c_str(), Bins, tEdges);
            h->Fill(valuex);
            rootObj->Add(h);
        }
    }
    if (i == 2) {
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

/*2D histogram fill wrapper*/
void SFPAnalyzer::MyFill(string name, int binsx, double minx, double maxx, double valuex,
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

/*2D histogram fill wrapper with variable y binning NOTE: see ToF_calibration.h*/
void SFPAnalyzer::MyFill(string name, int binsx, double minx, double maxx, double valuex, double valuey, int i) {
    TH2F* histo = (TH2F*)rootObj->FindObject(name.c_str());
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

Double_t SFPAnalyzer::ADC(double y, int i){
	double d1[21] = { 0.3896,0.3371,0.2979,0.2996,0.349,0.3479,0.3426,0.3446,0.3409,0.3386,0.3423,0.34,0,0,0,0,0.4205,0.7993,0,0.8353,0 };
	double d0[21] = { -0.4902,1.3294,0.0664,1.2273,-0.0586,1.2821,-0.4719,0.0708,-0.6398,0.7401,0.9958,-0.3831,0,0,0,0,2.1493,-0.8419,0,-0.4892,0 };
	if (i < 24) {
		return((y - 0.5 + gRandom->Rndm()) * d1[i] + d0[i]); //added randomization between +0.5 to -0.5 for binning 
	}
    else {
 		return(y);
	}
 }

Double_t SFPAnalyzer::TOF(double y, int i, int j){
	double sval[16] = { -97.11,-98.06,-97.8,-97.21,-98.02,-97.99,-111.96,-96.7,0,-97.5,-97.5,-98.59,-96.27,-96.55,-99.5,-96.7 };//gamma pos minus 3.1 for run 8
	double theta[16] = {0.7223,0.47211,0.24094,0.53169,0.39905,0.66434,0.60223,0.36137,0,0.26641,0.53169,0.79721,0.60223,0.36137,0.26641,0.79721}; //angles in radians
	double d[16] = {0.93131,0.91706,0.92973,0.96139,0.9044,0.89491,0.91706,0.92973,0.91706,0.91073,0.89491,0.89648,0.98039,0.97406,0.96614,0.95664}; //detector distance in cm
    double shift = 165;        //timing window in ns
	double E3 = 10;            //3he beam incident energy in MeV
	double mn = 1.008664*931.4943;      //neutron mass in MeV/c^2
	double m3 = 3.016029*931.4943;	   //3he mass in MeV/c^2	
	double m26 = 25.992333*931.4943;  //26si mass in MeV/c^2	
	double c0 = 5222.717;      //constants pulled out of E, 938.5656*100/(2*2.998^2);
	double En,Q,x;
/*-------------------CATRiNA TOF---------------------*/
	if(j==0){ //returns only ToF
		if(y<0){
			if(y<sval[i]){
				y=y-sval[i]+shift;        //shifts values below gamma to other side
				if(y>82.5){
					x=y-82.5;
				}
				else{
					x=y;
				}
			}
			else{
				y=y-sval[i];              //shifts values so that gamma is at 3.1 ns
				if(y>82.5){
					x=y-82.5;
				}
				else{
					x=y;
				}
			}
			return(x);
		}
	}
	if(j==1){ //returns energy only
		if(y<0){
			if(y<sval[i]){
				y=y-sval[i]+shift;        //shifts values below gamma to other side
				if(y>82.5){
					x=y-82.5;
				}
				else{
					x=y;
				}
			}
			else{
				y=y-sval[i];              //shifts values so that gamma is at 3.1 ns
				if(y>82.5){
					x=y-82.5;
				}
				else{
					x=y;
				}
			}
		}
		if(x>10 || x<80){
			En = c0*(d[i]*d[i])/(x*x);      //neutron energy in MeV
		}
		return(En);
	}
	if(j==3){ //returns Q only
		if(y<0){
			if(y<sval[i]){
				y=y-sval[i]+shift;        //shifts values below gamma to other side
				if(y>82.5){
					x=y-82.5;
				}
				else{
					x=y;
				}
			}
			else{
				y=y-sval[i];              //shifts values so that gamma is at 3.1 ns
				if(y>82.5){
					x=y-82.5;
				}
				else{
					x=y;
				}
			}
		}
		if(x>10 || x<80){
			En = c0*(d[i]*d[i])/(x*x);      //neutron energy in MeV
		}
		Q = En - E3 + (m3*E3+mn*En-2*sqrt(m3*mn*E3*En)*cos(theta[i]))/m26; //Q function
		return(Q);
	}
	else{
		return(y);
	}
}

void SFPAnalyzer::AnalyzeEvent(CoincEvent& cevent) {
    Reset();
    //Constants
    srand(time(NULL));
    float ComptonWindow = 0;
    float ngWindow = 0;	
    double Clover[6] = {-1,-1,-1,-1,-1};
    double CloverTime[6] = {-1,-1,-1,-1,-1};
	for (int j = 0; j < 16; j++) { //catrina loop
    	if (j == 8) continue; //detector 8 no bueno
        //if (!cevent.neutron[j].detector.empty()) { //ONLY saves event if catrina det triggered
        if (!cevent.neutron[16].detector.empty() && !cevent.neutron[j].detector.empty()) { //ONLY saves events if RF & catrina det triggered
        	float RFTime = fabs(cevent.neutron[j].detector[0].Time - cevent.neutron[16].detector[0].Time + 300); //300 places the RFTime to within 200 ns
        	if (RFTime > 200) continue; //only care for first 200 ns of rel RF time
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLOVERS Begin~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			for(int a = 0;a<20;a+=4){ //a =0(cl1),4(cl2),8(cl3),12(c3),16(d4)
				int b = a-(3*a)/4;
				double gsize = -1;
				double gsize1 = -1;
		   /*0*/if (cevent.CloverArray[a].crystals.size()>0 && (cevent.CloverArray[a+1].crystals.size()==0 && cevent.CloverArray[a+2].crystals.size()==0 && cevent.CloverArray[a+3].crystals.size()==0)) {
					if (cevent.CloverArray[a].crystals[0].Long > 200) {
						Clover[b] = ADC(cevent.CloverArray[a].crystals[0].Long, a);
						CloverTime[b] = cevent.CloverArray[a].crystals[0].Time;
						pevent.CloverChannel[a] = cevent.CloverArray[a].crystals[0].Ch;
						gsize = cevent.CloverArray[a].crystals.size();
						gsize1 = cevent.CloverArray[a+1].crystals.size();
					}
				}
		   /*1*/else if (cevent.CloverArray[a+1].crystals.size()>0 && (cevent.CloverArray[a].crystals.size()==0 && cevent.CloverArray[a+2].crystals.size()==0 && cevent.CloverArray[a+3].crystals.size()==0)) {
					if (cevent.CloverArray[a + 1].crystals[0].Long > 200) {
						Clover[b] = ADC(cevent.CloverArray[a + 1].crystals[0].Long, a + 1);
						CloverTime[b] = cevent.CloverArray[a + 1].crystals[0].Time;
						pevent.CloverChannel[a + 1] = cevent.CloverArray[a + 1].crystals[0].Ch;
						gsize1 = cevent.CloverArray[a+1].crystals.size();
						gsize = cevent.CloverArray[a].crystals.size();
					}
				}
		   /*2*/else if (cevent.CloverArray[a+2].crystals.size()>0 && (cevent.CloverArray[a+1].crystals.size()==0 && cevent.CloverArray[a].crystals.size()==0 && cevent.CloverArray[a+3].crystals.size()==0)) {
					if (cevent.CloverArray[a + 2].crystals[0].Long > 200) {
						Clover[b] = ADC(cevent.CloverArray[a + 2].crystals[0].Long, a + 2);
						CloverTime[b] = cevent.CloverArray[a + 2].crystals[0].Time;
						pevent.CloverChannel[a + 2] = cevent.CloverArray[a + 2].crystals[0].Ch;
					}
				}
		   /*3*/else if (cevent.CloverArray[a+3].crystals.size()>0 && (cevent.CloverArray[a+1].crystals.size()==0 && cevent.CloverArray[a+2].crystals.size()==0 && cevent.CloverArray[a].crystals.size()==0)) {
					if (cevent.CloverArray[a + 3].crystals[0].Long > 200) {
						Clover[b] = ADC(cevent.CloverArray[a + 3].crystals[0].Long, a + 3);
						CloverTime[b] = cevent.CloverArray[a + 3].crystals[0].Time;
						pevent.CloverChannel[a + 3] = cevent.CloverArray[a + 3].crystals[0].Ch;
					}
				}

				MyFill("gsize", 5, 0, 4,gsize,22,0,21, a); //size of crystals (0,1,2,3,4)
				MyFill("gsizevsgsize1", 5, 0, 4,gsize,5,0,4, gsize1); //size of crystals (0,1,2,3,4)
        		if (Clover[b]!=-1) { //only saves real clover hits 
					MyFill(Form("gE_%02d", b), 8192, 0, 8191, Clover[b]); //Crystals are in Clovers now (0,1,2,3,4)
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BGO VETO BEGIN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					if (b < 3) { // noshields past k = 2
						if (!cevent.Shield[b].shields.empty()) { 
							double bsize = cevent.CloverArray[b].crystals.size();
        	   				ComptonWindow = CloverTime[b] - cevent.Shield[b].shields[0].Time;
							MyFill("bsize", 5, 0, 4,bsize,4,0,3, b); //size of shields (0,1,2)
							MyFill("CloverRelTime", 1000, -3000, 3000, ComptonWindow,12,-1,10,b);
							if(ComptonWindow > 250){//250 ns BGO veto window
								pevent.CrystalE[b] = Clover[b];
							}//closes Compton Check
						}//closes shields.size() !=0
						else{
							pevent.CrystalE[b] = Clover[b];
						}//closes shields.size() !=0 else
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BGO VETO END~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					}//closes k<3
					else{
						pevent.CrystalE[b] = Clover[b];
      	    	 	}//closes k<3 else
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLOVERS End~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CATRINA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					double nsize = cevent.neutron[j].detector.size();
					MyFill("nsize", 5, 0, 4,nsize,17,0,16, j); //size of shields (0,1,2)
					ngWindow = cevent.neutron[j].detector[0].Time - CloverTime[b];
					double PSD = (cevent.neutron[j].detector[0].Long - cevent.neutron[j].detector[0].Short) / cevent.neutron[j].detector[0].Long;
					double RF = TOF(cevent.neutron[j].detector[0].Time - cevent.neutron[16].detector[0].Time + 300, j, 0);
              		MyFill(Form("Long_%02d", j), 8192, 0, 8191, cevent.neutron[j].detector[0].Long);
              		MyFill("ngRelTime",1000 ,-3000, 3000, ngWindow,18,0,17,j);
                	MyFill(Form("TOF_%02d", j), 300, 0, 99, RF);
                	MyFill(Form("RF_%02d", j), 3000, -1500, 1500, cevent.neutron[j].detector[0].Time - cevent.neutron[16].detector[0].Time+300);
            		MyFill(Form("PSD_%02d", j), 8192, 0, 8191, cevent.neutron[j].detector[0].Long, 1024, 0, 1, PSD);
            		pevent.Long[j] = cevent.neutron[j].detector[0].Long;
            		pevent.TR[j] = PSD;
            		pevent.RF[j] = TOF(cevent.neutron[j].detector[0].Time - cevent.neutron[16].detector[0].Time + 300, j, 0);
                    pevent.nE[j] = TOF(cevent.neutron[j].detector[0].Time - cevent.neutron[16].detector[0].Time + 300, j, 1);
                    pevent.nQ[j] = TOF(cevent.neutron[j].detector[0].Time - cevent.neutron[16].detector[0].Time + 300, j, 2);

        		}//closes Clover[b]!=-1
    		}//closes a<20 loop
		}//closes RF size()>0
	}//closes catrina detector j16 

}//closes AnalyzeEvent

ProcessedEvent SFPAnalyzer::GetProcessedEvent(CoincEvent& event) {
  AnalyzeEvent(event);
  return pevent;
}
