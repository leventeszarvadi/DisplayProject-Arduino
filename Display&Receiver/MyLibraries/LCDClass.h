#ifndef DisplayClass_h
#define DisplayClass_h

//#include <iostream>
#include <LiquidCrystal.h>


using namespace std;

const int songsNumber=10;



struct Song
{
	String name;
	int bigNumber;
	int beginSmallNumber;
	int endSmallNumber;	
};


class LCD{
private:
	LiquidCrystal lcd;
	Song songs[songsNumber];
	int rowValue[16];
	bool isClosed;
	bool firstTime;
	bool welcomeMessage;
	String pushedValue;
	int currentColumn;
	int currentSong;
	bool inASongSettings;
	bool settingsQuestion;
	bool settingsMode;
	int actualSongNumber;
	void init();
	void setOneSong(int i);
	void setNewSong(int);
	void displayASong(int i);
public:
	LCD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);
	void pushed(String button);
	void setOneSong(int i,String button);
	void display();
	bool open();
};
void LCD::init()
{
	actualSongNumber=0;
	isClosed=true;
	firstTime=true;
	welcomeMessage=true;
	inASongSettings=false;
	settingsQuestion=true;
	settingsMode=true;
	currentSong=0;
	currentColumn=0;
	for (int i=0; i<songsNumber; i++)
	{
		songs[i].name="Enek "+String(i+1);
		songs[i].bigNumber=0;
		songs[i].beginSmallNumber=0;
		songs[i].endSmallNumber=0;
	}
}

LCD::LCD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6)
{
	lcd.setParameters(pin1,pin2,pin3,pin4,pin5,pin6);
}

void LCD::pushed(String button)//jott egy gombnyomas
{
	if (!isClosed)//ha nincs lezarva
	{
		if (button=="esc")
		{
			isClosed=true;
			lcd.setCursor(0,0);
			lcd.print("Kikapcsolva     ");
			lcd.setCursor(0,1);
			lcd.print("                ");
		}
		else
		{
			if(firstTime)//ha elso alakalom
			{
				if (welcomeMessage)//udvozol, es elkezdi beallitani az enekeket
				{
					lcd.print("Udvozoljuk! :)");
					delay(3000);
					lcd.print("Enekek beallitasa!");
					delay(2000);
					welcomeMessage=false;

					for (int i=0; i<16; i++)
					{
						rowValue[i]=-1;
					}
					setOneSong(currentSong,button);
				}
				else
				{
					if(button!="OK")//ha nem OKE erkezik, azaz meg bealitas alatt van egy enek
					{
						if (settingsMode)
						{
							setOneSong(currentSong,button);
						}
						else
						{
							if(button=="next")
							{
								currentSong++;
							}
							else
							{
								if (button=="back")
								{
									currentSong--;
								}
							}
						}
					}
					else//ha oke erkezik akkor az enek mar be lett alitva
					{
						if (settingsMode)
						{
							setNewSong(currentSong);
							inASongSettings=false;
							currentSong++;
							lcd.noBlink();
						}
						else
						{
							settingsMode=true;
							currentColumn=3;
							lcd.setCursor(currentColumn,1);
							lcd.Blink();
						}
						
						
						if (currentSong!=songsNumber)//ha nem ert el a vegere akkor mfolytatja a beallitast
						{
							setOneSong(currentSong,button);
						}
						else//ha a vegere ert akkor megkerdi, hogy mit szeretne tenni
						{
							if(settingsQuestion)
							{
								lcd.setCursor(0,0);
								lcd.print("Menti a beallitasokat?");
								lcd.setCursor(2,1);
								lcd.print("IGEN");
								lcd.setCursor(8,1);
								lcd.print("VISSZA");
								settingsQuestion=false;
							}
							else
							{
								if (button!="OK")
								{
									settingsQuestion=true;
									currentSong--;
									for (int i=0; i<16; i++)
									{
										rowValue[i]=-1;
									}
									settingsMode=false;
									inASongSettings=false;
									setOneSong(currentSong,button);		

								}
								else//befejezodott a beallitas
								{
									lcd.setCursor(0,0);
									lcd.print("Sikeres beallitas!");
									for(int i=songsNumber-1; i>=0; --i)
									{
										if(songs[i].bigNumber==0)
										{
											actualSongNumber=i;
										}
										else
										{
											break;
										}
									}
									currentSong=0;
									displayASong(currentSong);
									firstTime=false;
								}
							}
			

						}	


					}	
					
				}
			}
			else//nem elso alkalom
			{
				switch(button)
				{
					case "next":
					{
						if(currentSong<actualSongNumber-1)
							currentSong++;
						else
						{
							currentSong=0;
						}
						break;
					}
					case "back":
					{
						if(currentSong>0)
							currentSong--;
						else
						{
							currentSong=actualSongNumber-1;
						}
					}	

				}
			}
		}
					
	}
	else//ha le van zarva
	{
		if (button=="esc")
		{
			
			init();
			isClosed=false;
			pushed("valami");
		}
	}
}



bool LCD::open()
{
	return !isClosed;
}

void LCD::setOneSong(int i, String button)//ez egy adott enek bealitasat vegzi, addig fut mig OKE gombot nem adnak ra
{
			
	if(!inASongSettings)
	{
		lcd.print(songs[i].name+":");
		lcd.setCursor(3, 1);
		lcd.print("EEE");
		lcd.setCursor(8,1);
		lcd.print("VV-VV");

		currentColumn=5;
		int bN=songs[i].bigNumber;
		while(bN!=0)
		{
			setCursor(currentColumn,1);
			lcd.print(bN%10);
			currentColumn--;
			bN=(int)bN/10;
		}
		currentColumn=9;
		int bSN=songs[i].beginSmallNumber;
		while(bSN!=0)
		{
			setCursor(currentColumn,1);
			lcd.print(bSN%10);
			currentColumn--;
			bSN=(int)bSN/10;
		}
		currentColumn=12;
		int eSN=songs[i].endSmallNumber;
		while(eSN!=0)
		{
			setCursor(currentColumn,1);
			lcd.print(eSN%10);
			currentColumn--;
			eSN=(int)eSN/10;
		}
		inASongSettings=true;
		currentColumn=3;
		setCursor(currentColumn,1);
		lcd.blink();
	}
	else//ha mar bealitason van sor
	{
		
		setCursor(currentColumn,1);
		switch (button)
		{
			case "next":
			{
				if (currentColumn<12)//ne tudjon kilepni a kernyobol
				{
					if (currentColumn==5)
						currentColumn+=2;
					if (currentColumn==9)
						currentColumn++;
					currentColumn++;
					setCursor(currentColumn,1);
				}
				break;
			}
			case "back":
			{
				if (currentColumn>3)
				{
					if(currentColumn==11)
						currentColumn--;
					if(currentColumn==8)
						currentColumn-=2;
					currentColumn--;
					setCursor(currentColumn,1);
				}
				break;
			}
			case "esc":
			{
				lcd.setCursor(0,0);
				lcd.print("Viszlat!");
				isClosed=true;
				init();
				break;	
			}
			case "modified":
			{
				break;
			}
			default://itt akkor egy szamot utott be
			{
				lcd.print(button-'0');
				rowValue[currentColumn]=pushedValue-'0';
				break;
			}
		}
	}
				
}


void LCD::setNewSong(int i)
{
	songs[i].bigNumber=0;
	if (rowValue[5]!=-1)
	{
		songs[i].bigNumber=rowValue[5];
		if (rowValue[4]!=-1)
		{
			songs[i].bigNumber=rowValue[4]*10+songs[i].bigNumber
			if(rowValue[5]!=-1)
			{
				songs[i].bigNumber=rowValue[3]*100+songs[i].bigNumber;
			}
		}
	}
		
	songs[i].beginSmallNumber=0;
	if (rowValue[9]!=-1)
	{
		songs[i].beginSmallNumber=rowValue[9];
		if(rowValue[8]!=-1)
		{
			songs[i]=rowValue[8]*10+rowValue[9];
		}
	}
		
	songs[i].endSmallNumber=0;
	if (rowValue[12]!=-1)
	{
		songs[i].endSmallNumber=rowValue[12];
		if (rowValue[11]!=-1)
		{
			songs[i].endSmallNumber=rowValue[11]*10+rowValue[12];
		}
	}


	for (int i=0; i<16; i++)
	{
		rowValue[i]=-1;
	}
}

void LCD::displayASong(int i)
{
	lcd.setCursor(0,0);
	lcd.print("E"+String(i)+":");
	lcd.setCursor(5,0);
	lcd.print(songs[i].bigNumber);
	if (songs[i].beginSmallNumber!=0)
	{
		if (songs[i].beginSmallNumber>9)
		{
			lcd.setCursor(9,0);
			lcd.print(songs[i].beginSmallNumber);
		}
		else
		{
			lcd.setCursor(10,0);
			lcd.print(songs[i].beginSmallNumber);
		}

		if (songs[i].endSmallNumber!=0)
		{
			if (songs[i].endSmallNumber>9)
			{
				lcd.setCursor(12,0);
				lcd.print(songs[i].endSmallNumber);
			}
			else
			{
				lcd.setCursor(13,0);
				lcd.print(songs[i].endSmallNumber);
			}
		}
	}

}
#endif
