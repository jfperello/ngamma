#include "EventBuilder.h"
#include "FastSort.h"

FastSort::FastSort(float si_windowSize, float ion_windowSize) {
  si_coincWindow = si_windowSize/1.0e3; //given in pico s, want in nano s
  ion_coincWindow = ion_windowSize/1.0e3; 
  event_address = NULL;
}

FastSort::~FastSort() {
  delete event_address;
}

void FastSort::ResetClovers() {
  for(int i=0; i<6; i++) {
    fastEvent.CloverArray[i] = sblank;
  }
}

void FastSort::ResetCATRiNA() {
  for(int i=0; i<17; i++) {
    fastEvent.neutron[16] = fpblank;
  }
}


/*Assign a set of Clover data that falls within the coincidence window of every detector*/

void FastSort::Processdetector(unsigned int detector_index) {
	float RF_coincWindow = ion_coincWindow;
      	for(unsigned int i=0; i<slowEvent.neutron[detector_index].detector.size(); i++) {
  		/*Dump RF hits that dont fall within the fast coincidence window with any CATRiNA detector*/
  		for(unsigned int k=0; k<slowEvent.neutron[16].detector.size(); k++) {
			float RFTime = fabs(slowEvent.neutron[16].detector[k].Time - slowEvent.neutron[detector_index].detector[i].Time);
			if(RFTime < RF_coincWindow) {
  				fastEvent.neutron[detector_index].detector.push_back(slowEvent.neutron[detector_index].detector[i]);
				fastEvent.neutron[16].detector.push_back(slowEvent.neutron[16].detector[k]);
      				//cout<<"RF Check"<<endl;
			}//closes RF window check     
  		}//closes k<RF.size() 
	}//closes i<neutron.detector.Size()
}


void FastSort::ProcessCrystal(unsigned int i) {
	vector<DetectorHit> crystals;
	vector<DetectorHit> shields;
	float BGO_coincWindow = si_coincWindow;
	for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
		if(i<12) {//only cl1, cl2 and cl3 have shields
			if(slowEvent.Shield[i].shields.size() > 0){ 
				for(int b=0; b<3; b++) { //loop over Clover shields
					for(unsigned int b1=0; b1<slowEvent.Shield[b].shields.size(); b1++) {
						/*Dump Clover data that doesnt fall outside the fast coincidence window with their respected shield*/
						float cloverRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.Shield[b].shields[b1].Time);
      						if(cloverRelTime > BGO_coincWindow) {
        						crystals.push_back(slowEvent.CloverArray[i].crystals[j]);
      							cout<<Form("shield Check for detector : %02d",i)<<endl;
						}//closes BGO window check
					}//closes Shield.shields.size()
				}//closes b3
			}//closes Shield.shields.size()>0
			else{
				crystals.push_back(slowEvent.CloverArray[i].crystals[j]);				
			}
		}//closes if i<12
		else{
			crystals.push_back(slowEvent.CloverArray[i].crystals[j]);
		}//closes else
		//cout<<Form("we are currently in gamma detecter : %02d",i)<<endl;
		fastEvent.CloverArray[i].crystals = crystals; 
	}//closes CloverArray.crystals.size() 
}


std::vector<CoincEvent> FastSort::GetFastEvents(CoincEvent& event) {
	slowEvent = event;
	std::vector<CoincEvent> fast_events;
/* as written, only neutron data that has an RF hit is saved. Only Gamma data that has and RF AND a neutron hit are saved */
	if(slowEvent.neutron[16].detector.size() >0){ //must have an RF hit
    		for(unsigned int k=0;k<16;k++){    	//loop over EJ315
			if(slowEvent.neutron[k].detector.size() == 0) continue; //save time on empties neutrons
        		ResetCATRiNA();
        		Processdetector(k);
			for(int j=0; j<20; j++) { //loop over Clover crystals
				if(slowEvent.CloverArray[j].crystals.size() == 0) continue; //save time on empties clovers
        			ResetClovers();
        			ProcessCrystal(j);
        			fast_events.push_back(fastEvent);
			}//closes j20
      		}//closes k16
    	}//closes RF.size()>0
	return fast_events;
}
