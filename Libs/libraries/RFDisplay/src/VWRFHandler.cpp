#pragma once
#include "VWRFHandler.h"

VWRFHandler::VWRFHandler(AbstractSongDataConverter* dsConverter, int rxPin, int txPin, int speed):
	m_dsConverter(dsConverter)
{	//rx=13, tx=12, speed=4000
	vw_set_rx_pin(rxPin);
  	vw_set_tx_pin(txPin);
  	vw_setup(speed);
  
  	firstTimeReceive=true;
}

bool VWRFHandler::sendData(SongData songData)
{
  	String mes = m_dsConverter->toString(songData);
	return vw_send((uint8_t *)mes.c_str(), mes.length());
}

bool VWRFHandler::receiveData(SongData* receviedSongData)
{
	if (firstTimeReceive)
		vw_rx_start();
	
	uint8_t buflen=VW_MAX_MESSAGE_LEN;
	uint8_t buf[buflen];
	bool receivedDataSuccessful=vw_get_message(buf,&buflen);
	if(receivedDataSuccessful)
	{
		*receviedSongData=m_dsConverter->fromBytes(buf,buflen);
	}
	return receivedDataSuccessful;
}