#ifndef SHIFTINFO_H
#define SHIFTINFO_H

#include <string>
#include <sstream>
enum weekDay { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, NODAY };

class shiftInfo
{
public:
	//Constructor does all the setting
	shiftInfo(std::pair<int, std::string> hourInfo, weekDay dayInfo)
	{
		hour = hourInfo.first;
		timeSig = hourInfo.second;
		dayName = dayInfo;
	}
	~shiftInfo() {}

	//toString function for testing purposes only
	std::string toString()
	{
		std::string day = "unset";
		if (dayName == MONDAY) { day = "M"; }
		else if (dayName == TUESDAY) { day = "T"; }
		else if (dayName == WEDNESDAY) { day = "W"; }
		else if (dayName == THURSDAY) { day = "TH"; }
		else if (dayName == FRIDAY) { day = "F"; }
		else if (dayName == NODAY) { day = "-----\n------ERROR------\n-------"; }
		std::ostringstream oss;
		oss << hour << timeSig << "-" << day << " ";
		return oss.str();
	}

	//getters
	int getHour() { return hour; }
	std::string getSig() { return timeSig; }
	weekDay getDay() { return dayName; }

private:
	int hour;
	std::string timeSig;
	weekDay dayName;
};
#endif

