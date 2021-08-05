/*
	ChannelMap.cpp
	Class which acts as the go between for global compass channels (board#*16 + channel) and
	physical detector information. Used in the event builder to assign compass data to real values
	in a simple way. Takes in a definition file and parses it into an unordered_map container.

	Written by G.W. McCann Oct. 2020
	 Updated by JF Perello May 2021 for CATRiNA
*/
#include "EventBuilder.h"
#include "ChannelMap.h"

ChannelMap::ChannelMap() :
	is_valid(false)
{
}

ChannelMap::ChannelMap(std::string& name) :
	is_valid(false)
{
	FillMap(name);
}

ChannelMap::ChannelMap(const char* name) :
	is_valid(false)
{
	std::string filename = name;
	FillMap(filename);
}

ChannelMap::~ChannelMap() {}

bool ChannelMap::FillMap(std::string& name) {
	std::ifstream input(name);
	if(!input.is_open()) {
		is_valid = false;
		return is_valid;
	}
	std::string junk, type, partname;
	int gchan, id;

	std::getline(input, junk);
	std::getline(input, junk);
	Channel this_chan;
	while(input>>gchan) {
		//Set default values
		this_chan.detectorType = -1;
		this_chan.detectorID = -1;
		this_chan.detectorPart = -1;
		input>>id>>type>>partname;
		if(type == "CRYST") {
			this_chan.detectorType = CRYST;
			this_chan.detectorID = id;
			this_chan.detectorPart = std::stoi(partname);
		} else if(type == "SHIELD") {
			this_chan.detectorType = SHIELD;
			this_chan.detectorID = id;
			this_chan.detectorPart = std::stoi(partname);
		} else if (type == "CATRINA") {
			this_chan.detectorType = CATRINA;
			this_chan.detectorID = id;
			this_chan.detectorPart = std::stoi(partname);

		} else if (type =="TRASH"){
			this_chan.detectorType = TRASH;
		}
		

		cmap[gchan] = this_chan;
	}

	input.close();
	is_valid = true;
	return is_valid;
}
