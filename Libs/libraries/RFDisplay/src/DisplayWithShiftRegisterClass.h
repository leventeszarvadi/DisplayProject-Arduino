#pragma once
#include <stdint.h>
#include "./utility/Models/SongData.h"
#include "Arduino.h"


const int number0 = 63;
const int number1 = 3;
const int number2 = 109;
const int number3 = 103;
const int number4 = 83;
const int number5 = 118;
const int number6 = 126;
const int number7 = 35;
const int number8 = 127;
const int number9 = 119;
const int characterA = 123;
const int characterB = 94;
const int characterC = 60;

class DisplayWithShiftRegister{
private:
	uint64_t generatedNumber = 0;

	void setValues(int address, int value);
	uint64_t generateBitsForLetters(char value);
	uint64_t generateBitsForNumbers(int value);
	void processingSong(const SongData &songData);

public:
	uint64_t getGeneratedNumber(const SongData &songData);
};

