#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <stack>
#include <queue>
#include "resource.h"
#include "texture_manager.hpp"
#include "resourceManager.hpp"
#include "Button.hpp"
#include "task.hpp"

class UniversalClass
{

public:

	sf::RenderWindow window;
	LPCWSTR lpszClass = L"__hidden__";
	
	TextureManager txtManager;
	ResourceManager<Button> butManager;
	sf::Sprite background;
	std::stack<int> stateStack;
	std::queue<Task> taskQueue;
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS wc;
	HWND hWnd, m_hwnd;
	MSG msg;

	UniversalClass();

	int mainLoop();

	void loadTextures();
	void loadAssets();

	void dummyWindowSetup();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	void mainMenuState();
	void editTaskState(Task&);

};

