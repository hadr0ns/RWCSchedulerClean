#ifndef TUTOR_H
#define TUTOR_H

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>

#define TRUEMAX 18
#define TRUEMIN 8
#define OVERRIDEMIN 10

#include "shiftInfo.h"
#include "Package.h"

class Tutor
{
public:
	Tutor() {}
	~Tutor() {}

	//SETTERS (in favor of a Constructor)
	void setName(std::string name) { tutorName = name; }
	void setLimit(int min, int pref, int max)
	{
		prefLimit = pref;
		if (pref < TRUEMIN) 
		{
			pref = TRUEMIN;
		}
		minLimit = min;
		if (minLimit > OVERRIDEMIN)
		{
			minLimit = OVERRIDEMIN;
		}
		else if (minLimit < TRUEMIN)
		{
			minLimit = TRUEMIN;
		}
		maxLimit = max;
		selectedLimit = TRUEMIN;
		if (maxLimit < TRUEMIN)
		{
			maxLimit = TRUEMIN;
		}
		if (maxLimit > TRUEMAX)
		{
			maxLimit = TRUEMAX;
		}
	}
	void setSoft(int soft) { softLimit = soft; }

	//-----TRANSFORMERS----- (...not Decepticons)

	void updateSoftLimit(int update) { softLimit += update; }

	//Call to add hours to temporary storage
	bool addtoHours(std::pair<int, std::string> newHour, weekDay dayValue);

	//Organize hours into a vectors of vectors of shiftInto (it sucks)
	void organizeIt();

	//Check to see if next hour follows the previous one.
	bool chunkCheck(shiftInfo exHour, shiftInfo questHour);

	void updateHours(int newValue) { hoursAssigned += newValue; }

	void changeActiveLimit()
	{
		if (iterationCount == 0) { activeUpdate(minLimit); }
		else if (iterationCount == 1) { activeUpdate(prefLimit); }
		else if (iterationCount == 2) { activeUpdate(maxLimit); }
		iterationCount++;
	}

	void activeUpdate(int newLimit)
	{
		if (selectedLimit < newLimit)
		{
			selectedLimit = newLimit;
		}
	}

	void resetNav()
	{
		prefNav = 0;
		availNav = 0;
		changeActiveLimit();
	}

	void setStatus()
	{
		if (hoursAssigned >= minLimit) { statusI = "Y\n"; }
		else
		{
			std::ostringstream oss;
			oss << "NO, FAILED BY " << minLimit - hoursAssigned << " HOURS\n";
			oss << "MinLimit " << minLimit << "\n";
			statusI = oss.str();
		}
	}

	//-----PRINTERS-----

	std::string fullPrint();

	std::string printInfo();

	//toString for status report on each tutor, printed in report file
	std::string statusReport()
	{
		std::ostringstream oss;
		oss << tutorName << ": \n\thourLimit-> " << prefLimit << "\n\tHoursAssigned-> " << hoursAssigned << "\n";
		setStatus();
		oss << "   " << "Minimum Met? " << statusI;
		return oss.str();
	}

	//-----GETTERS-----
	int getPref()
	{
		return prefLimit;
	}

	int metMin()
	{
		if (hoursAssigned >= minLimit) { return 1; }
		return 0;
	}

	int getPriority()
	{
		return minLimit - hoursAssigned;
	}

	bool needMin()
	{
		if (hoursAssigned >= minLimit) { return false; }
		return true;
	}

	int gethoursLimit()
	{
		return selectedLimit;
	}

	std::string getName() { return tutorName; }

	void getPref(std::vector<shiftInfo>& next)
	{
		next = preferredHours.at(prefNav);
		prefNav++;
	}

	void getAvail(std::vector<shiftInfo>& next)
	{
		next = availableHours.at(availNav);
		availNav++;
	}

	int hoursRemaining(bool check = false)
	{
		return selectedLimit - hoursAssigned;
	}

	bool pStatus(bool check = false)
	{
		if (sizeCheck(check)) { return true; }
		if (prefNav >= preferredHours.size()) { prefCheck = true; }
		return prefCheck;
	}

	bool aStatus(bool check = false)
	{
		if (sizeCheck(check)) { return true; }
		if (availNav >= availableHours.size()) { availCheck = true; }
		return availCheck;
	}

	bool sizeCheck(bool check = false)
	{
		if (check)
		{
			int newCheck = (std::min(softLimit, selectedLimit));
			if (hoursAssigned >= newCheck) { return true; }
			else { return false; }
		}
		if (hoursAssigned >= selectedLimit) { return true; }
		else { return false; }
	}

	int getAssigned()
	{
		return hoursAssigned;
	}

	bool minFilled()
	{
		if (hoursAssigned >= minLimit) {
			return true;
		}
			return false;
	}

	void addShift(Package newShift)
	{
		shifts.push_back(newShift);
	}

	std::string printShifts()
	{
		std::ostringstream oss;
		oss << tutorName << "'s ";
		oss << "Shifts: \n";
		for (auto s : shifts)
		{
			oss << s.toString() << "\n";
		}
		return oss.str();
	}

	std::vector<Package> getShifts()
	{
		return shifts;
	}

	Package convertPackage(std::vector<shiftInfo> shiftoption)
	{
		std::vector<int> hours;
		for (auto s : shiftoption)
		{
			hours.push_back(s.getHour());
		}
		weekDay name = shiftoption.at(0).getDay();
		std::string dayString = "NULL";
		switch (name)
		{
		case MONDAY:
			dayString = "Monday";
			break;
		case TUESDAY:
			dayString = "Tuesday";
			break;
		case WEDNESDAY:
			dayString = "Wednesday";
			break;
		case THURSDAY:
			dayString = "Thursday";
			break;
		case FRIDAY:
			dayString = "Friday";
			break;
		case NODAY:
			break;
		default:
			break;
		}
		Package converted(dayString, name, hours);
		return converted;
	}

private:
	std::string tutorName;
	int prefLimit = 0;
	int minLimit = 0;
	int maxLimit = 0;

	std::vector<Package> shifts;

	int selectedLimit = 0;
	int iterationCount = 0;

	int softLimit = 0;
	int hoursAssigned;

	std::vector<shiftInfo> prefInter;
	std::vector<shiftInfo> availInter;

	std::vector<std::vector<shiftInfo>> preferredHours;
	std::vector<std::vector<shiftInfo>> availableHours;

	std::string statusI;

	bool prefCheck = false;
	int prefNav = 0;

	bool availCheck = false;
	int availNav = 0;
};
#endif

