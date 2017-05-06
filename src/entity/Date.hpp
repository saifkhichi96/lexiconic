#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>

using std::istream;
using std::ostream;
using std::endl;

/*
Date structure stores date/time. It's intended to ease the time-related
calculations needed for periodic update feature of the application.
*/
struct Date
{
	int				day;								// Day of the month		(1-31)
	int				month;								// Month of the year	(1-12)
	int				year;								// The A.D. Year
	int				seconds;							// Number of seconds	(0-59)
	int				minutes;							// Number of minutes	(0-59)
	int				hours;								// Number of hours		(0-23)

					Date();								// Default public constructor
	int				operator  - (const Date&);			// Calculates number of days between two Dates
	friend ostream& operator << (ostream&, Date&);		// Writes Date object to an output stream
	friend istream& operator >> (istream&, Date&);		// Reads Date object from an input stream
};

#endif