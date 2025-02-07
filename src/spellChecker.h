/***********************************************************************
//
// File: spellChecker.h
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <iostream>
#include <string>

namespace seneca
{
	class SpellChecker
	{
		static const int MAX_WORDS = 6; // Max number of words in the file
		std::string m_badWords[MAX_WORDS]; // Array to store misspelled words
		std::string m_goodWords[MAX_WORDS]; // Array to store correct words
		int m_replacementCount[MAX_WORDS] = { 0 };  // Array to store the replacement count
		 
	public:
		// Constructor
		SpellChecker(const char* filename);
		// The operator searches text and replaces any misspelled word with the correct version.
		void operator()(std::string& text);
		// The function inserts into the parameter how many times each misspelled word has been replaced by the correct word using the current instance.
		void showStatistics(std::ostream& out) const;
	};
}
#endif