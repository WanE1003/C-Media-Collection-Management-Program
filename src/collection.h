/***********************************************************************
//
// File: collection.h
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>
#include <string>
#include <vector> // vector
#include "mediaItem.h"

namespace seneca
{
	class Collection
	{
		std::string m_name; // The name of collection
		std::vector<MediaItem*> m_mediaItem; // Collection of media items.
		void (*m_observer)(const Collection&, const MediaItem&) = nullptr; // observer function pointer

	public:
		// sets the name of the collection to the string referred to by the parameter and sets all other attributes to their default value.
		Collection(const std::string& name); 
		Collection(const Collection&) = delete;
		Collection(const Collection&&) = delete;
		Collection& operator=(const Collection&) = delete;
		Collection& operator=(const Collection&&) = delete;
		~Collection(); // a destructor

		// a query that returns the name of the collection.
		const std::string& name() const;  
		// a query that returns the number of items in the collection.
		size_t size() const;  
		// stores the address of the callback function (observer) into an attribute.
		void setObserver(void (*observer)(const Collection&, const MediaItem&));  

		// adds the item to the collection, only if the collection doesn't contain an item with the same title.
		Collection& operator+=(MediaItem* item); 
		// returns the item at index idx.
		MediaItem* operator[](size_t idx) const; 
		// returns the address of the item with the title title.
		MediaItem* operator[](const std::string& title) const;  

		// remove the quotation marks from the beginning/end of the title and summary.
		void removeQuotes(); 
		// sort in ascending order the collection of items based on the field specified as parameter.
		void sort(const std::string& field);  

		friend std::ostream& operator<<(std::ostream& out, const Collection& col);
	};

}
#endif // !SENECA_COLLECTION_H
