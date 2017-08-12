#include <DisplayClass.h> //this is my librarie, I added it to Arduino's Librarie
#include <TimedAction.h>
#include <VirtualWire.h>


 const int northSegment=10;
 const int northEastSegment=2;
 const int northWestSegment=11;
 const int middleSegment=5;
 const int southEastSegment=4;
 const int southWestSegment=6;
 const int southSegment=3;

 const int hypeSegment=A4;

 const int bigAddress1=8;
 const int bigAddress2=7;
 const int bigAddress3=9;                                 
 const int smallAddress1=A0;
 const int smallAddress2=A1;
 const int smallAddress3=A2;
 const int smallAddress4=A3;
 


int segmen[]={northSegment, northEastSegment, northWestSegment, middleSegment, southEastSegment, southWestSegment, southSegment,hypeSegment}; //vectorok amelyeket megkap az osztaly

int address[]={bigAddress1,bigAddress2,bigAddress3,smallAddress1,smallAddress2,smallAddress3,smallAddress4};

Display d(*&segmen,*&address, false); //create a class 




void message() //verify sign 
  {
  uint8_t buflen=VW_MAX_MESSAGE_LEN;
  uint8_t buf [buflen];
  char str[buflen];
  if (vw_get_message(buf,&buflen))
  {
     for (int i=0; i<buflen; ++i)
     {
        str[i]=(char)(buf[i]);        
     }


    if (str[0]=='G')//usable message (GOOD) //Gx/x/x/ a syntax, where x not obligatory
     //G may not be useful, check the bit error
    {
         int bigNumber=0;//number 0 never appears
          int beginSmallNumber=0;
        int endSmallNumber=0;
      int i=1; 

      //get numbers
      while (str[i]!='/' && i<buflen)
      {
        bigNumber*=10;
        bigNumber+=str[i]-'0';
        ++i;
      }
      i++;
      while (str[i]!='/' && i<buflen)
      {
        beginSmallNumber*=10;
        beginSmallNumber+=str[i]-'0';
        ++i;
      }
      i++;
      while (str[i]!='/' && i<buflen)
      {
        endSmallNumber*=10;
        endSmallNumber+=str[i]-'0';
        ++i;
      }
    //stop display, set number on display, start display
      d.clearDisplay(true);
      d.setBigNumber(bigNumber);
      d.setIntervallSmallNumber(beginSmallNumber,endSmallNumber);
      d.clearDisplay(false);
    }
  }
}

void use()//for timeaction
  d.displayNumbers();
}

TimedAction timedAction1 = TimedAction(0.1,use);//0.1 ms
TimedAction timedAction2 = TimedAction(1000,message);// 1s  check signal

//in theory parallel

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);


  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(13,LOW);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);


  Serial.begin(9600);
  vw_set_rx_pin(12);
  vw_set_ptt_inverted(true);
  vw_setup(4000);
  vw_rx_start();

  d.setTime(0.1);//0.1 ms


}


void loop()//start display and start signal check
{
    timedAction1.check();
    timedAction2.check();
}


