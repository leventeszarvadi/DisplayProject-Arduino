#pragma once
#include "./utility/Models/SongData.h"
#include "AbstractSongDataConverter.h"
#include "AbstractRFHandler.h"
#include "Manchester.h"



class ManchesterRFHandler: public AbstractRFHandler
{
public:
	ManchesterRFHandler(AbstractSongDataConverter* dsConverter, int rxPin, int txPin, int speed);

public: // from AstractRFHandler
	bool sendData(SongData songData) override;
	bool receiveData(SongData* receiedSongData) override;

private:
	AbstractSongDataConverter* m_dsConverter;
	bool firstTimeReceive;
};