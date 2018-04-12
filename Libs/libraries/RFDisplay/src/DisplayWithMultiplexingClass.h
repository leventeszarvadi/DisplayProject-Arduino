#ifndef DisplayClass_h
#define DisplayClass_h

#include "Arduino.h"
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
    void setBigNumber(int number);
    void setIntervallSmallNumber(int beginNumber, int endNumber);
	void clearDisplay(bool clearValue);
	void setTime(double time);
    void displayNumbers();
};

#endif
