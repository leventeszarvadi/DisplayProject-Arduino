#pragma once

#include "./utility/Models/SongData.h"

class AbstractRFHandler
{
public:
	virtual bool sendData(SongData songData) = 0;
	virtual bool receiveData(SongData* receiedSongData) = 0;
};