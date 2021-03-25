#ifndef DAY_H
#define DAY_H

#include <vector>
#include <string>

#include "Hour.h"
#include "shiftInfo.h"
#include "Package.h"

class Day
{
public:
	//CONSTRUCTOR/DECONSTRUCTOR
	Day(std::string setName)
	{
		dayName = setName;
		for (unsigned int i = 9; i <= 11; i++) { myHours.push_back(Hour(i, "am", dayName)); }
		myHours.push_back(Hour(12, "pm", dayName));
		for (unsigned int i = 1; i <= 8; i++) { myHours.push_back(Hour(i, "pm", dayName)); }
	}
	~Day() {}

	//-----SETTERS/ADDITIONS-----
	void setException(int hourName)
	{
		for (unsigned int i = 0; i < myHours.size(); i++)
		{
			if (hourName == myHours.at(i).getHour())
			{
				myHours.at(i).setLimit(0);
			}
		}
	}

	void setLimits(std::vector<int> limits)
	{
		for (unsigned int i = 0; i < limits.size(); i++)
		{
			myHours.at(i).setLimit(limits.at(i));
		}
	}

	void addStudent(std::string name)
	{
		std::pair<std::string, int> newStudent;
		newStudent.first = name;
		newStudent.second = 0;
		database.push_back(newStudent);
	}

	//-----TRANSFORMERS/OPERATORS-----
	//unwrap next and pass to next hour,return hours added by hour function, instead of bool, return 0 for false and >0 for anything else
	int selectHour(std::vector<shiftInfo> next, std::string tutorName, int hourLimit, bool check, Package &addPack);

	void increment(unsigned int i)
	{
		database.at(i).second += 1;
	}

	//-----GETTERS/CHECKS
	int checkHour(std::vector<shiftInfo> next, std::string tutorName, int hourLimit);

	bool studentLogged(std::string name);

	bool checkDayHours(unsigned int i)
	{
		if (database.at(i).second > dayLimit) { return false; }
		else { return true; }
	}

	int getHourCount()
	{
		int currentCount = 0;
		for (auto h : myHours)
		{
			currentCount += h.getLimit();
		}
		return currentCount;
	}

	//-----PRINTERS-----
	std::string print(int i)
	{
		if (i >= myHours.size()) { return " "; }
		else
		{
			return myHours.at(i).print();
		}
	}

	std::vector<std::string> getHourNames(int i)
	{
		std::set<std::string> transferSet = myHours.at(i).getTutors();
		std::vector<std::string> transferred;
		for (auto s : transferSet)
		{
			transferred.push_back(s);
		}
		if (transferred.size() == 0)
		{
			transferred.push_back("");
			/*std::cout << "EXCEPTION ENCOUNTERED!\n"*/;
		}
		return transferred;
	}

	std::string printDay()
	{
		std::ostringstream oss;
		oss << dayName << ":\n";
		for (unsigned int i = 0; i < myHours.size(); i++)
		{
			oss << myHours.at(i).printHours() << "\n";
		}
		return oss.str();
	}

	int getHourLimit(int i) {
		return myHours.at(i).getLimit();
	}

private:
	std::string dayName;
	std::vector<Hour> myHours;
	std::vector<std::pair<std::string, int>> database;
	int dayLimit = 3;
};
#endif
