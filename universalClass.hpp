#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <filesystem>
#include "resource.h"
#include "texture_manager.hpp"
#include "resourceManager.hpp"
#include "Button.hpp"
#include "task.hpp"
#include "Textbox.hpp"

class UniversalClass
{

public:

	sf::RenderWindow window;
	LPCWSTR lpszClass = L"__hidden__";
	
	TextureManager txtManager;
	ResourceManager<Textbox> textboxManager;
	ResourceManager<Button> butManager;
	ResourceManager<sf::Font> fontManager;
	sf::Sprite background;
	std::stack<int> stateStack;
	std::priority_queue<Task> taskQueue;
	std::vector<Task> taskVec;
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS wc;
	HWND hWnd, m_hwnd;
	MSG msg;

	UniversalClass();

	int mainLoop();

	void loadTextures();
	void loadAssets();
	void deserializeTasks();

	void dummyWindowSetup();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	void mainMenuState();
	void editTaskState(Task&);
	void currentTaskState();

};

