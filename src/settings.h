/***********************************************************************
//
// File: settings.h
// Date: Nov 14,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
//
***********************************************************************/

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca {
	struct Settings
	{
		short m_maxSummaryWidth = 80; // It will store the maximum width of text then printing the summary of a media item. 
		bool m_tableView = false; // when true, print to screen the information about the media items formatted as a table.
	};

	extern Settings g_settings; // declare a global variable of this type named g_settings
}
#endif