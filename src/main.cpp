#include "EventBuilder.h"
#include "GWMEventBuilder.h"
#include "Stopwatch.h"

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cerr<<"Incorrect number of command line arguments!"<<std::endl;
		std::cerr<<"Need to specify type of operation (buildSlow, buildFast, etc.) and input file."<<std::endl;
		return 1;
	}

	std::string filename = argv[2];
	std::string operation = argv[1];


	/* DEFAULT Operation Types:
		buildSlow (through slowSort and then analyze) DEPRECATED
		buildFast (start with slowSorted and then fast and analyze) DEPRECATED
		buildAll (all steps through analyze) DEPRECATED
		analyzeSlow (analyze from slowSorted) DEPRECATED
		analyzeFast (analyze from fastSorted) DEPRECATED
		archive (make an archive of raw binary data)
		convert (convert binary archive to root data)
		convertSlow (convert binary arhcive to event slow data)
		convertFast (convert binary archive to event fast data)
		convertSlowA (convert binary archive to analyzed slow event data)
		convertFastA (convert binary archive to analyzed fast event data)
		merge (combine root files)
		plot (generate a default histogram file from analyzed data)
	*/

	GWMEventBuilder theBuilder;
	if(!theBuilder.ReadConfigFile(filename)) {
		return 1;
	}
	Stopwatch timer;
	timer.Start();
	if(operation == "buildAll") {
		std::cout<<"DEPRECATED option, do not use unless you know what you're doing"<<std::endl;
		theBuilder.SetAnalysisType(GWMEventBuilder::BUILD_ALL);
		theBuilder.BuildEvents();
	} else if(operation == "buildSlow") {
		std::cout<<"DEPRECATED option, do not use unless you know what you're doing"<<std::endl;
		theBuilder.SetAnalysisType(GWMEventBuilder::BUILD_SLOW);
		theBuilder.BuildEvents();
	} else if(operation == "buildFast") {
		std::cout<<"DEPRECATED option, do not use unless you know what you're doing"<<std::endl;
		theBuilder.SetAnalysisType(GWMEventBuilder::BUILD_FAST);
		theBuilder.BuildEvents();
	} else if(operation == "analyzeSlow") {
		std::cout<<"DEPRECATED option, do not use unless you know what you're doing"<<std::endl;
		theBuilder.SetAnalysisType(GWMEventBuilder::ANALYZE_SLOW);
		theBuilder.BuildEvents();
	} else if(operation == "analyzeFast") {
		std::cout<<"DEPRECATED option, do not use unless you know what you're doing"<<std::endl;
		theBuilder.SetAnalysisType(GWMEventBuilder::ANALYZE_FAST);
		theBuilder.BuildEvents();
	} else if(operation == "archive") {
		int runNum;
		theBuilder.SetAnalysisType(GWMEventBuilder::ARCHIVE);
		std::cout<<"Enter the run number to be archived: ";
		std::cin>>runNum;
		std::cout<<std::endl;
		theBuilder.ArchiveBinaryFiles(runNum);
	} else if(operation == "convert") {
		theBuilder.SetAnalysisType(GWMEventBuilder::CONVERT);
		theBuilder.ConvertBin2ROOT();
	} else if(operation == "merge") {
		theBuilder.SetAnalysisType(GWMEventBuilder::MERGE);
		theBuilder.MergeROOTFiles();
	} /*else if(operation == "plot") {
		theBuilder.SetAnalysisType(GWMEventBuilder::PLOT);
		theBuilder.PlotHistograms();  JP -- not using
	}*/ else if (operation == "convertSlow"){
		theBuilder.SetAnalysisType(GWMEventBuilder::CONVERT_S);
		theBuilder.Convert2SortedRoot();
	} else if (operation == "convertFast"){
		theBuilder.SetAnalysisType(GWMEventBuilder::CONVERT_F);
		theBuilder.Convert2FastSortedRoot();
	} else if (operation == "convertSlowA"){
		theBuilder.SetAnalysisType(GWMEventBuilder::CONVERT_SA);
		theBuilder.Convert2SlowAnalyzedRoot();
	} else if (operation == "convertFastA"){
		theBuilder.SetAnalysisType(GWMEventBuilder::CONVERT_FA);
		theBuilder.Convert2FastAnalyzedRoot();
	} else {
		std::cerr<<"Unidentified type of operation! Check your first argument."<<std::endl;
		return 1;
	}
	timer.Stop();
	std::cout<<"Elapsed time (ms): "<<timer.GetElapsedMilliseconds()<<std::endl;

	return 0;
}
