/***********************************************************************
//
// File: spellChecker.cpp
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#include <string>
#include <fstream>	// for std::ifstream
#include <sstream>	// for std::istringstream
#include <iomanip>	// for std::setw
#include "spellChecker.h"

using namespace std;
namespace seneca
{
	// Constructor that reads from the file
	SpellChecker::SpellChecker(const char* filename)
	{
		ifstream file(filename);// Open file

		// If file can't be opened, throw an exception
		if (!file)
		{
			throw "Bad file name!"; // Throw a C-style exception
		}

		string line;
		int index = 0;

		// Read each line from the file
		while (getline(file, line) && index < MAX_WORDS)
		{
			istringstream stream(line);
			string badword, goodword;

			// Extract the bad and good words, ignoring leading/trailing spaces
			stream >> badword >> goodword;

			// Remove any leading or trailing spaces
			badword.erase(0, badword.find_first_not_of(' '));
			badword.erase(badword.find_last_not_of(' ') + 1);

			goodword.erase(0, goodword.find_first_not_of(' '));
			goodword.erase(goodword.find_last_not_of(' ') + 1);

			// Store the words in arrays
			m_badWords[index] = badword;
			m_goodWords[index] = goodword;

			index++;
		}

		// If there are fewer than 6 words in the file, throw an exception
		if (index < MAX_WORDS) {
			throw "Not enough words in the file!";
		}

		file.close();  // Close the file after reading
	}

	// Operator to replace misspelled words in the input text
	void SpellChecker::operator()(std::string& text)
	{
		for (size_t i = 0; i < MAX_WORDS; i++)
		{
			size_t pos = 0;
			while ((pos = text.find(m_badWords[i], pos)) != std::string::npos)
			{
				text.replace(pos, m_badWords[i].length(), m_goodWords[i]); // change bad word to good word
				pos += m_goodWords[i].length();  // Move past the last replacement
				m_replacementCount[i]++;  // Increment the replacement count
			}
		}
	}

	// Function to display how many times each word was replaced
	void SpellChecker::showStatistics(std::ostream& out) const
	{
		out << "Spellchecker Statistics" << endl;
		for (size_t i = 0; i < MAX_WORDS; i++)
		{
			out << left << setw(15) << m_badWords[i] << ": " << m_replacementCount[i] << " replacements" << endl;
		}
	}
}