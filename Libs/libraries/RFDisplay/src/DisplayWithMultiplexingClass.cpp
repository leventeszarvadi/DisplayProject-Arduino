#include "DisplayWithMultiplexingClass.h"

//PRIVATE METHODS
//display a number to the specified address
void Display::displayANumber(int adress, int number)
{
  digitalWrite(adress,1);//open segment
   switch(number)
      {
        case 0:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northSegment,0);
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(northWestSegment,1);
            delay(delayTime);
            digitalWrite(northWestSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            digitalWrite(southWestSegment,1);
            delay(delayTime);
            digitalWrite(southWestSegment,0);   
            digitalWrite(southSegment,1);
            delay(delayTime);
            digitalWrite(southSegment,0);
            delay(delayTime);
            
            break;
          }
        case 1:
          {
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            delay(delayTime);
            break;
          } 
        case 2:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northSegment,0);
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(middleSegment,1);
            delay(delayTime);
            digitalWrite(middleSegment,0);
            digitalWrite(southWestSegment,1);
            delay(delayTime);
            digitalWrite(southWestSegment,0);   
            digitalWrite(southSegment,1);
            delay(delayTime);
            digitalWrite(southSegment,0);
            delay(delayTime);
            break;
          }
        case 3:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northSegment,0);
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(middleSegment,1);
            delay(delayTime);
            digitalWrite(middleSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);  
            digitalWrite(southSegment,1);
            delay(delayTime);
            digitalWrite(southSegment,0);
            delay(delayTime);
            break;
          }
        case 4:
          {
            digitalWrite(northWestSegment,1);
            delay(delayTime);
            digitalWrite(northWestSegment,0);
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(middleSegment,1);
            delay(delayTime);
            digitalWrite(middleSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            delay(delayTime);
            break;
          }
        case 5:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northSegment,0);
            digitalWrite(northWestSegment,1);
            delay(delayTime);
            digitalWrite(northWestSegment,0);
            digitalWrite(middleSegment,1);
            delay(delayTime);
            digitalWrite(middleSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            digitalWrite(southSegment,1);
            delay(delayTime);
            digitalWrite(southSegment,0);
            delay(delayTime);
            break;
          }
        case 6:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northWestSegment,1);
            delay(delayTime);
            digitalWrite(northWestSegment,0);
            digitalWrite(middleSegment,1);
            delay(delayTime);
            digitalWrite(middleSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            digitalWrite(southWestSegment,1);
            delay(delayTime);
            digitalWrite(southWestSegment,0);   
            digitalWrite(southSegment,1);
            delay(delayTime);
            digitalWrite(southSegment,0);
            delay(delayTime);
            break;
          }
        case 7:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northSegment,0);
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            delay(delayTime);
         
            break;
          }
        case 8:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northSegment,0);
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(northWestSegment,1);
            delay(delayTime);
            digitalWrite(northWestSegment,0);
            digitalWrite(middleSegment,1);
            delay(delayTime);
            digitalWrite(middleSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            digitalWrite(southWestSegment,1);
            delay(delayTime);
            digitalWrite(southWestSegment,0);   
            digitalWrite(southSegment,1);
            delay(delayTime);
            digitalWrite(southSegment,0);
            delay(delayTime);
            break;
          }
        case 9:
          {
            digitalWrite(northSegment,1);
            delay(delayTime);
            digitalWrite(northSegment,0);
            digitalWrite(northEastSegment,1);
            delay(delayTime);
            digitalWrite(northEastSegment,0);
            digitalWrite(northWestSegment,1);
            delay(delayTime);
            digitalWrite(northWestSegment,0);
            digitalWrite(middleSegment,1);
            delay(delayTime);
            digitalWrite(middleSegment,0);
            digitalWrite(southEastSegment,1);
            delay(delayTime);
            digitalWrite(southEastSegment,0);
            digitalWrite(southSegment,1);
            delay(delayTime);
            digitalWrite(southSegment,0);
            delay(delayTime);
            break;
          }
      }
digitalWrite(adress,0);
}


//PUBLIC METHODS
Display::Display(int * segmentsArray, int * addressArray, bool hyphenSegmentHiddenValue )
{
	delayTime=100;
	clear = false;
	bigNumber=0;
    beginSmallNumber=0;
    endSmallNumber=0;
	hyphenSegmentHidden = hyphenSegmentHiddenValue;
	northSegment=segmentsArray[0];
	northEastSegment=segmentsArray[1];
	northWestSegment=segmentsArray[2];
	middleSegment=segmentsArray[3];
	southEastSegment=segmentsArray[4];
	southWestSegment=segmentsArray[5];
	southSegment=segmentsArray[6];
	hyphenSegment=segmentsArray[7];

	bigAddress1=addressArray[0];
	bigAddress2=addressArray[1];
	bigAddress3=addressArray[2];
	smallAddress1=addressArray[3];
	smallAddress2=addressArray[4];
	smallAddress3=addressArray[5];
	smallAddress4=addressArray[6];

}

void Display::setBigNumber(int number)
{
  bigNumber=number;  
}

void Display::setIntervallSmallNumber(int beginNumber, int endNumber)
{
  beginSmallNumber=beginNumber;
  endSmallNumber=endNumber;
}

void Display::clearDisplay(bool clearValue)
{
	clear=clearValue;
}

void Display::setTime(double time)
{
	delayTime=time;
}

 //display numbers on board
void Display::displayNumbers()
{
	if (!clear)
	{
    	if (bigNumber>0)
    	{
    		displayANumber(bigAddress3,bigNumber%10);
    		if (bigNumber>9)
    			displayANumber(bigAddress2,((int)bigNumber/10)%10);
    		if (bigNumber>99)
    			displayANumber(bigAddress1,((int)bigNumber/100));
    	}
   		if (endSmallNumber>0 && endSmallNumber<20)
   		{
   			if (!hyphenSegmentHidden)
   				digitalWrite(hyphenSegment,1);
   			displayANumber(smallAddress4,endSmallNumber%10);
   			if (endSmallNumber>9)
   				displayANumber(smallAddress3,1);
   			digitalWrite(hyphenSegment,0);
   		}

   		if (beginSmallNumber>0 && beginSmallNumber<20)
   		{

			displayANumber(smallAddress2,beginSmallNumber%10);
   			if (beginSmallNumber>9)
   				displayANumber(smallAddress1,1);
   		}
	}
}