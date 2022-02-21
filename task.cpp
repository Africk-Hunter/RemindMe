#include "task.hpp"
#include <iostream>
#include <time.h>

Task::Task() {

	taskName = "";
	taskNotes = ""; 
	dateDay = 0;
	dateMonth = 0;
	dateYear = 0;
	timeHours = 0;
	timeMinutes = 0;
	repeat = 0;

}

void Task::setTaskName(std::string nName) {
	taskName = nName;
}
void Task::setTaskNotes(std::string nNotes) {
	taskNotes = nNotes;
}
void Task::setDueTime(std::string nDay, std::string nTime) {
	std::string dayString, timeString;
	
	dayString += nDay[0];
	dayString += nDay[1];
	std::cout << dayString << std::endl;
	dateMonth = std::stoi(dayString);
	dayString = nDay[3];
	dayString += nDay[4];
	dateDay = std::stoi(dayString);
	dayString = nDay[6];
	dayString += nDay[7];
	dayString += nDay[8];
	dayString += nDay[9];
	dateYear = std::stoi(dayString);

	if (nTime.length() > 4) {
		timeString = nTime[0];
		timeString += nTime[1];
		timeHours = std::stoi(timeString);
		timeString = nTime[3];
		timeString += nTime[4];
		timeMinutes = std::stoi(timeString);
	}
	else {
		timeString = nTime[0];
		timeHours = std::stoi(timeString);
		timeString = nTime[2];
		timeString += nTime[3];
		timeMinutes = std::stoi(timeString);
	}
	

	tm.tm_sec = 0;
	tm.tm_wday = 0;
	tm.tm_yday = 0;
	tm.tm_hour = timeHours;
	tm.tm_min = timeMinutes;
	tm.tm_year = dateYear - 1900;
	tm.tm_mon = dateMonth -1;
	tm.tm_mday = dateDay;


	time_t rawtime = mktime(&tm);
	finalTime = static_cast<long int>(rawtime);
	
}
void Task::setRepeat(int repeatNum) {
	/*
		0 = Never
		1 = Daily
		2 = Weekly
		3 = Monthly
		4 = Yearly
	*/
	repeat = repeatNum;
}
std::string Task::getTaskName() {
	return taskName;
}
std::string Task::getTaskNotes() {
	return taskNotes;
}
long int Task::getTime() {
	return finalTime;
}
int Task::getRepeat() {
	return repeat;
}

void Task::saveEnteredData(sf::Text textTaskName, sf::Text textTaskNotes, sf::Text taskDueDate, sf::Text taskTimeDue) {
	taskName = textTaskName.getString();
	taskNotes = textTaskNotes.getString();
	setDueTime(taskDueDate.getString(), taskTimeDue.getString());
}