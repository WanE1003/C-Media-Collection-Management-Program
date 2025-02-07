/***********************************************************************
//
// File: tvShow.cpp
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/


#include <iostream>
#include <iomanip>      // for std::setw
#include <string>
#include <numeric>      // for std::accumulate
#include <list>         // for std::list
#include <algorithm>    // for std::for_each
#include "tvShow.h"
#include "settings.h"

using namespace std;
namespace seneca
{
    // The given display function
	void TvShow::display(std::ostream& out) const
	{
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
	}

    // Creating new TvShow object function.
    TvShow* TvShow::createItem(const std::string& strShow)
    {
        // Check if the parameter is empty or not.
        if (strShow.empty() || strShow[0] == '#')
        {
            throw "Not a valid show."; // if empty throw error.
        }

        // Stream that read data in the string.
        std::istringstream stream(strShow);

        // Declare temporary variables
        std::string idstr, title, yearstr, summary;

        // Read each variable until ',' using getline function.
        std::getline(stream, idstr, ',');
        std::getline(stream, title, ',');
        std::getline(stream, yearstr, ',');
        std::getline(stream, summary);

        // Remove all spaces using trim function.
        MediaItem::trim(idstr);
        MediaItem::trim(title);
        MediaItem::trim(yearstr);
        MediaItem::trim(summary);

        // Cast string variables to int
        int id = std::stoi(idstr);
        int year = std::stoi(yearstr);

        // Create new TvShow object and return it.
        return new TvShow(id, title, summary, year);
    }

    // The function that get the average length in seconds of an episode.
    double TvShow::getEpisodeAverageLength() const
    {
        // Calculates the total length of all episodes.
        unsigned int totalLength = std::accumulate(m_episodes.begin(), m_episodes.end(), 0,
            [](unsigned int sum, const TvEpisode& episode) {
                return sum + episode.m_length;
            });

        // returns the average length
        return static_cast<double>(totalLength) / m_episodes.size();
    }

    // The function that create a list with episode names that are at least 1 hour long.
    std::list<std::string> TvShow::getLongEpisodes() const
    {
        list<string> longEpisodes;

        // Get list with episode names that are at least 1 hour long using for_each function.
        std::for_each(m_episodes.begin(), m_episodes.end(),
            [&longEpisodes](const TvEpisode& episode) {
                if (episode.m_length >= 3600) // if the length is longer than 1 hour
                {
                    longEpisodes.push_back(episode.m_title); // push it to longEpisodes.
                }
            });

        return longEpisodes;
    }
}