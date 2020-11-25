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
  fastEvent.neutron = fpblank;
}

/*Assign a set of Clover data that falls within the coincidence window of every detector*/

void FastSort::Processdetector0(unsigned int detector0_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector0[detector0_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);
      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector0[detector0_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);
      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector0[detector0_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector0.push_back(slowEvent.neutron.detector0[detector0_index]);
}


void FastSort::Processdetector1(unsigned int detector1_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector1[detector1_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector1[detector1_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector1[detector1_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector1.push_back(slowEvent.neutron.detector1[detector1_index]);

}

void FastSort::Processdetector2(unsigned int detector2_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector2[detector2_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector2[detector2_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector2[detector2_index].Time);
	if(RFTime < 1e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector2.push_back(slowEvent.neutron.detector2[detector2_index]);

}

void FastSort::Processdetector3(unsigned int detector3_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector3[detector3_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector3[detector3_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector3[detector3_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector3.push_back(slowEvent.neutron.detector3[detector3_index]);

}

void FastSort::Processdetector4(unsigned int detector4_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector4[detector4_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector4[detector4_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector4[detector4_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector4.push_back(slowEvent.neutron.detector4[detector4_index]);

}

void FastSort::Processdetector5(unsigned int detector5_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector5[detector5_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector5[detector5_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector5[detector5_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector5.push_back(slowEvent.neutron.detector5[detector5_index]);

}

void FastSort::Processdetector6(unsigned int detector6_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector6[detector6_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector6[detector6_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector6[detector6_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector6.push_back(slowEvent.neutron.detector6[detector6_index]);

}

void FastSort::Processdetector7(unsigned int detector7_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector7[detector7_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector7[detector7_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector7[detector7_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector7.push_back(slowEvent.neutron.detector7[detector7_index]);

}

void FastSort::Processdetector8(unsigned int detector8_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector8[detector8_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector8[detector8_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector8[detector8_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector8.push_back(slowEvent.neutron.detector8[detector8_index]);

}

void FastSort::Processdetector9(unsigned int detector9_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector9[detector9_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector9[detector9_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector9[detector9_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector9.push_back(slowEvent.neutron.detector9[detector9_index]);

}

void FastSort::Processdetector10(unsigned int detector10_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector10[detector10_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector10[detector10_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector10[detector10_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector10.push_back(slowEvent.neutron.detector10[detector10_index]);

}

void FastSort::Processdetector11(unsigned int detector11_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector11[detector11_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector11[detector11_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector11[detector11_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector11.push_back(slowEvent.neutron.detector11[detector11_index]);

}



void FastSort::Processdetector12(unsigned int detector12_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector12[detector12_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector12[detector12_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector12[detector12_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector12.push_back(slowEvent.neutron.detector12[detector12_index]);

}

void FastSort::Processdetector13(unsigned int detector13_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector13[detector13_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector13[detector13_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector13[detector13_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector13.push_back(slowEvent.neutron.detector13[detector13_index]);

}

void FastSort::Processdetector14(unsigned int detector14_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector14[detector14_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector14[detector14_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector14[detector14_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector14.push_back(slowEvent.neutron.detector14[detector14_index]);

}

void FastSort::Processdetector15(unsigned int detector15_index) {
  for(int i=0; i<6; i++) { //loop over Clover crystals
    vector<DetectorHit> crystals;
    vector<DetectorHit> shields;
    /*Dump sabre data that doesnt fall within the fast coincidence window with CATRiNA*/
    for(unsigned int j=0; j<slowEvent.CloverArray[i].crystals.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].crystals[j].Time - slowEvent.neutron.detector15[detector15_index].Time);
      if(sabreRelTime < si_coincWindow) {
        crystals.push_back(slowEvent.CloverArray[i].crystals[j]);


      }
    }
    for(unsigned int j=0; j<slowEvent.CloverArray[i].shields.size(); j++) {
      float sabreRelTime = fabs(slowEvent.CloverArray[i].shields[j].Time - slowEvent.neutron.detector15[detector15_index].Time);
      if(sabreRelTime < si_coincWindow) {
        shields.push_back(slowEvent.CloverArray[i].shields[j]);

      }
    }
  
    fastEvent.CloverArray[i].crystals = crystals;
    fastEvent.CloverArray[i].shields = shields;

  }
  for(unsigned int j=0; j<slowEvent.neutron.RF.size(); j++) {
	float RFTime = fabs(slowEvent.neutron.RF[j].Time - slowEvent.neutron.detector15[detector15_index].Time);
	if(RFTime < 3e3) {
		  fastEvent.neutron.RF.push_back(slowEvent.neutron.RF[j]);
	}     
  }
  fastEvent.neutron.detector15.push_back(slowEvent.neutron.detector15[detector15_index]);

}

std::vector<CoincEvent> FastSort::GetFastEvents(CoincEvent& event) {
  slowEvent = event;
  std::vector<CoincEvent> fast_events;

    //loop over EJ315
    for(unsigned int i=0; i<slowEvent.neutron.detector0.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector0(i);
      fast_events.push_back(fastEvent);      
    }
    for(unsigned int i=0; i<slowEvent.neutron.detector1.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector1(i);
      fast_events.push_back(fastEvent);      
    }
    for(unsigned int i=0; i<slowEvent.neutron.detector2.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector2(i);
      fast_events.push_back(fastEvent);      
    }
  
    for(unsigned int i=0; i<slowEvent.neutron.detector3.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector3(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector4.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector4(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector5.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector5(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector6.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector6(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector7.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector7(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector8.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector8(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector9.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector9(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector10.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector10(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector11.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector11(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector12.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector12(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector13.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector13(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector14.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector14(i);
      fast_events.push_back(fastEvent);      
    }

    for(unsigned int i=0; i<slowEvent.neutron.detector15.size(); i++) {
      ResetClovers();
      ResetCATRiNA();
      Processdetector15(i);
      fast_events.push_back(fastEvent);      
    }
  return fast_events;
}

void FastSort::Run(const char *infile_name, const char *outfile_name) {

  TFile *input = new TFile(infile_name, "READ");
  TTree *intree = (TTree*) input->Get("SortTree");

  TFile *output = new TFile(outfile_name, "RECREATE");
  TTree *outtree = new TTree("SortTree","SortTree");

  intree->SetBranchAddress("event",&event_address);
  
  outtree->Branch("event", &fastEvent);
  Float_t blentries = intree->GetEntries();
  cout<<setprecision(5)<<fixed;
  Float_t place;
  for(ULong64_t i=0; i<intree->GetEntries(); i++) {
    intree->GetEntry(i);
    place = ((long double)i)/blentries*100;
    if(fmod(place,10.0) == 0) {
      std::cout<<"\rPercent of file processed: "<<place<<"%"<<flush;
    }
  }
  cout<<endl;
  input->Close();
  output->cd();
  outtree->Write(outtree->GetName(), TObject::kOverwrite);
  output->Close();
  delete output;
  delete input;
}
