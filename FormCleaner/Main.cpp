#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Tutor.h"

int main(int argc, char* argv[])
{
	//i/o files
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	//Data structure for entirety of program
	std::vector<Tutor> SchedulerList;

	//input parsing variables
	std::string testString;
	std::string name;
	std::string buffer;

	//get rid of the first line (the google forms line that prints all of the questions)
	std::getline(in, testString);

	//loop through and grab each line
	while (std::getline(in, testString))
	{
		//std::cout << testString << "\n";

		//iterate through and get rid of commas
		for (unsigned int i = 0; i < testString.size(); i++)
		{
			if (testString.at(i) == ',')
			{
				testString.replace(i, 1, " ");
			}
		}

		//std::cout << testString << "\n";
		
		//get rid of am and pm, there's no overlap so it's just not helpful
		for (unsigned int i = 0; i < testString.size(); i++)
		{
			if (testString.at(i) == 'm')
			{
				if (testString.at(i - 1) == 'a' || testString.at(i - 1) == 'p')
				{
					unsigned int j = i - 1;
					testString.erase(j, 2);
				}
			}
		}

		//std::cout << testString << "\n";

		std::istringstream iss(testString);
		
		//get rid of the timeStamp Nonsense
		iss >> buffer;
		iss >> buffer;
		
		//get name
		iss >> name;
		iss >> buffer;
		while (isalpha(buffer.at(0)) || buffer.at(0) == '(')
		{
			name += " " + buffer;
			iss >> buffer;
		}
		//std::cout << "Name: " << name << "\n";
		std::istringstream i2ss(buffer);
		int hours;
		i2ss >> hours;

		Tutor nextTutor(name);

		int min;
		int max;
		iss >> min;
		iss >> max;

		//std::cout << "min, max: " << min << ", " << max << "\n";

		nextTutor.setHours(hours, min, max);
		
		//loop through and grab each hour, use " as an indicator of start and finish and clear them as you go
		std::string next = "";
		while (iss >> buffer)
		{
			bool pass = false;
			if (buffer.at(0) == '\"')
			{
				if (next != "" && next != " ")
				{
					nextTutor.additem(next);
				}
				buffer.erase(0, 1);
			}
			else if (buffer.size() > 1)
			{
				if (buffer.at(buffer.size() - 1) == '\"')
				{
					buffer.erase(buffer.size() - 1, 1);
					pass = true;
				}
				else if (buffer == "None")
				{
					pass = true;
				}
			}
			next += buffer;
			//std::cout << next << "\n";
			if (pass) 
			{
				nextTutor.additem(next);
				next = ""; 
			}
			else { next += " "; }
			//std::cout << "Buffer: " << buffer << "\n";
			//std::cout << "Next: " << next << "\n";
		}
		if (next != "" && next != " ")
		{
			nextTutor.additem(next);
		}

		//std::cout << testString << "\n\n";
		nextTutor.buildSchedule();
		SchedulerList.push_back(nextTutor);
	}

	for (unsigned int i = 0; i < SchedulerList.size(); i++)
	{
		out << SchedulerList.at(i).toString();
	}

	return 0;
}