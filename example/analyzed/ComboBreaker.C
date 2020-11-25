
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <vector>
#include <iostream>

//clover calibration
#include "../etc/CloverCalibration.h" 

//includes the data structures, make sure this is the path to the DataStructs.h from where you execute the macro 
#include "../include/DataStructs.h"
#include "../include/EventBuilder.h"


//This includes the library... make sure it is the path to the directory from where you execute the macro
R__LOAD_LIBRARY(../lib/libSPSDict.so)

TFile *cutfile;
/* Declare Cuts Here. *
 * Form:              *
 * TCutG *cutname;    */
TCutG *ncut1_0, *ncut2_0, *ncut3_0;
TCutG *ncut1_1, *ncut2_1, *ncut3_1;
TCutG *ncut1_2, *ncut2_2, *ncut3_2;
TCutG *ncut1_3, *ncut2_3, *ncut3_3;
TCutG *ncut1_4, *ncut2_4, *ncut3_4;
TCutG *ncut1_5, *ncut2_5, *ncut3_5;
TCutG *ncut1_6, *ncut2_6, *ncut3_6;
TCutG *ncut1_7, *ncut2_7, *ncut3_7;
TCutG *ncut1_8, *ncut2_8, *ncut3_8;
TCutG *ncut1_9, *ncut2_9, *ncut3_9;
TCutG *ncut1_10, *ncut2_10, *ncut3_10;
TCutG *ncut1_11, *ncut2_11, *ncut3_11;
TCutG *ncut1_12, *ncut2_12, *ncut3_12;
TCutG *ncut1_13, *ncut2_13, *ncut3_13;
TCutG *ncut1_14, *ncut2_14, *ncut3_14;
TCutG *ncut1_15, *ncut2_15, *ncut3_15;


/* ****************** */


/* Three Cut Reading Functions. */

/* This function reads in the cuts. If you used a different cutfile, *
 * this is the second of two places you need to change the name.     */
Int_t readcuts(const Char_t *cfn="PSDcuts.root"){//ReadCuts Begin
	cutfile=new TFile(cfn);
	/* Add in your cuts below. */
	ncut1_0=(TCutG *) gROOT->FindObject("ncut1_0");
	ncut2_0=(TCutG *) gROOT->FindObject("ncut2_0");
	ncut3_0=(TCutG *) gROOT->FindObject("ncut3_0");
	ncut1_1=(TCutG *) gROOT->FindObject("ncut1_1");
	ncut2_1=(TCutG *) gROOT->FindObject("ncut2_1");
	ncut3_1=(TCutG *) gROOT->FindObject("ncut3_1");
	ncut1_0=(TCutG *) gROOT->FindObject("ncut1_0");
	ncut2_0=(TCutG *) gROOT->FindObject("ncut2_0");
	ncut3_0=(TCutG *) gROOT->FindObject("ncut3_0");
	ncut1_3=(TCutG *) gROOT->FindObject("ncut1_3");
	ncut2_3=(TCutG *) gROOT->FindObject("ncut2_3");
	ncut3_3=(TCutG *) gROOT->FindObject("ncut3_3");
	ncut1_4=(TCutG *) gROOT->FindObject("ncut1_4");
	ncut2_4=(TCutG *) gROOT->FindObject("ncut2_4");
	ncut3_4=(TCutG *) gROOT->FindObject("ncut3_4");
	ncut1_5=(TCutG *) gROOT->FindObject("ncut1_5");
	ncut2_5=(TCutG *) gROOT->FindObject("ncut2_5");
	ncut3_5=(TCutG *) gROOT->FindObject("ncut3_5");
	ncut1_6=(TCutG *) gROOT->FindObject("ncut1_6");
	ncut2_6=(TCutG *) gROOT->FindObject("ncut2_6");
	ncut3_6=(TCutG *) gROOT->FindObject("ncut3_6");
	ncut1_7=(TCutG *) gROOT->FindObject("ncut1_7");
	ncut2_7=(TCutG *) gROOT->FindObject("ncut2_7");
	ncut3_7=(TCutG *) gROOT->FindObject("ncut3_7");
	ncut1_8=(TCutG *) gROOT->FindObject("ncut1_8");
	ncut2_8=(TCutG *) gROOT->FindObject("ncut2_8");
	ncut3_8=(TCutG *) gROOT->FindObject("ncut3_8");
	ncut1_9=(TCutG *) gROOT->FindObject("ncut1_9");
	ncut2_9=(TCutG *) gROOT->FindObject("ncut2_9");
	ncut3_9=(TCutG *) gROOT->FindObject("ncut3_9");
	ncut1_10=(TCutG *) gROOT->FindObject("ncut1_10");
	ncut2_10=(TCutG *) gROOT->FindObject("ncut2_10");
	ncut3_10=(TCutG *) gROOT->FindObject("ncut3_10");
	ncut1_11=(TCutG *) gROOT->FindObject("ncut1_11");
	ncut2_11=(TCutG *) gROOT->FindObject("ncut2_11");
	ncut3_11=(TCutG *) gROOT->FindObject("ncut3_11");
	ncut1_12=(TCutG *) gROOT->FindObject("ncut1_12");
	ncut2_12=(TCutG *) gROOT->FindObject("ncut2_12");
	ncut3_12=(TCutG *) gROOT->FindObject("ncut3_12");
	ncut1_13=(TCutG *) gROOT->FindObject("ncut1_13");
	ncut2_13=(TCutG *) gROOT->FindObject("ncut2_13");
	ncut3_13=(TCutG *) gROOT->FindObject("ncut3_13");
	ncut1_14=(TCutG *) gROOT->FindObject("ncut1_14");
	ncut2_14=(TCutG *) gROOT->FindObject("ncut2_14");
	ncut3_14=(TCutG *) gROOT->FindObject("ncut3_14");
	ncut1_15=(TCutG *) gROOT->FindObject("ncut1_15");
	ncut2_15=(TCutG *) gROOT->FindObject("ncut2_15");
	ncut3_15=(TCutG *) gROOT->FindObject("ncut3_15");

	/* Close Cutfile */
	//cutfile->Close(); //no need to close cutfile
	return 0;}//ReadCuts End

/* This function checks to see if the cut exists. */
Bool_t cexists(const Char_t *cutname){//Existence Begin
	Bool_t returnvalue=kFALSE;
	if(gROOT->FindObjectClassName(cutname)) returnvalue=kTRUE;
	else {std::cout<<cutname<<" "<<"cut not found"<<std::endl;}
	return returnvalue;}//Existence End

/* This function checks whether something is in the cut or not. */
Bool_t checkcutg(const Char_t *cutname, Float_t x, Float_t y)
{
	Bool_t returnvalue=kFALSE;
	if(cexists(cutname)){
		TCutG *gcut=(TCutG *) gROOT->GetListOfSpecials()->FindObject(cutname);
		if (gcut->IsInside(x,y)==1) returnvalue=kTRUE;
		return returnvalue;
	} else{
		return returnvalue;
	}
}


void ComboBreaker(TString file) {
	//Open your file, get the tree, etc
	TFile *input = TFile::Open(file, "READ");
	TFile *output = TFile::Open("combobreaker/"+file, "RECREATE");
	TTree *tree = (TTree*) input->Get("Tree");
        TTree* outputTree = new TTree("Events", "Events");

	/*ROOT requires that for dictionary defined data you pass in a pointer
	 *So we make a pointer to the vector of DPPChannels like so*/
	ProcessedEvent *pevent = new ProcessedEvent;
	AnalyzedEvent* fevent = new AnalyzedEvent;
	AnalyzedEvent dummy; //used to reset tree

	//Setting branches
	tree->SetBranchAddress("event", &pevent); //pass in as pointer to pointer.
        outputTree->Branch("fevent", &fevent);



	//Constants
	double coincWindow = 3e6;
	float ComptonWindow=0;
	Long64_t totentries = tree->GetEntries();//Display number of entries.
	cout<<"Opened "<<file<<endl;//Lets user know that the file has been opened.
	cout<<totentries<<" need to be processed!"<<endl;//Lets user know how many entries need to be processed.

	/* Reading in the cutfile. If you used a different cutfile, this is the first of *
	 * two places where you need to rename it. */
	readcuts("PSDcuts.root");

	/* Declare Histgrams Here           *
	 * Make sure to use the right type. */
	TH2F* PSD[16];
	TH2F* ngLong[16];
	TH2F* ngLong1[16];
	TH2F* ngLong2[16];
	TH2F* ngLong3[16];
	TH2F* ngRF[16];
	TH2F* ngRF1[16];
	TH2F* ngRF2[16];
	TH2F* ngRF3[16];
	TH1F* CloverE;
	//Make some histos
	for(int i=0;i<16;i++){
		PSD[i]  = new TH2F(Form("PSD_%02d",i),Form("PSD %02d",i),4096,0,8191,4096,0,1);
		ngLong[i] = new TH2F(Form("ngLong_%02d",i),Form("ngLong_%02d",i),8192,0,8192,8192,0,8191);
		ngLong1[i] = new TH2F(Form("ngLong1_%02d",i),Form("ngLong1_%02d",i),8192,0,8192,8192,0,8191);
		ngLong2[i] = new TH2F(Form("ngLong2_%02d",i),Form("ngLong2_%02d",i),8192,0,8192,8192,0,8191);
		ngLong3[i] = new TH2F(Form("ngLong3_%02d",i),Form("ngLong3_%02d",i),8192,0,8192,8192,0,8191);
		ngRF[i] = new TH2F(Form("ngRF_%02d",i),Form("ngRF_%02d",i),8192,0,8192,800,-500,-300);
		ngRF1[i] = new TH2F(Form("ngRF1_%02d",i),Form("ngRF1_%02d",i),8192,0,8192,800,-500,-300);
		ngRF2[i] = new TH2F(Form("ngRF2_%02d",i),Form("ngRF2_%02d",i),8192,0,8192,800,-500,-300);
		ngRF3[i] = new TH2F(Form("ngRF3_%02d",i),Form("ngRF3_%02d",i),8192,0,8192,800,-500,-300);
	}
	CloverE  = new TH1F("CloverE","CloverE",8192,0,8191);

	int count = 0;

	//Lets user know how many entries need to be processed.

	cout<<totentries<<" need to be processed!"<<endl;
	for(int i=0; i<tree->GetEntries(); i++) {
		tree->GetEntry(i);
		*fevent = dummy;
		//Loop over hits in the event, using the size of the list
		for(int k=0;k<16;k++){
			if(pevent->neutronLong[k] > 10) {
				fevent->TR[k] = (pevent->neutronLong[k] - pevent->neutronShort[k])/pevent->neutronLong[k];
				fevent->nLong[k] = pevent->neutronLong[k];
				PSD[k]->Fill(fevent->nLong[k],fevent->TR[k]);
				if(pevent->RFTime!=-1){
					fevent->RF[k] = (pevent->neutronTime[k] - pevent->RFTime);
					if(checkcutg(Form("ncut1_%d",k),fevent->nLong[k],fevent->TR[k])){
						fevent->nLong1[k] = pevent->neutronLong[k];
						fevent->RF1[k] = (pevent->neutronTime[k] - pevent->RFTime);
					}//closes gate1 condition
					if(checkcutg(Form("ncut1_%d",k),fevent->nLong[k],fevent->TR[k])){
						fevent->nLong2[k] = pevent->neutronLong[k];
						fevent->RF2[k] = (pevent->neutronTime[k] - pevent->RFTime);
					}//closes gate2 condition
					if(checkcutg(Form("ncut1_%d",k),fevent->nLong[k],fevent->TR[k])){
						fevent->nLong3[k] = pevent->neutronLong[k];
						fevent->RF3[k] = (pevent->neutronTime[k] - pevent->RFTime);
					}//closes gate2 condition

				}//closes RF condition


			}//closes neutronLong condition
	
			/* crystal information */
			for(int j=0; j<6; j++) {
				ComptonWindow = 0;
             	  		if(pevent->CloverCrystalE[j] > 50) {
                    		/*	if(pevent->CloverShieldE[j] != 0) {
 	  		        		ComptonWindow = fabs(pevent->CloverShieldTime[j] - pevent->CloverCrystalTime[j]);
					}
                      			if(ComptonWindow < coincWindow) return; //Window check, anti-coincidence with shields  */
					if(pevent->CloverCrystalChannel[j] == 0){      
	   					fevent->CloverCrystalE[j] = ADC_00(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 12){      
	   		   			fevent->CloverCrystalE[j] = ADC_12(pevent->CloverCrystalE[j]);
					}
					if(pevent->CloverCrystalChannel[j] == 2){      
	   		   			fevent->CloverCrystalE[j] = ADC_02(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 3){      
	   		 		 	fevent->CloverCrystalE[j] = ADC_03(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 4){      
	   		   			fevent->CloverCrystalE[j] = ADC_04(pevent->CloverCrystalE[j]);
	   				}
				/*	if(pevent->CloverCrystalChannel[j] == 5){      
	   		   			fevent->CloverCrystalE[j] = ADC_05(pevent->CloverCrystalE[j]);
					} CL2G is double peaking*/ 
					if(pevent->CloverCrystalChannel[j] == 6){      
	   		   			fevent->CloverCrystalE[j] = ADC_06(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 7){      
	   		   			fevent->CloverCrystalE[j] = ADC_07(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 8){      
	   		   			fevent->CloverCrystalE[j] = ADC_08(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 9){      
	   		   			fevent->CloverCrystalE[j] = ADC_09(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 10){      
	   		   			fevent->CloverCrystalE[j] = ADC_10(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 11){      
	   		   			fevent->CloverCrystalE[j] = ADC_11(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 20){      
	   		   			fevent->CloverCrystalE[j] = ADC_20(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 21){      
	   		   			fevent->CloverCrystalE[j] = ADC_21(pevent->CloverCrystalE[j]);
	   				}
					if(pevent->CloverCrystalChannel[j] == 23){      
	   		   			fevent->CloverCrystalE[j] = ADC_23(pevent->CloverCrystalE[j]);
	   				}
					CloverE->Fill(fevent->CloverCrystalE[j]);
		      			ngRF[k]->Fill(fevent->CloverCrystalE[j], fevent->RF[k]);
		      			ngRF1[k]->Fill(fevent->CloverCrystalE[j], fevent->RF1[k]);
		      			ngRF2[k]->Fill(fevent->CloverCrystalE[j], fevent->RF2[k]);
		      			ngRF3[k]->Fill(fevent->CloverCrystalE[j], fevent->RF3[k]);
		        		ngLong[k]->Fill(fevent->CloverCrystalE[j], fevent->nLong[k]);
		        		ngLong1[k]->Fill(fevent->CloverCrystalE[j], fevent->nLong1[k]);
		        		ngLong2[k]->Fill(fevent->CloverCrystalE[j], fevent->nLong2[k]);
		        		ngLong3[k]->Fill(fevent->CloverCrystalE[j], fevent->nLong3[k]);
					count++;
	
					/* Status Update */
					if(!(i%5000))cout<<"\r"<<i<<" Entries Processed";

                   		}//closes Crystal>50
	        	}//closes j6
		}//closes k16
	        outputTree->Fill();

	}//closes i<entries
	cout<<"\r"<<totentries<<" Entries Processed";
	cout<<endl<<"Finished!"<<endl;	
	std::cout<<"Number of times in cond: "<<count<<std::endl;



	//Close and write everything
	input->Close();
	output->cd();
	for(int j=0;j<16;j++){
		PSD[j]->Write();
		ngRF[j]->Write();
		ngRF1[j]->Write();
		ngRF2[j]->Write();
		ngRF3[j]->Write();
		ngLong[j]->Write();
		ngLong1[j]->Write();
		ngLong2[j]->Write();
		ngLong3[j]->Write();
		
	}
        output->Write(outputTree->GetName(), TObject::kOverwrite);
	output->Close();

	//Delete the pointer we made for the vector of hits
        delete output;
        delete input;
}
