#ifndef PersonalizedLCD_h
#define PersonalizedLCD_h


#include "Arduino.h"
#include "LiquidCrystal.h"
#include "./utility/Models/LCDDisplaySong.h"

const int MAXSONG=15; //

struct Position{
	int column;
	int row;
};

class LCD{
private:
	LiquidCrystal *lcd;
	Position possiblePosition[8];
	char actualCharacters[8];
	int inSettingActualPosition=0;
	int counter=0;
	LCDDisplaySong actualSongCopy;
	LCDDisplaySong actualSong;
	LCDDisplaySong songList[MAXSONG];
	int actualSongNumber;
	bool inSettings=false;
	bool displayBlocked=true;
	bool inDeleteConfirmation=false;
	void initPossiblePositions();
	void inSettingsNextButtonPushed();
	void inSettingsBackButtonPushed();
	bool correctSettings(bool characterWassetUp[7]);
	void update();
	void errorMessage(bool active);
	void refreshDisplayStatus();
	void displayASong(int songNumber);
	void displaySongTemplateA();
	void displaySongTemplateB();
	void deleteAllSong();

public:
	LCD(int rs, int en, int d4, int d5, int d6, int d7);
	void init();
	void displayBlockButtonPushed ();
	void nextButtonPushed();
	void backButtonPushed();
	void settingsButtonPushed();
	void OKButtonPushed();
	void xButtonPushed(int buttonNumber);
	void cancelButtonPushed();
	void letterButtonPushed(char letter);
	bool isDisplayBlocked();
	LCDDisplaySong getActualSong();
	int getActualSongPosition();
	void setSongList(LCDDisplaySong *list);
	void setActualPosition(int position);
	LCDDisplaySong* getSongList();
	int getMaxSongNumber();
	void lcdLoadingDatasFromEEPROM();
	void clearAllSongs();
	bool savingDatasMessage();
};

#endif