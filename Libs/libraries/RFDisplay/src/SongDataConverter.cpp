#include "SongDataConverter.h"
#pragma once

String SongDataConverter::toString(const SongData& songData)
{
	String mes = "G";

    //GmainNumber/startVerse/endVerse/Version(A,B,C)/

    if (songData.mainNumber > 0 && songData.mainNumber < 1000)
    {
    	mes += String(songData.mainNumber);
    }
    mes += "/";

    if (songData.startVerse > 0 && songData.startVerse < 20)
    {
    	mes += String(songData.startVerse);
    }
	mes += "/";

	if (songData.endVerse > 0 && songData.endVerse < 20)
    {
    	mes += String(songData.endVerse);
    }
	mes += "/";

	if (songData.version >= 'A' && songData.version <= 'C')
    {
    	mes += String(songData.version);
    }
	mes += "/";

	return mes;
}
	
SongData SongDataConverter::fromString(const String& bytes) 
{
    SongData ds;
    int i;

    i=bytes.indexOf('/');
    ds.mainNumber=bytes.substring(1,i).toInt();
    bytes=bytes.substring(i+1);

    i=bytes.indexOf('/');
    ds.startVerse=bytes.substring(0,i).toInt();
    bytes=bytes.substring(i+1);

    i=bytes.indexOf('/');
    ds.endVerse=bytes.substring(0,i).toInt();
    bytes=bytes.substring(i+1);

    i=bytes.indexOf('/');
    if (bytes.substring(0,i).length()!=0)
    {
        ds.version=bytes.substring(0,i).c_str()[0];
    }
    
	return ds;
}

SongData SongDataConverter::fromBytes(const uint8_t* bytes,const int &length) 
{
    String message;
    for (int i=0; i<length; ++i)
    {
        message.concat((char)bytes[i]);
    }
    return fromString(message);
}

