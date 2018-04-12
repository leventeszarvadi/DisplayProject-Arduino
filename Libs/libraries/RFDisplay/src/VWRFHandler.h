#pragma once
#include "./utility/Models/SongData.h"
#include "AbstractSongDataConverter.h"
#include "AbstractRFHandler.h"
#include "VirtualWire.h"


class VWRFHandler : public AbstractRFHandler
{
public:
	VWRFHandler(AbstractSongDataConverter* dsConverter, int rxPin, int txPin, int speed);

public: // from AstractRFHandler
	bool sendData(SongData songData) override;
	bool receiveData(SongData* receiedSongData) override;

private:
	AbstractSongDataConverter* m_dsConverter;
	bool firstTimeReceive;
};

