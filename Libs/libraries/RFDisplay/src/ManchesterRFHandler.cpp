#pragma once
#include "ManchesterRFHandler.h"

ManchesterRFHandler::ManchesterRFHandler(AbstractSongDataConverter* dsConverter, int rxPin, int txPin, int speed)
{
	if (speed<0 || speed>7)
		speed=1;
	man.setupTransmit(txPin, speed);
	man.setupReceive(rxPin, speed);

	firstTimeReceive=true;
}

bool ManchesterRFHandler::sendData(SongData songData)
{
	uint8_t length=8;
	uint8_t transmitArrayData[length];

	transmitArrayData[0]=songData.mainNumber/100;
	transmitArrayData[1]=songData.mainNumber/10%10;
	transmitArrayData[2]=songData.mainNumber%10;

	transmitArrayData[3]=songData.version;

	transmitArrayData[4]=songData.startVerse/10;
	transmitArrayData[5]=songData.startVerse%10;

	transmitArrayData[6]=songData.endVerse/10;
	transmitArrayData[7]=songData.endVerse%10;

	man.transmitArray(length,transmitArrayData);
	return true;

}

bool ManchesterRFHandler::receiveData(SongData* receviedSongData)
{
	uint8_t length=8;
	uint8_t *data;
	if (firstTimeReceive)
	{
		firstTimeReceive=false;
		man.beginReceiveArray(length,data);
	}
	
	if (man.receiveComplete())
	{
		man.beginReceiveArray(length,data);
		receviedSongData->mainNumber=data[0]*100+data[1]*10+data[2];
		receviedSongData->version=data[3];
		receviedSongData->startVerse=data[4]*10+data[5];
		receviedSongData->endVerse=data[6]*10+data[7];
	}
	return false;
}