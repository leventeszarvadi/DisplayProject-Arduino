#include "PersonalizedLCD.h"


#include <stdio.h>
#include <string.h>

//--------------------------------------------------------
//---------PRIVATE FUNCTIONS------------------------------
//--------------------------------------------------------

void LCD::initPossiblePositions()
{
	possiblePosition[0].column=10;
	possiblePosition[0].row=0;
	possiblePosition[1].column=11;
	possiblePosition[1].row=0;
	possiblePosition[2].column=12;
	possiblePosition[2].row=0;
	possiblePosition[3].column=14;
	possiblePosition[3].row=0;
	possiblePosition[4].column=5;
	possiblePosition[4].row=1;
	possiblePosition[5].column=6;
	possiblePosition[5].row=1;
	possiblePosition[6].column=8;
	possiblePosition[6].row=1;
	possiblePosition[7].column=9;
	possiblePosition[7].row=1;
}

void LCD::inSettingsNextButtonPushed()
{
	inSettingActualPosition++;
	if (inSettingActualPosition==8)
	{
		inSettingActualPosition=0;
	}
	lcd->setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
}

void LCD::inSettingsBackButtonPushed()
{
	inSettingActualPosition--;
	if (inSettingActualPosition==-1)
	{
		inSettingActualPosition=7;
	}
	lcd->setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
}

bool LCD::correctSettings(bool* characterWasSetUp)
{
	if (!characterWasSetUp[2])
		return false;
	if (!characterWasSetUp[2] && characterWasSetUp[1])
		return false;
	if (!characterWasSetUp[1] && characterWasSetUp[0])
		return false;
	if (!characterWasSetUp[2] && characterWasSetUp[3])
		return false;
	if (!characterWasSetUp[2] && (characterWasSetUp[4] || characterWasSetUp[5] || characterWasSetUp[6] || characterWasSetUp[7]))
		return false;
	if (!characterWasSetUp[5] && characterWasSetUp[4])
		return false;
	if (!characterWasSetUp[7] && characterWasSetUp[6])
		return false;
	if ((characterWasSetUp[6] || characterWasSetUp[7]) && (!(characterWasSetUp[4] || characterWasSetUp[5])))
		return false;

	int startVerse=0;
	int endVerse=19;
	if (characterWasSetUp[5])
	{
		startVerse=actualCharacters[5];
		if (characterWasSetUp[4])
		{
			startVerse+=10*actualCharacters[4];
		}
		if (startVerse==0)
			return false;
	}

	if (characterWasSetUp[7])
	{
		endVerse=actualCharacters[7];
		if (characterWasSetUp[6])
		{
			endVerse+=10*actualCharacters[6];
		}
		if (endVerse==0)
			return false;
	}
	return startVerse<endVerse;
}

void LCD::update()
{

	int number=actualCharacters[2];
	int startVerse=0;
	int endVerse=0;
	char version='_';

	if(actualSong.characterWasSetUp[0])
	{
		number+=100*actualCharacters[0]+10*actualCharacters[1];
	}
	else
	{
		if (actualSong.characterWasSetUp[1])
		{
			number+=10*actualCharacters[1];
		}

	}
	if (actualSong.characterWasSetUp[2] && actualSong.characterWasSetUp[3])
	{
		version=actualCharacters[3];
	}

	if (actualSong.characterWasSetUp[5])
	{
		startVerse=actualCharacters[5];
		if (actualSong.characterWasSetUp[4])
		{
			startVerse+=10*actualCharacters[4];
		}
	}

	if (actualSong.characterWasSetUp[7])
	{
		endVerse=actualCharacters[7];
		if (actualSong.characterWasSetUp[6])
		{
			endVerse+=10*actualCharacters[6];
		}
	}	
	actualSong.mainNumber=number;
	actualSong.startVerse=startVerse;
	actualSong.endVerse=endVerse;
	actualSong.itWasSetUp=true;
	actualSong.version=version;
	songList[actualSongNumber]=actualSong;
}

void LCD::errorMessage(bool active)
{
	lcd->setCursor(0,1);
	active ? lcd->print("E."): lcd->print("S.");
}

void LCD::refreshDisplayStatus()
{
	lcd->setCursor(14,1);
	displayBlocked ? lcd->print("B."):lcd->print("  ");
}

void LCD::displayASong(int songNumber)
{
	actualSongNumber=songNumber;
	actualSong=songList[songNumber];
	Serial.println(".................................");
	Serial.println(actualSong.mainNumber);

	lcd->clear();
	refreshDisplayStatus();
	displaySongTemplateA();
	
	
	if (actualSong.itWasSetUp)
	{
		if (actualSong.mainNumber<100)
		{
			lcd->setCursor(11,0);
		}
		if (actualSong.mainNumber<10)
		{
			lcd->setCursor(12,0);
		}
		lcd->print(actualSong.mainNumber);
		lcd->setCursor(14,0);
		lcd->print(actualSong.version);
		lcd->setCursor(5,1);
		if (actualSong.startVerse<10){
			lcd->setCursor(6,1);
		}
		lcd->print(actualSong.startVerse);
		lcd->setCursor(7,1);
		lcd->print("-");
		lcd->setCursor(8,1);
		if (actualSong.endVerse<10){
			lcd->setCursor(9,1);
		}
		lcd->print(actualSong.endVerse);
	}
	else
	{
		displaySongTemplateB();
	}
}

void LCD::displaySongTemplateA()
{
	lcd->setCursor(0,0);
	lcd->print("Enek:");
	if (actualSongNumber+1<10)
	{
		lcd->setCursor(6,0);
	}
	else
	{
		lcd->setCursor(5,0);
	}
	lcd->print(actualSongNumber+1);
	lcd->setCursor(10,0);
}

void LCD::displaySongTemplateB()
{
	lcd->print("EEE V");
	lcd->setCursor(5,1);
	lcd->print("VV");
	lcd->setCursor(7,1);
	lcd->print("-");
	lcd->setCursor(8,1);
	lcd->print("VV");	
}

void LCD::deleteAllSong()
{
	LCDDisplaySong emptySongList[MAXSONG];
	for (int i=0; i<MAXSONG; ++i)
	{
		songList[i]=emptySongList[i];
	}
	counter=0;
	displayASong(counter);
}
//--------------------------------------------------------
//---------PUBLIC FUNCTIONS-------------------------------
//--------------------------------------------------------

LCD::LCD(int rs, int en, int d4, int d5, int d6, int d7)
{
	//(6,11,5,4,3,2)
	lcd = new LiquidCrystal(rs,en,d4,d5,d6,d7);
	lcd->begin(16,2);
	
	initPossiblePositions();		
}

void LCD::init()
{
	/*lcd->noBlink();
	lcd->print("Udvozoljuk! :) ");
	delay(2000);*/
	lcd->clear();
	lcd->print("Aldott");
	lcd->setCursor(3,1);
	lcd->print("szolgalatot!");
	delay(2000);
	lcd->clear();
	displayASong(counter);
}

void LCD::displayBlockButtonPushed()
{
	if (!inSettings){
		displayBlocked=!displayBlocked;
		refreshDisplayStatus();
	}
}

void LCD::nextButtonPushed()
{
	if (inSettings)
	{
		inSettingsNextButtonPushed();
	}
	else
	{
		counter++;
		if (counter==MAXSONG)
		{
			counter=0;
		}
		displayASong(counter);	
	}
	
}

void LCD::backButtonPushed()
{
	if (inSettings)
	{
		inSettingsBackButtonPushed();
	}
	else
	{
		counter--;
		if (counter==-1)
		{
			counter=MAXSONG-1;
		}
		displayASong(counter);	
	}
}

void LCD::settingsButtonPushed()
{	
	if (!inSettings)
	{
		actualSongCopy=actualSong;
		inSettings=true;
		inSettingActualPosition=0;
		lcd->clear();
		
		lcd->setCursor(0,1);
		lcd->print("S.");

		displaySongTemplateA();
		displaySongTemplateB();
	
		lcd->setCursor(10,0);
		
		if (actualSong.itWasSetUp)
		{
			if (actualSong.mainNumber<100){
				lcd->setCursor(11,0);
			}
			if (actualSong.mainNumber<10)
			{
				lcd->setCursor(12,0);
			}
			lcd->print(actualSong.mainNumber);
			lcd->setCursor(14,0);
			lcd->print(actualSong.version);
			lcd->setCursor(5,1);
			if (actualSong.startVerse!=0)
			{
				if (actualSong.startVerse<10)
				{
					lcd->setCursor(6,1);
				}
				lcd->print(actualSong.startVerse);
				lcd->setCursor(7,1);
				lcd->print("-");
				lcd->setCursor(8,1);
				
				if (actualSong.endVerse!=0)
				{
					if (actualSong.endVerse<10)
					{
						lcd->setCursor(9,1);
					}
					lcd->print(actualSong.endVerse);
				}
				else
				{
					lcd->print("VV");
				}
				
			}
			else
			{
				lcd->print("VV-VV");
			}
		}

		lcd->setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);	
		lcd->blink();
	}
}

void LCD::OKButtonPushed()
{
	if (inSettings)
	{
		if (correctSettings(actualSong.characterWasSetUp))
		{
			inSettings=false;
			lcd->noBlink();
			update();
			displayASong(actualSongNumber);
		}
		else
		{
			errorMessage(true);
			lcd->setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
		}
	}
	//else
	//{
	//	if(inDeleteConfirmation)
	//	{
	//		deleteAllSong();
	//		inDeleteConfirmation=false;
	//	}
	//}	
}

void LCD::xButtonPushed(int buttonNumber)
{
	if (inSettings && buttonNumber<10 && buttonNumber>=0 && inSettingActualPosition!=3)
	{
		errorMessage(false);
		lcd->setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
		if (inSettingActualPosition==4 || inSettingActualPosition == 6)
		{
			if(buttonNumber<2)
			{
				lcd->print(buttonNumber);
				actualSong.characterWasSetUp[inSettingActualPosition]=true;
				actualCharacters[inSettingActualPosition]=buttonNumber;
				inSettingsNextButtonPushed();
			}
		}
		else
		{
			lcd->print(buttonNumber);
			actualSong.characterWasSetUp[inSettingActualPosition]=true;
			actualCharacters[inSettingActualPosition]=buttonNumber;
			inSettingsNextButtonPushed();
		}
		lcd->setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
	}
}

void LCD::cancelButtonPushed()
{
	if (inSettings)
	{
		actualSong=actualSongCopy;
		inSettings=false;
		lcd->noBlink();
		displayASong(actualSongNumber);
	}	
}

void LCD::letterButtonPushed(char letter)
{

	if (inSettingActualPosition==3 && inSettings && letter>='A' && letter<='C')
	{
		errorMessage(false);
		lcd->setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
		lcd->print(letter);
		actualSong.characterWasSetUp[inSettingActualPosition]=true;

		actualCharacters[inSettingActualPosition]=letter;
		inSettingsNextButtonPushed();
	}
}

bool LCD::isDisplayBlocked()
{
	return displayBlocked;
}

LCDDisplaySong LCD::getActualSong()
{
	return actualSong;
}

int LCD::getActualSongPosition()
{
	return actualSongNumber;
}

void LCD::setSongList(LCDDisplaySong* list)
{
	for(int i=0; i<MAXSONG; ++i)
	{
		LCDDisplaySong song=list[i];
		for(int i=0; i<8; i++)
		{
			song.characterWasSetUp[i]=false;
		}
		if (song.mainNumber>99)
		{
			song.characterWasSetUp[0]=true;
			song.characterWasSetUp[1]=true;
			song.characterWasSetUp[2]=true;
			song.itWasSetUp=true;
		}
		else
		{
			if (song.mainNumber>9)
			{
				song.characterWasSetUp[1]=true;
				song.characterWasSetUp[2]=true;		
				song.itWasSetUp=true;		
			}
			else
			{
				if(song.mainNumber>0)
				{
					song.characterWasSetUp[2]=true;
					song.itWasSetUp=true;	
				}
			}
		}

		if(song.itWasSetUp)
		{
			if (song.version!='_')
				song.characterWasSetUp[3]=true;
			
			if (song.startVerse>9)
			{
				song.characterWasSetUp[4]=true;
				song.characterWasSetUp[5]=true;
			}
			else
			{
				if (song.startVerse>0)
					song.characterWasSetUp[5]=true;
			}

			if (song.endVerse>9)
			{
				song.characterWasSetUp[6]=true;
				song.characterWasSetUp[7]=true;
			}
			else
			{
				if(song.endVerse>0)
				{
					song.characterWasSetUp[7]=true;
				}
			}
		}

		songList[i]=song;		
	}
}

void LCD::setActualPosition(int position)
{
	actualSongNumber=counter=position;
}

LCDDisplaySong* LCD::getSongList()
{
	return songList;
}

int LCD::getMaxSongNumber()
{
	return MAXSONG;
}

void LCD::lcdLoadingDatasFromEEPROM()
{
	lcd->noBlink();
	lcd->print("Udvozoljuk! :) ");
	delay(2000);
	lcd->clear();
	lcd->print("Adatok");
	lcd->setCursor(3,1);
	lcd->print("betoltese...");
	delay(2000);
}

void LCD::clearAllSongs()
{
	inDeleteConfirmation=true;
	lcd->clear();
	lcd->print("Torol mindent?");
}

bool LCD::savingDatasMessage()
{
	Serial.println("Here");
	if(!inSettings)
	{
		lcd->noBlink();
		lcd->clear();
		lcd->print("Adatok");
		lcd->setCursor(3,1);
		lcd->print("mentese...");
		delay(2000);
		lcd->clear();
		displayASong(actualSongNumber);
		return true;
	}
	return false;
}