#ifndef _PAGE_H
#define _PAGE_H

#include "ex1.h"
#include "user.h"
#include "status.h"
#include "socialnetwork.h"
#include <vector>
#include <string>

class Status;
class User;
class SocialNetwork;

class Page
{
	std::string name;
	std::vector<User*> followers;
	std::vector<Status*> wall;
public:
	Page(const std::string& name); //c'tor
	Page(const Page& copiedPage); // copy c'tor 
	Page(const Page&& other) noexcept(true); // move c'tor 
	~Page(); // d'tor
	
	//get func:
	const std::string& getName() const;
	const std::vector<User*>& getFollowers() const;
	const std::vector<Status*>& getWall() const;

	//set func:
	void setname(std::string& newName);
	void setFollowers(User& newFollower);
	void setWall(Status& newStatus);
	void setStatus();
	void setStatusText(std::string& text);
	void setWallSize(unsigned int size);

	//methods
		//operators:
	const Page& operator+=(User& user);
	const bool operator>(Page& other);

	void showAllStatuses();
	bool addUserToPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	bool removeUserFromPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	void showUsersList();
	User* findFollower(const std::string& name);
	void insertStatus(Status* newStatus);
};

#endif
