#ifndef _UserExceptions_
#define _UserExceptions_
#include "ex1.h"
using namespace std;
#include <stdexcept>

class UserException_FriendNotFound : public std::exception
{
public:
	const char* friendNotFound() { return "User not found in friends list!";}
};

class UserException_NoFollowedPages : public std::exception
{
public:
	const char* noFollowedPages() { return "You're not following any pages!"; }
};

class UserException_PageNotFound : public std::exception
{
public:
	const char* pageNotFound() { return "Page not found in followed pages list!"; }
};

class UserException_AlreadyFriends : public std::exception
{
public:
	const char* alreadyFriends() { return "You're already friends with that user!"; }
};

class UserException_AlreadyFollowing : public std::exception
{
public:
	const char* alreadyFollowing() { return "You're already following that page!"; }
};

class UserException_FriendYourself : public std::exception
{
public:
	const char* friendYourself() { return "You're already friends with that user!"; }
};

class UserException_EmptyWall : public std::exception
{
public:
	const char* emptyWall() { return "this user has no statuses on their wall!"; }
};

class UserException_NoFriends : public std::exception
{
public:
	const char* noFriends() { return "this user has no friends at the moment!"; }
};

class UserException_IllegalStatus : public std::exception
{
public:
	const char* illegalStatus() { return "Failed to create a status - Illegal type!"; }
};

#endif // _UserExceptions_
