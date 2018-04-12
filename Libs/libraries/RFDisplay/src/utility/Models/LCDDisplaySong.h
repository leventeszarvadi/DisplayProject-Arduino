#pragma once
#include "SongData.h"

struct LCDDisplaySong : public SongData 
{
	bool itWasSetUp=false;
	bool characterWasSetUp[8];
};