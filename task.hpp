#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Task {

public:

	Task();

	void setTaskName(std::string);
	void setTaskNotes(std::string);
	void setDayOfWeek(std::string);
	void setTime(std::string);
	void setRepeat(int);
	
	std::string getTaskName();
	std::string getTaskNotes();
	std::string getDayOfWeek();
	std::string getTime();
	int getRepeat();


private:

	std::string taskName, taskNotes, dayOfWeek, dueTime;
	int dateDay, dateMonth, dateYear, timeHours, timeMinutes;
	int repeat;

};


/*

[ Characteristics of a Task ]



[ Behaviors of a Task ]



*/