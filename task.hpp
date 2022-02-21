#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cereal/archives/json.hpp>

class Task {

public:

	Task();

	void setTaskName(std::string);
	void setTaskNotes(std::string);
	void setDueTime(std::string, std::string);
	void setRepeat(int);
	
	std::string getTaskName();
	std::string getTaskNotes();
	long int getTime();
	int getRepeat();

	void saveEnteredData(sf::Text, sf::Text, sf::Text, sf::Text);

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(taskName), 
				CEREAL_NVP(taskNotes), 
				CEREAL_NVP(dateDay), 
				CEREAL_NVP(dateMonth), 
				CEREAL_NVP(dateYear),
				CEREAL_NVP(timeHours), 
				CEREAL_NVP(timeMinutes),
				CEREAL_NVP(finalTime),
				CEREAL_NVP(repeat));
	}

private:

	friend class cereal::access;
	struct tm tm;

	//time_t finalTime;

	std::string taskName,
		taskNotes;

	int dateDay,
		dateMonth,
		dateYear,
		timeHours,
		timeMinutes,
		repeat;
	long int finalTime;

};
