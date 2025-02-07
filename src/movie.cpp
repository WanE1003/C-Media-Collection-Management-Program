/***********************************************************************
//
// File: movie.cpp
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#include <iostream>
#include <iomanip> // for std::setw
#include <string>
#include <sstream> // for std::istringstream
#include "movie.h"
#include "settings.h"

using namespace std;
namespace seneca
{
    // The given display function
	void Movie::display(std::ostream& out) const
	{
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
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

    // Creating new Movie object function.
    Movie* Movie::createItem(const std::string& strMovie)
    {
        // Check if the parameter is empty or not.
        if (strMovie.empty() || strMovie[0] == '#')
        {
            throw "Not a valid movie."; // if empty throw error.
        }

        // Stream that read the data in the string.
        std::istringstream stream(strMovie);

        // Declare temporary variables.
        std::string title, summary, yearstr;

        // Read each variable until ',' using getline function.
        std::getline(stream, title, ',');
        std::getline(stream, yearstr, ',');
        std::getline(stream, summary);

        // Remove all spaces using trim function.
        MediaItem::trim(title);
        MediaItem::trim(yearstr);
        MediaItem::trim(summary);

        // Cast string variables to int.
        int year = std::stoi(yearstr); // std:: stoi for int.

        // Create new Movie object and return it.
        return new Movie(title, summary, year);
    }
}