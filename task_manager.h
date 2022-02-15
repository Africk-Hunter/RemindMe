#pragma once
#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "task.hpp"

class TaskManager {

public:

	TaskManager();

	void makeNewTask();


private:

	std::queue<Task> currentTasks;
	
};


/*

[ Characteristics of a Task ]



[ Behaviors of a Task ]



*/