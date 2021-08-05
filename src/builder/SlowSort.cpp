/*SlowSort.cpp
 *Class designed to first time-order raw data, and then based on a given coincidence window
 *sort the raw data into coincidence structures. Utilizes dictionary elements DPPChannel and
 *CoincEvent. Based on work by S. Balak, K. Macon, and E. Good from LSU. 
 *
 *Gordon M. Oct. 2019
 *
 *Refurbished and updated Jan 2020 GWM
 */
#include "EventBuilder.h"
#include "SlowSort.h"

/*Sort the Sabre Data in order of descending energy*/
bool CloverSort(DetectorHit i, DetectorHit j) {
  return (i.Long>j.Long);
}

/*Constructor takes input of coincidence window size, and fills sabre channel map*/
SlowSort::SlowSort() :
  coincWindow(-1.0), eventFlag(false), event(), cmap()
{
  event_stats = new TH2F("coinc_event_stats","coinc_events_stats;global channel;number of coincident hits;counts",144,0,144,20,0,20);
}

SlowSort::SlowSort(double windowSize, string& mapfile) :
  coincWindow(windowSize), eventFlag(false), event(), cmap(mapfile)
{
  event_stats = new TH2F("coinc_event_stats","coinc_events_stats;global channel;number of coincident hits;counts",144,0,144,20,0,20);
  InitVariableMaps();
}

SlowSort::~SlowSort() {
}

/**EXPERIMENT MODS go here**/
void SlowSort::InitVariableMaps() {

    /*For clovers: Each clovers has crystals&shield, so add the partID to the
      CRYST/SHIELD attribute to differentiate*/
    for (int i = 0; i < 21; i++) {
        CloverVMap[CRYST + i] = &event.CloverArray[i].crystals;

    }

    for (int i = 0; i < 3; i++) {
        CloverVMap[SHIELD + i] = &event.Shield[i].shields;
    }

    /*For catrina: Only one catrina array, so each variable is uniquely
      identified by the attribute + its partID
    */
    for (int i = 0; i < 17; i++) {
	fpVMap[CATRINA + i] = &event.neutron[i].detector;
    }

}

/*Reset output structure to blank*/
void SlowSort::Reset() {
  event = blank;
}

bool SlowSort::AddHitToEvent(CompassHit& mhit) {
  DPPChannel curHit;
  curHit.Timestamp = mhit.timestamp;
  curHit.Energy = mhit.lgate;
  curHit.EnergyShort = mhit.sgate;
  curHit.Channel = mhit.channel;
  curHit.Board = mhit.board;
  curHit.Flags = mhit.flags;

  if(hitList.empty()) {
    startTime = curHit.Timestamp;
    hitList.push_back(curHit);
  } else if (curHit.Timestamp < previousHitTime) {
    return false;
  } else if ((curHit.Timestamp - startTime) < coincWindow) {
    hitList.push_back(curHit);
  } else {
    ProcessEvent();
    hitList.clear();
    startTime = curHit.Timestamp;
    hitList.push_back(curHit);
    eventFlag = true;
  }

  return true;
}

void SlowSort::FlushHitsToEvent() {
  if(hitList.empty()) {
    eventFlag = false;
    return;
  }

  ProcessEvent();
  hitList.clear();
  eventFlag = true;
}

CoincEvent SlowSort::GetEvent() {
  eventFlag = false;
  return event;
}

/*Function called when a start of a coincidence event is detected*/
void SlowSort::StartEvent() {
  if(hitList.size() != 0) {
    cerr<<"Attempting to initalize hitList when not cleared!! Check processing order."<<endl;
  }
  startTime = hit.Timestamp;
  hitList.push_back(hit);
}

/*Function called when an event outside the coincidence window is detected
 *Process all of the hits in the list, and write them to the sorted tree
 */
void SlowSort::ProcessEvent() {
  Reset();
  DetectorHit dhit;
  int gchan;
  int size = hitList.size();
  for(DPPChannel& curHit: hitList) {
	gchan = curHit.Channel + curHit.Board*16; //global channel
    	event_stats->Fill(gchan, size);
    	dhit.Time = curHit.Timestamp/1.0e3;
    	dhit.Ch = gchan;
    	dhit.Long = curHit.Energy;
    	dhit.Short = curHit.EnergyShort;
    	auto channel_info = cmap.FindChannel(gchan);
    	if(channel_info == cmap.End()) {
      		continue;
    	}
	if (channel_info->second.detectorType == CRYST || channel_info->second.detectorType == SHIELD) {
            	auto variable = CloverVMap.find(channel_info->second.detectorType + channel_info->second.detectorID);
            	if (variable != CloverVMap.end()) {
                	variable->second->push_back(dhit);
            	}

        }else if (channel_info->second.detectorType == CATRINA) {

            	auto variable = fpVMap.find(channel_info->second.detectorType + channel_info->second.detectorPart);
            	if (variable != fpVMap.end()) {
                	variable->second->push_back(dhit);
            	}

        }else if (channel_info->second.detectorType == TRASH){
			continue;
        } 
	else {
      		std::cerr<<"bleh"<<std::endl;
      		std::cout<<"info: "<<channel_info->second.detectorType<<std::endl;
    	}
}
  //Organize the SABRE data in descending energy order
    for (int s = 0; s < 21; s++) {
        sort(event.CloverArray[s].crystals.begin(), event.CloverArray[s].crystals.end(), CloverSort);
    }
    for (int s = 0; s < 3; s++) {
        sort(event.Shield[s].shields.begin(), event.Shield[s].shields.end(), CloverSort);
    }
}
