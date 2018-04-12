#include "AbstractSongDataConverter.h"
#pragma once

class SongDataConverter : public AbstractSongDataConverter
{
public:
	String toString(const SongData& songData) override;
	SongData fromString(const String& bytes) override;
	SongData fromBytes(const uint8_t * bytes,const int &length) override;
};