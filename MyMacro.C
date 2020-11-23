
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <vector>
#include <iostream>

#include "etc/CloverCalibration.h" 

//includes the data structures, make sure this is the path to the DataStructs.h from where you execute the macro 
#include "include/DataStructs.h"
#include "include/EventBuilder.h"


//This includes the library... make sure it is the path to the directory from where you execute the macro
R__LOAD_LIBRARY(lib/libSPSDict.so)

void Events() {
	//Open your file, get the tree, etc
	TFile *input = TFile::Open("example/analyzed/run_112.root", "READ");
	TTree *tree = (TTree*) input->Get("Tree");
	ProcessedEvent *pevent = new ProcessedEvent;
	tree->SetBranchAddress("event", &pevent); //pass in as pointer to pointer.

	TFile *output = TFile::Open("calibrated/run_112_cal.root", "RECREATE");
        TTree* outputTree = new TTree("Events", "Events");
	AnalyzedEvent* fevent = new AnalyzedEvent;
	AnalyzedEvent dummy;
        outputTree->Branch("fevent", &fevent);
	double coincWindow = 3e6;
	Long64_t totentries = tree->GetEntries();//Display number of entries.
	cout<<totentries<<" need to be processed!"<<endl;//Lets user know how many entries need to be processed.


	//Setting branches
	/*ROOT requires that for dictionary defined data you pass in a pointer
	 *So we make a pointer to the vector of DPPChannels like so
	 */


	//Make some histos
	TH2F *PSD0 = new TH2F("PSD0","PSD0",8192,0,8191,8192,0,1);
	TH2F *PSD1 = new TH2F("PSD1","PSD1",8192,0,8191,8192,0,1);
	TH2F *PSD2 = new TH2F("PSD2","PSD2",8192,0,8191,8192,0,1);
	TH2F *PSD3 = new TH2F("PSD3","PSD3",8192,0,8191,8192,0,1);
	TH2F *PSD4 = new TH2F("PSD4","PSD4",8192,0,8191,8192,0,1);
	TH2F *PSD5 = new TH2F("PSD5","PSD5",8192,0,8191,8192,0,1);
	TH2F *PSD6 = new TH2F("PSD6","PSD6",8192,0,8191,8192,0,1);
	TH2F *PSD7 = new TH2F("PSD7","PSD7",8192,0,8191,8192,0,1);
	TH2F *PSD8 = new TH2F("PSD8","PSD8",8192,0,8191,8192,0,1);
	TH2F *PSD9 = new TH2F("PSD9","PSD9",8192,0,8191,8192,0,1);
	TH2F *PSD10 = new TH2F("PSD10","PSD10",8192,0,8191,8192,0,1);
	TH2F *PSD11 = new TH2F("PSD11","PSD11",8192,0,8191,8192,0,1);
	TH2F *PSD12 = new TH2F("PSD12","PSD12",8192,0,8191,8192,0,1);
	TH2F *PSD13 = new TH2F("PSD13","PSD13",8192,0,8191,8192,0,1);
	TH2F *PSD14 = new TH2F("PSD14","PSD14",8192,0,8191,8192,0,1);
	TH2F *PSD15 = new TH2F("PSD15","PSD15",8192,0,8191,8192,0,1);
	TH2F *ngLong1 = new TH2F("ngLong1","ngLong1",8192,0,8192,8192,0,8191);
	TH2F *ngRF9 = new TH2F("ngRF9","ngRF9",8192,0,8192,800,-500,-300);
	TH2F *ngTR1 = new TH2F("ngTR1","ngTR1",8192,0,8192,8192,0,1);
//	TH1F *myHist3 = new TH1F("myHist3","MyHist3",16834,0,16833);
//	TH1F *myHist4 = new TH1F("myHist4","MyHist4",16834,0,16833);
//	TH1F *myHist5 = new TH1F("myHist5","MyHist5",16834,0,16833);
//	TH1F *myHist6 = new TH1F("myHist6","MyHist6",16834,0,16833);
	int count = 0;
	for(int i=0; i<tree->GetEntries(); i++) {
		tree->GetEntry(i);
		*fevent = dummy;
		//Loop over hits in the event, using the size of the list
		if(pevent->neutronLong[0] > 0) {
			fevent->TR[0] = (pevent->neutronLong[0] - pevent->neutronShort[0])/pevent->neutronLong[0];
			fevent->nLong[0] = pevent->neutronLong[0];
			fevent->nShort[0] = pevent->neutronShort[0];
			if(pevent->RFTime!=-1){
				fevent->RF[0] = (pevent->neutronTime[0] - pevent->RFTime);
			}
			PSD0->Fill(fevent->nLong[0],fevent->TR[0]);
		}
		if(pevent->neutronLong[1] > 0) {
			fevent->TR[1] = (pevent->neutronLong[1] - pevent->neutronShort[1])/pevent->neutronLong[1];
			fevent->nLong[1] = pevent->neutronLong[1];
			fevent->nShort[1] = pevent->neutronShort[1];
			if(pevent->RFTime!=-1){
				fevent->RF[1] = (pevent->neutronTime[1] - pevent->RFTime);
			}
			PSD1->Fill(fevent->nLong[1],fevent->TR[1]);
		}
		if(pevent->neutronLong[2] > 0) {
			fevent->TR[2] = (pevent->neutronLong[2] - pevent->neutronShort[2])/pevent->neutronLong[2];
			fevent->nLong[2] = pevent->neutronLong[2];
			fevent->nShort[2] = pevent->neutronShort[2];
			if(pevent->RFTime!=-1){
				fevent->RF[2] = (pevent->neutronTime[2] - pevent->RFTime);
			}
			PSD2->Fill(fevent->nLong[2],fevent->TR[2]);
		}
		if(pevent->neutronLong[3] > 0) {
			fevent->TR[3] = (pevent->neutronLong[3] - pevent->neutronShort[3])/pevent->neutronLong[3];
			fevent->nLong[3] = pevent->neutronLong[3];
			fevent->nShort[3] = pevent->neutronShort[3];
			if(pevent->RFTime!=-1){
				fevent->RF[3] = (pevent->neutronTime[3] - pevent->RFTime);
			}
			PSD3->Fill(fevent->nLong[3],fevent->TR[3]);
		}
		if(pevent->neutronLong[4] > 0) {
			fevent->TR[4] = (pevent->neutronLong[4] - pevent->neutronShort[4])/pevent->neutronLong[4];
			fevent->nLong[4] = pevent->neutronLong[4];
			fevent->nShort[4] = pevent->neutronShort[4];
			if(pevent->RFTime!=-1){
				fevent->RF[4] = (pevent->neutronTime[4] - pevent->RFTime);
			}
			PSD4->Fill(fevent->nLong[4],fevent->TR[4]);
		}
		if(pevent->neutronLong[5] > 0) {
			fevent->TR[5] = (pevent->neutronLong[5] - pevent->neutronShort[5])/pevent->neutronLong[5];
			fevent->nLong[5] = pevent->neutronLong[5];
			fevent->nShort[5] = pevent->neutronShort[5];
			if(pevent->RFTime!=-1){
				fevent->RF[5] = (pevent->neutronTime[5] - pevent->RFTime);
			}
			PSD5->Fill(fevent->nLong[5],fevent->TR[5]);
		}
		if(pevent->neutronLong[6] > 0) {
			fevent->TR[6] = (pevent->neutronLong[6] - pevent->neutronShort[6])/pevent->neutronLong[6];
			fevent->nLong[6] = pevent->neutronLong[6];
			fevent->nShort[6] = pevent->neutronShort[6];
			if(pevent->RFTime!=-1){
				fevent->RF[6] = (pevent->neutronTime[6] - pevent->RFTime);
			}
			PSD6->Fill(fevent->nLong[6],fevent->TR[6]);
		}
		if(pevent->neutronLong[7] > 0) {
			fevent->TR[7] = (pevent->neutronLong[7] - pevent->neutronShort[7])/pevent->neutronLong[7];
			fevent->nLong[7] = pevent->neutronLong[7];
			fevent->nShort[7] = pevent->neutronShort[7];
			if(pevent->RFTime!=-1){
				fevent->RF[7] = (pevent->neutronTime[7] - pevent->RFTime);
			}
			PSD7->Fill(fevent->nLong[7],fevent->TR[7]);
		}
		if(pevent->neutronLong[8] > 0) {
			fevent->TR[8] = (pevent->neutronLong[8] - pevent->neutronShort[8])/pevent->neutronLong[8];
			fevent->nLong[8] = pevent->neutronLong[8];
			fevent->nShort[8] = pevent->neutronShort[8];
			if(pevent->RFTime!=-1){
				fevent->RF[8] = (pevent->neutronTime[8] - pevent->RFTime);
			}
			PSD8->Fill(fevent->nLong[8],fevent->TR[8]);
		}
		if(pevent->neutronLong[9] > 0) {
			fevent->TR[9] = (pevent->neutronLong[9] - pevent->neutronShort[9])/pevent->neutronLong[9];
			fevent->nLong[9] = pevent->neutronLong[9];
			fevent->nShort[9] = pevent->neutronShort[9];
			if(pevent->RFTime!=-1){
				fevent->RF[9] = (pevent->neutronTime[9] - pevent->RFTime);
			}
			PSD9->Fill(fevent->nLong[9],fevent->TR[9]);
		}
		if(pevent->neutronLong[10] > 0) {
			fevent->TR[10] = (pevent->neutronLong[10] - pevent->neutronShort[10])/pevent->neutronLong[10];
			fevent->nLong[10] = pevent->neutronLong[10];
			fevent->nShort[10] = pevent->neutronShort[10];
			if(pevent->RFTime!=-1){
				fevent->RF[10] = (pevent->neutronTime[10] - pevent->RFTime);
			}
			PSD10->Fill(fevent->nLong[10],fevent->TR[10]);
		}
		if(pevent->neutronLong[11] > 0) {
			fevent->TR[11] = (pevent->neutronLong[11] - pevent->neutronShort[11])/pevent->neutronLong[11];
			fevent->nLong[11] = pevent->neutronLong[11];
			fevent->nShort[11] = pevent->neutronShort[11];
			if(pevent->RFTime!=-1){
				fevent->RF[11] = (pevent->neutronTime[11] - pevent->RFTime);
			}
			PSD11->Fill(fevent->nLong[11],fevent->TR[11]);
		}
		if(pevent->neutronLong[12] > 0) {
			fevent->TR[12] = (pevent->neutronLong[12] - pevent->neutronShort[12])/pevent->neutronLong[12];
			fevent->nLong[12] = pevent->neutronLong[12];
			fevent->nShort[12] = pevent->neutronShort[12];
			if(pevent->RFTime!=-1){
				fevent->RF[12] = (pevent->neutronTime[12] - pevent->RFTime);
			}
			PSD12->Fill(fevent->nLong[12],fevent->TR[12]);
		}
		if(pevent->neutronLong[13] > 0) {
			fevent->TR[13] = (pevent->neutronLong[13] - pevent->neutronShort[13])/pevent->neutronLong[13];
			fevent->nLong[13] = pevent->neutronLong[13];
			fevent->nShort[13] = pevent->neutronShort[13];
			if(pevent->RFTime!=-1){
				fevent->RF[13] = (pevent->neutronTime[13] - pevent->RFTime);
			}
			PSD13->Fill(fevent->nLong[13],fevent->TR[13]);
		}
		if(pevent->neutronLong[14] > 0) {
			fevent->TR[14] = (pevent->neutronLong[14] - pevent->neutronShort[14])/pevent->neutronLong[14];
			fevent->nLong[14] = pevent->neutronLong[14];
			fevent->nShort[14] = pevent->neutronShort[14];
			if(pevent->RFTime!=-1){
				fevent->RF[14] = (pevent->neutronTime[14] - pevent->RFTime);
			}
			PSD14->Fill(fevent->nLong[14],fevent->TR[14]);
		}
		if(pevent->neutronLong[15] > 0) {
			fevent->TR[15] = (pevent->neutronLong[15] - pevent->neutronShort[15])/pevent->neutronLong[15];
			fevent->nLong[15] = pevent->neutronLong[15];
			fevent->nShort[15] = pevent->neutronShort[15];
			if(pevent->RFTime!=-1){
				fevent->RF[15] = (pevent->neutronTime[15] - pevent->RFTime);
			}
			PSD15->Fill(fevent->nLong[15],fevent->TR[15]);
		}


                for(int j=0; j<6; j++) {
             	   if(pevent->CloverCrystalE[j] > 50) {
		/*	if(pevent->CloverShieldE[j] != 0) {
 	  		        float ComptonWindow = fabs(pevent->CloverShieldTime[j] - pevent->CloverCrystalTime[j]);
			}
                        if(ComptonWindow < coincWindow) return; //Window check, anti-coincidence with shields  */
			if(pevent->CloverCrystalChannel[j] == 0){      
	   		   fevent->CloverCrystalE[j] = ADC_00(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 12){      
	   		   fevent->CloverCrystalE[j] = ADC_12(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
			}
			if(pevent->CloverCrystalChannel[j] == 2){      
	   		   fevent->CloverCrystalE[j] = ADC_02(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 3){      
	   		   fevent->CloverCrystalE[j] = ADC_03(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 4){      
	   		   fevent->CloverCrystalE[j] = ADC_04(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
	/*		if(pevent->CloverCrystalChannel[j] == 5){      
	   		   fevent->CloverCrystalE[j] = ADC_05(pevent->CloverCrystalE[j]);
			} CL2G is double peaking*/ 
			if(pevent->CloverCrystalChannel[j] == 6){      
	   		   fevent->CloverCrystalE[j] = ADC_06(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 7){      
	   		   fevent->CloverCrystalE[j] = ADC_07(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 8){      
	   		   fevent->CloverCrystalE[j] = ADC_08(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 9){      
	   		   fevent->CloverCrystalE[j] = ADC_09(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
 		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 10){      
	   		   fevent->CloverCrystalE[j] = ADC_10(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 11){      
	   		   fevent->CloverCrystalE[j] = ADC_11(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 20){      
	   		   fevent->CloverCrystalE[j] = ADC_20(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 21){      
	   		   fevent->CloverCrystalE[j] = ADC_21(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
			if(pevent->CloverCrystalChannel[j] == 23){      
	   		   fevent->CloverCrystalE[j] = ADC_23(pevent->CloverCrystalE[j]);
		       	   fevent->CloverCrystalChannel[j] = pevent->CloverCrystalChannel[j];
		           fevent->CloverCrystalTime[j] = pevent->CloverCrystalTime[j];
	   		}
		        ngRF9->Fill(fevent->CloverCrystalE[j], fevent->RF[9]);
		        ngLong1->Fill(fevent->CloverCrystalE[j], fevent->nLong[1]);
		        ngTR1->Fill(fevent->CloverCrystalE[j],fevent->TR[1]);
			count++;
	/* Status Update */
	if(!(i%5000))cout<<"\r"<<i<<" Entries Processed";

                   }
	        }
	        outputTree->Fill();
	}
	cout<<"\r"<<totentries<<" Entries Processed";
	cout<<endl<<"Finished!"<<endl;	
	std::cout<<"Number of times in cond: "<<count<<std::endl;



	//Close and write everything
	input->Close();
	output->cd();
	PSD1->Write();
	ngLong1->Write();
	ngTR1->Write();
        output->Write(outputTree->GetName(), TObject::kOverwrite);
	output->Close();

	//Delete the pointer we made for the vector of hits
        delete output;
        delete input;
}
