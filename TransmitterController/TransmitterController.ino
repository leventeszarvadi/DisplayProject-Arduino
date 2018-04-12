#include <EEPROM.h>
#include <AbstractRFHandler.h>
#include <PersonalizedLCD.h>
#include <VWRFHandler.h>
#include <SongDataConverter.h>
#include <IRremote.h>

int IR_RECV_PIN = 9;
IRrecv irrecv(IR_RECV_PIN);
decode_results res;

const long callAcceptButton=16753245;
const long phoneButton=16736925;
const long callDeclineButton=16769565;
const long chMinusButton=16720605;
const long chPlusButton=16712445;
const long eqButton=16761405;
const long backButton=16769055;
const long nextButton=16754775;
const long startStopButton=16748655;
const long minusButton=16750695;
const long plusButton=16756815;
const long Button0=16738455;
const long Button1=16724175;
const long Button2=16718055;
const long Button3=16743045;
const long Button4=16716015;
const long Button5=16726215;
const long Button6=16734885;
const long Button7=16728765;
const long Button8=16730805;
const long Button9=16732845;


const int blockLedOnBoard=10;
const int nextButtonOnBoard=7;
const int backButtonOnBoard=13;//
const int blockButtonOnBoard=8;

bool previousNextButtonStateOnBoard=false;
bool previousBackButtonStateOnBoard=false;
bool previousBlockButtonStateOnBoard=false;

int eepromAddress=0;
const int redLed=1;
const int displaysRefreshTime=6000;
unsigned long previousMillis = 0;
int sendingEmptyData=0;
const int MAX_TIMES_SENDING_EMPTY_DATA=10;
 
AbstractSongDataConverter *songDataConverter=new SongDataConverter();
AbstractRFHandler *rfHandler;
LCD lcd(6,11,5,4,3,2);

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  rfHandler=new VWRFHandler(songDataConverter,13,12,2000);
  pinMode(redLed,OUTPUT);
  pinMode(blockLedOnBoard,OUTPUT);
  pinMode(nextButtonOnBoard,INPUT);
  pinMode(backButtonOnBoard,INPUT);
  pinMode(blockButtonOnBoard,INPUT);

  lcd.lcdLoadingDatasFromEEPROM();
  loadingDatasFromLocalStorage();
  lcd.init();

  if (lcd.isDisplayBlocked())
  {
     digitalWrite(blockLedOnBoard,LOW);
  }
  else
  {
     digitalWrite(blockLedOnBoard,HIGH);
  }
 
  irrecv.enableIRIn(); 
}
void loop() {
  if(irrecv.decode(&res)) 
  {
    long results=res.value;
    bool correctSignal=true;
   // Serial.println(results);
    switch(results)
    {
      case plusButton:
        lcd.settingsButtonPushed();
        break;
      case minusButton:
        lcd.cancelButtonPushed();
        break;
      case nextButton:
        lcd.nextButtonPushed();
        break;
      case backButton:
        lcd.backButtonPushed();
        break;
      case startStopButton:
        lcd.OKButtonPushed();
        break;
      case eqButton:
        digitalWrite(blockLedOnBoard,!lcd.isDisplayBlocked());
        lcd.displayBlockButtonPushed();
        break;
      case Button0:
        lcd.xButtonPushed(0);
        break;
      case Button1:
        lcd.xButtonPushed(1);
        break;
      case Button2:
        lcd.xButtonPushed(2);
        break;
      case Button3:
        lcd.xButtonPushed(3);
        break;
      case Button4:
        lcd.xButtonPushed(4);
        break;
      case Button5:
        lcd.xButtonPushed(5);
        break;
      case Button6:
        lcd.xButtonPushed(6);
        break;
      case Button7:
        lcd.xButtonPushed(7);
        break;
      case Button8:
        lcd.xButtonPushed(8);
        break;
      case Button9:
        lcd.xButtonPushed(9);
        break;
      case callAcceptButton:
        lcd.letterButtonPushed('A');
        break;
      case phoneButton:
        lcd.letterButtonPushed('B');
        break;
      case callDeclineButton:
        lcd.letterButtonPushed('C');
        break;
      case chMinusButton:
        lcd.clearAllSongs();
        break;
      case chPlusButton:
        if(lcd.savingDatasMessage())
          saveSongListInLocalStorage(lcd.getSongList());
        break;
      default:
        correctSignal=false;
        break;
    }
    /*if(correctSignal)
    {
      digitalWrite(redLed,HIGH);
    }
    delay(50);
    digitalWrite(redLed,LOW);*/
    
    irrecv.resume();
  }
  else
  {
  
    //if not with remote controller
    bool nextButtonStateOnBoard = buttonPushedOnBoard(nextButtonOnBoard);
    bool backButtonStateOnBoard = buttonPushedOnBoard(backButtonOnBoard);
    bool blockButtonStateOnBoard = buttonPushedOnBoard(blockButtonOnBoard);
    
    if (nextButtonStateOnBoard && !previousNextButtonStateOnBoard)
    {
        lcd.nextButtonPushed();
    }
    previousNextButtonStateOnBoard=nextButtonStateOnBoard;

    if (backButtonStateOnBoard && !previousBackButtonStateOnBoard)
    {
        lcd.backButtonPushed();
    }
    previousBackButtonStateOnBoard=backButtonStateOnBoard;

    if (blockButtonStateOnBoard && !previousBlockButtonStateOnBoard)
    {
        lcd.displayBlockButtonPushed();
        if (lcd.isDisplayBlocked())
        {
           digitalWrite(blockLedOnBoard,LOW);
        }
        else
        {
           digitalWrite(blockLedOnBoard,HIGH);
        }
    }
    previousBlockButtonStateOnBoard=blockButtonStateOnBoard;  
   
  }
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > displaysRefreshTime)
  {
    previousMillis = currentMillis;
    LCDDisplaySong actualSong=lcd.getActualSong();
    if (!lcd.isDisplayBlocked() && actualSong.itWasSetUp)
    {   
      sendingEmptyData=0;
      SongData songData;
      songData.mainNumber=actualSong.mainNumber;
      songData.startVerse=actualSong.startVerse;
      songData.endVerse=actualSong.endVerse;
      songData.version=actualSong.version;
      
      rfHandler->sendData(songData);
    }
    else
    {
      if(sendingEmptyData<MAX_TIMES_SENDING_EMPTY_DATA)
      {
        sendingEmptyData++;
        rfHandler->sendData(SongData());
      }
    }
  }
  else
  {
    delay(100);
  }
}

bool buttonPushedOnBoard(int buttonPin)
{
  bool buttonState = (digitalRead(buttonPin)==HIGH);
  delay(5);
  return (buttonState && (digitalRead(buttonPin)==HIGH));
}

void loadingDatasFromLocalStorage()
{
  eepromAddress=0;
  int songListSize=lcd.getMaxSongNumber();
  LCDDisplaySong songList[songListSize];
  for (int i=0; i<songListSize; i++)
  {
    songList[i]=getNextSongFromLocalStorage();
  }
  lcd.setSongList(songList);
  eepromAddress=0;
}

LCDDisplaySong getNextSongFromLocalStorage()
{
  LCDDisplaySong song;
  song.mainNumber=EEPROM.read(eepromAddress++)*100+EEPROM.read(eepromAddress++)*10+EEPROM.read(eepromAddress++);
  song.version=EEPROM.read(eepromAddress++);
  song.startVerse=EEPROM.read(eepromAddress++)*10+EEPROM.read(eepromAddress++);
  song.endVerse=EEPROM.read(eepromAddress++)*10+EEPROM.read(eepromAddress++);
  return song;
}

void saveSongListInLocalStorage(LCDDisplaySong* list)
{
  eepromClear();
  eepromAddress=0;
  int songListSize=lcd.getMaxSongNumber();
  for (int i=0; i<songListSize; i++)
  {
    saveSongInLocalStorage(list[i]);
  }
  //EEPROM.write(eepromAddress++, (byte)(lcd.getActualSongPosition()));
  eepromAddress=0;
}
void saveSongInLocalStorage(LCDDisplaySong song)
{
  EEPROM.write(eepromAddress++, (byte)(song.mainNumber/100));
  EEPROM.write(eepromAddress++, ((byte)(song.mainNumber/10))%10);
  EEPROM.write(eepromAddress++, (byte)(song.mainNumber%10));
  EEPROM.write(eepromAddress++, (byte)song.version);
  EEPROM.write(eepromAddress++, (byte)(song.startVerse/10));
  EEPROM.write(eepromAddress++, (byte)(song.startVerse%10));
  EEPROM.write(eepromAddress++, (byte)(song.endVerse/10));
  EEPROM.write(eepromAddress++, (byte)(song.endVerse%10));
}

void eepromClear()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) 
  {
    EEPROM.write(i, 0);
  }
}



