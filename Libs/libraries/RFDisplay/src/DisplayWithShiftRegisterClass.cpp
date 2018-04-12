#include "DisplayWithShiftRegisterClass.h"


void DisplayWithShiftRegister::processingSong(const SongData &songData)
{
	generatedNumber = 0;
	if (songData.mainNumber>99)
		setValues(1, songData.mainNumber / 100);
	
	if (songData.mainNumber>9)
		setValues(2, songData.mainNumber / 10 % 10);
	
	if (songData.mainNumber>0)
		setValues(3, songData.mainNumber % 10);

	if (songData.version!='_')
		setValues(4, songData.version);

	if (songData.startVerse>9)
		setValues(7, songData.startVerse / 10);
	if (songData.startVerse>0)
		setValues(8, songData.startVerse % 10);
	if (songData.endVerse>9)
		setValues(5, songData.endVerse / 10);
	if (songData.endVerse>0)
		setValues(6, songData.endVerse % 10);
}



void DisplayWithShiftRegister::setValues(int address, int value)
{
	Serial.println("JArok itt is");
	
	switch (address)
	{
		case 1:
		{
				  uint64_t actualNumber = generateBitsForNumbers(value) << 1;
				  generatedNumber = generatedNumber | actualNumber;
				  break;
		}
		case 2:
		{
				  uint64_t actualNumber = generateBitsForNumbers(value) << 9;
				  generatedNumber = generatedNumber | actualNumber;
				  break;
		}
		case 3:
		{
				  uint64_t actualNumber = generateBitsForNumbers(value) << 17;
				  generatedNumber = generatedNumber | actualNumber;
				  break;
		}
		case 4:
		{
				  if (value>='A' && value<='C')
				  {
					  uint64_t actualNumber = generateBitsForLetters(value) << 25;
					  generatedNumber = generatedNumber | actualNumber;
				  }
				  break;
		}
		case 5:
		{
				  if (value == 1)
				  {
				  	 uint64_t actualNumber = 4295032832;
					  
					  generatedNumber = generatedNumber | actualNumber;
				  }
				  break;
		}
		case 6:
		{
				generatedNumber |= (uint64_t)256; //for hypenSegment;
				  uint64_t actualNumber = generateBitsForNumbers(value) << 33;
				  generatedNumber = generatedNumber | actualNumber;
				  break;
		}
		case 7:
		{
				  if (value == 1)
				  {
					 uint64_t actualNumber = 1099511627777;
					  generatedNumber = generatedNumber | actualNumber;
				  }
				  break;
		}
		case 8:
		{
				  uint64_t actualNumber = generateBitsForNumbers(value) << 41;
				  generatedNumber = generatedNumber | actualNumber;
				  break;
		}
	}
	
}

uint64_t DisplayWithShiftRegister::getGeneratedNumber(const SongData &songData)
{
	Serial.print("mainNumber: ");
	Serial.println(songData.mainNumber);
	Serial.print("startVerse: ");
	Serial.println(songData.startVerse);
	Serial.print("endVerse: ");
	Serial.println(songData.endVerse);
	Serial.print("version: ");
	Serial.println(songData.version);

	processingSong(songData);
	return generatedNumber;
}

uint64_t DisplayWithShiftRegister::generateBitsForNumbers(int value)
{
	switch (value)
	{
	case 0:
	{
			  return (uint64_t)number0;
	}
	case 1:
	{
			  return (uint64_t)number1;
	}
	case 2:
	{
			  return (uint64_t)number2;
	}
	case 3:
	{
			  return (uint64_t)number3;
	}
	case 4:
	{
			  return (uint64_t)number4;
	}
	case 5:
	{
			  return (uint64_t)number5;
	}
	case 6:
	{
			  return (uint64_t)number6;
	}
	case 7:
	{
			  return (uint64_t)number7;
	}
	case 8:
	{
			  return (uint64_t)number8;
	}
	case 9:
	{
			  return (uint64_t)number9;
	}

	}
	return 0;
}

uint64_t DisplayWithShiftRegister::generateBitsForLetters(char value)
{
	switch (value)
	{
	case 'A':
	{
				return (uint64_t)characterA;
	}
	case 'B':
	{
				return (uint64_t)characterB;
	}
	case 'C':
	{
				return (uint64_t)characterC;
	}
	}
	return 0;
}