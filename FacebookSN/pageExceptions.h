#ifndef _PageExceptions_
#define _PageExceptions_
#include "ex1.h"
using namespace std;
#include <stdexcept>

class PageException_FollowerNotFound : public std::exception
{
public:
	const char* followerNotFound() { return "User not found in followers list!"; }
};
class PageException_UserEmptyWall : public std::exception
{
public:
	const char* noStatusesToPrint() { return "You have no statuses on your wall!"; }
};
class PageException_UserAlreadyFollows : public std::exception
{
public:
	const char* userAlreadyFollows() { return "This user is already following your page!"; }
};
class PageException_NoFollowers : public std::exception
{
public:
	const char* noFollowers() { return "Your page has no followers!"; }
};
class PageException_PageEmptyWall : public std::exception
{
public:
	const char* emptyWall() { return "this page has no statuses on their wall!"; }
};

#endif // _PageExceptions_