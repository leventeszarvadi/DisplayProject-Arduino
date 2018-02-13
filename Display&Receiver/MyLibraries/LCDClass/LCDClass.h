#ifndef LCDClass_h
#define LCDClass_h

#include "LiquidCrystal.h"

const int maxSong=10;
const LiquidCrystal mlcd(6,11,5,4,3,2);

struct Position{
	int column;
	int row;
};

struct Song {
	int number=0;
	int startVerse=0;
	int endVerse=0;
	bool itWasSetUp=false;
	bool characterWasSetUp[7];
};



class LCD{
private:

	Position possiblePosition[7];
	char actualCharacters[7];
	int inSettingActualPosition=0;
	int counter=0;
	Song actualSong;
	Song songList[maxSong];
	int actualSongNumber;
	bool inSettings=false;
	bool displayBlocked=true;
	void blockButtonsInSettingMode(bool block);
	void inSettingsNextButtonPushed();
	void inSettingsBackButtonPushed();
	bool correctSettings(bool characterWassetUp[7]);
	void update();
public:
	LCD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);
	void init();
	void displayBlockButtonPushed ();
	void displayASong(int songNumber);
	void nextButtonPushed();
	void backButtonPushed();
	void settingsButtonPushed();
	void OKButtonPushed();
	void xButtonPushed(int buttonNumber);
};

#endif
