/* The Arrays in the Tree of   *
 * interest are defined below. */

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <vector>
#include <iostream>


//includes the data structures, make sure this is the path to the DataStructs.h from where you execute the macro 
#include "../include/DataStructs.h"
#include "../include/EventBuilder.h"
// #include "EnergyCalibration_1meter_ASH.h" //make sure to attack the correct Energy Calibration (ie, 1 m vs 2 m; 4V vs 2.5V input)

R__LOAD_LIBRARY(../lib/libSPSDict.so)
TFile *cutfile;
/* Declare Cuts Here. *
 * Form:              *
 * TCutG *cutname;    */
TCutG *ncut0;
TCutG *ncut1;
TCutG *ncut2;
TCutG *ncut3;
TCutG *ncut4;
TCutG *ncut5;
TCutG *ncut6;
TCutG *ncut7;
TCutG *ncut8;
TCutG *ncut9;
TCutG *ncut10;
TCutG *ncut11;
TCutG *ncut12;
TCutG *ncut13;
TCutG *ncut14;
TCutG *ncut15;

/* ****************** */


/* Three Cut Reading Functions. */

/* This function reads in the cuts. If you used a different cutfile, *
 * this is the second of two places you need to change the name.     */
Int_t readcuts(const Char_t *cfn="TRcuts.root"){//ReadCuts Begin
	cutfile=new TFile(cfn);
	/* Add in your cuts below. */
	ncut0=(TCutG *) gROOT->FindObject("ncut0");
	ncut1=(TCutG *) gROOT->FindObject("ncut1");
	ncut2=(TCutG *) gROOT->FindObject("ncut2");
	ncut3=(TCutG *) gROOT->FindObject("ncut3");
	ncut4=(TCutG *) gROOT->FindObject("ncut4");
	ncut5=(TCutG *) gROOT->FindObject("ncut5");
	ncut6=(TCutG *) gROOT->FindObject("ncut6");
	ncut7=(TCutG *) gROOT->FindObject("ncut7");
	ncut8=(TCutG *) gROOT->FindObject("ncut8");
	ncut9=(TCutG *) gROOT->FindObject("ncut9");
	ncut10=(TCutG *) gROOT->FindObject("ncut10");
	ncut11=(TCutG *) gROOT->FindObject("ncut11");
	ncut12=(TCutG *) gROOT->FindObject("ncut12");
	ncut13=(TCutG *) gROOT->FindObject("ncut13");
	ncut14=(TCutG *) gROOT->FindObject("ncut14");
	ncut15=(TCutG *) gROOT->FindObject("ncut15");
	/* Close Cutfile */
	cutfile->Close();
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



void Process(TString file){

	/* Declare Histgrams Here           *
	 * Make sure to use the right type. */
	TH2F* TRvL[16];
	TH2F* LongTDC[16];
	TH1F* TDC[16];
	TH1F* nTDC[16];
	TH1F* CloverE;
	TH2F* ngamma[16];
	TH2F* allngamma[16];
	TH2F* Longng[16];

	/* ********************** */
	//Open your file, get the tree, etc
	TFile *input = TFile::Open(file, "READ");
	TTree *tree = (TTree*) input->Get("Events");
	AnalyzedEvent *fevent = new AnalyzedEvent;
	tree->SetBranchAddress("fevent", &fevent); //pass in as pointer to pointer.

/*	TFile *output = TFile::Open("run_21_gated.root", "RECREATE");
        TTree* outputTree = new TTree("gEvents", "gEvents");
	xEvent* gevent = new AnalyzedEvent;
	xEvent dummy;
        outputTree->Branch("gevent", &gevent);*/
	Long64_t totentries = tree->GetEntries();//Display number of entries.
	cout<<"Opened "<<file<<endl;//Lets user know that the file has been opened.
	cout<<totentries<<" need to be processed!"<<endl;//Lets user know how many entries need to be processed.
	/* Sets up all the relevant branches. */

	/* Reading in the cutfile. If you used a   *
	 * different cutfile, this is the first of *
	 * two places where you need to rename it. */
	readcuts("TRcuts.root");
	
	/* Initializing Histograms. *
	 * Again, make sure to use  *
         * the correct type.        */
	for(int i=0;i<16;i++){//Init Begin
		TRvL[i]  = new TH2F(Form("TRvL_%02d",i),Form("Tail Ratio vs Long %02d",i),4096,0,8191,1028,0,1);
		LongTDC[i]  = new TH2F(Form("LongTDC_%02d",i),Form(" Long vs TDC all%02d",i),400,-500,-300,4096,0,8191);
		TDC[i]  = new TH1F(Form("TDC_%02d",i),Form("Timing Spectrum %02d",i),400,-500,-300);
		nTDC[i]  = new TH1F(Form("nTDC_%02d",i),Form("Gated Timing Spectrum nCut %02d",i),400,-500,-300);
		ngamma[i]  = new TH2F(Form("ngamma_%02d",i),Form("nTDC vs CrystalEnergy %02d",i),8192,0,8191,400,-500,-300);
		allngamma[i]  = new TH2F(Form("allngamma_%02d",i),Form("TDC vs CrystalEnergy %02d",i),8192,0,8191,400,-500,-300);
		Longng[i]  = new TH2F(Form("Longng_%02d",i),Form("nLong vs CrystalEnergy %02d",i),8192,0,8191,4096,0,8191);
		
	}//Init End
	CloverE  = new TH1F("CloverE","CloverE",8192,0,8191);

	
	cout<<"0 Entries Processed";
	
	for(int i=0;i<totentries;i++){//Processing For Begin
		tree->GetEntry(i);//Get an entry for processing
		for(int j=0;j<16;j++){//For j16 Begin
			TRvL[j]->Fill(fevent->nLong[j],fevent->TR[j]);
			for(int k=0; k<6; k++) {
				CloverE->Fill(fevent->CloverCrystalE[k]);
				if(fevent->RF[j] < -50){
					TDC[j]->Fill(fevent->RF[j]);
					allngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 0 */
				if((j==0)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut0",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 1 */
				if((j==1)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut1",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 2 */
				if((j==2)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut2",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 3 */
				if((j==3)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut3",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 4 */
				if((j==4)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut4",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 5 */
				if((j==5)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut5",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 6 */
				if((j==6)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut6",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 7 */
				if((j==7)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut7",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 9 */
				if((j==9)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut9",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 10 */
				if((j==10)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut10",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 11 */
				if((j==11)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut11",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 12 */
				if((j==12)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut12",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 13 */
				if((j==13)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut13",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 14 */
				if((j==14)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut14",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
	//-----------------------------------------------------------------------------------//		
				/* Detector 15 */
				if((j==15)&&(fevent->nLong[j]!=0)&&(checkcutg("ncut15",fevent->nLong[j],fevent->TR[j]))){
					nTDC[j]->Fill(fevent->RF[j]);
					LongTDC[j]->Fill(fevent->RF[j],fevent->nLong[j]);
					ngamma[j]->Fill(fevent->CloverCrystalE[k],fevent->RF[j]);
					Longng[j]->Fill(fevent->CloverCrystalE[k],fevent->nLong[j]);
				}
			}//For k5



				
		}//For j16 end

	
	/* Status Update */
	if(!(i%5000))cout<<"\r"<<i<<" Entries Processed";
	}//Processing For End


	/* End Status Update */
	cout<<"\r"<<totentries<<" Entries Processed";
	cout<<endl<<"Finished!"<<endl;	
	TFile fout("gated/run_114_gated.root","RECREATE");

	/* Write the histograms to the file here. */
	for(int i=0;i<16;i++){//For Write Begin
		TRvL[i]->Write();
		LongTDC[i]->Write();
		TDC[i]->Write();
		nTDC[i]->Write();
		ngamma[i]->Write();
		allngamma[i]->Write();
		Longng[i]->Write();
	}
	CloverE->Write();//For Write End

	fout.Close();

}//Process End
