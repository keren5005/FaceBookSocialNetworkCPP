#include "ex1.h"
//****************** MISCELLANEOUS ******************

//the function terminates the system
void facebookTerminate()
{
	cout << "Facebook has terminated due to an error! Please contact support!\n";
	exit(1);
}

void checkMemory(void* ptr) 
{
	if (ptr == nullptr) {
		std::cout << "Memory allocation failed!";
		exit(1);
	}
}
//the function finds the maximum day in a month 
int getMaxDay(int month) 
{
	switch (month) 
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		return 28;
	}
	//Assuming that the month received is legal.
}

//****************** MANAGE FACEBOOK ******************

//the menu of the system
void manageSystem(SocialNetwork& system)
{
	int input;
	do
	{
		std::cout << "Choose an action:\n";

		std::cout << "1 - Show all existing accounts in the system\n";
		std::cout << "0 - Return to main menu\n";

		std::cin >> input;

		switch (input)
		{
		case 0:
			break;
		case 1:
			system.showAllAccounts();
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}
//sign in\up as a user
void manageUsers(SocialNetwork& system)
{
	int input;
	do
	{
		if (system.getUsersAmount() == 0)
		{
			std::cout << "No users exist in the system. Please create a new user: \n";
			input = 1;
		}
		else
		{
			std::cout << "Choose an action:\n";

			std::cout << "1 - Sign up (Create a new user)\n";
			std::cout << "2 - Log in (Choose a user)\n";
			std::cout << "0 - Return to main menu\n";

			std::cin >> input;
		}

		User* user;

		switch (input)
		{
		case 0:
			break;
		case 1:
			user = addUser(system);
			userMenu(*user, system);
			break;
		case 2:
			user = findUser(system);
			userMenu(*user, system);
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}
// sign in/up as a page
void managePages(SocialNetwork& system)
{
	int input;
	do
	{
		if (system.getPagesAmount() == 0)
		{
			std::cout << "No pages exist in the system. Please create a new page: \n";
			input = 1;
		}
		else
		{
			std::cout << "Choose an action:\n";

			std::cout << "1 - Create a new page\n";
			std::cout << "2 - Manage existing page\n";
			std::cout << "0 - Return to main menu\n";

			std::cin >> input;
		}

		Page* page;

		switch (input)
		{
		case 0:
			break;
		case 1:
			page = addPage(system);
			pageMenu(*page, system);
			break;
		case 2:
			page = findPage(system);
			pageMenu(*page, system);
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
		}

	} while (input != 0);
}

//****************** MENUS ******************

//the menu of the user
void userMenu(User& user, SocialNetwork& system)
{
	int input;
	bool success;

	std::cout << "~X~X Welcome, " << user.getName() << "! X~X~\n";

	do
	{
		std::cout << "Choose an action:\n";

		std::cout << "1 - Add a new status\n";
		std::cout << "2 - Show all of my statuses\n";
		std::cout << "3 - Show the latest statuses from my friends\n";
		std::cout << "4 - Send friend request\n";
		std::cout << "5 - Unfriend a user\n";
		std::cout << "6 - Follow a new page\n";
		std::cout << "7 - Unfollow a page\n";
		std::cout << "8 - Show friends list\n";
		std::cout << "9 - Show followed pages\n";
		std::cout << "0 - Log out\n";

		std::cin >> input;

		switch (input)
		{
		case 0:
			std::cout << "You logged out of " << user.getName() << ".\n\n";
			break;
		case 1:
			try
			{
			user.createNewStatus();
			cout << "\n" << user.getName() << ", Your new status has been posted!\n\n";
			}
			catch (UserException_IllegalStatus& exc)
			{
				cout << exc.illegalStatus();
			}
			break;
		case 2:
			user.showAllUserStatuses();
			break;
		case 3:
			if (user.getConnections().size() == 0)
				try {
					throw UserException_NoFriends();
				}
				catch (UserException_NoFriends& exc)
				{
					cout << exc.noFriends();
				}
			else
				user.show10LatestFriendsStatuses();
			break;
		case 4:
			success = sendFriendRequest(user, system);
			if (success)
				std::cout << "\n" << "They have accepted your friend request!\n";
			break;
		case 5:
			if (user.getConnections().size() == 0)
				try {
					throw UserException_NoFriends();
				}
				catch (UserException_NoFriends& exc)
				{
					cout << exc.noFriends() << endl;
				}
			else
			{
				unfollowFriend(user);
				std::cout << "\n" << "You're no longer friends!\n";
			}
			break;
		case 6:
			followPage(user, system);
			break;
		case 7:
			unfollowPage(user, system);
			break;
		case 8:
			user.showAllFriends();
			break;
		case 9:
			user.showAllFollowedPages();
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}
// the menu of the page
void pageMenu(Page& page, SocialNetwork& system)
{
	int input;

	std::cout << "~X~X You are now logged into " << page.getName() << "! X~X~\n";

	do
	{
		std::cout << "Choose an action:\n";

		std::cout << "1 - Add a new status\n";
		std::cout << "2 - Show all of my statuses\n";
		std::cout << "3 - Add a new follower\n";
		std::cout << "4 - Remove an existing follower\n";
		std::cout << "5 - Show followers list\n";
		std::cout << "0 - Log out\n";

		std::cin >> input;

		switch (input)
		{
		case 0:
			std::cout << "You logged out of " << page.getName() << ".\n\n";
			break;
		case 1:
			page.setStatus();
			break;
		case 2:
			page.showAllStatuses();
			break;
		case 3:
			addFollowerToPage(page, system);
			break;
		case 4:
			if (page.getFollowers().size() == 0)
				try
				{
				throw PageException_NoFollowers();
				}
				catch (PageException_NoFollowers& exc)
				{
					cout << exc.noFollowers() << endl;
				}
			else
				removeFollowerFromPage(page, system);
			break;
		case 5:
			page.showUsersList();
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}

//****************** USER ACTIONS ******************

User* addUser(SocialNetwork& system) noexcept(false)
{
	std::string name;
	int day, month, year;
	User* user = nullptr;
	bool legalDOB;

	std::cin.ignore();
	do 
	{
		try
		{
			std::cout << "Enter your name: ";
			getline(std::cin, name);

			user = system.findUser(name);
			if (user != nullptr)
				throw SNException_RepeatedUsername();
		}
		catch (SNException_RepeatedUsername& exc)
		{
			cout << exc.repeatedUsername();
			cout << "Try again! \n";
		}
	} while (user != nullptr);

	User* newUser;

	do {
		
			std::cout << "Please enter your date of birth in the following format: <day> <month> <year> \n";
			std::cin >> day >> month >> year;

		try
		{
			newUser = system.setUser(day, month, year, name);
			return newUser;
		}
		catch(SNException_IllegalDOB& exc)
		{
			cout << exc.illegalDOB() << " Try again!";
			cout << endl;
			legalDOB = false;
		}
	} while (!legalDOB);
}

User* findUser(SocialNetwork& system) noexcept(false)
{
	char name[MAX_NAME_LEN];
	User* userPtr;
	std::cin.ignore(); //Get rid of buffer chars if there are any
	do
	{
		std::cout << "Choose a user: ";
		std::cin.getline(name, MAX_NAME_LEN);

		userPtr = system.findUser(name);
		try
		{

			if (userPtr == nullptr)
				throw SNException_UserNotFound();
		}
		catch (SNException_UserNotFound& exc)
		{
			cout << exc.userNotFound();
		}
	} while (userPtr == nullptr);
	return userPtr;
}

bool sendFriendRequest(User& user, SocialNetwork& system) noexcept(false)
{
	char friendName[MAX_NAME_LEN];
	User* friendPtr;
	bool validInput;
	std::cin.ignore(); //In case of chars in buffer
	do 
	{
		validInput = true;
		std::cout << "Choose a user to send a friend request to: ";
		std::cin.getline(friendName, MAX_NAME_LEN);

		friendPtr = system.findUser(friendName);
		try
		{
			if (friendPtr == nullptr)
			{
				validInput = false;
				throw SNException_UserNotFound();
			}
		}
		catch (SNException_UserNotFound& exc)
		{
			cout << exc.userNotFound();
			cout << " Try again!" << endl;
		}
		
	} while (!validInput);

	return user.friendRequest(*friendPtr);
}

void unfollowFriend(User& user) 
{
	std::string friendName;
	User* friendPtr = nullptr;
	bool legalInput = false;
	std::cin.ignore();
	do
	{
		std::cout << "Choose a user to unfriend: ";
		getline(std::cin, friendName);

		try
		{
			user.unfriend(friendName);
			legalInput = true;
		}
		catch (UserException_FriendNotFound& exc) 
		{
			cout << exc.friendNotFound() << " Please try again." << endl;
		}
	} while (legalInput == false);

	
}

//****************** PAGE ACTIONS ******************

Page* addPage(SocialNetwork& system) noexcept(false) 
{
	std::string name;
	Page* page = nullptr;
	std::cin.ignore(); //gets chars from buffer
	do 
	{
		std::cout << "Enter your page's name: ";
		getline(std::cin, name);

		try
		{
			page = system.findPage(name);
			if (page != nullptr)
				throw SNException_RepeatedPage();
		}
		catch (SNException_RepeatedPage& exc)
		{
			cout << exc.repeatedPage() << " Please select a different name." << endl;
		}
	} while (page != nullptr);

	return system.setPage(name);
}

Page* findPage(SocialNetwork& system) noexcept(false) 
{
	char name[MAX_NAME_LEN];
	Page* pagePtr;
	std::cin.ignore(); //In case of chars in buffer
	do
	{
		std::cout << "Choose a page: ";
		std::cin.getline(name, MAX_NAME_LEN);

		pagePtr = system.findPage(name);
		try
		{
			if (pagePtr == nullptr)
				throw SNException_PageNotFound();
		}
		catch (SNException_PageNotFound& exc)
		{
			cout << exc.pageNotFound() << " Please try again." << endl;
		}
	} while (pagePtr == nullptr);
	return pagePtr;
}

void followPage(User& user, SocialNetwork& system) noexcept(false)
{
	char pageName[MAX_NAME_LEN];
	Page* pagePtr;
	std::cin.ignore(); //In case of chars in buffer
	do
	{
		std::cout << "Please enter the page you'd like to follow: ";
		std::cin.getline(pageName, MAX_NAME_LEN);

		pagePtr = system.findPage(pageName);
		try
		{
			if (pagePtr == nullptr)
				throw SNException_PageNotFound();
		}
		catch (SNException_PageNotFound& exc)
		{
			cout << exc.pageNotFound() << " Please try again." << endl;
		}
	} while (pagePtr == nullptr);

	if (user.addPageToFollowedPages(*pagePtr))
		std::cout << "You are now following " << pageName << "!\n";
}

void unfollowPage(User& user, SocialNetwork& system) noexcept(false)
{
	if (user.getFollowedPages().size() == 0)
		try
		{
			throw UserException_NoFollowedPages();
		}
		catch (UserException_NoFollowedPages& exc)
		{
			cout << exc.noFollowedPages() << endl;
		}
	else
	{
		char pageName[MAX_NAME_LEN];
		Page* pagePtr = nullptr;
		std::cin.ignore(); //In case of chars in buffer
		do
		{
			std::cout << "Choose a page to unfollow: ";
			std::cin.getline(pageName, MAX_NAME_LEN);
			try
			{
				pagePtr = user.findPage(pageName);

				if (pagePtr == NULL)
					throw UserException_PageNotFound();
			}
			catch(UserException_PageNotFound& exc)
			{
				cout << exc.pageNotFound() << " Please try again." << endl;
			}
		} while (pagePtr == nullptr);

		if (user.removePageFromFollowedPages(*pagePtr))
			std::cout << "You are no longer following " << pageName << "!\n";
	}
}

void addFollowerToPage(Page& page, SocialNetwork& system) noexcept(false)
{
	char followerName[MAX_NAME_LEN];
	User* followerPtr = nullptr;
	User* alreadyFollows;
	bool validInput;
	std::cin.ignore(); //In case of chars in buffer
	do
	{
		validInput = true;
		std::cout << "Choose a user to follow your page: ";
		std::cin.getline(followerName, MAX_NAME_LEN);
		
		try
		{
			followerPtr = system.findUser(followerName);
			if (followerPtr == nullptr) {
				validInput = false;
				throw SNException_UserNotFound();
			}
		}
		catch (SNException_UserNotFound& exc)
		{
			cout << exc.userNotFound() << " Please try again." << endl;
		}
		alreadyFollows = page.findFollower(followerName);
		if (alreadyFollows != nullptr) {
			std::cout << followerName << " is already following you! Please try again.\n";
			validInput = false;
		}
	} while (!validInput);

	if (page.addUserToPageFollowers(*followerPtr))
		std::cout << followerName << " is now following your page!\n";
}

void removeFollowerFromPage(Page& page, SocialNetwork& system) noexcept(false)
{
	char followerName[MAX_NAME_LEN];
	User* followerPtr = nullptr;
	std::cin.ignore(); //gets chars from buffer
	do
	{
		std::cout << "Choose a user to remove from followers: ";
		std::cin.getline(followerName, MAX_NAME_LEN);

		followerPtr = page.findFollower(followerName);

		try
		{
			if (followerPtr == NULL)
				throw PageException_FollowerNotFound();
		}
		catch (PageException_FollowerNotFound& exc)
		{
			cout << exc.followerNotFound() << " Please try again." << endl;
		}
	} while (followerPtr == nullptr);

	page.removeUserFromPageFollowers(*followerPtr);

	std::cout << followerName << " is no longer following your page!\n";
}

void loadData(ifstream& file, SocialNetwork& system)
{
	file.open("data.txt");
	try
	{
		if (!file.is_open())
			throw SNException_FileNotOpened();
	}
	catch (SNException_FileNotOpened& exc)
	{
		cout << exc.fileNotOpened();
		exit(1);
	}

	file.seekg(0, std::ios::end);
	if (file.tellg() == 0) //If file is empty
	{
		system.initializeFaceBookUsers();
		return;
	}
	file.seekg(0, std::ios::beg);

	//Since data from the file derives from a previous run of the program, 
	//the data in the file is necessarily valid.


	unsigned int numOfUsers, numOfPages;

	file >> numOfUsers >> numOfPages;
	system.setUsersAmount(numOfUsers);
	system.setPagesAmount(numOfPages);

	file.get();
	for (unsigned int userIdx = 0; userIdx < numOfUsers; userIdx++) //For each user:
	{
		std::string name;
		getline(file, name);

		Time time;
		file >> time.date.day >> time.date.month >> time.date.year;

		User* newUser = new User(time.date.day, time.date.month, time.date.year, name);

		unsigned int numOfStatuses;
		file >> numOfStatuses;
		newUser->setWallSize(numOfStatuses);

		for (unsigned int statusIdx = 0; statusIdx < numOfStatuses; statusIdx++) //For each user status
		{
			unsigned int statusType; //1 - text, 2 - image, 3 - video
			file >> statusType;

			file >> time.date.day >> time.date.month >> time.date.year >> time.hours >> time.minutes;

			std::string text, extra; //extra is either image or video, if file type isn't plain text.
			file.get();
			getline(file, text);
			if (statusType != 1)
				getline(file, extra);

			Status* newStatus;

			switch (statusType)
			{
			case 2:
				newStatus = new StatusImage(extra, text);
				break;
			case 3:
				newStatus = new StatusVideo(extra, text);
				break;
			default:
				newStatus = new Status(text);
			}
			newStatus->setTime(time);

			newUser->insertStatus(newStatus);

		}
		system.insertUser(newUser);

		if (numOfStatuses == 0) //Meaning the last thing we read from the file is an int
			file.get();
	}

	for (unsigned int pageIdx = 0; pageIdx < numOfPages; pageIdx++) //For each page:
	{
		std::string name;
		getline(file, name);

		Time time;

		Page* newPage = new Page(name);

		unsigned int numOfStatuses;
		file >> numOfStatuses;
		newPage->setWallSize(numOfStatuses);

		for (unsigned int statusIdx = 0; statusIdx < numOfStatuses; statusIdx++) //For each user status
		{
			unsigned int statusType; //1 - text, 2 - image, 3 - video
			file >> statusType;

			file >> time.date.day >> time.date.month >> time.date.year >> time.hours >> time.minutes;

			std::string text, extra; //extra is either image or video, if file type isn't plain text.
			
			file.get();
			getline(file, text);
			if (statusType != 1)
				getline(file, extra);

			Status* newStatus;

			switch (statusType)
			{
			case 2:
				newStatus = new StatusImage(extra, text);
				break;
			case 3:
				newStatus = new StatusVideo(extra, text);
				break;
			default:
				newStatus = new Status(text);
			}
			newStatus->setTime(time);

			newPage->insertStatus(newStatus);
		}
		system.insertPage(newPage);

		if (numOfStatuses == 0) //Meaning the last thing we read from the file is an int
			file.get();
	}
	vector<User*> allUsers = system.getAllUsers();
	vector<User*>::iterator Uitr = allUsers.begin();

	for (unsigned int userIdx = 0; userIdx < numOfUsers; userIdx++, Uitr++) //For each user:
	{
		unsigned int numOfFriends;
		file >> numOfFriends;
		if (numOfFriends != 0)
			(*Uitr)->reserveConnections(numOfFriends);

		file.get();
		for (unsigned int friendIdx = 0; friendIdx < numOfFriends; friendIdx++) //For each friend
		{
			std::string friendName;
			getline(file, friendName);
			
			User* seekFriend = (*Uitr)->findFriend(friendName); //Searches if users are already friends
			if (seekFriend == nullptr) {
				User* newFriend = system.findUser(friendName);
				(*Uitr)->friendRequest(*newFriend);
			}
		}

		unsigned int numOfFanPages;
		file >> numOfFanPages;
		if(numOfFanPages != 0)
			(*Uitr)->reserveFollowedPages(numOfFanPages);

		file.get();
		for (unsigned int pageIdx = 0; pageIdx < numOfFanPages; pageIdx++) //For each page
		{
			std::string pageName;
			getline(file, pageName);

			Page* newFollowedPage = system.findPage(pageName);
			(*Uitr)->addPageToFollowedPages(*newFollowedPage);
		}
	}
	file.close();
}

void saveData(ofstream& file, SocialNetwork& system)
{
	file.open("data.txt");
	try
	{
		if (!file.is_open())
			throw SNException_FileNotOpened();
	}
	catch (SNException_FileNotOpened& exc)
	{
		cout << exc.fileNotOpened();
		exit(1);
	}

	unsigned int usersAmount = system.getUsersAmount();
	unsigned int pagesAmount = system.getPagesAmount();

	file << usersAmount << endl << pagesAmount << endl;

	vector<User*> users = system.getAllUsers();
	vector<Page*> pages = system.getAllPages();

	vector<User*>::iterator Uitr = users.begin();

	for (unsigned int userIdx = 0; userIdx < usersAmount; userIdx++, Uitr++) //For each user
	{
		file << (*Uitr)->getName() << endl;
		
		Date date = (*Uitr)->getDateOfBirth();
		file << date.day << endl << date.month << endl << date.year << endl;

		vector<Status*> wall = (*Uitr)->getWall();
		vector<Status*>::iterator Sitr = wall.begin();

		file << wall.size() << endl;

		for (unsigned int statusIdx = 0; statusIdx < wall.size(); statusIdx++, Sitr++) //For each status
		{
			if (typeid(*Sitr) == typeid(StatusVideo*))
				file << 3 << endl;
			else if (typeid(*Sitr) == typeid(StatusImage*))
				file << 2 << endl;
			else
				file << 1 << endl;

			Time time = (*Sitr)->getTime();
			file << time.date.day << endl << time.date.month << endl << time.date.year << endl << time.hours << endl << time.minutes << endl;

			file << (*Sitr)->Status::getStatus() << endl;
			if (typeid(*Sitr) == typeid(StatusVideo*))
				file << ((StatusVideo*)(*Sitr))->getVideo() << endl;
			else if (typeid(*Sitr) == typeid(StatusImage*))
				file << ((StatusImage*)(*Sitr))->getImage() << endl;
		}
	}

	vector<Page*>::iterator Pitr = pages.begin();

	for (unsigned int pageIdx = 0; pageIdx < pagesAmount; pageIdx++, Pitr++) //For each page
	{
		file << (*Pitr)->getName() << endl;

		vector<Status*> wall = (*Pitr)->getWall();
		vector<Status*>::iterator Sitr = wall.begin();

		file << wall.size() << endl;

		for (unsigned int statusIdx = 0; statusIdx < wall.size(); statusIdx++, Sitr++) //For each status
		{
			if (typeid(*Sitr) == typeid(StatusVideo*))
				file << 3 << endl;
			else if (typeid(*Sitr) == typeid(StatusImage*))
				file << 2 << endl;
			else
				file << 1 << endl;

			Time time = (*Sitr)->getTime();
			file << time.date.day << endl << time.date.month << endl << time.date.year << endl << time.hours << endl << time.minutes << endl;

			file << (*Sitr)->Status::getStatus() << endl;
			if (typeid(*Sitr) == typeid(StatusVideo*))
				file << ((StatusVideo*)(*Sitr))->getVideo() << endl;
			else if (typeid(*Sitr) == typeid(StatusImage*))
				file << ((StatusImage*)(*Sitr))->getImage() << endl;
		}
	}

	Uitr = users.begin();

	for (unsigned int userIdx = 0; userIdx < usersAmount; userIdx++, Uitr++) //For each user
	{
		vector<User*> friends = (*Uitr)->getConnections();

		file << friends.size() << endl;

		vector<User*>::iterator Fitr = friends.begin();

		for (unsigned int friendIdx = 0; friendIdx < friends.size(); friendIdx++, Fitr++)
		{
			file << (*Fitr)->getName() << endl;
		}

		vector<Page*> likedPages = (*Uitr)->getFollowedPages();

		file << likedPages.size() << endl;

		vector<Page*>::iterator Pitr = likedPages.begin();

		for (unsigned int pagesIdx = 0; pagesIdx < likedPages.size(); pagesIdx++, Pitr++)
		{
			file << (*Pitr)->getName() << endl;
		}
	}

	file.close();
}

