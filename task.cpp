#include "task.hpp"
#include <iostream>

Task::Task() {

	taskName = "a";
	taskNotes = "b"; 
	dayOfWeek = "c";
	dateDay = 1;
	dateMonth = 2;
	dateYear = 3;
	timeHours = 4;
	timeMinutes = 5;
	repeat = 6;

}

void Task::setTaskName(std::string nName) {
	taskName = nName;
}
void Task::setTaskNotes(std::string nNotes) {
	taskNotes = nNotes;
}
void Task::setDayOfWeek(std::string nDay) {
	std::string tempString;
	dayOfWeek = nDay;

	tempString = nDay[0] + nDay[1];
	dateMonth = std::stoi(tempString);
	tempString = nDay[3] + nDay[4];
	dateDay = std::stoi(tempString);
	tempString = nDay[6] + nDay[7] + nDay[8] + nDay[9];
	dateYear = std::stoi(tempString);

}
void Task::setTime(std::string nTime) {
	std::string tempString;
	dueTime = nTime;

	tempString = nTime[0] + nTime[1];
	timeHours = std::stoi(tempString);
	tempString = nTime[3] + nTime[4];
	timeMinutes = std::stoi(tempString);

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
std::string Task::getDayOfWeek() {
	return dayOfWeek;
}
std::string Task::getTime() {
	return dueTime;
}
int Task::getRepeat() {
	return repeat;
}

