#include "Tutor.h"

bool Tutor::addtoHours(std::pair<int, std::string> newHour, weekDay dayValue)
{
	shiftInfo next(newHour, dayValue);
	if (newHour.second == "AM" || newHour.second == "PM")
	{
		prefInter.push_back(next);
		return true;
	}
	else if (newHour.second == "am" || newHour.second == "pm")
	{
		availInter.push_back(next);
		return true;
	}
	else
	{
		return false;
	}
}

void Tutor::organizeIt()
{
	std::vector<shiftInfo> newChunk;
	//preferred run
	for (unsigned int i = 0; i < prefInter.size(); i++)
	{
		if (newChunk.size() == 0)
		{
			newChunk.push_back(prefInter.at(i));
		}
		else if (newChunk.size() == 3)
		{
			preferredHours.push_back(newChunk);
			newChunk.clear();
		}
		else if (chunkCheck(newChunk.at(newChunk.size() - 1), prefInter.at(i)))
		{
			newChunk.push_back(prefInter.at(i));
		}
		else
		{
			preferredHours.push_back(newChunk);
			newChunk.clear();
			i--;
		}
	}
	if (newChunk.size() > 0) { preferredHours.push_back(newChunk); }
	newChunk.clear();
	//available run
	for (unsigned int i = 0; i < availInter.size(); i++)
	{
		if (newChunk.size() == 0)
		{
			newChunk.push_back(availInter.at(i));
		}
		else if (newChunk.size() == 3)
		{
			availableHours.push_back(newChunk);
			newChunk.clear();
		}
		else if (chunkCheck(newChunk.at(newChunk.size() - 1), availInter.at(i)))
		{
			newChunk.push_back(availInter.at(i));
		}
		else
		{
			availableHours.push_back(newChunk);
			newChunk.clear();
			i--;
		}
	}
	if (newChunk.size() > 0) { availableHours.push_back(newChunk); }
}

bool Tutor::chunkCheck(shiftInfo exHour, shiftInfo questHour)
{
	if (exHour.getDay() != questHour.getDay())
	{
		return false;
	}
	if (exHour.getSig() != questHour.getSig())
	{
		if (exHour.getHour() == 11 && questHour.getHour() == 12)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (exHour.getHour() == questHour.getHour() - 1)
		{
			return true;
		}
		else if (exHour.getHour() == 12 && questHour.getHour() == 1)
		{
			return true;
		}
		else { return false; }
	}
	return false;
}

std::string Tutor::printInfo()
{
	std::ostringstream oss;
	oss << tutorName << " " << prefLimit << "\n";
	oss << "Preferred Hours: ";
	for (unsigned int i = 0; i < prefInter.size(); i++)
	{
		oss << prefInter.at(i).toString();
	}
	oss << "\nAvailable Hours: ";
	for (unsigned int i = 0; i < availInter.size(); i++)
	{
		oss << availInter.at(i).toString();
	}
	oss << "\n";
	return oss.str();
}

std::string Tutor::fullPrint()
{
	std::ostringstream oss;
	oss << tutorName << ": \nPreferred Hours: ";
	for (unsigned int i = 0; i < preferredHours.size(); i++)
	{
		oss << "[ ";
		for (unsigned int j = 0; j < preferredHours.at(i).size(); j++)
		{
			oss << preferredHours.at(i).at(j).toString() << ",";
		}
		oss << "]\n";
	}
	oss << "\nAvailable Hours: ";
	for (unsigned int i = 0; i < availableHours.size(); i++)
	{
		oss << "[ ";
		for (unsigned int j = 0; j < availableHours.at(i).size(); j++)
		{
			oss << availableHours.at(i).at(j).toString() << ",";
		}
		oss << "]\n";
	}
	oss << "\n";
	return oss.str();
}
