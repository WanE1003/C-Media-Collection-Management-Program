/***********************************************************************
// WorkShop # 3
/***********************************************************************
//
// File: tvShow.h
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include <iostream>
#include <string>
#include <vector>   // for std::vector
#include <list>     // for std::list
#include <sstream>  // for std::istringstream
#include "mediaItem.h"

namespace seneca
{
    // Forward declaration
	class TvShow; 

    // Given TvEpisode struct
	struct TvEpisode
	{
		const TvShow* m_show{};
		unsigned short m_numberOverall{};
		unsigned short m_season{};
		unsigned short m_numberInSeason{};
		std::string m_airDate{};
		unsigned int m_length{};
		std::string m_title{};
		std::string m_summary{};
	};

	class TvShow : public MediaItem // The derived class from MediaItem class
	{
		int m_id; // the identifier of this show
		std::vector<TvEpisode> m_episodes; // a list of episodes

		// Constructor
		TvShow(int id, const std::string& title, const std::string& summary, unsigned short year)
			: MediaItem(title, summary, year), m_id(id) {};
            // call the constructor of base class.

	public:

        // Overrided function to print the information about a tv show.
		void display(std::ostream& out) const override;

        // A class function that receives as parameter the representation of the TV Show as a string and 
        // builds a dynamically allocated object of type TvShow using the information from the string and 
        // returns it to the client.
		static TvShow* createItem(const std::string& strShow); // Declared as static

        // A class function that function builds an episode with the information from the string, searches in the collection 
        // for a TV show with the specified id, and adds it to the list of episodes of the found show.
		template<typename Collection_t> static void addEpisode(Collection_t& col, const std::string& strEpisode);

        // The function that get the average length in seconds of an episode.
		double getEpisodeAverageLength() const;

        // The function that create a list with episode names that are at least 1 hour long.
		std::list<std::string> getLongEpisodes() const;
	};

    template<typename Collection_t>  
    void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode)
    {
        // Check if the parameter is empty or not.
        if (strEpisode.empty() || strEpisode[0] == '#')
        {
            throw "Not a valid episode.";  // if empty throw error.
        }

        // Stream that read data in the string.
        std::istringstream stream(strEpisode);

        // Declare temporary variables
        std::string idStr, episodeNumberStr, seasonNumberStr, episodeInSeasonStr;
        std::string airDate, lengthStr, title, summary;

        // Read each variable until ',' using getline function.
        std::getline(stream, idStr, ',');
        std::getline(stream, episodeNumberStr, ',');
        std::getline(stream, seasonNumberStr, ',');
        std::getline(stream, episodeInSeasonStr, ',');
        std::getline(stream, airDate, ',');
        std::getline(stream, lengthStr, ',');
        std::getline(stream, title, ',');
        std::getline(stream, summary);

        // Remove all spaces using trim function.
        MediaItem::trim(idStr);
        MediaItem::trim(episodeNumberStr);
        MediaItem::trim(seasonNumberStr);
        MediaItem::trim(episodeInSeasonStr);
        MediaItem::trim(airDate);
        MediaItem::trim(lengthStr);
        MediaItem::trim(title);
        MediaItem::trim(summary);

        // Cast string variables to int
        int id = std::stoi(idStr);
        unsigned short episodeNumber = std::stoi(episodeNumberStr);
        unsigned short seasonNumber = seasonNumberStr.empty() ? 1 : std::stoi(seasonNumberStr);
        unsigned short episodeInSeason = std::stoi(episodeInSeasonStr);

        // Read lengthstr string to get the length.
        std::istringstream timeStream(lengthStr);
        int hours, minutes, seconds;
        char colon;
        timeStream >> hours >> colon >> minutes >> colon >> seconds; // read each hours, minutes, seconds.
        unsigned int length = hours * 3600 + minutes * 60 + seconds;

        // Create new tvshow object
        TvShow* tvshow = nullptr;
        for (size_t i = 0; i < col.size(); ++i) 
        {
            // Safely casts col[i] to a TvShow pointer
            tvshow = dynamic_cast<TvShow*>(col[i]);
            // Breaks the loop if tvshow is valid and its id matches the given id
            if (tvshow != nullptr && tvshow->m_id == id)
            {
                break;
            }
            
        }

        // Create TvEpisode object with variables.
        TvEpisode episode{ tvshow, episodeNumber, seasonNumber, episodeInSeason,
            airDate, length, title, summary};

        // Adds episode to the tvshow's list of episodes
        tvshow->m_episodes.push_back(episode);
    }

}
#endif