#ifndef _EX1_H 
#define _EX1_H 
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include "structs.h"
#include "socialNetwork.h"
#include "page.h"
#include "user.h"
#include <vector>
#include <string>
#include <typeinfo>
#include "socialNetworkExceptions.h"
#include "userExceptions.h"
#include "pageExceptions.h"
#pragma warning (disable: 4996)

constexpr int MAX_NAME_LEN = 30;
constexpr int MIN_CONNECTIONS_NUM = 3;
constexpr int MIN_PAGES_NUM = 3;
constexpr int MIN_STATUSES_NUM = 3;
constexpr int LATEST_STAT_NUM = 10;
constexpr int TIME_STR_LEN = 25;
constexpr int MAX_STATUS_LEN = 120;
constexpr int MIN_FOLLOWERS_NUM = 3;
constexpr int MIN_STATUS_NUM = 2;
constexpr int MAX_PAGE_LEN_NAME = 100;
constexpr int BIG = 128;

void facebookTerminate();

void checkMemory(void* ptr);
int getMaxDay(int month);

void manageSystem(SocialNetwork& system);
void manageUsers(SocialNetwork& system);
void managePages(SocialNetwork& system);
void userMenu(User& user, SocialNetwork& system);
void pageMenu(Page& page, SocialNetwork& system);

User* addUser(SocialNetwork& system);
User* findUser(SocialNetwork& system);
Page* addPage(SocialNetwork& system);
Page* findPage(SocialNetwork& system);

bool sendFriendRequest(User& user, SocialNetwork& system);
void unfollowFriend(User& user);
void followPage(User& user, SocialNetwork& system);
void unfollowPage(User& user, SocialNetwork& system);
void addFollowerToPage(Page& page, SocialNetwork& system);
void removeFollowerFromPage(Page& page, SocialNetwork& system);
Date insertDateOfBirth(int day, int month, int year);

void loadData(ifstream& file, SocialNetwork& system);
void saveData(ofstream& file, SocialNetwork& system);
#endif
