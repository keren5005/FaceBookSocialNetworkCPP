#ifndef _TIME_H
#define _TIME_H

const int MIN_PHY_SIZE = 3;

class User;
class Status;
class Page;
class SocialNetwork;

struct Date
{
	int day;
	int month;
	int year;

};

struct Time
{
	Date date;
	int hours;
	int minutes;
};

struct tm* localtime(const time_t* time);

#endif
