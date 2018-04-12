#pragma once
#include "./utility/Models/SongData.h"
#include "Arduino.h"

class AbstractSongDataConverter
{
public:
	virtual String toString(const SongData& songData) = 0;
	virtual SongData fromString(const String& bytes) = 0;
	virtual SongData fromBytes(const uint8_t * bytes, const int &length) = 0;
};