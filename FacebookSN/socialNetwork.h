#ifndef __FACEBOOK_H
#define __FACEBOOK_H

#include "ex1.h"
#include "Page.h"
#include "user.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


class User;
class Page;
class Status;

class SocialNetwork
{
	std::vector<User*> allUsers; // users -> amount users -> {name, ....}  \n , 
	std::vector<Page*> allPages;

public:
	SocialNetwork() = default; //c'tor
	SocialNetwork(const SocialNetwork& facebook) = delete;
	~SocialNetwork();
	
	//get funcs:
	const std::vector<User*> getAllUsers();
	const std::vector<Page*> getAllPages();
	const int getUsersAmount();
	const int getPagesAmount();

	//set funcs:
	void setUsersAmount(unsigned int numOfUsers);
	void setPagesAmount(unsigned int numOfPages);
	User* setUser(int day, int month, int year, std::string& name);
	Page* setPage(const std::string& name);

	//methods
	User* findUser(const std::string name);
	Page* findPage(const std::string name);
	void showAllAccounts();
	void initializeFaceBookUsers();
	void insertUser(User* newUser);
	void insertPage(Page* newPage);
};

#endif
