#include "status.h"
using namespace std;


//********************************* S T A T U S **********************************

//c'tor
Status::Status(std::string text) {
	setTime();
	this->text = text;
}

//copy c'tor
Status::Status(const Status& other)
{
	this->setTime();
	text = other.text;
}
//********************************************************************************

//get funcs: allows access to the class attributes
const Time& Status::getTime() const
{
	return time;
}

const std::string& Status::getStatus() const
{
	return text;
}

//********************************************************************************

//set funcs: insert values into class attributes
void Status::setTime() 
{
	time_t now = std::time(0);
	tm* locTime = gmtime(&now);

	time.date.day = locTime->tm_mday;
	time.date.month = locTime->tm_mon + 1;
	time.date.year = locTime->tm_year + 1900;
	time.hours = locTime->tm_hour;
	time.minutes = locTime->tm_min;
}

void Status::setTime(Time time)
{
	this->time = time;
}

void Status::setStatus(const std::string& text)
{
	this->text = text;
}

//********************************************************************************

//methods: 

const bool Status::operator==(const Status& other) const
{
	return this->text == other.text;
}

//prints the status
void Status::printStatus() const
{
	std::cout << "Created on: " << std::setfill('0') << std::setw(2) << time.date.day << "/" << std::setfill('0') << std::setw(2) << time.date.month << "/"
		<< time.date.year << " at ";
	std::cout << std::setfill('0') << std::setw(2) << time.hours << ":";
	std::cout << std::setfill('0') << std::setw(2) << time.minutes << ".\n";

	cout << "This status was printed in black & white." << endl;
	cout << "This status is shown using a simple program." << endl;
	cout << this->text << endl;
}

//**************************** S T A T U S   I M A G E *****************************

//C'tor
StatusImage::StatusImage(std::string& image, std::string& text) : Status(text)
{
	this->image = image;
}
//Copy c'tor
StatusImage::StatusImage(const StatusImage& other) : Status(other)
{
	image = other.image;
}

//****************************************GET FUNC**************************************
const std::string& StatusImage::getStatus() const 
{
	return text + image;
}

const std::string& StatusImage::getImage() const
{
	return image;
}


//*******************************************SET FUNC**********************************
void StatusImage::setStatus(const std::string& image, const std::string& text)
{
	this->image = image;
	this->text = text;
}

const bool StatusImage::operator==(const Status& other) const
{
	if (text == other.getStatus()) return false;

	const StatusImage* otherImg = dynamic_cast<const StatusImage*>(&other);
	
	return (image == otherImg->image);
}

void StatusImage::printStatus() const
{
	Status::printStatus();
	cout << "This status was printed in RGB colors." << endl;
	cout << "This status is shown using a simple program." << endl;
	cout << "Text: " << this->text << ", file name: " << this->image << endl;
}

//**************************** S T A T U S   V I D E O *****************************

//C'tor
StatusVideo::StatusVideo(std::string& video, std::string& text) : Status(text)
{
	this->video = video;
}
//Copy c'tor
StatusVideo::StatusVideo(const StatusVideo& other) : Status(other) 
{
	video = other.video;
}

//****************************************GET FUNC**************************************
const std::string& StatusVideo::getStatus() const
{
	return text + video;
}

const std::string& StatusVideo::getVideo() const
{
	return video;
}


//*******************************************SET FUNC**********************************
void StatusVideo::setStatus(const std::string& video, const std::string& text)
{
	this->video = video;
	this->text = text;
}

const bool StatusVideo::operator==(const Status& other) const
{
	if (text == other.getStatus()) return false;

	const StatusVideo* otherVid = dynamic_cast<const StatusVideo*>(&other);

	return (video == otherVid->video);
}

void StatusVideo::printStatus() const
{
	Status::printStatus();
	cout << "This status was printed in RGB colors." << endl;
	cout << "This status is shown using a video player program." << endl;
	cout << "Text: " << this->text << ", file name: " << this->video << endl;
}
