/***********************************************************************
//
// File: book.h
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <iostream>
#include <string>
#include "mediaItem.h"

namespace seneca
{
	class Book : public MediaItem // The derived class from MediaItem class.
	{
		std::string m_author; // The author of the book.
		std::string m_country; // The country of publication.
		double m_price; // The price of the book.

		// The constructor that is private.
		Book(const std::string& author, const std::string& title, const std::string& summary, unsigned short year, const std::string& country, double price)
			: MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {};
			// call the constructor of base class.

	public:

		// Overrided function to print the information about a single book.
		void display(std::ostream& out) const override;

		// class function that receives as parameter the representation of the book as a string and 
		// builds a dynamically allocated object of type Book using the information from the string and 
		// returns it to the client.
		static Book* createItem(const std::string& strBook); // Declared as static.

	};
}

#endif