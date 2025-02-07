/***********************************************************************
//
// File: collection.cpp
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#include <iostream>
#include <string>
#include <algorithm>// for std::for_each, std::sort
#include <vector>	// for std::vector
#include "collection.h"

using namespace std;
namespace seneca
{
	// Constructor
	Collection::Collection(const std::string& name) : m_name(name) {};

	// Destructor
	Collection::~Collection()
	{
		for (auto item : m_mediaItem)
		{
			delete item;
		}
	}
	
	// A query that returns the name of the collection.
	const std::string& Collection::name() const
	{
		return m_name;
	}

	// A query that returns the number of items in the collection.
	size_t Collection::size() const
	{
		return m_mediaItem.size();
	}

	// The function that stores the address of the callback function (observer) into an attribute.
	void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&))
	{
		m_observer = observer;
	}

	// The operator that adds the item to the collection.
	Collection& Collection::operator+=(MediaItem* item)
	{
		for (const auto& it : m_mediaItem)
		{
			// If item is already in the collection, deletes the parameter.
			if (it->getTitle() == item->getTitle())
			{
				delete item;
				return *this;
			}
		}
		// Add the item to collection.
		m_mediaItem.push_back(item);

		if (m_observer)
		{
			m_observer(*this, *item); // Passing the current object (*this) and the new item as arguments.
		}
		return *this;
	}

	// The operator that returns the item at index idx.
	MediaItem* Collection::operator[](size_t idx) const
	{
		if (idx >= m_mediaItem.size()) // if the index is bigger than size of item throw error
		{
			throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_mediaItem.size()) + "] items.");
		}

		return m_mediaItem[idx];
	}

	// The operator that returns the address of the item with the title title.
	MediaItem* Collection::operator[](const std::string& title) const
	{
		// find the item with the title
		auto it = std::find_if(m_mediaItem.begin(), m_mediaItem.end(),
			[&title](MediaItem* item) {
				return item->getTitle() == title;
			});
		// return address of item if the item exists, return nullptr if not
		return (it != m_mediaItem.end() ? *it : nullptr);
	}

	// The function that remove the quotation marks from the beginning/end of the title and summary.
	void Collection::removeQuotes()
	{
		// STL loop to remove all quotes in the title.
		std::for_each(m_mediaItem.begin(), m_mediaItem.end(), [](MediaItem* item) {

			// Get title from the items.
			string title = item->getTitle();

			// remove quotes using erase function in the title 
			title.erase(std::remove(title.begin(), title.end(), '"'), title.end());
			
			item->setTitle(title);
		});

		// STL loop to remove all quotes in the summary.
		std::for_each(m_mediaItem.begin(), m_mediaItem.end(), [](MediaItem* item) {

			// Get summary from the items.
			string summary = item->getSummary();

			// remove quotes using erase function in the summary. 
			summary.erase(std::remove(summary.begin(), summary.end(), '"'), summary.end());

			item->setSummary(summary);
		});
	}

	// The function that sort in ascending order the collection of items based on the field specified as parameter.
	void Collection::sort(const std::string& field)
	{
		// Using STL sort, sort the items in ascending order.
		std::sort(m_mediaItem.begin(), m_mediaItem.end(), [field](MediaItem* a, MediaItem* b) {
			if (field == "title")
			{
				return a->getTitle() < b->getTitle();
			}
			else if (field == "year")
			{
				return a->getYear() < b->getYear();
			}
			else if (field == "summary")
			{
				return a->getSummary() < b->getSummary();
			}
			return false;
		});
	}

	// Helper that overload the insertion operator to insert the content of a Collection object into an ostream object.
	std::ostream& operator<<(std::ostream& out, const Collection& col)
	{
		// Iterate over all elements in the collection.
		for (const auto& item : col.m_mediaItem)
		{
			if (item)
			{
				// Insert each one into the ostream object .
				out << *item;
			}
		}
		return out;
	}
}