#include "Date.hpp"
#include <fstream>
#include <ctime>


/*
Default constructor of the Date structure. Initializes members with
current date/time.
*/
Date::Date()
{
	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	day = timeinfo->tm_mday;
	month = timeinfo->tm_mon;
	year = 1900 + timeinfo->tm_year;

	seconds = timeinfo->tm_sec;
	minutes = timeinfo->tm_min;
	hours = timeinfo->tm_hour;
}


/*
Calculates number of days between two Dates
: parameter: const Date& date (date whose difference is to be calculated
			 from current date).
: returns number of days passes between two given dates.
*/
int Date::operator-(const Date& date)
{
	float x = (day - date.day) +
		30.4375f * (month - date.month) +
		365.2500f * (year - date.year);

	return static_cast<int>(x);
}


/*
Writes a Date object to an output stream.
: parameters: ostream& cout (output stream to which the Date object is to
			  be written).
			  Date& d (reference to the Date object which is to be written).
: returns output stream object's reference to allow chaining as in
  cout << Date_1 << Date_2;
*/
ostream& operator << (ostream& cout, Date& d)
{
	cout << d.day << endl;
	cout << d.month << endl;
	cout << d.year << endl;

	return cout;
}


/*
Reads a Date object from an input stream.
: parameters: istream& cin (input stream from which the Date object is to
			  be read).
			  Date& d (reference to the Date object in which the read Date
			  is to be stored).
: returns input stream object's reference to allow chaining as in
  cin >> Date_1 >> Date_2;
*/
istream& operator >> (istream& cin, Date& d)
{
	cin >> d.day;
	cin >> d.month;
	cin >> d.year;

	return cin;
}