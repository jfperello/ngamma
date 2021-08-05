/*
 *Goal is to provide a fast coinc window for rejecting si.
 *And a way to orgainize focal plane data within slow cw.
 *
 */
#ifndef FASTSORT_H
#define FASTSORT_H

#include "DataStructs.h"
#include <TH2.h>

class FastSort {
  
  public:
    FastSort(float si_windowSize, float ion_windowSize);
    ~FastSort();
    std::vector<CoincEvent> GetFastEvents(CoincEvent& event);

  private:
    void ResetClovers();
    void ResetCATRiNA();
    void Processdetector(unsigned int detector_index);
    void ProcessCrystal(unsigned int detector_index);

    float si_coincWindow, ion_coincWindow;
    CoincEvent *event_address, slowEvent;
    CoincEvent fastEvent, blank;
    clovers sblank;
    catrina fpblank;


};

#endif
