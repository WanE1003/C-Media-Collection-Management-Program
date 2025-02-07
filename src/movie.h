/***********************************************************************
//
// File: movie.h
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include <iostream>
#include <string>
#include "mediaItem.h"

namespace seneca
{
	class Movie : public MediaItem // The derived class from MediaItem class.
	{
		// The private constructor.
		Movie(const std::string& title, const std::string& summary, unsigned short year)
			: MediaItem(title, summary, year) {};
			// call the constructor of base class.
	public:

		// Overrided function to print the information about a movie.
		void display(std::ostream& out) const override;

		// A class function that receives as parameter the representation of the movie as a string and 
		// builds a dynamically allocated object of type Movie using the information from the string and 
		// returns it to the client.
		static Movie* createItem(const std::string& strMovie); // Declared as static
	};
}

#endif