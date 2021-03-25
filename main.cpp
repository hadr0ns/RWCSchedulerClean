#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

#include "Tutor.h"
#include "Day.h"

//Checks string and returns enum value of day.
bool checkDay(std::string dayName, weekDay& currentDay)
{
	if (dayName == "Monday") { currentDay = MONDAY; return true; }
	if (dayName == "Tuesday") { currentDay = TUESDAY; return true; }
	if (dayName == "Wednesday") { currentDay = WEDNESDAY; return true; }
	if (dayName == "Thursday") { currentDay = THURSDAY; return true; }
	if (dayName == "Friday") { currentDay = FRIDAY; return true; }
	return false;
}

//partition and quicksort for organizing students by preferred hour requests (greatest to least)
int partition(std::vector<Tutor>& masterList, int l, int h)
{
	int p = masterList.at(h).getPref();
	int i = l;
	for (int j = l; j <= h; j++)
	{
		//std::cout << "Running partition\n";
		if (masterList.at(j).getPref() > p)
		{
			Tutor switcher = masterList.at(i);
			masterList.at(i) = masterList.at(j);
			masterList.at(j) = switcher;
			i += 1;
		}
	}
	Tutor Switcher = masterList.at(i);
	masterList.at(i) = masterList.at(h);
	masterList.at(h) = Switcher;
	return i;
}

void quicksort(std::vector<Tutor>& masterList, int l, int h)
{

	if (l < h)
	{
		//std::cout << "running Quicksort";
		int p = partition(masterList, l, h);
		quicksort(masterList, l, p - 1);
		quicksort(masterList, p + 1, h);
	}
}

//P2 and Q2 sorts students by (minLimit - hoursAssigned)
int partition2(std::vector<Tutor>& masterList, int l, int h)
{
	int p = masterList.at(h).getPriority();
	int i = l;
	for (int j = l; j <= h; j++)
	{
		//std::cout << "Running partition\n";
		if (masterList.at(j).getPriority() > p)
		{
			Tutor switcher = masterList.at(i);
			masterList.at(i) = masterList.at(j);
			masterList.at(j) = switcher;
			i += 1;
		}
	}
	Tutor Switcher = masterList.at(i);
	masterList.at(i) = masterList.at(h);
	masterList.at(h) = Switcher;
	return i;
}

void quicksort2(std::vector<Tutor>& masterList, int l, int h)
{

	if (l < h)
	{
		//std::cout << "running Quicksort";
		int p = partition2(masterList, l, h);
		quicksort2(masterList, l, p - 1);
		quicksort2(masterList, p + 1, h);
	}
}

//returns int value of enum weekDay... is this even neccesary since enum represents in int values?
int getDayNum(weekDay currentDay)
{
	switch (currentDay)
	{
	case MONDAY:
		return 0;
	case TUESDAY:
		return 1;
	case WEDNESDAY:
		return 2;
	case THURSDAY:
		return 3;
	case FRIDAY:
		return 4;
	default:
		return 10;
	}
}

//Same thing as above, but gets int from strings
int setDayNum(std::string exDay)
{
	if (exDay == "Monday") { return 0; }
	else if (exDay == "Tuesday") { return 1; }
	else if (exDay == "Wednesday") { return 2; }
	else if (exDay == "Thursday") { return 3; }
	else if (exDay == "Friday") { return 4; }
	else { return 1000; }
}

//converts singe digit char into int
int NumberConverter(char numberChar)
{
	int newNum = 777;
	if (numberChar == '0') { newNum = 0; }
	if (numberChar == '1') { newNum = 1; }
	if (numberChar == '2') { newNum = 2; }
	if (numberChar == '3') { newNum = 3; }
	if (numberChar == '4') { newNum = 4; }
	if (numberChar == '5') { newNum = 5; }
	if (numberChar == '6') { newNum = 6; }
	if (numberChar == '7') { newNum = 7; }
	if (numberChar == '8') { newNum = 8; }
	if (numberChar == '9') { newNum = 9; }
	return newNum;
}

//converts time into int and string for values
std::pair<int, std::string> TimeConverter(std::string inputNum)
{
	int newNum = 0;
	std::string timeSig;
	if (inputNum.size() > 1)
	{
		if (isdigit(inputNum.at(1)))
		{
			newNum = 10 + NumberConverter(inputNum.at(1));
			timeSig = inputNum.substr(2, 2);
		}
		else
		{
			newNum = NumberConverter(inputNum.at(0));
			timeSig = inputNum.substr(1, 2);
		}
	}
	else { std::cout << "ERROR" << std::endl; }
	std::pair<int, std::string> newTime;
	newTime.first = newNum;
	newTime.second = timeSig;
	return newTime;
}

//build string for printing schedule
std::string schedule(std::vector<Day> request)
{
	std::ostringstream oss;
	oss << "," << "," << "RWC WRITING SCHEDULER\n";
	oss << "," << "Monday," << "Tuesday," << "Wednesday," << "Thursday," << "Friday\n";
	for (unsigned int i = 0; i <= 11; i++)
	{
		int hourName = i;
		if (i < 4)
		{
			hourName = i + 9;
		}
		else { hourName = i - 3; }
		std::vector<std::vector<std::string>> printBot2000;
		for (int j = 0; j < request.size(); j++) 
		{
			printBot2000.push_back(request.at(j).getHourNames(i));
		}
		for (int k = 0; k < request.at(2).getHourLimit(i); k++)
		{
			oss << hourName << ",";
			for (int j = 0; j < printBot2000.size(); j++)
			{
				if (k < printBot2000.at(j).size())
				{
					oss << printBot2000.at(j).at(k);
				}
				oss << ",";
			}
			oss << "\n";
		} 
	}
	return oss.str();
}

//Assigns tutors to schedule slots based on preference first, then availability
void setSchedule(std::vector<Tutor>& masterList, std::vector<Day>& weekDays, bool check, bool check2, bool topOff = false)
{
	bool finished = false;
	int count = 0;
	//bool minCheck = false;
	while (!finished)
	{
		//bool halfMinCheck = false;
		bool groupCheck = false;
		std::vector<shiftInfo> next;
		for (unsigned int i = 0; i < masterList.size(); i++)
		{
			if (masterList.at(i).pStatus(check)) { /*do nothing*/ }
			//else if (!masterList.at(i).needMin() && !minCheck) { groupCheck = true; }
			else if(topOff && masterList.at(i).minFilled()) {/*do nothing*/ }
			else
			{
				Package addedShift;
				//halfMinCheck = true;
				int addedHours = 0;
				groupCheck = true;
				masterList.at(i).getPref(next);
				//run function to pass next chunk
				std::string nextName = masterList.at(i).getName();
				int tutorLimit = masterList.at(i).hoursRemaining(check);
				if (next.at(0).getDay() == MONDAY)
				{
					addedShift.setNum(MONDAY);
					addedShift.setName("Monday");
					addedHours = weekDays.at(0).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == TUESDAY)
				{
					addedShift.setNum(TUESDAY);
					addedShift.setName("Tuesday");
					addedHours = weekDays.at(1).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == WEDNESDAY)
				{
					addedShift.setNum(WEDNESDAY);
					addedShift.setName("Wednesday");
					addedHours = weekDays.at(2).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == THURSDAY)
				{
					addedShift.setNum(THURSDAY);
					addedShift.setName("Thursday");
					addedHours = weekDays.at(3).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == FRIDAY)
				{
					addedShift.setNum(FRIDAY);
					addedShift.setName("Friday");
					addedHours = weekDays.at(4).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else { std::cout << "ERROR------" << masterList.at(i).getName() << std::endl; }
				if (addedHours == 0) { i--; }
			}
		}
		if (!groupCheck) { finished = true; }
		//if (!halfMinCheck) { minCheck = true; }
		quicksort2(masterList, 0, masterList.size() - 1);
	}
	finished = false;
	//minCheck = false;
	while (!finished)
	{
		bool halfMinCheck = false;
		int addedHours = 0;
		bool groupCheck = false;
		std::vector<shiftInfo> next;
		for (unsigned int i = 0; i < masterList.size(); i++)
		{
			if (masterList.at(i).aStatus(check)) { /*do nothing*/ }
			//else if (!masterList.at(i).needMin() && !minCheck) {/*do nothing*/ }
			else if (topOff && masterList.at(i).minFilled()) {/*do nothing*/ }
			else
			{
				Package addedShift;
				halfMinCheck = true;
				groupCheck = true;
				masterList.at(i).getAvail(next);
				std::string nextName = masterList.at(i).getName();
				int tutorLimit = masterList.at(i).hoursRemaining(check);
				if (next.at(0).getDay() == MONDAY)
				{
					addedShift.setNum(MONDAY);
					addedShift.setName("Monday");
					addedHours = weekDays.at(0).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == TUESDAY)
				{
					addedShift.setNum(TUESDAY);
					addedShift.setName("Tuesday");
					addedHours = weekDays.at(1).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == WEDNESDAY)
				{
					addedShift.setNum(WEDNESDAY);
					addedShift.setName("Wednesday");
					addedHours = weekDays.at(2).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == THURSDAY)
				{
					addedShift.setNum(THURSDAY);
					addedShift.setName("Thursday");
					addedHours = weekDays.at(3).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else if (next.at(0).getDay() == FRIDAY)
				{
					addedShift.setNum(FRIDAY);
					addedShift.setName("Friday");
					addedHours = weekDays.at(4).selectHour(next, nextName, tutorLimit, check2, addedShift);
					masterList.at(i).updateHours(addedHours);
					if (addedShift.getSize() > 0)
					{
						masterList.at(i).addShift(addedShift);
					}
				}
				else { /*std::cout << "ERROR------\n";*/ }
				if (addedHours == 0) { i--; }
			}
		}
		if (!groupCheck) { finished = true; }
		//if (!halfMinCheck) { minCheck = true; }
		quicksort2(masterList, 0, masterList.size() - 1);
	}
}

//Increments soft limit by predetermined amount------ OBSOLETE FUNCTION!!
void updateSoftLimit(const int c, std::vector<Tutor>& masterList)
{
	for (unsigned int i = 0; i < masterList.size(); i++)
	{
		masterList.at(i).updateSoftLimit(c);
	}
}

int main(int argc, char* argv[])
{
	//set up data structures
	std::vector<Tutor> masterList;
	std::vector<Day> weekDays;
	weekDays.push_back(Day("Monday"));
	weekDays.push_back(Day("Tuesday"));
	weekDays.push_back(Day("Wednesday"));
	weekDays.push_back(Day("Thursday"));
	weekDays.push_back(Day("Friday"));

	//counting hour Slots
	int slotCount = 0;

	//set up print files
		// in = schedule request form
	std::ifstream in(argv[1]);
	// setup = settings page
	std::ifstream setup(argv[2]);
	// out = Schedule
	std::ofstream out(argv[3]);
	// status = status report ---- NEEDS UPDATING
	std::ofstream status(argv[4]);

	//Initialize variables and structures used in reading process
	std::vector<int> hourValues;
	int softLimit = 0;
	std::string input;
	bool softCheck = false;

	//Read settings form
	while (std::getline(setup, input))
	{
		if (input.size() > 0)
		{
			if (isdigit(input.at(0)))
			{
				int place;
				std::string toss;
				std::istringstream iss(input);
				if (softCheck)
				{
					iss >> softLimit;
					softCheck = false;
				}
				else
				{
					iss >> toss;
					iss >> place;
					slotCount += place;
					hourValues.push_back(place);
				}
			}
			else if (input == "Soft-Limit:") {
				softCheck = true;
			}
			else if (input == "Exceptions:") {}
			else
			{
				std::istringstream iss(input);
				std::string exDay;
				iss >> exDay;
				int x = setDayNum(exDay);
				int next;
				while (iss >> next)
				{
					weekDays.at(x).setException(next);
				}
			}
		}
	}

	//set up weekdays hour slots based on settings form
	for (unsigned int i = 0; i < weekDays.size(); i++)
	{
		weekDays.at(i).setLimits(hourValues);
	}

	//get input from request form
	std::string nextInput;
	while (std::getline(in, nextInput))
	{
		std::istringstream iss(nextInput);
		Tutor newTutor;

		//name
		std::string name;
		std::string next;
		iss >> name;
		iss >> next;
		while (next != "Hours")
		{
			name += " " + next;
			iss >> next;
		}
		//std::cout << name << "\n";
		newTutor.setName(name);

		int newLimit;
		int minLimit;
		int maxLimit;
		iss >> minLimit;
		iss >> newLimit;
		iss >> maxLimit;
		newTutor.setLimit(minLimit, newLimit, maxLimit);
		newTutor.setSoft(softLimit);

		//grab individual hours
		weekDay newDay = NODAY;
		while (iss >> next)
		{
			int dayNum;
			if (next.size() > 4)
			{
				if (checkDay(next, newDay))
				{
					dayNum = getDayNum(newDay);
				}
			}
			else if (next.size() > 1 && isdigit(next.at(0)))
			{
				std::pair<int, std::string> timeName;
				timeName = TimeConverter(next);
				newTutor.addtoHours(timeName, newDay);
			}
		}
		masterList.push_back(newTutor);
	}

	//sort input and clump
	for (unsigned int i = 0; i < masterList.size(); i++)
	{
		masterList.at(i).organizeIt();
	}

	//shuffle masterList ------- OBSOLETE
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//shuffle(masterList.begin(), masterList.end(), std::default_random_engine(seed));

	//Sort masterList by requests
	quicksort(masterList, 0, masterList.size() - 1);

	//Assign shift times
	bool check = false;
	unsigned int const REPEAT = 3;
	for (unsigned int i = 0; i < REPEAT; i++)
	{
		if (i == REPEAT - 1) { check = false; }
		setSchedule(masterList, weekDays, check, true);
		//updateSoftLimit(UPDATE, masterList);
		for (unsigned int i = 0; i < masterList.size(); i++)
		{
			masterList.at(i).resetNav();
		}
	}

	//std::cout << "\n\n\tSecond Run!\n\n";

	for (unsigned int i = 0; i < REPEAT; i++) 
	{
		setSchedule(masterList, weekDays, check, false, true);
		for (unsigned int i = 0; i < masterList.size(); i++)
		{
			masterList.at(i).resetNav();
		}
	}

	slotCount = 0;
	for (auto d : weekDays)
	{
		slotCount += d.getHourCount();
	}

	//print to status report sheet
	status << "STATUS REPORT:\n\n";
	int minCount = 0;
	int assignedCount = 0;
	int eightCount = 0;
	for (unsigned int i = 0; i < masterList.size(); i++)
	{
		status << masterList.at(i).statusReport();
		minCount += masterList.at(i).metMin();
		assignedCount += masterList.at(i).getAssigned();
		if (masterList.at(i).getAssigned() >= 8) 
		{
			eightCount++;
		}
		else if (masterList.at(i).metMin())
		{
			eightCount++;
		}
	}
	double size = masterList.size();
	double y = minCount;
	double x = y / size;
	status << "\n\nFinal minCount = " << minCount << "/" << masterList.size() << " === " << std::setprecision(2) << x << "%\n";
	double z = eightCount;
	double a = z / size;
	status << "Final eightCount = " << eightCount << "/" << masterList.size() << " === " << std::setprecision(2) << a << "%\n";
	status << "Number of Slots = " << slotCount << "\n";
	status << "Assigned # " << assignedCount << "\n";
	status << "Slots left: " << slotCount - assignedCount << "\n";


	//print schedule to .csv file
	out << schedule(weekDays);

	//std::cout << "\n";
	for (auto t : masterList)
	{
		std::cout << t.printShifts() << "\n";
	}


	/*std::vector<Package> shiftCollection;
	std::set<int> hashCodes;
	for (auto t : masterList)
	{
		std::vector<Package> shifts = t.getShifts();
		for (auto p : shifts)
		{
			shiftCollection.push_back(p);
			hashCodes.insert(p.hashCode());
		}
	}

	for (auto h : hashCodes)
	{
		std::cout << "(" << h << "):\n";
		for (auto p : shiftCollection)
		{
			if (p.hashCode() == h)
			{
				std::cout << p.toString() << "\n";
			}
		}
		std::cout << "\n";
	}*/


	//system("pause");
	return 0;
}