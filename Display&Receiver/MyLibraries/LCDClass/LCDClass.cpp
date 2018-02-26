#include "LCDClass.h"


#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

LCD::LCD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6)
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

	mlcd.begin(16,2);

	//*lcd=  new LiquidCrystal(pin1,pin2,pin3,pin4,pin5,pin6);
}


void LCD::init(){
	mlcd.noBlink();
	//mlcd.blink();
	mlcd.print("Udvozoljuk! :) ");
	delay(2000);
	mlcd.clear();
	mlcd.print("Aldott");
	mlcd.setCursor(3,1);
	mlcd.print("szolgalatot!");
	delay(2000);
	mlcd.clear();
	displayASong(counter);
}

void LCD::displayBlockButtonPushed(){
	if (!inSettings){
		displayBlocked=!displayBlocked;
		refreshDisplayStatus();
	}
	
}

Song LCD::getActualSong()
{
	return actualSong;
}

bool LCD::isDisplayBlocked()
{
	return displayBlocked;
}
void LCD::refreshDisplayStatus()
{
	mlcd.setCursor(14,1);
	displayBlocked ? mlcd.print("B."):mlcd.print("  ");
}

//this diplay a Song
void LCD::displayASong(int songNumber){
	actualSongNumber=songNumber;
	actualSong=songList[songNumber];

	mlcd.clear();
	refreshDisplayStatus();
	mlcd.setCursor(0,0);
	mlcd.print("Enek:");
	if (actualSongNumber+1<10)
	{
		mlcd.setCursor(6,0);
	}
	else
	{
		mlcd.setCursor(5,0);
	}
	mlcd.print(actualSongNumber+1);
	mlcd.setCursor(10,0);
	
	if (actualSong.itWasSetUp)
	{
		if (actualSong.number<100){
			mlcd.setCursor(11,0);
		}
		if (actualSong.number<10)
		{
			mlcd.setCursor(12,0);
		}
		mlcd.print(actualSong.number);
		mlcd.setCursor(14,0);
		mlcd.print(actualSong.version);
		mlcd.setCursor(5,1);
		if (actualSong.startVerse<10){
			mlcd.setCursor(6,1);
		}
		mlcd.print(actualSong.startVerse);
		mlcd.setCursor(7,1);
		mlcd.print("-");
		mlcd.setCursor(8,1);
		if (actualSong.endVerse<10){
			mlcd.setCursor(9,1);
		}
		mlcd.print(actualSong.endVerse);
	}
	else
	{
		mlcd.print("EEE V");
		mlcd.setCursor(5,1);
		mlcd.print("VV");
		mlcd.setCursor(7,1);
		mlcd.print("-");
		mlcd.setCursor(8,1);
		mlcd.print("VV");
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
		if (counter==maxSong)
		{
			counter=0;
		}
		displayASong(counter);	
	}
	
}

void LCD::cancelButtonPushed()
{
	if (inSettings)
	{
		actualSong=actualSongCopy;
		inSettings=false;
		mlcd.noBlink();
		displayASong(actualSongNumber);
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
			counter=maxSong-1;
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
		mlcd.clear();
		mlcd.setCursor(0,0);

		mlcd.print("Enek:");
		if (actualSongNumber+1<10)
		{
			mlcd.setCursor(6,0);
		}
		else
		{
			mlcd.setCursor(5,0);
		}
		mlcd.print(actualSongNumber+1);
		mlcd.setCursor(0,1);
		mlcd.print("S.");
		mlcd.setCursor(10,0);

		mlcd.print("EEE V");
		mlcd.setCursor(5,1);
		mlcd.print("VV");
		mlcd.setCursor(7,1);
		mlcd.print("-");
		mlcd.setCursor(8,1);
		mlcd.print("VV");
	
		mlcd.setCursor(10,0);
		
		if (actualSong.itWasSetUp)
		{
			if (actualSong.number<100){
				mlcd.setCursor(11,0);
			}
			if (actualSong.number<10)
			{
				mlcd.setCursor(12,0);
			}
			mlcd.print(actualSong.number);
			mlcd.setCursor(14,0);
			mlcd.print(actualSong.version);
			mlcd.setCursor(5,1);
			if (actualSong.startVerse!=0)
			{
				if (actualSong.startVerse<10)
				{
					mlcd.setCursor(6,1);
				}
				mlcd.print(actualSong.startVerse);
				mlcd.setCursor(7,1);
				mlcd.print("-");
				mlcd.setCursor(8,1);
				
				if (actualSong.endVerse!=0)
				{
					if (actualSong.endVerse<10)
					{
						mlcd.setCursor(9,1);
					}
					mlcd.print(actualSong.endVerse);
				}
				else
				{
					mlcd.print("VV");
				}
				
			}
			else
			{
				mlcd.print("VV-VV");
			}
		}

		mlcd.setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);	
		mlcd.blink();



	}
	

}

void LCD::OKButtonPushed()
{
	if (inSettings)
	{
		if (correctSettings(actualSong.characterWasSetUp))
		{
			inSettings=false;
			mlcd.noBlink();
			update();
			displayASong(actualSongNumber);
		}
		else
		{
			errorMessage(true);
			mlcd.setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
		}
	}
	
	
}

void LCD::errorMessage(bool active)
{
	mlcd.setCursor(0,1);
	active ? mlcd.print("E."): mlcd.print("S.");
}


void LCD::inSettingsBackButtonPushed()
{
	inSettingActualPosition--;
	if (inSettingActualPosition==-1)
	{
		inSettingActualPosition=7;
	}
	mlcd.setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
}

void LCD::inSettingsNextButtonPushed()
{
	inSettingActualPosition++;
	if (inSettingActualPosition==8)
	{
		inSettingActualPosition=0;
	}
	mlcd.setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
}

bool LCD::correctSettings(bool characterWasSetUp[7])
{
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

void LCD::xButtonPushed(int buttonNumber)
{
	if (inSettings && buttonNumber<10 && buttonNumber>=0 && inSettingActualPosition!=3)
	{
		errorMessage(false);
		mlcd.setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
		if (inSettingActualPosition==4 || inSettingActualPosition == 6)
		{
			if(buttonNumber<2)
			{
				mlcd.print(buttonNumber);
				actualSong.characterWasSetUp[inSettingActualPosition]=true;
				actualCharacters[inSettingActualPosition]=buttonNumber;
				inSettingsNextButtonPushed();
			}
		}
		else
		{
			mlcd.print(buttonNumber);
			actualSong.characterWasSetUp[inSettingActualPosition]=true;
			actualCharacters[inSettingActualPosition]=buttonNumber;
			inSettingsNextButtonPushed();
		}
		mlcd.setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
	}
	
}

void LCD::letterButtonPushed(char letter)
{

	if (inSettingActualPosition==3 && inSettings && letter>='A' && letter<='C')
	{
		errorMessage(false);
		mlcd.setCursor(possiblePosition[inSettingActualPosition].column,possiblePosition[inSettingActualPosition].row);
		mlcd.print(letter);
		actualSong.characterWasSetUp[inSettingActualPosition]=true;

		actualCharacters[inSettingActualPosition]=letter;
		inSettingsNextButtonPushed();
	}
}

void LCD::adminButtonPushed()
{

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

	actualSong.number=number;
	actualSong.startVerse=startVerse;
	actualSong.endVerse=endVerse;
	actualSong.itWasSetUp=true;
	actualSong.version=version;
	songList[actualSongNumber]=actualSong;
}