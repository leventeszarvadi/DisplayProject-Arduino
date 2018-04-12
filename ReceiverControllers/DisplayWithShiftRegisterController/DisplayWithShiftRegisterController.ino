#include <AbstractRFHandler.h>
#include <AbstractSongDataConverter.h>
#include <DisplayWithShiftRegisterClass.h>
#include <SongDataConverter.h>
#include <VWRFHandler.h>


/*
 * 
 * ===============================================================
ON VERSION ORIGINAL, V1


 //Pin connected to ST_CP of 74HC595
int latchPin = 6;
//Pin connected to SH_CP of 74HC595
int clockPin = 7;
////Pin connected to DS of 74HC595
int dataPin = 5;


=================================================================
*/


/*
 * ==============================================================
 * ON VERSION M1 

*/

 //Pin connected to ST_CP of 74HC595
int latchPin = 7;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 5;

//================================================================
 
//ledPin

int cooler = 2;
int ledPin=13;

DisplayWithShiftRegister disp;
AbstractSongDataConverter * songDataConverter = new SongDataConverter();
AbstractRFHandler *rfHandler;
SongData previousSongData;
void setup() {
  rfHandler=new VWRFHandler(songDataConverter,12,13,2000);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(cooler,OUTPUT);

  

 digitalWrite(latchPin,0);
 shiftOut(dataPin,clockPin,0);
 digitalWrite(latchPin,1);
 
digitalWrite(cooler,LOW);
myblink(3);

} 
void loop() {
  SongData songData;

  //if received successfull
 if(rfHandler->receiveData(&songData))
 {
    if (!equalSongData(&songData,&previousSongData))
    {
      SongData emptySongData;
      
      if (equalSongData(&emptySongData,&songData))
      {
        digitalWrite(cooler,LOW);
      }
      else
      {
        digitalWrite(cooler,HIGH);
      }
      
      previousSongData=songData;
      uint64_t g=disp.getGeneratedNumber(songData);
      
      //=====================
      //function, resolving mistake
      g=resolveMistake(g);
      //==================

      
      digitalWrite(latchPin,0);
      shiftOut(dataPin,clockPin,g);
      digitalWrite(latchPin,1);
    }
 }
}


void shiftOut(int myDataPin, int myClockPin, uint64_t myDataOut) {
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  
  for (int i=64; i>=0; i--)  {
    bool pinState = myDataOut & ((uint64_t)1<<i);
    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);  
    digitalWrite(myDataPin, 0);
    digitalWrite(myClockPin, 0);
  }
}

uint64_t resolveMistake(uint64_t generatedNumber)
{  
  /*
    firstNumber -> x
    secondNumber -> y
    thirdNumber -> z

    (cable from x, First chip is on the x)
      __       __       __
    | x  |   | y  |   | z  |
      --       --       --
    |  I |   | II |   |III |   ...
      ''       ''       ''

===================================
(0)    6
       __      
   5 |    |1  <= normaly
       --      
   4 |  7 |2  
       ''       
      3


(0)    3
       __      
   2 |    |4  <=mistake
       --      
   1 |  7 |5  
       ''       
      6
      
    ......._......._......._zzzzzzz_yyyyyyy_xxxxxxx_
    123456789012345678901234567890123456789012345678
    bit lenght=48;
*/
uint64_t returnNumber=0;
uint64_t takeOutNumber=127;
takeOutNumber=takeOutNumber<<1;

returnNumber=returnNumber|((convertNumber((generatedNumber&takeOutNumber)>>1))<<1);

takeOutNumber=takeOutNumber<<8;
returnNumber=returnNumber|((convertNumber((generatedNumber&takeOutNumber)>>9))<<9);

takeOutNumber=takeOutNumber<<8;
returnNumber=returnNumber|((convertNumber((generatedNumber&takeOutNumber)>>17))<<17);

takeOutNumber=1; //for 0'th pin ......._......._......._zzzzzzz_yyyyyyy_xxxxxxx_ , => _ <=
returnNumber=returnNumber|(generatedNumber&takeOutNumber);
takeOutNumber=takeOutNumber<<8;
returnNumber=returnNumber|(generatedNumber&takeOutNumber);
takeOutNumber=takeOutNumber<<8;
returnNumber=returnNumber|(generatedNumber&takeOutNumber);

generatedNumber = (generatedNumber>>24)<<24;
return returnNumber|generatedNumber;
}


uint64_t convertNumber(uint64_t number)
{
  uint64_t converteredNumber=0;
  converteredNumber=converteredNumber | (number&(1<<6)); //for 7'th bit, does not modify
  //xxxxxxx
  //1234567
  //1=>4
  //2=>5
  //3=>6
  //4=>1
  //5=>2
  //6=>3

  for (int i=0; i<3; i++)
  {
    uint64_t x1=1;
    uint64_t x2=1;
    
    x1=x1<<i;
    x2=x2<<(i+3);
    converteredNumber=converteredNumber | ((number & x1)<<3);
    converteredNumber=converteredNumber | ((number & x2)>>3);
  }
  return converteredNumber;
}

void myblink(int x)
{
  for(int i=0; i<x; i++)
  {
    digitalWrite(ledPin,HIGH);
    delay(500);
    digitalWrite(ledPin,LOW);
    delay(500);
  }
}

bool equalSongData(const SongData* songData1, const SongData* songData2)
{
  return (songData1->mainNumber == songData2->mainNumber &&
          songData1->startVerse == songData2->startVerse &&
          songData1->endVerse == songData2->endVerse &&
          songData1->version == songData2->version );
}
/*
void myprint(uint64_t x)
{
  for(int i=63; i>=0; i--)
  {
    bool k=x&((uint64_t)1<<i);
    Serial.print(k);
  }
  Serial.println();
}
*/
