#ifndef _SNExceptions_
#define _SNExceptions_
#include "ex1.h"
using namespace std;
#include <stdexcept>

class SNException_RepeatedUsername : public std::exception
{
public:
	const char* repeatedUsername() { return "The user already exists on Facebook!"; } 
};

class SNException_IllegalDOB : public std::exception
{
public:
	const char* illegalDOB() { return "Error! Invalid date entered!"; }
};

class SNException_UserNotFound : public std::exception
{
public:
	const char* userNotFound() { return "Error! User not found!"; }
};

class SNException_RepeatedPage : public std::exception
{
public:
	const char* repeatedPage() { return "The page already exists on Facebook!"; }
};

class SNException_PageNotFound : public std::exception
{
public:
	const char* pageNotFound() { return "Error! Page not found!"; }
};

class SNException_FileNotOpened : public std::exception
{
public:
	const char* fileNotOpened() { return "Error! Failed to open file!"; }
};

#endif // _UserExceptions_
