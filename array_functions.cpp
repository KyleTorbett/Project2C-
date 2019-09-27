/*
 *  by Kyle Torbett
 *
 */
#define ARRAY_FUNCTIONS_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
using namespace constants;
using namespace std;

struct entry
{
std::string word;
int number_occurances;
};

entry myEntryArray[200];
int nextSlotInArray = 0;
int arraySize = 0;
bool check = false;

void clearArray()   {
	for(int i=0;i<nextSlotInArray;i++)   {
		myEntryArray[i].word="";
		myEntryArray[i].number_occurances=0;
	}
	nextSlotInArray=0;
	arraySize=0;
}

int getArraySize()   {
	return arraySize;
}

std::string getArrayWordAt(int i)   {
	return myEntryArray[i].word;

}
int getArrayWord_NumbOccur_At(int i)   {
	return myEntryArray[i].number_occurances;
}

void processToken(std::string &token)   {
	strip_unwanted_chars(token);
	if(token !="")   {
	check = false;
	int temp =0;

    while(temp<arraySize)   {
    	string testA = token;
    	toUpper(testA);
    	string testB = myEntryArray[temp].word;
    	toUpper(testB);
    	if(testA==testB)    {
    		myEntryArray[temp].number_occurances++;
    		check = true;
    		break;
    	} else   {
    		temp++;
    		continue;
    	}
    }
    if(check==false)   {
    	myEntryArray[nextSlotInArray].word =token;
    	myEntryArray[nextSlotInArray].number_occurances++;
    	nextSlotInArray++;
    	arraySize++;
    }
}
}

void processLine(std::string &myString)   {
	stringstream ss(myString);
		string tempToken;
		while (getline(ss, tempToken, ' ')) {
			processToken(tempToken);
		}
}

bool processFile(std::fstream &myfstream)   {
	if (myfstream.is_open() == false) {
				return false;
			}
			else {
				string line;
				while(myfstream.eof() == false) {
					getline(myfstream, line);
					processLine(line);
				}
				return true;
			}
}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode = std::ios_base::in)   {
		myfile.open(myFileName);
		if (myfile.is_open()) {
			return true;
		}
		else {
			return false;
		}
}

void closeFile(std::fstream& myfile)  {
if(myfile.is_open())   {
	myfile.close();
}
}

int writeArraytoFile(const std::string &outputfilename)   {
ofstream myOutput;
myOutput.open(outputfilename);
if(arraySize==0||nextSlotInArray==0)   {
	return FAIL_NO_ARRAY_DATA;
}
if(!myOutput.is_open()){
	return FAIL_FILE_DID_NOT_OPEN;
}

for(int i=0;i<nextSlotInArray;i++)   {
	myOutput << "" + myEntryArray[i].word + " " + to_string(myEntryArray[i].number_occurances) + "\n";
}
myOutput.close();
return SUCCESS;
}

void Ascending()   {
	for (int i = 0; i< nextSlotInArray; i++) {
		for (int j=0; j < nextSlotInArray-1; j++)  {
			string word1 = myEntryArray[j].word;
			string word2 = myEntryArray[j + 1].word;
			toUpper(word1);
			toUpper(word2);
			if (word1 > word2)  {
				entry two = myEntryArray[j + 1];
				entry one = myEntryArray[j];
				myEntryArray[j + 1] = one;
				myEntryArray[j] = two;
			}
		}
	}
}

void sortArrayDescending()   {  // forGeeks >Geeks
	int j;
	entry temp;
	for(int i=1;i<arraySize;i++)  {
		j=i;
	while(j>0 && myEntryArray[j].word>myEntryArray[j-1].word)   {
		temp = myEntryArray[j];
		myEntryArray[j] = myEntryArray[j-1];
		myEntryArray[j-1] = temp;
		j--;
	}
	}
}

void sortArrayNumberOccurances()   {
	int j;
	entry temp;
	for(int i=1;i<arraySize;i++)  {
		j=i;
	while(j>0 && myEntryArray[j].number_occurances<myEntryArray[j-1].number_occurances)   {
		temp = myEntryArray[j];
		myEntryArray[j] = myEntryArray[j-1];
		myEntryArray[j-1] = temp;
		j--;
	}
	}
}
void sortArray(constants::sortOrder so)     {
		switch(so)   {
		case DESCENDING:  sortArrayDescending();break;
		case NUMBER_OCCURRENCES:sortArrayNumberOccurances();				break;
		case ASCENDING:	Ascending();			break;
		case NONE: 					break;
}
}
