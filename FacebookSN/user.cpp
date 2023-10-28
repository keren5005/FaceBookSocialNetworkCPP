#include "user.h"
using namespace std;
//***************************************************************

//c'tor
User::User(int day, int month, int year, std::string name) noexcept(false)
{
	this->name = name;

	DOB = insertDateOfBirth(day, month, year);
}

User::User(const User& copiedUser)
{
	this->name = copiedUser.getName();
	this->DOB = copiedUser.getDateOfBirth();
	this->followedPages = copiedUser.getFollowedPages();
	this->friendsArr = copiedUser.getConnections();

	vector<Status*> oldStatuses = copiedUser.getWall();

	vector<Status*>::iterator itr = oldStatuses.begin();
	vector<Status*>::iterator itrEnd = oldStatuses.end();

	for (; itr != itrEnd; ++itr)
	{
		Status* temp = (*itr)->clone();
		wall.push_back(temp);
	}
}

User::User(const User&& other) noexcept(true)
{
	name = other.getName();
	DOB = other.getDateOfBirth();
	wall = other.getWall();
	friendsArr = other.getConnections();
	followedPages = other.getFollowedPages();
}

User::~User()
{
	vector<Status*>::iterator itr = wall.begin();
	vector<Status*>::iterator itrEnd = wall.end();

	for (; itr != itrEnd; ++itr)
		delete (*itr);
}

//insert func

Date insertDateOfBirth(int day, int month, int year) noexcept(false)
{
	Date date;
	
	if ((year < 1900 || year > 2022) || (month < 1 || month > 12) || (day < 1 || day > getMaxDay(month)))
		throw SNException_IllegalDOB();

	date.year = year;
	date.month = month;
	date.day = day;

	return date;
}

//***************************************************************************************************

//get func

const std::string& User::getName() const
{
	return name;
}

const Date& User::getDateOfBirth() const
{
	return DOB;
}

const std::vector<Status*>& User::getWall() const
{
	return wall;
}

//gets list of all friends the user has (the connections with other users)
const std::vector<User*> User::getConnections() const
{
	return friendsArr;
}

const std::vector<Page*> User::getFollowedPages() const
{
	return followedPages;
}

//*******************************************************************************************************

//set func 
void User::setName(std::string& newName)
{
	name = newName;
}

void User::setDateOfBirth(Date& newDOB)
{
	DOB = newDOB;
}

void User::setWall(Status& newStatus)
{

	if (wall.size() == wall.capacity())
		wall.reserve(wall.capacity() * 2);

	wall.push_back(&newStatus);

}

//adds new connection (friend) to user
void User::setConnections(User& newFriend)
{
	if (friendsArr.size() == friendsArr.capacity())
		friendsArr.reserve(friendsArr.capacity() * 2);

	friendsArr.push_back(&newFriend);
}

void User::setfollowedPages(Page& newPage)
{
	if (followedPages.size() == followedPages.capacity())
		followedPages.reserve(followedPages.capacity() * 2);

	followedPages.push_back(&newPage);
}

void User::setStatusText(std::string& text)
{
	Status* newStatus = new Status(text);
	checkMemory(newStatus);

	setWall(*newStatus);
}

void User::setWallSize(unsigned int size)
{
	wall.reserve(size);
}

//********************************************************************************************************

//methods

const User& User::operator+=(User& newFriend)
{
	friendRequest(newFriend);
	return *this;
}
const bool User::operator>(User& other)
{
	vector<User*> otherConnections = other.getConnections();
	return friendsArr.size() > otherConnections.size() ? true : false;
}

//makes two users friends (each user adds the other user to friends array)
bool User::friendRequest(User& requestedUser) noexcept(false)
{
	User* friendPtr;
	std::string friendName;

	friendName = requestedUser.getName();
	friendPtr = findFriend(friendName);
	try 
	{
		if (friendPtr != nullptr) //Exceptions
			throw UserException_AlreadyFriends();

		if (friendPtr == this)
			throw UserException_FriendYourself();
	}
	catch (UserException_AlreadyFriends& exc)
	{
		cout << exc.alreadyFriends() << endl;
		return false;
	}
	catch (UserException_FriendYourself& exc)
	{
		cout << exc.friendYourself() << endl;
		return false;
	}

	setConnections(requestedUser);
	requestedUser.setConnections(*this);
	return true;
}
//removes friendship from two users (each user removes the other user from friends array)
void User::unfriend(std::string& name) noexcept(false)
{	
	User* friendPtr = findFriend(name);
		if (friendPtr == NULL)
			throw UserException_FriendNotFound();

		unfriendOneSide(*friendPtr);
		(* friendPtr).unfriendOneSide(*this);
}
//prints all statuses of user
void User::showAllUserStatuses() noexcept(false)
{
	int size = wall.size();
	if (size == 0)
	{
		try
		{
			throw UserException_EmptyWall();
		}
		catch (UserException_EmptyWall& exc)
		{
			cout << exc.emptyWall() << endl;
		}
	}
	else 
	{
		std::cout << "Showing all statuses for user " << name << ":\n";
		std::cout << "~ ~ ~ ~ ~\n\n";

		std::vector<Status*>::iterator itr = wall.begin();
		std::vector<Status*>::iterator end = wall.end();

		for (; itr != end; ++itr)
		{
			(*itr)->printStatus();
			std::cout << "\n";
		}
		std::cout << "~ ~ ~ ~ ~\n";
	}
}
//show the 10 most recent statuses of each friend the user has
void User::show10LatestFriendsStatuses() noexcept(false)
{
	int amountFriends = friendsArr.size();

	std::vector<User*>::iterator usersItr = friendsArr.begin();
	std::vector<User*>::iterator usersItrEnd = friendsArr.end();

	for (; usersItr != usersItrEnd; ++usersItr)
	{
		int sizeOfWall = (*usersItr)->getWall().size();
		if (sizeOfWall == 0)
		{
			try
			{
				throw UserException_EmptyWall();
			}
			catch (UserException_EmptyWall& exc)
			{
				cout << exc.emptyWall() << endl;
			}
		}
		else
		{
			std::cout << (*usersItr)->getName() << "'s latest statuses:\n\n"; 
			int amountStatuses = (*usersItr)->getWall().size();

			std::vector<Status*> statusesOfFriend = (*usersItr)->getWall();
			std::vector<Status*>::iterator statusItr = statusesOfFriend.begin();

			for (int j = sizeOfWall - 1 ; j >=  sizeOfWall - LATEST_STAT_NUM && amountStatuses > 0; j--, amountStatuses--)
			{
				(*statusItr)->printStatus();
				std::cout << "\n";
				++statusItr;
			}
		}
	}

}
//prints all of user's friends
void User::showAllFriends() noexcept(false)
{
	int size = friendsArr.size();
	if (size == 0)
	{
		try
		{
			throw UserException_NoFriends();
		}
		catch (UserException_NoFriends& exc)
		{
			cout << exc.noFriends() << endl;
		}
	}
	else 
	{
		std::cout << name << "'s friends: \n";
		std::cout << "~ ~ ~ ~ ~\n";

		std::vector<User*>::iterator itr = friendsArr.begin();
		std::vector<User*>::iterator end = friendsArr.end();

		for (; itr != end; ++itr)
		{
			std::cout << (*itr)->getName() << "\n";
		}
		std::cout << "~ ~ ~ ~ ~\n";
	}
}
//prints all pages user follows
void User::showAllFollowedPages() noexcept(false)
{
	int size = followedPages.size();
	if (size == 0) //Exceptions
	{
		try
		{
			throw UserException_NoFollowedPages();
		}
		catch (UserException_NoFollowedPages& exc)
		{
			cout << exc.noFollowedPages() << endl;
		}
	}
	else
	{
		std::cout << name << "'s followed pages: \n";
		std::cout << "~ ~ ~ ~ ~\n";
		std::vector<Page*>::iterator itr = followedPages.begin();
		std::vector<Page*>::iterator end = followedPages.end();

		for (; itr != end; ++itr)
		{
			std::cout << (*itr)->getName() << "\n";
		}
		std::cout << "~ ~ ~ ~ ~\n";
	}
}
//adds a new page to follow. returns true if succeeds, else returns false.
bool User::addPageToFollowedPages(Page& page, bool noErrMsg) noexcept(false)
{
	Page* searchedPage = findPage(page.getName());

	if (searchedPage == nullptr)
	{
		if (followedPages.size() == followedPages.capacity())
			followedPages.reserve(2 * followedPages.capacity());

		followedPages.push_back(&page);
		page.addUserToPageFollowers(*this, true);
		return true;
	}
	else
		try
		{
			if (!noErrMsg) //Meaning, we're not here because of a loop //Exceptions
			{
				throw UserException_AlreadyFollowing();
				
			}
		}
		catch (UserException_AlreadyFollowing& exc)
		{
			cout << exc.alreadyFollowing() << endl;
			return false;
		}
	return true;
}
//removes a page from followed pages. returns true if succeeds, else returns false.
bool User::removePageFromFollowedPages(Page& page, bool noErrMsg)
{
	std::vector<Page*>::iterator itr = followedPages.begin();
	std::vector<Page*>::iterator itrEnd = followedPages.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getName() == page.getName())
		{
			(*itr) = nullptr;

			std::vector<Page*>::iterator itr2 = itr;
			std::vector<Page*>::iterator itr2End = itrEnd - 1;

			for (; itr2 != itr2End; ++itr2)
				(*itr2) = *(itr2 + 1);

			followedPages.pop_back();
			page.removeUserFromPageFollowers(*this, true);
			return true;
		}
	}
	if (!noErrMsg) //Meaning, we're not here because of a loop //Exceptions
	{
		try
		{
			throw UserException_PageNotFound();
		}
		catch (UserException_PageNotFound& exc)
		{
			cout << exc.pageNotFound() << endl;
		}
		return false;
	}
	return true;
}
//searches array of friends to find a user's name. Returns pointer to user if found, else returns nullptr.
User* User::findFriend(const std::string& name) {

	std::vector<User*>::iterator itr = friendsArr.begin();
	std::vector<User*>::iterator itrEnd = friendsArr.end();

	for (; itr != itrEnd; ++itr)
	{
		if (name == (*itr)->getName())
			return (*itr);
	}
	return nullptr;
}
//searches array of followed pages to find a page's name. Returns pointer to page if found, else returns nullptr.
Page* User::findPage(const std::string& name) {
	std::vector<Page*>::iterator itr = followedPages.begin();
	std::vector<Page*>::iterator itrEnd = followedPages.end();

	for (; itr != itrEnd; ++itr)
	{
		if (name == (*itr)->getName())
			return (*itr);
	}
	return nullptr;
}
//creates a new status for user.
void User::createNewStatus()
{

	unsigned int type;
	cout << "Please select the type of status you'd like to create:\n"
		<< "1 - Text only.\n"
		<< "2 - Text & Image.\n"
		<< "3 - Image & Video.\n";

	cin >> type;
	
	std::string content1;
	std::string content2;

	Status* newStatus;

	switch (type)
	{
	case 1:
		cout << "Please type in your text:" << endl;
		cin >> content1;
		newStatus = new Status(content1);
		break;
	case 2:
		cout << "Please type in your text:" << endl;
		cin >> content1;
		cout << "Please type in your file name:" << endl;
		cin >> content2;
		newStatus = new StatusImage(content1, content2);
		break;
	case 3:
		cout << "Please type in your text:" << endl;
		cin >> content1;
		cout << "Please type in your file name:" << endl;
		cin >> content2;
		newStatus = new StatusVideo(content1, content2);
		break;
	default:
		throw UserException_IllegalStatus();
	}
	setWall(*newStatus);
}
void User::insertStatus(Status* newStatus)
{
	wall.push_back(newStatus);
}
void User::reserveConnections(unsigned int newSize)
{
	friendsArr.reserve(newSize);
}
void User::reserveFollowedPages(unsigned int newSize)
{
	followedPages.reserve(newSize);
}
//private func that removes a user from another user's friends list.
void User::unfriendOneSide(User& reqwestedUser)
{
	int amountUsers = friendsArr.size();
	bool isFound = false;

	std::vector<User*>::iterator itr = friendsArr.begin();
	std::vector<User*>::iterator itrEnd = friendsArr.end();

	for (;  itr != itrEnd && !isFound; ++itr)
	{
		if ((*itr)->getName() == reqwestedUser.getName())
		{
			std::vector<User*>::iterator itr2 = itr;
			std::vector<User*>::iterator itr2End = itrEnd - 1;

			for (; itr2 != itr2End; ++itr2)
				*itr2 = *(itr2 + 1);

			isFound = true;
		}
	}

	friendsArr.pop_back();
}