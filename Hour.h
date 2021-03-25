#ifndef HOUR_H
#define HOUR_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>

//#include "Slot.h"
#include "shiftInfo.h"
class Hour
{
public:
	//Constructor/Deconstructor
	Hour(int setName, std::string setName2, std::string dayName)
	{
		hourName = setName;
		name2 = setName2;
		maxEmployees = 1000;
	}
	~Hour() {}

	//Setters
	void setLimit(int newLimit)
	{
		if (maxEmployees != 0)
		{
			maxEmployees = newLimit;
		}
	}

	//-----PRINTERS-----
	std::string print()
	{
		std::ostringstream oss;
		for (auto s : tutors)
		{
			oss << s;
			oss << " - ";
		}
		return oss.str();
	}

	std::string printHours() {
		std::ostringstream oss;
		oss << hourName << ": ";
		for (auto s : tutors)
		{
			oss << s;
			oss << " - ";
		}
		return oss.str();
	}

	//-----GETTERS-----
	int getHour() { return hourName; }

	std::string getSig() { return name2; }

	int checkTutor(shiftInfo next, std::string name)
	{
		if (tutors.size() >= maxEmployees) { return 0; }
		else if (checkSlots(name)) { return 0; }
		else { return 1; }
	}

	bool checkSlots(std::string name)
	{
		bool present = false;
		for (auto s : tutors)
		{
			if (name == s)
			{
				present = true;
			}
		}
		return present;
	}

	int placeTutor(shiftInfo next, std::string name)
	{
		if (tutors.size() >= maxEmployees) { return 0; }
		else if (checkSlots(name)) { return 0; }
		else
		{
			//Slot next(name); //add a function to add endvalues for end of shift
			tutors.insert(name);
			return 1;
		}
	}

	int getLimit()
	{
		return maxEmployees;
	}

	void sortSlots() {

	}

	std::set<std::string> getTutors()
	{
		return tutors;
	}

private:
	int hourName;
	std::string name2;
	std::set<std::string> tutors;
	int maxEmployees = 0;
};
#endif
