/*
 *
 *  Created on: September 22, 2019
 *      Author: Caleb Gondek
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "constants.h"

//TODO add a global array of entry structs (global to this file)
//TODO add variable to keep track of next available slot in array

struct Entry {
	std::string word;
	int numberOccurences;
};

int arraySize = 0; // Is this allowed?
Entry wordsArray [constants::MAX_WORDS];

/*
 * zero out array that tracks words and their occurrences
 */
void clearArray() {
	//TODO: Fix this!
	return;
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
	//TODO: Fix this!
	return "";
}

int getArrayWord_NumbOccur_At(int i) {
	//TODOL Fix this!
	return -1;
}

/*
 * Keep track of how many times each token seen
 */
void processToken(std::string &token) {
	//TODO: Fix this!
	return;
}

/*
 * take 1 line and extract all the tokens from it
 * feed each token to processToken for recording
 */
void processLine(std::string &myString) {
	//TODO: Fix this!
	return;
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
	}
	else {
		std::string line;
		while (!myfstream.eof()) {
			getline(myfstream,line);
			processLine(line);
		}
	}
	return true;
}

/*
 * if you are debugging the file must be in the project parent directory
 *in this case Project2 with the .project and .cProject files
 */
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode = std::ios_base::in) {
	myfile.open(myFileName.c_str(),mode);
	return true;
}

/*
 *  if myfile is open then close it
 */
void closeFile(std::fstream& myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
	return;
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 */
int writeArraytoFile(const std::string &outputfilename) {
	//TODO: Fix this!
	return -1;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so) {
	switch(so)
	{
	case constants::sortOrder::NONE:
		//TODO: Implement this!
		break;
	case constants::sortOrder::ASCENDING:
		//TODO: Implement this!
		break;
	case constants::sortOrder::DESCENDING:
		//TODO: Implement this!
		break;
	case constants::sortOrder::NUMBER_OCCURRENCES:
		//TODO: Implement this!
		break;
	default: // This shouldn't happen
		//TODO: Figure out some error message or something
		break;
	}

	return;
}

/*
 * This function takes myString and searches for tokens separated by
 * constants::CHAR_TO_SEARCH_FOR (a space). This constant is defined in file
 * constants.h. For each token it finds it calls processToken(tempToken).
 */
void extractTokensFromLine(std::string &myString) {
	std::stringstream ss(myString);
	std::string tempToken;

	while (getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}
