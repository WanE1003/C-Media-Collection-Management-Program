/***********************************************************************
//
// File: book.cpp
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#include <iostream>
#include <iomanip> // for std::setw
#include <string>
#include <sstream> // for std::istringstream
#include "book.h"
#include "settings.h"

using namespace std;
namespace seneca
{
    // The given display function
	void Book::display(std::ostream& out) const 
	{
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
	}

    // Creating new Book object funtion
    Book* Book::createItem(const std::string& strBook)
    {
        if (strBook.empty() || strBook[0] == '#') // chech if the parameter is empty or not.
        {
            throw "Not a valid book."; // if empty throw error.
        }

        // Stream that read data in the string.
        std::istringstream stream(strBook);

        // Declare temporary variables.
        std::string author, title, country, summary, priceStr, yearStr;

        // Read each variable until ',' using getline function.
        std::getline(stream, author, ',');
        std::getline(stream, title, ',');
        std::getline(stream, country, ',');
        std::getline(stream, priceStr, ',');
        std::getline(stream, yearStr, ',');
        std::getline(stream, summary);

        // Remove all spaces using trim function.
        MediaItem::trim(author);
        MediaItem::trim(title);
        MediaItem::trim(country);
        MediaItem::trim(priceStr);
        MediaItem::trim(yearStr);
        MediaItem::trim(summary);

        // Cast string variables to int or double.
        double price = std::stod(priceStr); // std::stod for double / float.
        int year = std::stoi(yearStr); // std:: stoi for int.

        // Create new Book object and return it.
        return new Book(author, title, summary, year, country, price);
    }

    
}