#ifndef PACKAGE_H
#define PACKAGE_H
#include <string>
#include <vector>
#include <sstream>

#include "shiftInfo.h"
//enum weekDay { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, NODAY };
class Package
{
public:

	Package() {}

	Package(std::string newName, weekDay newNum, std::vector<int> hourSet) 
	{
		dayName = newName;
		dayNum = newNum;
		hours = hourSet;
	}

	void addHour(int hour)
	{
		hours.push_back(hour);
	}

	void setHours(std::vector<int> hourSet)
	{
		hours = hourSet;
	}

	void setNum(weekDay newNum)
	{
		dayNum = newNum;
	}

	void setName(std::string newName)
	{
		dayName = newName;
	}

	int getSize()
	{
		return hours.size();
	}

	int hashCode() 
	{
		int hash = 1;
		//hash *= hash;
		for (unsigned int i = 0; i < hours.size(); i++)
		{
			if (i == 0)
			{
				hash += (hours.at(i) * hours.at(i));
			}
			else {
				hash += hours.at(i);
			}
			//hash += i;
		}
		//hash += hours.size();
		switch (dayNum)
		{
		case MONDAY:
			hash += 10;
			break;
		case TUESDAY:
			hash += 100;
			break;
		case WEDNESDAY:
			hash += 1000;
			break;
		case THURSDAY:
			hash += 10000;
			break;
		case FRIDAY:
			hash += 100000;
			break;
		default:
			hash += 1;
			break;
		}

		return hash;
	}

	std::string toString()
	{
		std::ostringstream oss;
		oss << dayName << ": { ";
		for (unsigned int i = 0; i < hours.size(); i++)
		{
			oss << hours.at(i) << " ";
		}
		oss << "} " << hashCode();
		return oss.str();
	}

private:
	std::string dayName = "";
	weekDay dayNum = NODAY;
	std::vector<int> hours;
};

#endif