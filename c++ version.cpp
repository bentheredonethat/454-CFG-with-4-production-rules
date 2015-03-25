﻿#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

// given a rule, and position in input string, permute if rule applies then return new string
string  produceNewString(string stringToChange, int whichRule, int currentchar){

	string newString = "";

	// depending on rule, use specified production rule
	switch (whichRule){
	case 0: // a -> ab
		if (stringToChange[currentchar] == 'a') newString = stringToChange + "b";
		break;
	case 1: // b -> ba
		if (stringToChange[currentchar] == 'b') newString = stringToChange + 'a';
		break;
	case 2: // a-> aa
		if (stringToChange[currentchar] == 'a') newString = stringToChange + 'a';
		break;
	case 3: // b -> bb
		if (stringToChange[currentchar] == 'b') newString = stringToChange + 'b';
		break;
	}
	return newString;
}

// write to file all strings generated by production rules up to length n, using either 2 or 4 rules as specified
void createDict(){

	unsigned int numChars, numRules;

	// how long is longest bit string
	cout << "Bit string length : ";
	cin >> numChars;

	// how many rules to use
	cout << "Use all rules? enter 2 or 4: " << endl;
	cin >> numRules;

	// will hold words in language up to given stringLength
	ofstream outFile("dictionary.txt");
	outFile.write("\xef\xbb\xbf",3);

	// keep track of current generation of strings
	vector <string> prevGen = { "a", "b" };

	// check if ok to make new strings
	while (prevGen[0].size() <= numChars){

		vector <string> newGen; // hold each new generation

		// record strings from old generation because must be valid
		for (unsigned int i = 0; i < prevGen.size(); i++) outFile.write((',' + prevGen[i]).c_str(), prevGen[i].size() + 1);

		// for each ancestor, permute each character via the production rules
		for (unsigned int currentAncestor = 0; currentAncestor < prevGen.size(); currentAncestor++){

			// for each character in the current ancestor use each rule
			for (unsigned int currentChar = 0; currentChar < prevGen[currentAncestor].size(); currentChar++){

				// for each rule, check if a new string is produced, if so add to new generation
				for (unsigned int currentRule = 0; currentRule < numRules; currentRule++){

					// generate new string as result of current rule
					string child = produceNewString(prevGen[currentAncestor], currentRule,currentChar);

					// if the new child is not in the current newGen, add to newGen
					if (child.size() > 1){

						// nothin in generation so add
						if (newGen.empty()) newGen.push_back(child);
						
						// child already there
						else if (find(newGen.begin(), newGen.end(), child) != newGen.end()) 
							continue;

						// not already in child
						else
							newGen.push_back(child);

					}
					
				}
			}
		}

		// update old generation
		prevGen = newGen;
	}
}

int main(){

	// generate dictionary
	createDict();

	return 0;

}
