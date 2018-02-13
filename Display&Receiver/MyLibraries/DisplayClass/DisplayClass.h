#ifndef DisplayClass_h
#define DisplayClass_h
//Szarvadi Levente - Andras
//2017.06.12
class Display{
  private:
    int bigNumber;
    int beginSmallNumber;
    int endSmallNumber;
    bool hyphenSegmentHidden;
    bool clear;
    double delayTime;

    int bigAddress1;
	int bigAddress2;
	int bigAddress3;
	int smallAddress1;
	int smallAddress2;
	int smallAddress3;
	int smallAddress4;

//signal for Segments
	int northSegment;
	int northEastSegment;
	int northWestSegment;
	int middleSegment;
	int southEastSegment;
	int southWestSegment;
	int southSegment;
	int hyphenSegment;

	//display a number to the specified address
    void displayANumber(int address, int number);
  
  public :

    Display(int * segmentsArray, int * addressArray, bool hyphenSegmentHidden);
    
    void setBigNumber(int number)
    {
      bigNumber=number;  
    }
    
    void setIntervallSmallNumber(int beginNumber, int endNumber)
    {
      beginSmallNumber=beginNumber;
      endSmallNumber=endNumber;
    }

    void clearDisplay(bool clearValue)
    {
		clear=clearValue;
    }

    void setTime(double time)
    {
    	delayTime=time;
    }
    
    //display numbers on board
    void displayNumbers()
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
	   				digitalWrite(hyphenSegment,HIGH);
	   			displayANumber(smallAddress4,endSmallNumber%10);
	   			if (endSmallNumber>9)
	   				displayANumber(smallAddress3,1);
	   			digitalWrite(hyphenSegment,LOW);
	   		}

	   		if (beginSmallNumber>0 && beginSmallNumber<20)
	   		{

				displayANumber(smallAddress2,beginSmallNumber%10);
	   			if (beginSmallNumber>9)
	   				displayANumber(smallAddress1,1);

	   		}

    	}

    }
     
};

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

//display a number to the specified address
void Display::displayANumber(int adress, int number)
{
  digitalWrite(adress,HIGH);//open segment
   switch(number)
      {
        case 0:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northSegment,LOW);
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(northWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(northWestSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            digitalWrite(southWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(southWestSegment,LOW);   
            digitalWrite(southSegment,HIGH);
            delay(delayTime);
            digitalWrite(southSegment,LOW);
            delay(delayTime);
            
            break;
          }
        case 1:
          {
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            delay(delayTime);
            break;
          } 
        case 2:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northSegment,LOW);
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(middleSegment,HIGH);
            delay(delayTime);
            digitalWrite(middleSegment,LOW);
            digitalWrite(southWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(southWestSegment,LOW);   
            digitalWrite(southSegment,HIGH);
            delay(delayTime);
            digitalWrite(southSegment,LOW);
            delay(delayTime);
            break;
          }
        case 3:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northSegment,LOW);
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(middleSegment,HIGH);
            delay(delayTime);
            digitalWrite(middleSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);  
            digitalWrite(southSegment,HIGH);
            delay(delayTime);
            digitalWrite(southSegment,LOW);
            delay(delayTime);
            break;
          }
        case 4:
          {
            digitalWrite(northWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(northWestSegment,LOW);
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(middleSegment,HIGH);
            delay(delayTime);
            digitalWrite(middleSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            delay(delayTime);
            break;
          }
        case 5:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northSegment,LOW);
            digitalWrite(northWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(northWestSegment,LOW);
            digitalWrite(middleSegment,HIGH);
            delay(delayTime);
            digitalWrite(middleSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            digitalWrite(southSegment,HIGH);
            delay(delayTime);
            digitalWrite(southSegment,LOW);
            delay(delayTime);
            break;
          }
        case 6:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(northWestSegment,LOW);
            digitalWrite(middleSegment,HIGH);
            delay(delayTime);
            digitalWrite(middleSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            digitalWrite(southWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(southWestSegment,LOW);   
            digitalWrite(southSegment,HIGH);
            delay(delayTime);
            digitalWrite(southSegment,LOW);
            delay(delayTime);
            break;
          }
        case 7:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northSegment,LOW);
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            delay(delayTime);
         
            break;
          }
        case 8:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northSegment,LOW);
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(northWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(northWestSegment,LOW);
            digitalWrite(middleSegment,HIGH);
            delay(delayTime);
            digitalWrite(middleSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            digitalWrite(southWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(southWestSegment,LOW);   
            digitalWrite(southSegment,HIGH);
            delay(delayTime);
            digitalWrite(southSegment,LOW);
            delay(delayTime);
            break;
          }
        case 9:
          {
            digitalWrite(northSegment,HIGH);
            delay(delayTime);
            digitalWrite(northSegment,LOW);
            digitalWrite(northEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(northEastSegment,LOW);
            digitalWrite(northWestSegment,HIGH);
            delay(delayTime);
            digitalWrite(northWestSegment,LOW);
            digitalWrite(middleSegment,HIGH);
            delay(delayTime);
            digitalWrite(middleSegment,LOW);
            digitalWrite(southEastSegment,HIGH);
            delay(delayTime);
            digitalWrite(southEastSegment,LOW);
            digitalWrite(southSegment,HIGH);
            delay(delayTime);
            digitalWrite(southSegment,LOW);
            delay(delayTime);
            break;
          }
      }
digitalWrite(adress,LOW);
 
}

#endif
