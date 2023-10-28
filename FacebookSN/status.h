#ifndef __STATUS_H
#define __STATUS_H
#include "ex1.h"

class Page;
class SocialNetwork;
class User;
#include <string>

class Status
{
protected:
	Time time;
	std::string text;
public:
	Status(std::string text); //c'tor
	Status(const Status& other); //copy c'tor
	//Move c'tor not needed, no addresses to "steal".
	virtual ~Status() = default; 

	//get func:
	const Time& getTime() const;
	virtual const std::string& getStatus() const;

	// set func:
	void setTime();
	void setTime(Time time);
	virtual void setStatus(const std::string& text);

	//methods
		//Operators:
	virtual const bool operator==(const Status& other) const; 


	virtual void printStatus() const; 
	virtual Status* clone() const { return new Status(*this); }

};

class StatusImage : public Status
{
protected:
	std::string image;

public:
	StatusImage(std::string& image, std::string& text);
	StatusImage(const StatusImage& other);
	//Move c'tor not needed
	virtual ~StatusImage() = default; // d'tor not needed, std::string destructs itself

	//get funcs:
	virtual const std::string& getStatus() const override;
	virtual const std::string& getImage() const;

	//set funcs:
	virtual void setStatus(const std::string& image, const std::string& text);

	//methods func:
	virtual const bool operator==(const Status& other) const override;
	virtual void printStatus() const;
	virtual Status* clone() const override { return new StatusImage(*this); }
};

class StatusVideo : public Status
{
protected:
	std::string video;

public:
	StatusVideo(std::string& video, std::string& text);
	StatusVideo(const StatusVideo& other);
	//Move c'tor not needed
	virtual ~StatusVideo() = default; // d'tor not needed, std::string destructs itself

	//get funcs:
	virtual const std::string& getStatus() const override;
	virtual const std::string& getVideo() const;

	//set funcs:
	virtual void setStatus(const std::string& video, const std::string& text);

	//methods func:
	virtual const bool operator==(const Status& other) const;
	virtual void printStatus() const;
	virtual Status* clone() const override { return new StatusVideo(*this); }
};

#endif
