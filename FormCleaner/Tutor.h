#ifndef TUTOR_H
#define TUTOR_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
class Tutor
{
public:
	Tutor(std::string newName)
	{
		name = newName;
		switcheroo = true;
	}
	~Tutor() {}

	void setHours(int newHours, int newMin, int newMax)
	{
		hours = newHours;
		min = newMin;
		max = newMax;
	}

	void additem(std::string next)
	{
		if (switcheroo)
		{
			Preffered.push_back(next);
			switcheroo = false;
		}
		else
		{
			Banned.push_back(next);
			switcheroo = true;
		}
	}

	//seperate hours and store them in int variables
	std::vector<int> getInt(std::string next)
	{
		std::vector<int> hours;
		std::istringstream iss(next);
		int num;
		while (iss >> num)
		{
			hours.push_back(num);
		}
		return hours;
	}

	//basic (and unfortunately clunky) vector search
	bool find(int x, std::vector<int> parent)
	{
		for (unsigned int i = 0; i < parent.size(); i++)
		{
			if (parent.at(i) == x)
			{
				return true;
			}
		}
		return false;
	}

	bool checkException(int j)
	{
		if (j == 6 || j == 7 || j == 8) { return true; }
		else { return false; }
	}

	void buildSchedule()
	{
		std::ostringstream oss;
		std::string day;
		for (unsigned int i = 0; i < 5; i++)
		{
			if (i == 0) { day = "Monday"; }
			else if (i == 1) { day = "Tuesday"; }
			else if (i == 2) { day = "Wednesday"; }
			else if (i == 3) { day = "Thursday"; }
			else if (i == 4) { day = "Friday"; }
			std::vector<int> prefInt;
			std::vector<int> banInt;
			if (Preffered.size() != Banned.size()) { std::cout << name << ": INTAKE ERROR\n"; }
			oss << day << " ";
			if (Preffered.at(i) != "None") { prefInt = getInt(Preffered.at(i)); }
			if (Banned.at(i) != "None") { banInt = getInt(Banned.at(i)); }
			for (unsigned int j = 9; j < 12; j++)
			{
				if (find(j, banInt)) {}
				else if (day == "Tuesday" && j == 11) {}
				else if (find(j, prefInt)) { oss << j << "AM "; }
				else { oss << j << "am "; }
			}
			if (find(12, banInt)) {}
			else if (find(12, prefInt)) { oss << 12 << "PM "; }
			else { oss << 12 << "pm "; }
			for (unsigned int j = 1; j < 9; j++)
			{
				if (find(j, banInt)) {}
				else if ((day == "Monday" || day == "Friday") && checkException(j)) {}
				else if (find(j, prefInt)) { oss << j << "PM "; }
				else { oss << j << "pm "; }
			}
		}
		hoursList = oss.str();
	}

	std::string toString()
	{
		std::ostringstream oss;
		oss << name << " Hours " << min << " " << hours << " " << max << " " << hoursList << "\n";
		return oss.str();
	}

private:
	std::string name;
	std::vector<std::string> Preffered;
	std::vector<std::string> Banned;
	std::string hoursList;
	bool switcheroo;
	int hours;
	int min;
	int max;
};
#endif
