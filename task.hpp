#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cereal/archives/json.hpp>

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

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(taskName), 
				CEREAL_NVP(taskNotes), 
				CEREAL_NVP(dayOfWeek), 
				CEREAL_NVP(dateDay), 
				CEREAL_NVP(dateMonth), 
				CEREAL_NVP(dateYear),
				CEREAL_NVP(timeHours), 
				CEREAL_NVP(timeMinutes),
				CEREAL_NVP(repeat)); // serialize things by passing them to the archive
	}

private:
	friend class cereal::access;

	std::string taskName, taskNotes, dayOfWeek, dueTime;
	int dateDay, dateMonth, dateYear, timeHours, timeMinutes;
	int repeat = 5;

};


/*

[ Characteristics of a Task ]



[ Behaviors of a Task ]



*/