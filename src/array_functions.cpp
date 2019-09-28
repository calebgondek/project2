/*
 *
 *  Created on: September 22, 2019
 *      Author: Caleb Gondek
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "utilities.h"
#include "constants.h"
#include "array_functions.h"

struct Entry {
	std::string word;
	int numberOccurences;
};

const int EMPTY_ARRAY_SIZE = 0;
const int FIRST_OCCURRENCE = 1;

int arraySize = EMPTY_ARRAY_SIZE;
Entry wordsArray[constants::MAX_WORDS];


/*
 * Compares str1 and str2 without regard for case
 */
int compareStrings(std::string str1, std::string str2) {
	toUpper(str1);
	toUpper(str2);
	return str1.compare(str2);
}

/*
 * zero out array that tracks words and their occurrences
 */
void clearArray() {
	arraySize = EMPTY_ARRAY_SIZE;
}

/*
 * how many unique words are in array
 */
int getArraySize() {
	return arraySize;
}

/*
 * get data at a particular location
 */
std::string getArrayWordAt(int i) {
	std::string word = "";
	if (i < arraySize) {
		word = wordsArray[i].word;
	}
	return word;
}

int getArrayWord_NumbOccur_At(int i) {
	int number = constants::FAIL_NO_ARRAY_DATA;
	if (i < arraySize) {
		number = wordsArray[i].numberOccurences;
	}
	return number;
}

/*
 * Keep track of how many times each token seen
 */
void processToken(std::string &token) {
	if (strip_unwanted_chars(token)) {
		for (int i = 0; i < arraySize; ++i) {
			if (compareStrings(token,wordsArray[i].word) == 0) {
				wordsArray[i].numberOccurences += 1;
				return;
			}
		}
		Entry newEntry;
		newEntry.word = token;
		newEntry.numberOccurences = FIRST_OCCURRENCE;
		wordsArray[arraySize] = newEntry;
		++arraySize;
	}
}

/*
 * This function takes myString and searches for tokens separated by
 * constants::CHAR_TO_SEARCH_FOR (a space). This constant is defined in file
 * constants.h. For each token it finds it calls processToken(tempToken).
 */
void processLine(std::string &myString) {
	std::stringstream ss(myString);
	std::string tempToken;

	while (getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

/*
 * loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise
 */
bool processFile(std::fstream &myfstream) {
	if (!myfstream.is_open()) {
		return false;
	} else {
		std::string line;
		while (!myfstream.eof()) {
			getline(myfstream, line);
			processLine(line);
		}
	}
	return true;
}

/*
 * if you are debugging the file must be in the project parent directory
 *in this case Project2 with the .project and .cProject files
 */
bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode) {

	myfile.open(myFileName.c_str(), mode);
	return myfile.is_open();
}

/*
 *  if myfile is open then close it
 */
void closeFile(std::fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
	return;
}

/*
 * serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 */
int writeArraytoFile(const std::string &outputfilename) {
	if (arraySize == 0) {
		return constants::FAIL_NO_ARRAY_DATA;
	}
	std::ofstream myOutputfile;
	myOutputfile.open(outputfilename);

	if (!myOutputfile.is_open()) {
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}

	for (int i = 0; i < arraySize; ++i) {
		myOutputfile <<  wordsArray[i].word << ' ' << wordsArray[i].numberOccurences << std::endl;
	}

	return constants::SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so) {
	int i, j;

	Entry tempEntry;

	switch (so) {
	case constants::sortOrder::ASCENDING:
		for (i = 1; i < arraySize; ++i) {
			for (j = i; j > 0; --j) {
				if (compareStrings(wordsArray[j-1].word,wordsArray[j].word) > 0) {
					tempEntry = wordsArray[j];
					wordsArray[j] = wordsArray[j - 1];
					wordsArray[j - 1] = tempEntry;
				}
			}
		}
		break;
	case constants::sortOrder::DESCENDING:
		for (i = 1; i < arraySize; ++i) {
			for (j = i; j > 0; --j) {
				if (compareStrings(wordsArray[j-1].word,wordsArray[j].word) < 0) {
					tempEntry = wordsArray[j];
					wordsArray[j] = wordsArray[j - 1];
					wordsArray[j - 1] = tempEntry;
				}
			}
		}
		break;
	case constants::sortOrder::NUMBER_OCCURRENCES:
		for (i = 1; i < arraySize; ++i) {
			for (j = i; j > 0; --j) {
				if (wordsArray[j - 1].numberOccurences
						> wordsArray[j].numberOccurences) {
					tempEntry = wordsArray[j];
					wordsArray[j] = wordsArray[j - 1];
					wordsArray[j - 1] = tempEntry;
				}
			}
		}
		break;
	case constants::sortOrder::NONE:
	default:
		break; // Do nothing for NONE and otherwise
	}

	return;
}
