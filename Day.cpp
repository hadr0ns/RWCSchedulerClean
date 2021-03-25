#include "Day.h"

int Day::checkHour(std::vector<shiftInfo> next, std::string tutorName, int hourLimit)
{
	int hourCount = 0;
	for (unsigned int i = 0; i < next.size(); i++)
	{
		if (hourLimit <= 0) { break; }
		for (unsigned int j = 0; j < myHours.size(); j++)
		{
			if (next.at(i).getHour() == myHours.at(j).getHour())
			{
				int result = myHours.at(j).checkTutor(next.at(i), tutorName);
				if (result == 0 && hourCount == 1) { hourCount = 0; }
				hourLimit -= result;
				hourCount += result;
			}
		}
	}
	return hourCount;
}

int Day::selectHour(std::vector<shiftInfo> next, std::string tutorName, int hourLimit, bool check, Package &addPack)
{
	if ((checkHour(next, tutorName, hourLimit) <= 1) && check) { /*std::cout << "NO 1-hour Shifts!\n";*/ return 0; }
	int hourCount = 0;
	//std::vector<int> hourPack;
	for (unsigned int i = 0; i < next.size(); i++)
	{
		if (hourLimit <= 0) { break; }
		for (unsigned int j = 0; j < myHours.size(); j++)
		{
			if (next.at(i).getHour() == myHours.at(j).getHour())
			{

				if (!studentLogged(tutorName)) { /*std::cout << "FAILED\n";*/ return 0; }
				int result = myHours.at(j).placeTutor(next.at(i), tutorName);
				if (result > 0) { addPack.addHour(next.at(i).getHour()); }
				hourLimit -= result;
				hourCount += result;
			}
		}
	}
	return hourCount;
}

bool Day::studentLogged(std::string name)
{
	bool present = false;
	unsigned int position;
	for (unsigned int i = 0; i < database.size(); i++)
	{
		if (database.at(i).first == name)
		{
			present = true;
			position = i;
		}
	}
	if (present)
	{
		if (checkDayHours(position))
		{
			increment(position);
		}
		else { return false; }
	}
	else
	{
		addStudent(name);
	}
	return true;
}
